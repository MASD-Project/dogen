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
#ifndef DOGEN_IDENTIFICATION_LEXICAL_CAST_ENTITIES_TECHNICAL_SPACE_LC_HPP
#define DOGEN_IDENTIFICATION_LEXICAL_CAST_ENTITIES_TECHNICAL_SPACE_LC_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/lexical_cast.hpp>
#include "dogen.identification/types/entities/technical_space.hpp"

namespace boost {

template<>
inline std::string lexical_cast(const dogen::identification::entities::technical_space& v) {
    using dogen::identification::entities::technical_space;

    switch (v) {
    case technical_space::invalid:
        return "technical_space::invalid";
    case technical_space::agnostic:
        return "technical_space::agnostic";
    case technical_space::cpp:
        return "technical_space::cpp";
    case technical_space::csharp:
        return "technical_space::csharp";
    case technical_space::cmake:
        return "technical_space::cmake";
    case technical_space::xml:
        return "technical_space::xml";
    case technical_space::odb:
        return "technical_space::odb";
    case technical_space::sln:
        return "technical_space::sln";
    default:
        throw boost::bad_lexical_cast();
    }
}

template<>
inline dogen::identification::entities::technical_space lexical_cast(const std::string & s) {
    using dogen::identification::entities::technical_space;

    if (s == "invalid" || s == "technical_space::invalid")
        return technical_space::invalid;
    if (s == "agnostic" || s == "technical_space::agnostic")
        return technical_space::agnostic;
    if (s == "cpp" || s == "technical_space::cpp")
        return technical_space::cpp;
    if (s == "csharp" || s == "technical_space::csharp")
        return technical_space::csharp;
    if (s == "cmake" || s == "technical_space::cmake")
        return technical_space::cmake;
    if (s == "xml" || s == "technical_space::xml")
        return technical_space::xml;
    if (s == "odb" || s == "technical_space::odb")
        return technical_space::odb;
    if (s == "sln" || s == "technical_space::sln")
        return technical_space::sln;
    throw boost::bad_lexical_cast();
}

}

#endif
