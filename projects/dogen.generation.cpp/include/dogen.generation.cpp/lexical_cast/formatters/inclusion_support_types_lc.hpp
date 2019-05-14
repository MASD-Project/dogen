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
#ifndef DOGEN_GENERATION_CPP_LEXICAL_CAST_FORMATTERS_INCLUSION_SUPPORT_TYPES_LC_HPP
#define DOGEN_GENERATION_CPP_LEXICAL_CAST_FORMATTERS_INCLUSION_SUPPORT_TYPES_LC_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/lexical_cast.hpp>
#include "dogen.generation.cpp/types/formatters/inclusion_support_types.hpp"

namespace boost {

template<>
std::string lexical_cast(const dogen::generation::cpp::formatters::inclusion_support_types& v) {
    using dogen::generation::cpp::formatters::inclusion_support_types;

    switch (v) {
    case inclusion_support_types::invalid:
        return "inclusion_support_types::invalid";
    case inclusion_support_types::not_supported:
        return "inclusion_support_types::not_supported";
    case inclusion_support_types::regular_support:
        return "inclusion_support_types::regular_support";
    case inclusion_support_types::canonical_support:
        return "inclusion_support_types::canonical_support";
    default:
        throw boost::bad_lexical_cast();
    }
}

template<>
dogen::generation::cpp::formatters::inclusion_support_types lexical_cast(const std::string & s) {
    using dogen::generation::cpp::formatters::inclusion_support_types;

    if (s == "invalid" || s == "inclusion_support_types::invalid")
        return inclusion_support_types::invalid;
    if (s == "not_supported" || s == "inclusion_support_types::not_supported")
        return inclusion_support_types::not_supported;
    if (s == "regular_support" || s == "inclusion_support_types::regular_support")
        return inclusion_support_types::regular_support;
    if (s == "canonical_support" || s == "inclusion_support_types::canonical_support")
        return inclusion_support_types::canonical_support;
    throw boost::bad_lexical_cast();
}

}

#endif
