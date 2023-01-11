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
#ifndef DOGEN_UTILITY_LEXICAL_CAST_FORMATTERS_QUOTE_TYPE_LC_HPP
#define DOGEN_UTILITY_LEXICAL_CAST_FORMATTERS_QUOTE_TYPE_LC_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/lexical_cast.hpp>
#include "dogen.utility/types/formatters/quote_type.hpp"

namespace boost {

template<>
inline std::string lexical_cast(const dogen::utility::formatters::quote_type& v) {
    using dogen::utility::formatters::quote_type;

    switch (v) {
    case quote_type::invalid:
        return "quote_type::invalid";
    case quote_type::single_quote:
        return "quote_type::single_quote";
    case quote_type::double_quote:
        return "quote_type::double_quote";
    default:
        throw boost::bad_lexical_cast();
    }
}

template<>
inline dogen::utility::formatters::quote_type lexical_cast(const std::string & s) {
    using dogen::utility::formatters::quote_type;

    if (s == "invalid" || s == "quote_type::invalid")
        return quote_type::invalid;
    if (s == "single_quote" || s == "quote_type::single_quote")
        return quote_type::single_quote;
    if (s == "double_quote" || s == "quote_type::double_quote")
        return quote_type::double_quote;
    throw boost::bad_lexical_cast();
}

}

#endif
