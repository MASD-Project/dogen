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
#include <string>
#include <ostream>
#include <stdexcept>
#include "dogen.physical/io/entities/legacy_archetype_kind_io.hpp"

namespace dogen::physical::entities {

std::ostream& operator<<(std::ostream& s, const legacy_archetype_kind& v) {
    s << "{ " << "\"__type__\": " << "\"legacy_archetype_kind\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case legacy_archetype_kind::invalid:
        attr = "\"invalid\"";
        break;
    case legacy_archetype_kind::visual_studio_solution:
        attr = "\"visual_studio_solution\"";
        break;
    case legacy_archetype_kind::visual_studio_project:
        attr = "\"visual_studio_project\"";
        break;
    case legacy_archetype_kind::odb_options:
        attr = "\"odb_options\"";
        break;
    case legacy_archetype_kind::msbuild_targets:
        attr = "\"msbuild_targets\"";
        break;
    case legacy_archetype_kind::tests_cmakelists:
        attr = "\"tests_cmakelists\"";
        break;
    case legacy_archetype_kind::source_cmakelists:
        attr = "\"source_cmakelists\"";
        break;
    case legacy_archetype_kind::include_cmakelists:
        attr = "\"include_cmakelists\"";
        break;
    case legacy_archetype_kind::cpp_header:
        attr = "\"cpp_header\"";
        break;
    case legacy_archetype_kind::cpp_implementation:
        attr = "\"cpp_implementation\"";
        break;
    case legacy_archetype_kind::tests_cpp_main:
        attr = "\"tests_cpp_main\"";
        break;
    case legacy_archetype_kind::tests_cpp_implementation:
        attr = "\"tests_cpp_implementation\"";
        break;
    case legacy_archetype_kind::templates:
        attr = "\"templates\"";
        break;
    case legacy_archetype_kind::csharp_implementation:
        attr = "\"csharp_implementation\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for legacy_archetype_kind");
    }
    s << attr << " }";
    return s;
}

}
