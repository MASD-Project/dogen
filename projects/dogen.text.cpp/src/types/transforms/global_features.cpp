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
#include "dogen.variability/types/helpers/value_factory.hpp"
#include "dogen.text.cpp/types/transforms/global_features.hpp"

namespace dogen::text::cpp::transforms {

namespace {

dogen::variability::entities::feature
make_masd_cpp_aspect_requires_manual_default_constructor() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("requires_manual_default_constructor");
    r.name().qualified("masd.cpp.aspect.requires_manual_default_constructor");
    r.description(R"(If true, the modeling element requires a manual defaul constructor.

)");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "false" }));
    return r;
}

dogen::variability::entities::feature
make_masd_cpp_aspect_requires_manual_move_constructor() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("requires_manual_move_constructor");
    r.name().qualified("masd.cpp.aspect.requires_manual_move_constructor");
    r.description(R"(If true, the modeling element requires a manual move constructor.

)");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "false" }));
    return r;
}

dogen::variability::entities::feature
make_masd_cpp_aspect_requires_stream_manipulators() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("requires_stream_manipulators");
    r.name().qualified("masd.cpp.aspect.requires_stream_manipulators");
    r.description(R"(If true, the modeling element requires stream manipulators.

)");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "false" }));
    return r;
}

dogen::variability::entities::feature
make_masd_cpp_standard() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("standard");
    r.name().qualified("masd.cpp.standard");
    r.description(R"(Which version of C++ to use.

)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "c++-14" }));
    return r;
}

dogen::variability::entities::feature
make_masd_cpp_helper_family() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("family");
    r.name().qualified("masd.cpp.helper.family");
    r.description(R"(Which family of helpers to use for this modeling element.

)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "Default" }));
    return r;
}

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


std::list<dogen::variability::entities::feature>
global_features::make_features() {
    using namespace dogen::variability::entities;
    std::list<dogen::variability::entities::feature> r;
    r.push_back(make_masd_cpp_aspect_requires_manual_default_constructor());
    r.push_back(make_masd_cpp_aspect_requires_manual_move_constructor());
    r.push_back(make_masd_cpp_aspect_requires_stream_manipulators());
    r.push_back(make_masd_cpp_standard());
    r.push_back(make_masd_cpp_helper_family());
    r.push_back(make_masd_cpp_streaming_string_conversion_method());
    r.push_back(make_masd_cpp_streaming_requires_quoting());
    r.push_back(make_masd_cpp_streaming_remove_unprintable_characters());
    return r;
}

}
