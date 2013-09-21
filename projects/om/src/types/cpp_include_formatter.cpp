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
#include <ostream>
#include <boost/filesystem/path.hpp>
#include "dogen/om/types/cpp_include_formatter.hpp"

namespace {

const bool is_system(true);
const bool is_user(false);

const std::string include("#include ");
const std::string open_system("<");
const std::string close_system(">");
const std::string open_user("\"");
const std::string close_user("\"");

}

namespace dogen {
namespace om {

void cpp_include_formatter::
format(std::ostream& s, const cpp_includes& i) const {
    for (const auto& inc : i.system()) {
        s << include << open_system << inc.generic_string()
          << close_system << std::endl;
    }

    for (const auto& inc : i.user()) {
        s << include << open_user << inc.generic_string()
          << close_user << std::endl;
    }
}

} }
