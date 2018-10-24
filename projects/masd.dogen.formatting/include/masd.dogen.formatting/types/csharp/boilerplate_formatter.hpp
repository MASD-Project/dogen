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
#ifndef MASD_DOGEN_FORMATTNG_TYPES_CSHARP_BOILERPLATE_FORMATTER_HPP
#define MASD_DOGEN_FORMATTNG_TYPES_CSHARP_BOILERPLATE_FORMATTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <string>
#include "masd.dogen.formatting/types/decoration_properties.hpp"

namespace masd::dogen::formatting::csharp {

/**
 * @brief Formats all of the boilerplate content in a C# file such as
 * licence, modeline, using statements, etc.
 */
class boilerplate_formatter {
public:
    boilerplate_formatter(const boilerplate_formatter&) = default;
    boilerplate_formatter& operator=(const boilerplate_formatter&) = delete;
    boilerplate_formatter(boilerplate_formatter&& rhs) = default;

public:
    /**
     * @brief Initialise boiler plate formatter.
     *
     * @param generate_preamble if true, the preamble will be
     * generated.
     */
    explicit boilerplate_formatter(const bool generate_preamble = true);

private:
    /**
     * @brief Formats the file's preamble.
     *
     * The preamble is made up of the modeline, any potential code
     * generation marker and the licence.
     */
    void format_preamble(std::ostream& s,
        const decoration_properties& dc) const;

    /**
     * @brief Formats the file's postamble.
     *
     * The postamble is composed of a bottom modeline, if any.
     */
    void format_postamble(std::ostream& s,
        const decoration_properties& dc) const;

    /**
     * @brief Formats the using statements.
     */
    void format_usings(std::ostream& s,
        const std::list<std::string>& usings) const;

public:
    /**
     * @brief Formats the initial section of boilerplate.
     */
    void format_begin(std::ostream& s, const decoration_properties& dc,
        const std::list<std::string>& usings) const;

    /**
     * @brief Formats the end of the boilerplate.
     */
    void format_end(std::ostream& s, const decoration_properties& dc) const;

private:
    const bool generate_preamble_;
};

}

#endif
