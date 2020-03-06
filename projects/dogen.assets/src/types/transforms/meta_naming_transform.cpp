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
#include "dogen.assets/types/meta_model/orm/common_odb_options.hpp"
#include "dogen.assets/types/meta_model/visual_studio/msbuild_targets.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.assets/types/meta_model/model.hpp"
#include "dogen.assets/io/meta_model/model_io.hpp"
#include "dogen.assets/types/helpers/meta_name_factory.hpp"
#include "dogen.assets/types/meta_model/elements_traversal.hpp"
#include "dogen.assets/types/transforms/transformation_error.hpp"
#include "dogen.assets/types/transforms/meta_naming_transform.hpp"

namespace {

const std::string transform_id("assets.transforms.meta_naming_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace dogen::assets::transforms {

using mnf = helpers::meta_name_factory;

class updater {
public:
    void operator()(meta_model::element&) {
        /*
         * Element ignored on purpose; we cannot update non-assets
         * meta-model elements.
         */
    }

    void operator()(meta_model::structural::module& v) {
        static const auto n(mnf::make_module_name());
        v.meta_name(n);
    }

    void operator()(meta_model::structural::object_template& v) {
        static const auto n(mnf::make_object_template_name());
        v.meta_name(n);
    }

    void operator()(meta_model::structural::builtin& v) {
        static const auto n(mnf::make_builtin_name());
        v.meta_name(n);
    }

    void operator()(meta_model::structural::enumeration& v) {
        static const auto n(mnf::make_enumeration_name());
        v.meta_name(n);
    }

    void operator()(meta_model::structural::primitive& v) {
        static const auto n(mnf::make_primitive_name());
        v.meta_name(n);
    }

    void operator()(meta_model::structural::object& v) {
        static const auto n(mnf::make_object_name());
        v.meta_name(n);
    }

    void operator()(meta_model::structural::exception& v) {
        static const auto n(mnf::make_exception_name());
        v.meta_name(n);
    }

    void operator()(meta_model::structural::visitor& v) {
        static const auto n(mnf::make_visitor_name());
        v.meta_name(n);
    }

    void operator()(meta_model::structural::entry_point& v) {
        static const auto n(mnf::make_entry_point_name());
        v.meta_name(n);
    }

    void operator()(meta_model::structural::assistant& v) {
        static const auto n(mnf::make_assistant_name());
        v.meta_name(n);
    }

    void operator()(meta_model::decoration::licence& v) {
        static const auto n(mnf::make_licence_name());
        v.meta_name(n);
    }

    void operator()(meta_model::decoration::modeline& v) {
        static const auto n(mnf::make_modeline_name());
        v.meta_name(n);
    }

    void operator()(meta_model::decoration::modeline_group& v) {
        static const auto n(mnf::make_modeline_group_name());
        v.meta_name(n);
    }

    void operator()(meta_model::decoration::generation_marker& v) {
        static const auto n(mnf::make_generation_marker_name());
        v.meta_name(n);
    }

    void operator()(meta_model::variability::profile_template& v) {
        static const auto n(mnf::make_variability_profile_template_name());
        v.meta_name(n);
    }

    void operator()(meta_model::variability::feature_template_bundle& v) {
        static const auto
            n(mnf::make_variability_feature_template_bundle_name());
        v.meta_name(n);
    }

    void operator()(meta_model::variability::feature_bundle& v) {
        static const auto n(mnf::make_variability_feature_bundle_name());
        v.meta_name(n);
    }

    void operator()(meta_model::variability::initializer& v) {
        static const auto n(mnf::make_variability_initializer_name());
        v.meta_name(n);
    }

    void operator()(assets::meta_model::templating::logic_less_template& v) {
        static const auto n(mnf::make_templating_logic_less_templates_name());
        v.meta_name(n);
    }

    void operator()(assets::meta_model::serialization::type_registrar& v) {
        static const auto n(mnf::make_serialization_type_registrar_name());
        v.meta_name(n);
    }

    void operator()(assets::meta_model::visual_studio::solution& v) {
        static const auto n(mnf::make_visual_studio_solution_name());
        v.meta_name(n);
    }

    void operator()(assets::meta_model::visual_studio::project& v) {
        static const auto n(mnf::make_visual_studio_project_name());
        v.meta_name(n);
    }

    void operator()(assets::meta_model::visual_studio::msbuild_targets& v) {
        static const auto n(mnf::make_visual_studio_msbuild_targets_name());
        v.meta_name(n);
    }

    void operator()(assets::meta_model::orm::common_odb_options& v) {
        static const auto n(mnf::make_orm_common_odb_options_name());
        v.meta_name(n);
    }

    void operator()(assets::meta_model::build::cmakelists& v) {
        static const auto n(mnf::make_build_cmakelists_name());
        v.meta_name(n);
    }
};

void meta_naming_transform::
apply(const context& ctx, meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg, "meta-naming transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    m.meta_name(mnf::make_model_name());

    updater u;
    meta_model::elements_traversal(m, u);

    stp.end_transform(m);
}

}
