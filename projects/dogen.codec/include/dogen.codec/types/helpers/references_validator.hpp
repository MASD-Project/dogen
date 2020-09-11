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
#ifndef DOGEN_CODEC_TYPES_HELPERS_REFERENCES_VALIDATOR_HPP
#define DOGEN_CODEC_TYPES_HELPERS_REFERENCES_VALIDATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "dogen.codec/types/entities/reference_graph_data.hpp"

namespace dogen::codec::helpers {

/**
 * @brief Checks that there are no cycles in the references graph.
 */
class references_validator final {
private:
    /**
     * @brief Trivial struct that records all the data we need for our
     * little DFS excursion.
     *
     * We need the set because we want to know if we've been somewhere
     * before, and we need the list just so we can print a useful
     * error message for the user with the complete path that contains
     * the cycle.
     */
    struct dfs_data {
        std::unordered_set<std::string> set;
        std::list<std::string> list;
    };

private:
    static void dfs_visit(const std::string& vertex,
        const std::unordered_map<std::string, std::list<std::string>>&
        edges_per_model, dfs_data dd = dfs_data());

public:
    static void validate(const entities::reference_graph_data& rgd);
};

}

#endif
