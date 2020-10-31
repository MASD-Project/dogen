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
#include "dogen.logical/types/features/streaming.hpp"
#include "dogen.variability/types/helpers/value_factory.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"

namespace dogen::logical::features {

namespace {

dogen::variability::entities::feature
make_masd_cpp_streaming_string_conversion_method() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("string_conversion_method");
    r.name().qualified("masd.cpp.streaming.string_conversion_method");
    r.description(R"(Which conversion method to use to convert strings.

)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));
    return r;
}

dogen::variability::entities::feature
make_masd_cpp_streaming_requires_quoting() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("requires_quoting");
    r.name().qualified("masd.cpp.streaming.requires_quoting");
    r.description(R"(If true, streaming this type must be preceeded by quoting.

)");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "false" }));
    return r;
}

dogen::variability::entities::feature
make_masd_cpp_streaming_remove_unprintable_characters() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("remove_unprintable_characters");
    r.name().qualified("masd.cpp.streaming.remove_unprintable_characters");
    r.description(R"(If true, streaming this type requires removing unprintable characters.

)");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "false" }));
    return r;
}

}

streaming::feature_group
streaming::make_feature_group(const dogen::variability::entities::feature_model& fm) {
    feature_group r;
    const dogen::variability::helpers::feature_selector s(fm);

    r.string_conversion_method = s.get_by_name("masd.cpp.streaming.string_conversion_method");
    r.requires_quoting = s.get_by_name("masd.cpp.streaming.requires_quoting");
    r.remove_unprintable_characters = s.get_by_name("masd.cpp.streaming.remove_unprintable_characters");

    return r;
}

streaming::static_configuration streaming::make_static_configuration(
    const feature_group& fg,
    const dogen::variability::entities::configuration& cfg) {

    static_configuration r;
    const dogen::variability::helpers::configuration_selector s(cfg);
    r.string_conversion_method = s.get_text_content_or_default(fg.string_conversion_method);
    r.requires_quoting = s.get_boolean_content_or_default(fg.requires_quoting);
    r.remove_unprintable_characters = s.get_boolean_content_or_default(fg.remove_unprintable_characters);
    return r;
}

std::list<dogen::variability::entities::feature>
streaming::make_features() {
    using namespace dogen::variability::entities;
    std::list<dogen::variability::entities::feature> r;
    r.push_back(make_masd_cpp_streaming_string_conversion_method());
    r.push_back(make_masd_cpp_streaming_requires_quoting());
    r.push_back(make_masd_cpp_streaming_remove_unprintable_characters());
    return r;
}

}
