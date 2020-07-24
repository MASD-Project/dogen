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
#ifndef DOGEN_IDENTIFICATION_TYPES_HELPERS_LEGACY_LOGICAL_NAME_TREE_PARSER_HPP
#define DOGEN_IDENTIFICATION_TYPES_HELPERS_LEGACY_LOGICAL_NAME_TREE_PARSER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_set>
#include "dogen.identification/types/entities/technical_space.hpp"
#include "dogen.identification/types/entities/logical_location.hpp"
#include "dogen.identification/types/entities/logical_name_tree.hpp"

namespace dogen::identification::helpers {

/**
 * @brief Parses identifiers according to a well-defined syntax, and
 * generates a tree of names from them.
 */
class legacy_logical_name_tree_parser {
public:
    /**
     * @brief Initialises the parser.
     *
     * @param ts what technical space syntax to use.
     */
    explicit legacy_logical_name_tree_parser(
        const entities::technical_space ts);

public:
    /**
     * @brief Parse the string into a name tree.
     */
    entities::logical_name_tree parse(const std::string& s) const;

private:
    const entities::technical_space technical_space_;
};

}

#endif
