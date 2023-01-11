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
#ifndef DOGEN_LEXICAL_CAST_DIFFING_DESTINATION_LC_HPP
#define DOGEN_LEXICAL_CAST_DIFFING_DESTINATION_LC_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/lexical_cast.hpp>
#include "dogen/types/diffing_destination.hpp"

namespace boost {

template<>
inline std::string lexical_cast(const dogen::diffing_destination& v) {
    using dogen::diffing_destination;

    switch (v) {
    case diffing_destination::invalid:
        return "diffing_destination::invalid";
    case diffing_destination::file:
        return "diffing_destination::file";
    case diffing_destination::console:
        return "diffing_destination::console";
    default:
        throw boost::bad_lexical_cast();
    }
}

template<>
inline dogen::diffing_destination lexical_cast(const std::string & s) {
    using dogen::diffing_destination;

    if (s == "invalid" || s == "diffing_destination::invalid")
        return diffing_destination::invalid;
    if (s == "file" || s == "diffing_destination::file")
        return diffing_destination::file;
    if (s == "console" || s == "diffing_destination::console")
        return diffing_destination::console;
    throw boost::bad_lexical_cast();
}

}

#endif