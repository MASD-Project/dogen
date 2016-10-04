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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTERS_SERIALIZATION_TRAITS_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTERS_SERIALIZATION_TRAITS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace serialization {

struct traits {
    /**
     * @brief Name of this facet.
     */
    static std::string facet_name();

    /**
     * @brief Name of the canonical formatter.
     */
    static std::string canonical_formatter_name();

    /**
     * @brief Name of the class header formatter.
     */
    static std::string class_header_formatter_name();

    /**
     * @brief Name of the class implementation formatter.
     */
    static std::string class_implementation_formatter_name();

    /**
     * @brief Name of the enumeration header formatter.
     */
    static std::string enum_header_formatter_name();

    /**
     * @brief Name of the forward declaration's formatter.
     */
    static std::string forward_declarations_formatter_name();

    /**
     * @brief Name of the registrar header formatter.
     */
    static std::string registrar_header_formatter_name();

    /**
     * @brief Name of the registrar implementation formatter.
     */
    static std::string registrar_implementation_formatter_name();

    /**
     * @brief Name of the primitive implementation formatter.
     */
    static std::string primitive_header_formatter_name();
};

} } } } }

#endif
