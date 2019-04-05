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
#include "masd.dogen.extraction/types/cpp/scoped_boilerplate_formatter.hpp"

namespace masd::dogen::extraction::cpp {

scoped_boilerplate_formatter::scoped_boilerplate_formatter(std::ostream& s,
    const std::string& preamble, const std::string& postamble,
    const std::list<std::string>& includes, const std::string& header_guard)
    : stream_(s), preamble_(preamble), postamble_(postamble),
      includes_(includes), header_guard_(header_guard) {
    formatter_.format_begin(stream_, preamble_, includes, header_guard);
}

scoped_boilerplate_formatter::~scoped_boilerplate_formatter() {
    formatter_.format_end(stream_, postamble_, header_guard_);
}

}
