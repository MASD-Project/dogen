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
#include <boost/filesystem/path.hpp>
#include "masd.dogen.extraction/types/indent_filter.hpp"
#include "masd.dogen.extraction/types/cpp/include_formatter.hpp"

namespace {

const std::string include("#include ");

}

namespace masd::dogen::extraction::cpp {

void include_formatter::
format(std::ostream& s, const std::list<std::string>& includes) const {
    for (const auto& inc : includes)
        s << include << inc << std::endl;

    if (!includes.empty())
        s << masd::dogen::extraction::manage_blank_lines << std::endl;
}

}
