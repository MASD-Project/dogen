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
#ifndef DOGEN_RELATIONAL_LEXICAL_CAST_TRACING_IO_TYPE_LC_HPP
#define DOGEN_RELATIONAL_LEXICAL_CAST_TRACING_IO_TYPE_LC_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/lexical_cast.hpp>
#include "dogen.relational/types/tracing/io_type.hpp"

namespace boost {

template<>
inline std::string lexical_cast(const dogen::relational::tracing::io_type& v) {
    using dogen::relational::tracing::io_type;

    switch (v) {
    case io_type::invalid:
        return "io_type::invalid";
    case io_type::input:
        return "io_type::input";
    case io_type::output:
        return "io_type::output";
    default:
        throw boost::bad_lexical_cast();
    }
}

template<>
inline dogen::relational::tracing::io_type lexical_cast(const std::string & s) {
    using dogen::relational::tracing::io_type;

    if (s == "invalid" || s == "io_type::invalid")
        return io_type::invalid;
    if (s == "input" || s == "io_type::input")
        return io_type::input;
    if (s == "output" || s == "io_type::output")
        return io_type::output;
    throw boost::bad_lexical_cast();
}

}

#endif
