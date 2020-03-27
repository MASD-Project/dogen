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
#include "dogen.m2t.cpp/types/transforms/build/traits.hpp"

namespace dogen::m2t::cpp::transforms::build {

std::string traits::facet_qn() {
    static std::string r("masd.cpp.build");
    return r;
}

std::string traits::facet_sn() {
    static std::string r("build");
    return r;
}

std::string traits::canonical_archetype() {
    static std::string r(traits::facet_qn() + ".canonical_archetype");
    return r;
}

std::string traits::include_cmakelists_archetype() {
    static std::string r("masd.cpp.build.include_cmakelists");
    return r;
}

std::string traits::include_cmakelists_archetype_sn() {
    static std::string r("include_cmakelists");
    return r;
}

std::string traits::source_cmakelists_archetype() {
    static std::string r("masd.cpp.build.source_cmakelists");
    return r;
}

std::string traits::source_cmakelists_archetype_sn() {
    static std::string r("source_cmakelists");
    return r;
}

}
