/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.assets/io/meta_model/model_io.hpp"
#include "dogen.assets/types/meta_model/structural/object.hpp"
#include "dogen.assets/io/meta_model/origin_types_io.hpp"
#include "dogen.assets/types/transforms/context.hpp"
#include "dogen.assets/types/transforms/transformation_error.hpp"
#include "dogen.assets/types/meta_model/serialization/type_registrar.hpp"
#include "dogen.assets/types/transforms/type_registrar_transform.hpp"

namespace {

const std::string transform_id("assets.transforms.type_registrar_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string multiple_targets("Found more than one target registrar: ");
const std::string missing_leaf("Could not locate leaf: ");

}

namespace dogen::assets::transforms {

void type_registrar_transform::apply(const context& ctx, meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg, "type registrar transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    /*
     * If there are no registrars at all then there is nothing to do.
     */
    if (m.serialization_elements().type_registrars().empty()) {
        BOOST_LOG_SEV(lg, debug) << "Model has no registrars.";
        return;
    }

    using meta_model::name;
    using meta_model::origin_types;
    std::list<std::pair<name, name>> referenced_registrars;
    using meta_model::serialization::type_registrar;
    boost::shared_ptr<type_registrar> target_registrar;
    for (auto& pair : m.serialization_elements().type_registrars()) {
        auto& rg(*pair.second);
        const auto id(rg.name().qualified().dot());
        BOOST_LOG_SEV(lg, debug) << "Processing registrar: " << id;

        /*
         * If we are in the presence of the registrar for the target
         * model, we want to populate all of its data fields.
         */
        const auto ot(rg.origin_type());
        if (ot == origin_types::target) {
            BOOST_LOG_SEV(lg, debug) << "Target model registrar.";

            /*
             * There can only be one target registrar.
             */
            if (target_registrar.get() != nullptr) {
                BOOST_LOG_SEV(lg, error) << multiple_targets << id;
                BOOST_THROW_EXCEPTION(
                    transformation_error(multiple_targets + id));
            }
            target_registrar = pair.second;

            /*
             * The registrar needs to know about all of the leaf types
             * in this model - it is these that it will register.
             */
            for (const auto& l : m.leaves())
                rg.leaves().push_back(l);

            /*
             * Now tell all objects in the target model about the
             * registrar. Note that in practice we only need to tell
             * objects that are directly or indirectly involved in
             * inheritance relationships, but its hard to do this
             * right, so instead we take the machine-gun approach and
             * tell everyone.
             */
            auto& objs(m.structural_elements().objects());
            for(auto& pair : objs) {
                auto& o(*pair.second);

                /*
                 * We can safely ignore types that do not belong to
                 * the target model.
                 */
                if (o.origin_type() != origin_types::target)
                    continue;

                o.type_registrar(rg.name());
            }

            /*
             * We need to ensure the leaves are stable sorted.
             */
            rg.leaves().sort(
                [](const name& a, const name& b) {
                    return a.qualified().dot() < b.qualified().dot();
                });
        } else if (ot == origin_types::non_proxy_reference) {
            BOOST_LOG_SEV(lg, debug) << "Non-proxy reference registrar.";

            /*
             * Figure out if this registrar belongs to a model that
             * the target has referenced directly. If so, keep track
             * of both the referenced model and registrar's name.
             */
            for (const auto& pair : m.references()) {
                const auto& ref(pair.first);
                const auto lhs(ref.location());
                const auto rhs(rg.name().location());

                if (lhs.external_modules() == rhs.external_modules() &&
                    lhs.model_modules() == rhs.model_modules()) {
                    const auto p(std::make_pair(ref, rg.name()));
                    referenced_registrars.push_back(p);
                }
            }
        } else {
            /*
             * No work to do for proxy models (Platform Definition Models)
             * as they do not have registration requirements for now.
             */
            BOOST_LOG_SEV(lg, debug) << "Ignoring registrar with other origin: "
                                     << ot;
        }
    }

    /*
     * If there is no target registrar then there is nothing to do.
     */
    if (!target_registrar) {
        BOOST_LOG_SEV(lg, debug) << "Model has no target registrar.";
        return;
    }

    /*
     * If there are no referenced registrars, then we're done.
     */
    if (referenced_registrars.empty()) {
        BOOST_LOG_SEV(lg, debug) << "No referenced registrars found.";
        return;
    }

    /*
     * Finally, update all of the model and registrar dependencies on
     * the target model.
     */
    auto& tr(*target_registrar);
    for (const auto& pair : referenced_registrars) {
        const auto& ref(pair.first);
        tr.model_dependencies().push_back(ref);

        const auto& ref_rg(pair.second);
        tr.registrar_dependencies().push_back(ref_rg);
    }

    stp.end_transform(m);
}

}
