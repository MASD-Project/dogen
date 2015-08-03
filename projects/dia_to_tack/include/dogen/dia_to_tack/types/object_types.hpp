/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#ifndef DOGEN_DIA_TO_TACK_TYPES_OBJECT_TYPES_HPP
#define DOGEN_DIA_TO_TACK_TYPES_OBJECT_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen {
namespace dia_to_tack {

/**
 * @brief Identifier for the type of Dia object.
 */
enum class object_types : unsigned int {
    invalid = 0, ///< Represents an uninitialised enum
    uml_large_package = 1, ///< A UML package
    uml_class = 2, ///< A UML class
    uml_generalization = 3, ///< UML Inheritance
    uml_association = 4, ///< UML Association
    uml_note = 5, ///< UML Note
    uml_message = 6, ///< UML Message
    uml_realization = 7 ///< UML Realization
};

} }

#endif
