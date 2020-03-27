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
#include "dogen.m2t.cpp/types/transforms/serialization/traits.hpp"

namespace dogen::m2t::cpp::transforms::serialization {

std::string traits::facet_qn() {
    static std::string r(cpp::traits::backend_qn() + ".serialization");
    return r;
}

std::string traits::facet_sn() {
    static std::string r("serialization");
    return r;
}

std::string traits::canonical_archetype() {
    static std::string r(traits::facet_qn() + ".canonical_archetype");
    return r;
}

std::string traits::class_header_archetype_qn() {
    static std::string r(traits::facet_qn() + ".class_header");
    return r;
}

std::string traits::class_header_archetype_sn() {
    static std::string r("class_header");
    return r;
}

std::string traits::class_implementation_archetype_qn() {
    static std::string r(traits::facet_qn() + ".class_implementation");
    return r;
}

std::string traits::class_implementation_archetype_sn() {
    static std::string r("class_implementation");
    return r;
}

std::string traits::enum_header_archetype_qn() {
    static std::string r(traits::facet_qn() + ".enum_header");
    return r;
}

std::string traits::enum_header_archetype_sn() {
    static std::string r("enum_header");
    return r;
}

std::string traits::class_forward_declarations_archetype_qn() {
    static std::string r(traits::facet_qn() + ".class_forward_declarations");
    return r;
}

std::string traits::class_forward_declarations_archetype_sn() {
    static std::string r("class_forward_declarations");
    return r;
}

std::string traits::primitive_forward_declarations_archetype_qn() {
    static std::string r(traits::facet_qn() + ".primitive_forward_declarations");
    return r;
}

std::string traits::primitive_forward_declarations_archetype_sn() {
    static std::string r("primitive_forward_declarations");
    return r;
}

std::string traits::builtin_header_archetype_qn() {
    static std::string r(traits::facet_qn() + ".builtin_header");
    return r;
}

std::string traits::builtin_header_archetype_sn() {
    static std::string r("builtin_header");
    return r;
}

std::string traits::primitive_header_archetype_qn() {
    static std::string r(traits::facet_qn() + ".primitive_header");
    return r;
}

std::string traits::primitive_header_archetype_sn() {
    static std::string r("primitive_header");
    return r;
}

std::string traits::primitive_implementation_archetype_qn() {
    static std::string r(traits::facet_qn() + ".primitive_implementation");
    return r;
}

std::string traits::primitive_implementation_archetype_sn() {
    static std::string r("primitive_implementation");
    return r;
}

std::string traits::type_registrar_header_archetype_qn() {
    static std::string r(traits::facet_qn() + ".type_registrar_header");
    return r;
}

std::string traits::type_registrar_header_archetype_sn() {
    static std::string r("type_registrar_header");
    return r;
}

std::string traits::type_registrar_implementation_archetype_qn() {
    static std::string r(traits::facet_qn() + ".type_registrar_implementation");
    return r;
}

std::string traits::type_registrar_implementation_archetype_sn() {
    static std::string r("type_registrar_implementation");
    return r;
}

}
