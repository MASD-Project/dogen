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
#include "dogen.logical/types/features/primitive.hpp"
#include "dogen.variability/types/helpers/value_factory.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"

namespace dogen::logical::features {

namespace {

dogen::variability::entities::feature
make_masd_primitive_underlying_element() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("underlying_element");
    r.name().qualified("masd.primitive.underlying_element");
    r.description(R"(Name of the underlying element to use for the primitive.)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    return r;
}

dogen::variability::entities::feature
make_masd_primitive_is_nullable() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("is_nullable");
    r.name().qualified("masd.primitive.is_nullable");
    r.description(R"(If true, the primitive can be null.)");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "false" }));
    return r;
}

dogen::variability::entities::feature
make_masd_primitive_use_type_aliasing() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("use_type_aliasing");
    r.name().qualified("masd.primitive.use_type_aliasing");
    r.description(R"(If true, use type aliasing to implement the primitive if the technical space supports
it.)");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "false" }));
    return r;
}

}

primitive::feature_group
primitive::make_feature_group(const dogen::variability::entities::feature_model& fm) {
    feature_group r;
    const dogen::variability::helpers::feature_selector s(fm);

    r.underlying_element = s.get_by_name("masd.primitive.underlying_element");
    r.is_nullable = s.get_by_name("masd.primitive.is_nullable");
    r.use_type_aliasing = s.get_by_name("masd.primitive.use_type_aliasing");

    return r;
}

primitive::static_configuration primitive::make_static_configuration(
    const feature_group& fg,
    const dogen::variability::entities::configuration& cfg) {

    static_configuration r;
    const dogen::variability::helpers::configuration_selector s(cfg);
    if (s.has_configuration_point(fg.underlying_element))
        r.underlying_element = s.get_text_content(fg.underlying_element);
    r.is_nullable = s.get_boolean_content_or_default(fg.is_nullable);
    r.use_type_aliasing = s.get_boolean_content_or_default(fg.use_type_aliasing);
    return r;
}

std::list<dogen::variability::entities::feature>
primitive::make_features() {
    using namespace dogen::variability::entities;
    std::list<dogen::variability::entities::feature> r;
    r.push_back(make_masd_primitive_underlying_element());
    r.push_back(make_masd_primitive_is_nullable());
    r.push_back(make_masd_primitive_use_type_aliasing());
    return r;
}

}
