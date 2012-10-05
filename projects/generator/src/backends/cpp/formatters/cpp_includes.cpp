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
 * You should have received a copy of the GNU General PublicLicense
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include <ostream>
#include "dogen/generator/backends/cpp/formatters/cpp_includes.hpp"

namespace {

const std::string include("#include ");
const std::string open_system("<");
const std::string close_system(">");
const std::string open_user("\"");
const std::string close_user("\"");

}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

cpp_includes::cpp_includes(std::ostream& stream) : stream_(stream) {}

void cpp_includes::format(std::list<std::string> value, bool is_system) {
    value.sort();
    for (auto i : value) {
        stream_ << include << (is_system ? open_system : open_user)
                << i
                << (is_system ? close_system : close_user)
                << std::endl;
    }
}

} } } } }
