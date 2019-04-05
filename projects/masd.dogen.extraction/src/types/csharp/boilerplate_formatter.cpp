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
#include "masd.dogen.extraction/types/csharp/using_formatter.hpp"
#include "masd.dogen.extraction/types/csharp/boilerplate_formatter.hpp"

namespace masd::dogen::extraction::csharp {

boilerplate_formatter::boilerplate_formatter(
    const bool generate_preamble)
    : generate_preamble_(generate_preamble) { }

void boilerplate_formatter::
format_preamble(std::ostream& s, const decoration_properties& dc) const {
    if (!generate_preamble_)
        return;

    s << dc.preamble();
}

void boilerplate_formatter::
format_usings(std::ostream& s, const std::list<std::string>& usings) const {
    using_formatter f;
    f.format(s, usings);
}

void boilerplate_formatter::
format_begin(std::ostream& s, const decoration_properties& dc,
    const std::list<std::string>& usings) const {

    format_preamble(s, dc);
    format_usings(s, usings);
}

void boilerplate_formatter::
format_postamble(std::ostream& s, const decoration_properties& dc) const {
    s << dc.postamble();
}

void boilerplate_formatter::
format_end(std::ostream& s, const decoration_properties& dc) const {
    format_postamble(s, dc);
}

}
