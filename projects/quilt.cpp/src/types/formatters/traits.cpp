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
#include "dogen/quilt.cpp/types/formatters/traits.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

std::string traits::model_name() {
    static std::string r("cpp");
    return r;
}

std::string traits::header_formatter_group_name() {
    static std::string r("cpp.header_files");
    return r;
}

std::string traits::implementation_formatter_group_name() {
    static std::string r("cpp.implementation_files");
    return r;
}

std::string traits::includers_formatter_name(const std::string& facet_name) {
    return facet_name + ".includers_formatter";
}

std::string traits::include_cmakelists_formatter_name() {
    static std::string r("cpp.include_cmakelists");
    return r;
}

std::string traits::source_cmakelists_formatter_name() {
    static std::string r("cpp.source_cmakelists");
    return r;
}

std::string
traits::class_header_formatter_name(const std::string& facet_name) {
    return facet_name + ".class_header_formatter";
}

} } } }
