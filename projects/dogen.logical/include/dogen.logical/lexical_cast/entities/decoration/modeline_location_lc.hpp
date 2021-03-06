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
#ifndef DOGEN_LOGICAL_LEXICAL_CAST_ENTITIES_DECORATION_MODELINE_LOCATION_LC_HPP
#define DOGEN_LOGICAL_LEXICAL_CAST_ENTITIES_DECORATION_MODELINE_LOCATION_LC_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/lexical_cast.hpp>
#include "dogen.logical/types/entities/decoration/modeline_location.hpp"

namespace boost {

template<>
inline std::string lexical_cast(const dogen::logical::entities::decoration::modeline_location& v) {
    using dogen::logical::entities::decoration::modeline_location;

    switch (v) {
    case modeline_location::invalid:
        return "modeline_location::invalid";
    case modeline_location::top:
        return "modeline_location::top";
    case modeline_location::bottom:
        return "modeline_location::bottom";
    default:
        throw boost::bad_lexical_cast();
    }
}

template<>
inline dogen::logical::entities::decoration::modeline_location lexical_cast(const std::string & s) {
    using dogen::logical::entities::decoration::modeline_location;

    if (s == "invalid" || s == "modeline_location::invalid")
        return modeline_location::invalid;
    if (s == "top" || s == "modeline_location::top")
        return modeline_location::top;
    if (s == "bottom" || s == "modeline_location::bottom")
        return modeline_location::bottom;
    throw boost::bad_lexical_cast();
}

}

#endif
