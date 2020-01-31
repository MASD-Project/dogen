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
#include "dogen.assets/types/helpers/name_builder.hpp"
#include "dogen.assets/types/helpers/meta_name_factory.hpp"

namespace dogen::assets::helpers {

meta_model::location meta_name_factory::make_location() {
    meta_model::location r;
    r.external_modules().push_back("dogen");
    r.model_modules().push_back("assets");
    r.internal_modules().push_back("meta_model");
    return r;
}

meta_model::name meta_name_factory::make_name(const std::string& sn) {
    static const auto l(make_location());
    name_builder b;
    b.location(l);
    b.simple_name(sn);
    return b.build();
}

meta_model::name meta_name_factory::make_model_name() {
    static const auto r(make_name("model"));
    return r;
}

meta_model::name meta_name_factory::make_module_name() {
    static const auto r(make_name("module"));
    return r;
}

meta_model::name meta_name_factory::make_object_template_name() {
    static const auto r(make_name("object_template"));
    return r;
}

meta_model::name meta_name_factory::make_builtin_name() {
    static const auto r(make_name("builtin"));
    return r;
}

meta_model::name meta_name_factory::make_enumeration_name() {
    static const auto r(make_name("enumeration"));
    return r;
}

meta_model::name meta_name_factory::make_primitive_name() {
    static const auto r(make_name("primitive"));
    return r;
}

meta_model::name meta_name_factory::make_object_name() {
    static const auto r(make_name("object"));
    return r;
}

meta_model::name meta_name_factory::make_exception_name() {
    static const auto r(make_name("exception"));
    return r;
}

meta_model::name meta_name_factory::make_visitor_name() {
    static const auto r(make_name("visitor"));
    return r;
}

meta_model::name meta_name_factory::make_licence_name() {
    static const auto r(make_name("licence"));
    return r;
}

meta_model::name meta_name_factory::make_modeline_name() {
    static const auto r(make_name("modeline"));
    return r;
}

meta_model::name meta_name_factory::make_modeline_group_name() {
    static const auto r(make_name("modeline_group"));
    return r;
}

meta_model::name meta_name_factory::make_generation_marker_name() {
    static const auto r(make_name("generation_marker"));
    return r;
}

meta_model::name meta_name_factory::make_variability_profile_template_name() {
    static const auto r(make_name("variability_profile_template"));
    return r;
}

meta_model::name meta_name_factory::
make_variability_feature_bundle_name() {
    static const auto r(make_name("variability_feature_bundle"));
    return r;
}

meta_model::name meta_name_factory::
make_variability_feature_template_initializer_name() {
    static const auto r(
        make_name("variability_feature_template_initializer"));
    return r;
}

meta_model::name meta_name_factory::
make_templating_logic_less_templates_name() {
    static const auto r(
        make_name("templating_logic_less_templates"));
    return r;
}

meta_model::name meta_name_factory::make_serialization_type_registrar_name() {
    static const auto r(
        make_name("serialization_type_registrar"));
    return r;
}

meta_model::name meta_name_factory::make_build_visual_studio_compent_name() {
    static const auto r(
        make_name("build_visual_studio_component"));
    return r;
}

}
