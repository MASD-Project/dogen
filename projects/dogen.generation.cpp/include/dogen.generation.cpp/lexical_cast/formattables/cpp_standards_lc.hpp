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
#ifndef DOGEN_GENERATION_CPP_LEXICAL_CAST_FORMATTABLES_CPP_STANDARDS_LC_HPP
#define DOGEN_GENERATION_CPP_LEXICAL_CAST_FORMATTABLES_CPP_STANDARDS_LC_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/lexical_cast.hpp>
#include "dogen.generation.cpp/types/formattables/cpp_standards.hpp"

namespace boost {

template<>
std::string lexical_cast(const dogen::generation::cpp::formattables::cpp_standards& v) {
    using dogen::generation::cpp::formattables::cpp_standards;

    switch (v) {
    case cpp_standards::invalid:
        return "cpp_standards::invalid";
    case cpp_standards::cpp_98:
        return "cpp_standards::cpp_98";
    case cpp_standards::cpp_11:
        return "cpp_standards::cpp_11";
    case cpp_standards::cpp_14:
        return "cpp_standards::cpp_14";
    case cpp_standards::cpp_17:
        return "cpp_standards::cpp_17";
    default:
        throw boost::bad_lexical_cast();
    }
}

template<>
dogen::generation::cpp::formattables::cpp_standards lexical_cast(const std::string & s) {
    using dogen::generation::cpp::formattables::cpp_standards;

    if (s == "invalid" || s == "cpp_standards::invalid")
        return cpp_standards::invalid;
    if (s == "cpp_98" || s == "cpp_standards::cpp_98")
        return cpp_standards::cpp_98;
    if (s == "cpp_11" || s == "cpp_standards::cpp_11")
        return cpp_standards::cpp_11;
    if (s == "cpp_14" || s == "cpp_standards::cpp_14")
        return cpp_standards::cpp_14;
    if (s == "cpp_17" || s == "cpp_standards::cpp_17")
        return cpp_standards::cpp_17;
    throw boost::bad_lexical_cast();
}

}

#endif
