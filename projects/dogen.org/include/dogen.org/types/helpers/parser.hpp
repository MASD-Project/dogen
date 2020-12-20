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

#include "dogen.org/types/entities/affiliated_keyword.hpp"
#include "dogen.org/types/entities/block.hpp"
#include "dogen.org/types/entities/drawer.hpp"
#include "dogen.org/types/entities/drawer_content.hpp"
#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <istream>
#include <boost/optional.hpp>
#include "dogen.org/types/entities/headline.hpp"
#include "dogen.org/types/entities/document.hpp"

namespace dogen::org::helpers {

/**
 * @brief Parses a small number of well-defined org-mode constructs
 * such as headlines and blocks.
 */
class parser final {
private:
    /**
     * @brief Returns true if the string is empty or made up of just
     * whitespace.
     */
    static bool is_empty_or_whitespace(const std::string& s);

public:
    /**
     * @brief Attempts to parse the string as an headline. If the
     * string is not a headline returns an empty optional.
     */
    static boost::optional<entities::headline>
    try_parse_headline(const std::string& s);

    /**
     * @brief Attempts to parse the string as an affiliated keyword.
     */
    static boost::optional<entities::affiliated_keyword>
    try_parse_affiliated_keyword(const std::string& s);

public:
    /**
     * @brief Attempts to parse the string as the start of an org
     * drawer.
     */
    static boost::optional<entities::drawer>
    try_parse_drawer_start(const std::string& s);

    /**
     * @brief Returns true if the string denotes the end of a drawer.
     */
    static bool is_drawer_end(const std::string& s);

    /**
     * @brief Parse the string as drawer contents.
     *
     * If the contents take the form of a KVP, it performs the
     * appropriate split; else the entire contents are placed in the
     * value field.
     */
    static entities::drawer_content parse_drawer_content(const std::string& s);

public:
    /**
     * @brief Attempts to parse the string as the start of a block.
     */
    static boost::optional<entities::block>
    try_parse_greater_block_start(const std::string& s);

    /**
     * @brief Returns true if the string denotes the end of a block.
     *
     * Note that this method detects mismatching block ends and
     * throws.
     */
    static bool is_greater_block_end(const std::string& s,
        const std::string& block_name);
};

}

#endif
