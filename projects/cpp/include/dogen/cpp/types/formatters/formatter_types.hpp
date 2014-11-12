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
#ifndef DOGEN_CPP_TYPES_FORMATTERS_FORMATTER_TYPES_HPP
#define DOGEN_CPP_TYPES_FORMATTERS_FORMATTER_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen {
namespace cpp {
namespace formatters {

/**
 * @brief Describes all of the formatter interfaces.
 */
enum class formatter_types : unsigned int {
    invalid = 0, ///< Represents an uninitialised enum
    class_formatter = 1,
    visitor_formatter = 2,
    enum_formatter = 3,
    registrar_formatter = 4,
    namespace_formatter = 5,
    exception_formatter = 6,
    forward_declarations_formatter = 7,
    includers_formatter = 8,
    odb_options_formatter = 9,
    cmakelists_formatter = 10
};

} } }

#endif
