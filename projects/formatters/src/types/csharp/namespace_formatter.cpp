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
#include <ostream>
#include <boost/algorithm/string/join.hpp>
#include "dogen/formatters/types/csharp/namespace_formatter.hpp"

namespace {

const std::string empty;
const std::string dot(".");

}

namespace dogen {
namespace formatters {
namespace csharp {

namespace_formatter::namespace_formatter(const bool add_new_line)
    : add_new_line_(add_new_line) {}

void namespace_formatter::
format_begin(std::ostream& s, const std::string& ns) const {
    s << "namespace " << ns  << std::endl
      << "{" << std::endl;
}

void namespace_formatter::
format_end(std::ostream& s, const std::string& /*ns*/) const {
    s << "}"; // no space and no std::endl by design
}

void namespace_formatter::
format_begin(std::ostream& s, const std::list<std::string>& ns) const {
    const auto joined_ns(boost::algorithm::join(ns, dot));
    format_begin(s, joined_ns);
}

void namespace_formatter::
format_end(std::ostream& s, const std::list<std::string>& /*ns*/) const {
    format_end(s, empty);

    if (add_new_line_)
        s << std::endl;
}

} } }
