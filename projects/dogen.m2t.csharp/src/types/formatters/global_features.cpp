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
#include "dogen.m2t.csharp/types/formatters/global_features.hpp"

namespace dogen::m2t::csharp::formatters {

namespace {

dogen::variability::entities::feature
make_masd_generation_csharp_directory() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("directory");
    r.name().qualified("masd.generation.csharp.directory");
    r.description(R"(
)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "cs" }));
    return r;
}

dogen::variability::entities::feature
make_masd_generation_csharp_aspect_requires_static_reference_equals() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("requires_static_reference_equals");
    r.name().qualified("masd.generation.csharp.aspect.requires_static_reference_equals");
    r.description(R"(
)");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "true" }));
    return r;
}

dogen::variability::entities::feature
make_masd_generation_csharp_helper_family() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("family");
    r.name().qualified("masd.generation.csharp.helper.family");
    r.description(R"(
)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "Default" }));
    return r;
}

dogen::variability::entities::feature
make_masd_generation_csharp_assistant_requires_assistance() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("requires_assistance");
    r.name().qualified("masd.generation.csharp.assistant.requires_assistance");
    r.description(R"(
)");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "false" }));
    return r;
}

dogen::variability::entities::feature
make_masd_generation_csharp_assistant_method_postfix() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("method_postfix");
    r.name().qualified("masd.generation.csharp.assistant.method_postfix");
    r.description(R"(
)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    return r;
}

}


std::list<dogen::variability::entities::feature>
global_features::make_features() {
    using namespace dogen::variability::entities;
    std::list<dogen::variability::entities::feature> r;
    r.push_back(make_masd_generation_csharp_directory());
    r.push_back(make_masd_generation_csharp_aspect_requires_static_reference_equals());
    r.push_back(make_masd_generation_csharp_helper_family());
    r.push_back(make_masd_generation_csharp_assistant_requires_assistance());
    r.push_back(make_masd_generation_csharp_assistant_method_postfix());
    return r;
}

}
