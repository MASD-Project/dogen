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
#include "masd.dogen.variability/types/helpers/value_factory.hpp"
#include "masd.dogen.generation.csharp/types/formatters/global_features.hpp"

namespace masd::dogen::generation::csharp::formatters {

namespace {

masd::dogen::variability::meta_model::feature_template
make_masd_generation_csharp_directory() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("directory");
    r.name().qualified("masd.generation.csharp.directory");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.kind(template_kind::instance);
    masd::dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "cs" }));

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

masd::dogen::variability::meta_model::feature_template
make_masd_generation_csharp_aspect_requires_static_reference_equals() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("requires_static_reference_equals");
    r.name().qualified("masd.generation.csharp.aspect.requires_static_reference_equals");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    r.kind(template_kind::instance);
    masd::dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "true" }));

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

masd::dogen::variability::meta_model::feature_template
make_masd_generation_csharp_visual_studio_project_solution_guid() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("project_solution_guid");
    r.name().qualified("masd.generation.csharp.visual_studio.project_solution_guid");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.kind(template_kind::instance);
    masd::dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "00000000-0000-0000-0000-000000000000" }));

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

masd::dogen::variability::meta_model::feature_template
make_masd_generation_csharp_visual_studio_project_guid() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("project_guid");
    r.name().qualified("masd.generation.csharp.visual_studio.project_guid");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.kind(template_kind::instance);
    masd::dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "00000000-0000-0000-0000-000000000000" }));

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

masd::dogen::variability::meta_model::feature_template
make_masd_generation_csharp_visual_studio_solution_postfix() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.csharp.visual_studio.solution.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.kind(template_kind::instance);
    masd::dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

masd::dogen::variability::meta_model::feature_template
make_masd_generation_csharp_visual_studio_project_postfix() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.csharp.visual_studio.project.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.kind(template_kind::instance);
    masd::dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

masd::dogen::variability::meta_model::feature_template
make_masd_generation_csharp_helper_family() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("family");
    r.name().qualified("masd.generation.csharp.helper.family");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    r.kind(template_kind::instance);
    masd::dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "Default" }));

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

masd::dogen::variability::meta_model::feature_template
make_masd_generation_csharp_assistant_requires_assistance() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("requires_assistance");
    r.name().qualified("masd.generation.csharp.assistant.requires_assistance");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    r.kind(template_kind::instance);
    masd::dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "false" }));

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

masd::dogen::variability::meta_model::feature_template
make_masd_generation_csharp_assistant_method_postfix() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("method_postfix");
    r.name().qualified("masd.generation.csharp.assistant.method_postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    r.kind(template_kind::instance);

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

}

std::list<masd::dogen::variability::meta_model::feature_template>
global_features::make_templates() {
    using namespace masd::dogen::variability::meta_model;
    std::list<feature_template> r;
    r.push_back(make_masd_generation_csharp_directory());
    r.push_back(make_masd_generation_csharp_aspect_requires_static_reference_equals());
    r.push_back(make_masd_generation_csharp_visual_studio_project_solution_guid());
    r.push_back(make_masd_generation_csharp_visual_studio_project_guid());
    r.push_back(make_masd_generation_csharp_visual_studio_solution_postfix());
    r.push_back(make_masd_generation_csharp_visual_studio_project_postfix());
    r.push_back(make_masd_generation_csharp_helper_family());
    r.push_back(make_masd_generation_csharp_assistant_requires_assistance());
    r.push_back(make_masd_generation_csharp_assistant_method_postfix());
    return r;
}

}
