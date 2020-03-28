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
#include "dogen.logical/types/entities/orm/common_odb_options.hpp"
#include "dogen.logical/types/entities/visual_studio/msbuild_targets.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.logical/types/entities/model.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/entities/elements_traversal.hpp"
#include "dogen.logical/types/transforms/transformation_error.hpp"
#include "dogen.logical/types/transforms/meta_naming_transform.hpp"

namespace {

const std::string transform_id("logical.transforms.meta_naming_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace dogen::logical::transforms {

using mnf = helpers::meta_name_factory;

class updater {
public:
    void operator()(entities::element&) {
        /*
         * Element ignored on purpose; we cannot update non-assets
         * meta-model elements.
         */
    }

    void operator()(entities::structural::module& v) {
        static const auto n(mnf::make_module_name());
        v.meta_name(n);
    }

    void operator()(entities::structural::object_template& v) {
        static const auto n(mnf::make_object_template_name());
        v.meta_name(n);
    }

    void operator()(entities::structural::builtin& v) {
        static const auto n(mnf::make_builtin_name());
        v.meta_name(n);
    }

    void operator()(entities::structural::enumeration& v) {
        static const auto n(mnf::make_enumeration_name());
        v.meta_name(n);
    }

    void operator()(entities::structural::primitive& v) {
        static const auto n(mnf::make_primitive_name());
        v.meta_name(n);
    }

    void operator()(entities::structural::object& v) {
        static const auto n(mnf::make_object_name());
        v.meta_name(n);
    }

    void operator()(entities::structural::exception& v) {
        static const auto n(mnf::make_exception_name());
        v.meta_name(n);
    }

    void operator()(entities::structural::visitor& v) {
        static const auto n(mnf::make_visitor_name());
        v.meta_name(n);
    }

    void operator()(entities::structural::entry_point& v) {
        static const auto n(mnf::make_entry_point_name());
        v.meta_name(n);
    }

    void operator()(entities::structural::assistant& v) {
        static const auto n(mnf::make_assistant_name());
        v.meta_name(n);
    }

    void operator()(entities::decoration::licence& v) {
        static const auto n(mnf::make_licence_name());
        v.meta_name(n);
    }

    void operator()(entities::decoration::modeline& v) {
        static const auto n(mnf::make_modeline_name());
        v.meta_name(n);
    }

    void operator()(entities::decoration::modeline_group& v) {
        static const auto n(mnf::make_modeline_group_name());
        v.meta_name(n);
    }

    void operator()(entities::decoration::generation_marker& v) {
        static const auto n(mnf::make_generation_marker_name());
        v.meta_name(n);
    }

    void operator()(entities::variability::profile& v) {
        static const auto n(mnf::make_variability_profile_name());
        v.meta_name(n);
    }

    void operator()(entities::variability::profile_template& v) {
        static const auto n(mnf::make_variability_profile_template_name());
        v.meta_name(n);
    }

    void operator()(entities::variability::feature_template_bundle& v) {
        static const auto
            n(mnf::make_variability_feature_template_bundle_name());
        v.meta_name(n);
    }

    void operator()(entities::variability::feature_bundle& v) {
        static const auto n(mnf::make_variability_feature_bundle_name());
        v.meta_name(n);
    }

    void operator()(entities::variability::initializer& v) {
        static const auto n(mnf::make_variability_initializer_name());
        v.meta_name(n);
    }

    void operator()(logical::entities::templating::logic_less_template& v) {
        static const auto n(mnf::make_templating_logic_less_templates_name());
        v.meta_name(n);
    }

    void operator()(logical::entities::serialization::type_registrar& v) {
        static const auto n(mnf::make_serialization_type_registrar_name());
        v.meta_name(n);
    }

    void operator()(logical::entities::visual_studio::solution& v) {
        static const auto n(mnf::make_visual_studio_solution_name());
        v.meta_name(n);
    }

    void operator()(logical::entities::visual_studio::project& v) {
        static const auto n(mnf::make_visual_studio_project_name());
        v.meta_name(n);
    }

    void operator()(logical::entities::visual_studio::msbuild_targets& v) {
        static const auto n(mnf::make_visual_studio_msbuild_targets_name());
        v.meta_name(n);
    }

    void operator()(logical::entities::orm::common_odb_options& v) {
        static const auto n(mnf::make_orm_common_odb_options_name());
        v.meta_name(n);
    }

    void operator()(logical::entities::build::cmakelists& v) {
        static const auto n(mnf::make_build_cmakelists_name());
        v.meta_name(n);
    }
};

void meta_naming_transform::
apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "meta-naming transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    m.meta_name(mnf::make_model_name());

    updater u;
    entities::elements_traversal(m, u);

    stp.end_transform(m);
}

}
