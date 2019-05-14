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
#ifndef DOGEN_VARIABILITY_LEXICAL_CAST_META_MODEL_BINDING_ACTION_LC_HPP
#define DOGEN_VARIABILITY_LEXICAL_CAST_META_MODEL_BINDING_ACTION_LC_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/lexical_cast.hpp>
#include "dogen.variability/types/meta_model/binding_action.hpp"

namespace boost {

template<>
std::string lexical_cast(const dogen::variability::meta_model::binding_action& v) {
    using dogen::variability::meta_model::binding_action;

    switch (v) {
    case binding_action::invalid:
        return "binding_action::invalid";
    case binding_action::ignore:
        return "binding_action::ignore";
    case binding_action::copy:
        return "binding_action::copy";
    default:
        throw boost::bad_lexical_cast();
    }
}

template<>
dogen::variability::meta_model::binding_action lexical_cast(const std::string & s) {
    using dogen::variability::meta_model::binding_action;

    if (s == "invalid" || s == "binding_action::invalid")
        return binding_action::invalid;
    if (s == "ignore" || s == "binding_action::ignore")
        return binding_action::ignore;
    if (s == "copy" || s == "binding_action::copy")
        return binding_action::copy;
    throw boost::bad_lexical_cast();
}

}

#endif
