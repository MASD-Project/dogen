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
#include "dogen.m2t.cpp/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/types/traits.hpp"

namespace dogen::m2t::cpp::transforms::types {

std::string traits::facet() {
    static std::string r(cpp::traits::backend_qn() + ".types");
    return r;
}

std::string traits::facet_sn() {
    static std::string r("types");
    return r;
}

std::string traits::canonical_archetype() {
    static std::string r(traits::facet() + ".canonical_archetype");
    return r;
}

std::string traits::class_header_archetype() {
    static std::string r(traits::facet() + ".class_header");
    return r;
}

std::string traits::class_header_archetype_sn() {
    static std::string r("class_header");
    return r;
}

std::string traits::class_forward_declarations_archetype() {
    static std::string r(traits::facet() + ".class_forward_declarations");
    return r;
}

std::string traits::class_forward_declarations_archetype_sn() {
    static std::string r("class_forward_declarations");
    return r;
}

std::string traits::visitor_forward_declarations_archetype() {
    static std::string r(traits::facet() + ".visitor_forward_declarations");
    return r;
}

std::string traits::visitor_forward_declarations_archetype_sn() {
    static std::string r("visitor_forward_declarations");
    return r;
}

std::string traits::primitive_forward_declarations_archetype() {
    static std::string r(traits::facet() + ".primitive_forward_declarations");
    return r;
}

std::string traits::primitive_forward_declarations_archetype_sn() {
    static std::string r("primitive_forward_declarations");
    return r;
}

std::string traits::class_implementation_archetype() {
    static std::string r(traits::facet() + ".class_implementation");
    return r;
}

std::string traits::class_implementation_archetype_sn() {
    static std::string r("class_implementation");
    return r;
}

std::string traits::enum_header_archetype() {
    static std::string r(traits::facet() + ".enum_header");
    return r;
}

std::string traits::enum_header_archetype_sn() {
    static std::string r("enum_header");
    return r;
}

std::string traits::exception_header_archetype() {
    static std::string r(traits::facet() + ".exception_header");
    return r;
}

std::string traits::exception_header_archetype_sn() {
    static std::string r("exception_header");
    return r;
}

std::string traits::namespace_header_archetype() {
    static std::string r(traits::facet() + ".namespace_header");
    return r;
}

std::string traits::namespace_header_archetype_sn() {
    static std::string r("namespace_header");
    return r;
}

std::string traits::visitor_header_archetype() {
    static std::string r(traits::facet() + ".visitor_header");
    return r;
}

std::string traits::visitor_header_archetype_sn() {
    static std::string r("visitor_header");
    return r;
}

std::string traits::builtin_header_archetype() {
    static std::string r(traits::facet() + ".builtin_header");
    return r;
}

std::string traits::builtin_header_archetype_sn() {
    static std::string r("builtin_header");
    return r;
}

std::string traits::primitive_header_archetype() {
    static std::string r(traits::facet() + ".primitive_header");
    return r;
}

std::string traits::primitive_header_archetype_sn() {
    static std::string r("primitive_header");
    return r;
}

std::string traits::primitive_implementation_archetype() {
    static std::string r(traits::facet() + ".primitive_implementation");
    return r;
}

std::string traits::primitive_implementation_archetype_sn() {
    static std::string r("primitive_implementation");
    return r;
}

std::string traits::feature_template_bundle_header_archetype() {
    static std::string r(traits::facet() + ".feature_template_bundle_header");
    return r;
}

std::string traits::feature_template_bundle_header_archetype_sn() {
    static std::string r("feature_template_bundle_header");
    return r;
}

std::string traits::feature_template_bundle_implementation_archetype() {
    static std::string r(traits::facet() + ".feature_template_bundle_implementation");
    return r;
}

std::string traits::feature_template_bundle_implementation_archetype_sn() {
    static std::string r("feature_template_bundle_implementation");
    return r;
}

std::string traits::feature_bundle_header_archetype() {
    static std::string r(traits::facet() + ".feature_bundle_header");
    return r;
}

std::string traits::feature_bundle_header_archetype_sn() {
    static std::string r("feature_bundle_header");
    return r;
}

std::string traits::feature_bundle_implementation_archetype() {
    static std::string r(traits::facet() + ".feature_bundle_implementation");
    return r;
}

std::string traits::feature_bundle_implementation_archetype_sn() {
    static std::string r("feature_bundle_implementation");
    return r;
}

std::string traits::variability_initializer_header_archetype() {
    static std::string r(traits::facet() + ".variability_initializer_header");
    return r;
}

std::string traits::variability_initializer_header_archetype_sn() {
    static std::string r("variability_initializer_header");
    return r;
}

std::string traits::variability_initializer_implementation_archetype() {
    static std::string r(traits::facet() +
        ".variability_initializer_implementation");
    return r;
}

std::string traits::variability_initializer_implementation_archetype_sn() {
    static std::string r("variability_initializer_implementation");
    return r;
}

std::string traits::main_archetype() {
    static std::string r(traits::facet() + ".main");
    return r;
}

std::string traits::main_archetype_sn() {
    static std::string r("main");
    return r;
}

}
