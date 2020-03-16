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
#ifndef DOGEN_GENERATION_TYPES_FORMATTERS_NAMESPACE_FORMATTER_HPP
#define DOGEN_GENERATION_TYPES_FORMATTERS_NAMESPACE_FORMATTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <string>
#include "dogen.logical/types/meta_model/technical_space.hpp"

namespace dogen::generation::formatters {

/**
 * @brief Formats namespaces for technical spaces that support them.
 */
class namespace_formatter final {
public:
    /**
     * @brief Creates a namespace formatter.
     *
     * @param s Stream to write into.
     * @param ts Target technical space to generate namespaces for.
     * @param ns Namespace or namespaces, if any.
     * @param add_new_line If true, adds a new line at the end.
     * @param use_nesting If true and supported by the target
     * technical space, uses nested namespaces syntax. If false,
     * creates multiple lines per namespace.
     */
    /**@{*/
    namespace_formatter(std::ostream& s,
        const logical::meta_model::technical_space ts,
        const std::list<std::string>& ns,
        const bool add_new_line = false,  const bool use_nesting = false);
    namespace_formatter(std::ostream& s,
        const logical::meta_model::technical_space ts,
        const std::string& ns,
        const bool add_new_line = false,  const bool use_nesting = false);
    namespace_formatter(std::ostream& s,
        const logical::meta_model::technical_space ts,
        const bool add_new_line = false,  const bool use_nesting = false);
    /**@}*/

private:
    void format_cpp_begin();
    void format_csharp_begin();
    void format_cpp_end();
    void format_csharp_end();

public:
    /**
     * @brief Formats the opening of a namespace.
     */
    void format_begin();

    /**
     * @brief Formats the closing of a namespace.
     */
    void format_end();

private:
    std::ostream& stream_;
    const logical::meta_model::technical_space technical_space_;
    const std::list<std::string> namespaces_;
    const bool add_new_line_;
    const bool use_nesting_;
};

}

#endif
