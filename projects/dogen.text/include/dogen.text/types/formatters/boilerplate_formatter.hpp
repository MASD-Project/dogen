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
#ifndef DOGEN_TEXT_TYPES_FORMATTERS_BOILERPLATE_FORMATTER_HPP
#define DOGEN_TEXT_TYPES_FORMATTERS_BOILERPLATE_FORMATTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include "dogen.text/types/formatters/boilerplate_properties.hpp"

namespace dogen::text::formatters {

/**
 * @brief Formats all of the boilerplate content in a file such as
 * licence, modeline, dependencies, etc.
 */
class boilerplate_formatter final {
public:
    boilerplate_formatter(std::ostream& s, const boilerplate_properties& bp);

private:
    /**
     * @brief Formats the file's preamble.
     *
     * The preamble is made up of the modeline, any potential code
     * generation marker and the licence.
     */
    void format_preamble() const;

    /**
     * @brief Formats the file's postamble.
     *
     * The postamble is composed of a bottom modeline, if any.
     */
    void format_postamble() const;

    /**
     * @brief Formats the starting part of the header guards.
     */
    void format_guards_begin() const;

    /**
     * @brief Formats the ending part of the header guards.
     */
    void format_guards_end() const;

    /**
     * @brief Formats the preprocessor includes.
     */
    void format_dependencies() const;

public:
    /**
     * @brief Formats the initial section of boilerplate.
     */
    void format_begin() const;

    /**
     * @brief Formats the end of the boilerplate.
     */
    void format_end() const;

private:
    std::ostream& stream_;
    const boilerplate_properties boilerplate_properties_;
    const bool supports_header_guards_;
};

}

#endif
