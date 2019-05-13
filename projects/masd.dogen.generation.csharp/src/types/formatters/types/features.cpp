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
#include "masd.dogen.generation.csharp/types/formatters/types/features.hpp"

namespace masd::dogen::generation::csharp::formatters::types {

namespace {

masd::dogen::variability::meta_model::feature_template
make_masd_generation_csharp_types_directory() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("directory");
    r.name().qualified("masd.generation.csharp.types.directory");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.kind(template_kind::instance);
    masd::dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "Types" }));

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

masd::dogen::variability::meta_model::feature_template
make_masd_generation_csharp_types_postfix() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.csharp.types.postfix");
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
make_masd_generation_csharp_types_class_postfix() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.csharp.types.class.postfix");
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
make_masd_generation_csharp_types_enum_postfix() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.csharp.types.enum.postfix");
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
make_masd_generation_csharp_types_primitive_postfix() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.csharp.types.primitive.postfix");
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
make_masd_generation_csharp_types_builtin_postfix() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.csharp.types.builtin.postfix");
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
make_masd_generation_csharp_types_exception_postfix() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.csharp.types.exception.postfix");
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

}

std::list<masd::dogen::variability::meta_model::feature_template>
features::make_templates() {
    using namespace masd::dogen::variability::meta_model;
    std::list<feature_template> r;
    r.push_back(make_masd_generation_csharp_types_directory());
    r.push_back(make_masd_generation_csharp_types_postfix());
    r.push_back(make_masd_generation_csharp_types_class_postfix());
    r.push_back(make_masd_generation_csharp_types_enum_postfix());
    r.push_back(make_masd_generation_csharp_types_primitive_postfix());
    r.push_back(make_masd_generation_csharp_types_builtin_postfix());
    r.push_back(make_masd_generation_csharp_types_exception_postfix());
    return r;
}

}
