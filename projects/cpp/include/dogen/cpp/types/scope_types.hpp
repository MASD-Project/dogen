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
#ifndef DOGEN_CPP_TYPES_SCOPE_TYPES_HPP
#define DOGEN_CPP_TYPES_SCOPE_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen {
namespace cpp {

/**
 * @brief Types of scopes as defined by the C++ programming language standard.
 */
enum class scope_types : unsigned int {
    invalid = 0, ///< Represents an uninitialised enum
    local = 1, ///< A name has local scope or block scope if it is declared in a block.
    function_type = 2, ///< The only type of identifier with function scope is a label name.
    function_prototype_type = 3, ///< In any function declarator, parameter names have function prototype scope.
    global_type = 4, ///< Identifier declaration that appears outside of any block.
    namespace_type = 5, ///< Identifier declaration that appears inside a namespace block.
    class_type = 6 ///< Identifier declaration that appears inside class block.
};

} }

#endif
