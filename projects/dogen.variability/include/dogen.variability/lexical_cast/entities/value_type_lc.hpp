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
#ifndef DOGEN_VARIABILITY_LEXICAL_CAST_ENTITIES_VALUE_TYPE_LC_HPP
#define DOGEN_VARIABILITY_LEXICAL_CAST_ENTITIES_VALUE_TYPE_LC_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/lexical_cast.hpp>
#include "dogen.variability/types/entities/value_type.hpp"

namespace boost {

template<>
inline std::string lexical_cast(const dogen::variability::entities::value_type& v) {
    using dogen::variability::entities::value_type;

    switch (v) {
    case value_type::invalid:
        return "value_type::invalid";
    case value_type::text:
        return "value_type::text";
    case value_type::text_collection:
        return "value_type::text_collection";
    case value_type::number:
        return "value_type::number";
    case value_type::boolean:
        return "value_type::boolean";
    case value_type::key_value_pair:
        return "value_type::key_value_pair";
    default:
        throw boost::bad_lexical_cast();
    }
}

template<>
inline dogen::variability::entities::value_type lexical_cast(const std::string & s) {
    using dogen::variability::entities::value_type;

    if (s == "invalid" || s == "value_type::invalid")
        return value_type::invalid;
    if (s == "text" || s == "value_type::text")
        return value_type::text;
    if (s == "text_collection" || s == "value_type::text_collection")
        return value_type::text_collection;
    if (s == "number" || s == "value_type::number")
        return value_type::number;
    if (s == "boolean" || s == "value_type::boolean")
        return value_type::boolean;
    if (s == "key_value_pair" || s == "value_type::key_value_pair")
        return value_type::key_value_pair;
    throw boost::bad_lexical_cast();
}

}

#endif
