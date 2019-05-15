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
#ifndef DOGEN_CODING_LEXICAL_CAST_HELPERS_MAPPING_ACTIONS_LC_HPP
#define DOGEN_CODING_LEXICAL_CAST_HELPERS_MAPPING_ACTIONS_LC_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/lexical_cast.hpp>
#include "dogen.coding/types/helpers/mapping_actions.hpp"

namespace boost {

template<>
inline std::string lexical_cast(const dogen::coding::helpers::mapping_actions& v) {
    using dogen::coding::helpers::mapping_actions;

    switch (v) {
    case mapping_actions::invalid:
        return "mapping_actions::invalid";
    case mapping_actions::translate:
        return "mapping_actions::translate";
    case mapping_actions::erase:
        return "mapping_actions::erase";
    default:
        throw boost::bad_lexical_cast();
    }
}

template<>
inline dogen::coding::helpers::mapping_actions lexical_cast(const std::string & s) {
    using dogen::coding::helpers::mapping_actions;

    if (s == "invalid" || s == "mapping_actions::invalid")
        return mapping_actions::invalid;
    if (s == "translate" || s == "mapping_actions::translate")
        return mapping_actions::translate;
    if (s == "erase" || s == "mapping_actions::erase")
        return mapping_actions::erase;
    throw boost::bad_lexical_cast();
}

}

#endif