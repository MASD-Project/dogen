/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/cpp/types/traits.hpp"

namespace dogen {
namespace cpp {

std::string traits::enabled() {
    static std::string r("enabled");
    return r;
}

std::string traits::supported() {
    static std::string r("supported");
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

std::string traits::integrated_facet() {
    static std::string r("integrated_facet");
    return r;
}

std::string traits::extension() {
    static std::string r("extension");
    return r;
}

std::string traits::inclusion_path() {
    static std::string r("inclusion_path");
    return r;
}

std::string traits::inclusion_delimiter_type() {
    static std::string r("inclusion_delimiter_type");
    return r;
}

std::string traits::include_directory_name() {
    static std::string r("cpp.include_directory_name");
    return r;
}

std::string traits::source_directory_name() {
    static std::string r("cpp.source_directory_name");
    return r;
}

} }
