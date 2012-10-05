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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. Seethe
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General PublicLicense
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include <sstream>
#include <ostream>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/generator/backends/cpp/formatters/cpp_header_guards.hpp"

namespace {

const std::string ifndef("#ifndef ");
const std::string define("#define ");
const std::string endif("#endif");

const std::string msvc_line_1("#if defined(_MSC_VER) && (_MSC_VER >= 1200)");
const std::string msvc_line_2("#pragma once");
const std::string msvc_line_3("#endif");

}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

header_guards::header_guards(std::ostream& stream)
    : stream_(stream) { }

void header_guards::format_start(std::string guard_name) {
    stream_ << ifndef << guard_name;
    stream_ << std::endl << define << guard_name;

    stream_ << std::endl << std::endl
            << msvc_line_1 << std::endl
            << msvc_line_2 << std::endl
            << msvc_line_3 << std::endl;
}

void header_guards::format_end() {
    stream_ << endif << std::endl;
}

} } } } }
