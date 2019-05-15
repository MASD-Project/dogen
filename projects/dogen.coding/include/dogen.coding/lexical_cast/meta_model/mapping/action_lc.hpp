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
#ifndef DOGEN_CODING_LEXICAL_CAST_META_MODEL_MAPPING_ACTION_LC_HPP
#define DOGEN_CODING_LEXICAL_CAST_META_MODEL_MAPPING_ACTION_LC_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/lexical_cast.hpp>
#include "dogen.coding/types/meta_model/mapping/action.hpp"

namespace boost {

template<>
inline std::string lexical_cast(const dogen::coding::meta_model::mapping::action& v) {
    using dogen::coding::meta_model::mapping::action;

    switch (v) {
    case action::invalid:
        return "action::invalid";
    case action::translate:
        return "action::translate";
    case action::erase:
        return "action::erase";
    default:
        throw boost::bad_lexical_cast();
    }
}

template<>
inline dogen::coding::meta_model::mapping::action lexical_cast(const std::string & s) {
    using dogen::coding::meta_model::mapping::action;

    if (s == "invalid" || s == "action::invalid")
        return action::invalid;
    if (s == "translate" || s == "action::translate")
        return action::translate;
    if (s == "erase" || s == "action::erase")
        return action::erase;
    throw boost::bad_lexical_cast();
}

}

#endif
