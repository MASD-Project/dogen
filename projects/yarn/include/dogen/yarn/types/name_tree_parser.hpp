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
#ifndef DOGEN_YARN_TYPES_NAME_TREE_PARSER_HPP
#define DOGEN_YARN_TYPES_NAME_TREE_PARSER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_set>
#include "dogen/yarn/types/languages.hpp"
#include "dogen/yarn/types/location.hpp"
#include "dogen/yarn/types/name_tree.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Parses identifiers according to a well-defined syntax, and
 * generates a tree of names from them.
 */
class name_tree_parser {
public:
    /**
     * @brief Initialises the parser.
     *
     * @param top_level_modules names of all the top-level modules in
     * the current model.
     * @param model_location location for the element representing the
     * model.
     * @param language what programming language syntax to use.
     */
    name_tree_parser(const std::unordered_set<std::string>& top_level_modules,
        const location& model_location, const languages language);

public:
    /**
     * @brief Parse the string into a name tree.
     */
    name_tree parse(const std::string& s) const;

private:
    const std::unordered_set<std::string>& top_level_modules_;
    const location& model_location_;
    const languages language_;
};

} }

#endif
