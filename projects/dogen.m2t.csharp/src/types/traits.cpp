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
#include "dogen.m2t.csharp/types/traits.hpp"

namespace dogen::m2t::csharp {

std::string traits::kernel() {
    static std::string r("masd");
    return r;
}

std::string traits::backend_qn() {
    static std::string r("masd.csharp");
    return r;
}

std::string traits::backend_sn() {
    static std::string r("csharp");
    return r;
}

std::string traits::enabled() {
    static std::string r("enabled");
    return r;
}

std::string traits::overwrite() {
    static std::string r("overwrite");
    return r;
}

std::string traits::directory() {
    static std::string r("directory");
    return r;
}

std::string traits::postfix() {
    static std::string r("postfix");
    return r;
}

std::string traits::empty_part() {
    static std::string r;
    return r;
}

std::string traits::backend_directory_name() {
    static std::string r("masd.csharp.directory");
    return r;
}

std::string traits::csharp::helper::family() {
    static std::string r("masd.csharp.helper.family");
    return r;
}

std::string traits::csharp::aspect::requires_static_reference_equals() {
    static std::string r("masd.csharp.aspect.requires_static_reference_equals");
    return r;
}

std::string traits::csharp::assistant::requires_assistance() {
    static std::string r("masd.csharp.assistant.requires_assistance");
    return r;
}

std::string traits::csharp::assistant::method_postfix() {
    static std::string r("masd.csharp.assistant.method_postfix");
    return r;
}

}
