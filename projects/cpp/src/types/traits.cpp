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

std::string traits::bool_true() {
    static std::string r("true");
    return r;
}

std::string traits::bool_false() {
    static std::string r("false");
    return r;
}

std::string traits::enabled() {
    static std::string r("cpp.enabled");
    return r;
}

std::string traits::split_project() {
    static std::string r("cpp.split_project");
    return r;
}

std::string traits::source_directory() {
    static std::string r("cpp.source_directory");
    return r;
}

std::string traits::include_directory() {
    static std::string r("cpp.include_directory");
    return r;
}

std::string traits::header_file_extension() {
    static std::string r("cpp.header_file_extension");
    return r;
}

std::string traits::implementation_file_extension() {
    static std::string r("cpp.implementation_file_extension");
    return r;
}

std::string traits::enable_facet_folders() {
    static std::string r("cpp.enable_facet_folders");
    return r;
}

std::string traits::enable_unique_file_names() {
    static std::string r("cpp.enable_unique_file_names");
    return r;
}

std::string traits::facet::enabled() {
    static std::string r("enabled");
    return r;
}

std::string traits::facet::supported() {
    static std::string r("supported");
    return r;
}

std::string traits::facet::directory() {
    static std::string r("directory");
    return r;
}

std::string traits::facet::postfix() {
    static std::string r("postfix");
    return r;
}

std::string traits::formatter::enabled() {
    static std::string r("enabled");
    return r;
}

std::string traits::formatter::postfix() {
    static std::string r("postfix");
    return r;
}

} }
