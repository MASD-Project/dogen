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
#ifndef DOGEN_LOGICAL_LEXICAL_CAST_META_MODEL_ORM_LETTER_CASE_LC_HPP
#define DOGEN_LOGICAL_LEXICAL_CAST_META_MODEL_ORM_LETTER_CASE_LC_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/lexical_cast.hpp>
#include "dogen.logical/types/meta_model/orm/letter_case.hpp"

namespace boost {

template<>
inline std::string lexical_cast(const dogen::logical::meta_model::orm::letter_case& v) {
    using dogen::logical::meta_model::orm::letter_case;

    switch (v) {
    case letter_case::invalid:
        return "letter_case::invalid";
    case letter_case::upper_case:
        return "letter_case::upper_case";
    case letter_case::lower_case:
        return "letter_case::lower_case";
    default:
        throw boost::bad_lexical_cast();
    }
}

template<>
inline dogen::logical::meta_model::orm::letter_case lexical_cast(const std::string & s) {
    using dogen::logical::meta_model::orm::letter_case;

    if (s == "invalid" || s == "letter_case::invalid")
        return letter_case::invalid;
    if (s == "upper_case" || s == "letter_case::upper_case")
        return letter_case::upper_case;
    if (s == "lower_case" || s == "letter_case::lower_case")
        return letter_case::lower_case;
    throw boost::bad_lexical_cast();
}

}

#endif
