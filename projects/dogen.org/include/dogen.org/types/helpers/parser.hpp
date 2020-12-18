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
#ifndef DOGEN_ORG_TYPES_HELPERS_PARSER_HPP
#define DOGEN_ORG_TYPES_HELPERS_PARSER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include "dogen.org/types/entities/headline.hpp"
#include "dogen.org/types/entities/document.hpp"

namespace dogen::org::helpers {

/**
 * @brief Parses a string containing a valid org-mode document into
 * its domain representation.
 */
class parser final {
private:
    /**
     * @brief Splits the string by newlines.
     */
    static std::list<std::string> split_into_lines(const std::string& s);

    /**
     * @brief Parses the remaining content as part of an headline.
     */
    std::list<entities::headline>
    parse_headlines(const std::list<std::string>& lines,
        std::list<std::string>::const_iterator& i);

public:
    static entities::document parse(const std::string& s);
};

}

#endif
