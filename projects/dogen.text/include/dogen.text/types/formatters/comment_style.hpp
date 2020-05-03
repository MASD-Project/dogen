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
#ifndef DOGEN_TEXT_TYPES_FORMATTERS_COMMENT_STYLE_HPP
#define DOGEN_TEXT_TYPES_FORMATTERS_COMMENT_STYLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen::text::formatters {

/**
 * @brief Supported styles of comments.
 */
enum class comment_style : unsigned int {
    invalid = 0, ///< Represents an uninitialised enum
    c_style = 1, ///< Original C programming language style.
    cpp_style = 2, ///< One line, C++ style.
    csharp_style = 3, ///< C# programming language style.
    shell_style = 4, ///< UNIX shell scripting comments.
    sql_style = 5, ///< Comments start with a double-dash.
    xml_style = 6 ///< Comments using XML syntax.
};

}

#endif
