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
#ifndef DOGEN_GENERATION_CSHARP_LEXICAL_CAST_FORMATTABLES_AUXILIARY_FUNCTION_TYPES_LC_HPP
#define DOGEN_GENERATION_CSHARP_LEXICAL_CAST_FORMATTABLES_AUXILIARY_FUNCTION_TYPES_LC_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/lexical_cast.hpp>
#include "dogen.generation.csharp/types/formattables/auxiliary_function_types.hpp"

namespace boost {

template<>
inline std::string lexical_cast(const dogen::generation::csharp::formattables::auxiliary_function_types& v) {
    using dogen::generation::csharp::formattables::auxiliary_function_types;

    switch (v) {
    case auxiliary_function_types::invalid:
        return "auxiliary_function_types::invalid";
    case auxiliary_function_types::assistant:
        return "auxiliary_function_types::assistant";
    case auxiliary_function_types::helper:
        return "auxiliary_function_types::helper";
    default:
        throw boost::bad_lexical_cast();
    }
}

template<>
inline dogen::generation::csharp::formattables::auxiliary_function_types lexical_cast(const std::string & s) {
    using dogen::generation::csharp::formattables::auxiliary_function_types;

    if (s == "invalid" || s == "auxiliary_function_types::invalid")
        return auxiliary_function_types::invalid;
    if (s == "assistant" || s == "auxiliary_function_types::assistant")
        return auxiliary_function_types::assistant;
    if (s == "helper" || s == "auxiliary_function_types::helper")
        return auxiliary_function_types::helper;
    throw boost::bad_lexical_cast();
}

}

#endif
