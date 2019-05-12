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
#include "masd.dogen.coding/types/features/primitive.hpp"
#include "masd.dogen.variability/types/helpers/value_factory.hpp"

namespace masd::dogen::coding::features {

namespace {

masd::dogen::variability::meta_model::feature_template
make_masd_primitive_underlying_element() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("underlying_element");
    r.name().qualified("masd.primitive.underlying_element");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    r.kind(template_kind::instance);

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

masd::dogen::variability::meta_model::feature_template
make_masd_primitive_is_nullable() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("is_nullable");
    r.name().qualified("masd.primitive.is_nullable");
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
make_masd_primitive_use_type_aliasing() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("use_type_aliasing");
    r.name().qualified("masd.primitive.use_type_aliasing");
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

}

std::list<masd::dogen::variability::meta_model::feature_template>
primitive::make_templates() {
    using namespace masd::dogen::variability::meta_model;
    std::list<feature_template> r;
    r.push_back(make_masd_primitive_underlying_element());
    r.push_back(make_masd_primitive_is_nullable());
    r.push_back(make_masd_primitive_use_type_aliasing());
    return r;
}

}
