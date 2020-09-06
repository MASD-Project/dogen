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
#include "dogen.identification/io/entities/model_type_io.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/transforms/context.hpp"
#include "dogen.logical/types/transforms/transformation_error.hpp"
#include "dogen.logical/types/entities/serialization/type_registrar.hpp"
#include "dogen.logical/types/transforms/type_registrar_transform.hpp"

namespace {

const std::string transform_id("logical.transforms.type_registrar_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string multiple_targets("Found more than one target registrar: ");
const std::string missing_leaf("Could not locate leaf: ");

}

namespace dogen::logical::transforms {

void type_registrar_transform::apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "type registrar transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    /*
     * If there are no registrars at all then there is nothing to do.
     */
    if (m.serialization_elements().type_registrars().empty()) {
        BOOST_LOG_SEV(lg, debug) << "Model has no registrars.";
        return;
    }

    using identification::entities::logical_name;
    using identification::entities::model_type;
    std::list<logical_name> registrar_dependencies;
    using entities::serialization::type_registrar;
    boost::shared_ptr<type_registrar> target_registrar;
    for (auto& pair : m.serialization_elements().type_registrars()) {
        auto& rg(*pair.second);
        const auto id(rg.name().qualified().dot());
        BOOST_LOG_SEV(lg, debug) << "Processing registrar: " << id;

        /*
         * If we are in the presence of the registrar for the target
         * model, we want to populate all of its data fields.
         */
        const auto mt(rg.provenance().model_type());
        if (mt == model_type::target) {
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
                if (o.provenance().model_type() != model_type::target)
                    continue;

                o.type_registrar(rg.name());
            }

            /*
             * We need to ensure the leaves are stable sorted.
             */
            rg.leaves().sort(
                [](const logical_name& rhs, const logical_name& lhs) {
                    return rhs.id().value() < lhs.id().value();
                });
        } else if (mt == model_type::non_pdm_reference) {
            BOOST_LOG_SEV(lg, debug) << "Non-PDM reference registrar.";

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
                    registrar_dependencies.push_back(rg.name());
                }
            }
        } else {
            /*
             * No work to do for proxy models (Platform Definition Models)
             * as they do not have registration requirements for now.
             */
            BOOST_LOG_SEV(lg, debug) << "Ignoring registrar with other origin: "
                                     << mt;
        }
    }

    /*
     * If there is a target registrar, update all of the model and
     * registrar dependencies on the target model.
     */
    if (target_registrar)
        target_registrar->registrar_dependencies(registrar_dependencies);

    stp.end_transform(m);
}

}
