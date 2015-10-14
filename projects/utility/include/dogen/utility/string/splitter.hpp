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
#ifndef DOGEN_UTILITY_STRING_SPLITTER_HPP
#define DOGEN_UTILITY_STRING_SPLITTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_set>

namespace dogen {
namespace utility {
namespace string {

/**
 * @brief Splits a string given a separator.
 */

class splitter {
public:
    /**
     * @brief Splits the string by a supplied scope operator, e.g. '::'.
     */
    static std::list<std::string> split_scoped(const std::string& n,
        const std::string& scope_operator = "::");

    /**
     * @brief Splits a string using CSV.
     */
    static std::list<std::string> split_csv(const std::string& n);
};

} } }

#endif
