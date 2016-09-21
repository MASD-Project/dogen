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
#ifndef DOGEN_FORMATTERS_TYPES_DECORATION_FORMATTER_HPP
#define DOGEN_FORMATTERS_TYPES_DECORATION_FORMATTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include "dogen/formatters/types/comment_styles.hpp"
#include "dogen/formatters/types/decoration_configuration.hpp"

namespace dogen {
namespace formatters {

class decoration_formatter {
private:
    /**
     * @brief Adds the formatted modeline to the content.
     */
    void add_modeline(std::list<std::string>& content, const modeline& m) const;

    /**
     * @brief Adds the formatted modeline to the content.
     */
    void add_marker(std::list<std::string>& content,
        const std::string& marker) const;

    /**
     * @brief Adds the formatted modeline to the content.
     */
    void add_licence(std::list<std::string>& content, const licence& l) const;

public:
    void format_preamble(std::ostream& s, const comment_styles& single_line_cs,
        const comment_styles& multi_line_cs,
        const decoration_configuration& dc) const;

    void format_preamble(std::ostream& s, const comment_styles& cs,
        const decoration_configuration& dc) const;

    void format_postamble(std::ostream& s, const comment_styles& cs,
        const decoration_configuration& dc) const;
};

} }

#endif
