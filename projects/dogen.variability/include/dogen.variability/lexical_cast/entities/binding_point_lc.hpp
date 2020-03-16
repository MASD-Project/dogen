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
#ifndef DOGEN_VARIABILITY_LEXICAL_CAST_ENTITIES_BINDING_POINT_LC_HPP
#define DOGEN_VARIABILITY_LEXICAL_CAST_ENTITIES_BINDING_POINT_LC_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/lexical_cast.hpp>
#include "dogen.variability/types/entities/binding_point.hpp"

namespace boost {

template<>
inline std::string lexical_cast(const dogen::variability::entities::binding_point& v) {
    using dogen::variability::entities::binding_point;

    switch (v) {
    case binding_point::invalid:
        return "binding_point::invalid";
    case binding_point::any:
        return "binding_point::any";
    case binding_point::global:
        return "binding_point::global";
    case binding_point::element:
        return "binding_point::element";
    case binding_point::property:
        return "binding_point::property";
    case binding_point::operation:
        return "binding_point::operation";
    default:
        throw boost::bad_lexical_cast();
    }
}

template<>
inline dogen::variability::entities::binding_point lexical_cast(const std::string & s) {
    using dogen::variability::entities::binding_point;

    if (s == "invalid" || s == "binding_point::invalid")
        return binding_point::invalid;
    if (s == "any" || s == "binding_point::any")
        return binding_point::any;
    if (s == "global" || s == "binding_point::global")
        return binding_point::global;
    if (s == "element" || s == "binding_point::element")
        return binding_point::element;
    if (s == "property" || s == "binding_point::property")
        return binding_point::property;
    if (s == "operation" || s == "binding_point::operation")
        return binding_point::operation;
    throw boost::bad_lexical_cast();
}

}

#endif
