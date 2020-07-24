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

#include <algorithm>

namespace dogen::identification::helpers {

class legacy_logical_name_tree_parser final {
public:
    legacy_logical_name_tree_parser() = default;
    legacy_logical_name_tree_parser(const legacy_logical_name_tree_parser&) = default;
    legacy_logical_name_tree_parser(legacy_logical_name_tree_parser&&) = default;
    ~legacy_logical_name_tree_parser() = default;
    legacy_logical_name_tree_parser& operator=(const legacy_logical_name_tree_parser&) = default;

public:
    bool operator==(const legacy_logical_name_tree_parser& rhs) const;
    bool operator!=(const legacy_logical_name_tree_parser& rhs) const {
        return !this->operator==(rhs);
    }

};

}

#endif
