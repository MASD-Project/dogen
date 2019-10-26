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
#ifndef DOGEN_RELATIONAL_LEXICAL_CAST_TRACING_TRANSFORM_TYPE_LC_HPP
#define DOGEN_RELATIONAL_LEXICAL_CAST_TRACING_TRANSFORM_TYPE_LC_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/lexical_cast.hpp>
#include "dogen.relational/types/tracing/transform_type.hpp"

namespace boost {

template<>
inline std::string lexical_cast(const dogen::relational::tracing::transform_type& v) {
    using dogen::relational::tracing::transform_type;

    switch (v) {
    case transform_type::invalid:
        return "transform_type::invalid";
    case transform_type::chain:
        return "transform_type::chain";
    case transform_type::leaf:
        return "transform_type::leaf";
    default:
        throw boost::bad_lexical_cast();
    }
}

template<>
inline dogen::relational::tracing::transform_type lexical_cast(const std::string & s) {
    using dogen::relational::tracing::transform_type;

    if (s == "invalid" || s == "transform_type::invalid")
        return transform_type::invalid;
    if (s == "chain" || s == "transform_type::chain")
        return transform_type::chain;
    if (s == "leaf" || s == "transform_type::leaf")
        return transform_type::leaf;
    throw boost::bad_lexical_cast();
}

}

#endif
