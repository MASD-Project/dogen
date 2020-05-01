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
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.variability/types/entities/configuration.hpp"
#include "dogen.logical/types/transforms/context.hpp"
#include "dogen.logical/io/entities/input_model_set_io.hpp"
#include "dogen.logical/types/entities/elements_traversal.hpp"
#include "dogen.logical/types/transforms/transformation_error.hpp"
#include "dogen.logical/types/transforms/dynamic_stereotypes_transform.hpp"

namespace {

const std::string transform_id(
    "logical.transforms.dynamic_stereotypes_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string unexpected_stereotypes("Unexpected dynamic stereotypes:");

}

namespace dogen::logical::transforms {

namespace {

/**
 * @brief Updates all dynamic stereotypes for model elements which
 * require them.
 */
class updater {
private:
    /**
     * @brief Obtains all stereotype names that were not realised as
     * profile bindings.
     */
    template<typename Configurable>
    std::list<std::string> obtain_non_realised_bindings(Configurable &c) {
        const auto& n(c.configuration()->name());
        const auto& qn(n.qualified());
        BOOST_LOG_SEV(lg, trace) << "Extracting: " << n.simple()
                                 << " (" << qn << ") ";

        /*
         * A non-realised binding means we could not find a profile
         * that matched the name. In that case, we consider it to be a
         * dynamic stereotype, to be used elsewhere.
         */
        std::list<std::string> r;
        const auto& pbs(c.configuration()->profile_bindings());
        for (const auto& pb : pbs) {
            if (!pb.realized())
                r.push_back(pb.name());
        }
        return r;
    }

    /**
     * @brief Update the dynamic stereotypes for the supplied element.
     */
    void update(logical::entities::element& e) {
        e.dynamic_stereotypes(obtain_non_realised_bindings(e));
    }

    /**
     * @brief Ensures there are no dynamic stereotypes for this
     * modeling element.
     */
    void ensure_none(logical::entities::element& e) {
        const auto ds(obtain_non_realised_bindings(e));
        if (ds.empty())
            return;

        const auto id(e.name().qualified().dot());
        BOOST_LOG_SEV(lg, error) << unexpected_stereotypes << id
                                 << " Values: " << ds;
        BOOST_THROW_EXCEPTION(
            transformation_error(unexpected_stereotypes + id));
    }

public:
    /*
     * Elements that may have dynamic stereotypes.
     */
    void operator()(logical::entities::element& e) { update(e); }
    void operator()(logical::entities::structural::object_template &v) {
        update(v);
        for (auto& attr : v.local_attributes())
            attr.dynamic_stereotypes(obtain_non_realised_bindings(attr));
    }
    void operator()(logical::entities::structural::enumeration& v) {
        update(v);
        for (auto& enm : v.enumerators())
            enm.dynamic_stereotypes(obtain_non_realised_bindings(enm));
    }
    void operator()(logical::entities::structural::object& v) {
        update(v);
        for (auto& attr : v.local_attributes())
            attr.dynamic_stereotypes(obtain_non_realised_bindings(attr));
    }

    /*
     * Elements that are not expected to have dynamic stereotypes.
     */
    void operator()(entities::structural::module& v) { ensure_none(v); }
    void operator()(entities::structural::builtin& v) { ensure_none(v); }
    void operator()(entities::structural::primitive& v) { ensure_none(v); }
    void operator()(entities::structural::exception& v) { ensure_none(v); }
    void operator()(entities::structural::visitor& v) { ensure_none(v); }
    void operator()(entities::structural::assistant& v) { ensure_none(v); }
    void operator()(entities::structural::entry_point& v) { ensure_none(v); }
    void operator()(entities::decoration::modeline& v) { ensure_none(v); }
    void operator()(entities::decoration::licence& v) { ensure_none(v); }
    void operator()(entities::decoration::modeline_group& v) { ensure_none(v); }
    void operator()(entities::decoration::generation_marker& v) {
        ensure_none(v);
    }
    void operator()(entities::variability::profile& v) { ensure_none(v); }
    void operator()(entities::variability::profile_template& v) {
        ensure_none(v);
    }
    void operator()(entities::variability::feature_template_bundle& v) {
        ensure_none(v);
    }
    void operator()(entities::variability::feature_bundle& v) {
        ensure_none(v);
    }
    void operator()(entities::variability::initializer& v) { ensure_none(v); }
    void operator()(entities::templating::logic_less_template& v) {
        ensure_none(v);
    }
    void operator()(entities::serialization::type_registrar& v) {
        ensure_none(v);
    }
    void operator()(entities::visual_studio::solution& v) { ensure_none(v); }
    void operator()(entities::visual_studio::project& v) { ensure_none(v); }
    void operator()(entities::visual_studio::msbuild_targets& v) {
        ensure_none(v);
    }
    void operator()(entities::orm::common_odb_options& v) { ensure_none(v); }
    void operator()(entities::build::cmakelists& v) { ensure_none(v); }
    void operator()(entities::physical::backend& v) { ensure_none(v); }
    void operator()(entities::physical::facet& v) { ensure_none(v); }
    void operator()(entities::physical::archetype& v) { ensure_none(v); }
    void operator()(entities::physical::part& v) { ensure_none(v); }
};

}

void dynamic_stereotypes_transform::
apply(const transforms::context& ctx, entities::input_model_set& ms) {
    tracing::scoped_transform_tracer stp(lg, "dynamic stereotypes transform",
        transform_id, *ctx.tracer(), ms);

    updater u;
    using logical::entities::elements_traversal;
    elements_traversal(ms.target(), u);
    for (auto& m : ms.references())
        elements_traversal(m, u);

    stp.end_transform(ms);
}

}
