/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * These files are code-generated via overrides to test dogen. Do not commit them.
 *
 * Generation timestamp: 2022-10-20T10:20:30
 * WARNING: do not edit this file manually.
 * Generated by MASD Dogen v1.0.33
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
#ifndef DOGEN_ORG_LEXICAL_CAST_ENTITIES_DRAWER_TYPE_LC_HPP
#define DOGEN_ORG_LEXICAL_CAST_ENTITIES_DRAWER_TYPE_LC_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/lexical_cast.hpp>
#include "dogen.org/types/entities/drawer_type.hpp"

namespace boost {

template<>
inline std::string lexical_cast(const dogen::org::entities::drawer_type& v) {
    using dogen::org::entities::drawer_type;

    switch (v) {
    case drawer_type::invalid:
        return "drawer_type::invalid";
    case drawer_type::regular:
        return "drawer_type::regular";
    case drawer_type::property_drawer:
        return "drawer_type::property_drawer";
    default:
        throw boost::bad_lexical_cast();
    }
}

template<>
inline dogen::org::entities::drawer_type lexical_cast(const std::string & s) {
    using dogen::org::entities::drawer_type;

    if (s == "invalid" || s == "drawer_type::invalid")
        return drawer_type::invalid;
    if (s == "regular" || s == "drawer_type::regular")
        return drawer_type::regular;
    if (s == "property_drawer" || s == "drawer_type::property_drawer")
        return drawer_type::property_drawer;
    throw boost::bad_lexical_cast();
}

}

#endif