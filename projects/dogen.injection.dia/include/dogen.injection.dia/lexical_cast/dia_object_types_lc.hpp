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
#ifndef DOGEN_INJECTION_DIA_LEXICAL_CAST_DIA_OBJECT_TYPES_LC_HPP
#define DOGEN_INJECTION_DIA_LEXICAL_CAST_DIA_OBJECT_TYPES_LC_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/lexical_cast.hpp>
#include "dogen.injection.dia/types/dia_object_types.hpp"

namespace boost {

template<>
std::string lexical_cast(const dogen::injection::dia::dia_object_types& v) {
    using dogen::injection::dia::dia_object_types;

    switch (v) {
    case dia_object_types::invalid:
        return "dia_object_types::invalid";
    case dia_object_types::uml_large_package:
        return "dia_object_types::uml_large_package";
    case dia_object_types::uml_class:
        return "dia_object_types::uml_class";
    case dia_object_types::uml_generalization:
        return "dia_object_types::uml_generalization";
    case dia_object_types::uml_association:
        return "dia_object_types::uml_association";
    case dia_object_types::uml_note:
        return "dia_object_types::uml_note";
    case dia_object_types::uml_message:
        return "dia_object_types::uml_message";
    case dia_object_types::uml_realization:
        return "dia_object_types::uml_realization";
    default:
        throw boost::bad_lexical_cast();
    }
}

template<>
dogen::injection::dia::dia_object_types lexical_cast(const std::string & s) {
    using dogen::injection::dia::dia_object_types;

    if (s == "invalid" || s == "dia_object_types::invalid")
        return dia_object_types::invalid;
    if (s == "uml_large_package" || s == "dia_object_types::uml_large_package")
        return dia_object_types::uml_large_package;
    if (s == "uml_class" || s == "dia_object_types::uml_class")
        return dia_object_types::uml_class;
    if (s == "uml_generalization" || s == "dia_object_types::uml_generalization")
        return dia_object_types::uml_generalization;
    if (s == "uml_association" || s == "dia_object_types::uml_association")
        return dia_object_types::uml_association;
    if (s == "uml_note" || s == "dia_object_types::uml_note")
        return dia_object_types::uml_note;
    if (s == "uml_message" || s == "dia_object_types::uml_message")
        return dia_object_types::uml_message;
    if (s == "uml_realization" || s == "dia_object_types::uml_realization")
        return dia_object_types::uml_realization;
    throw boost::bad_lexical_cast();
}

}

#endif
