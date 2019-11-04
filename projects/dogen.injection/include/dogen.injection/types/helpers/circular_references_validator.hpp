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
#ifndef DOGEN_INJECTION_TYPES_HELPERS_CIRCULAR_REFERENCES_VALIDATOR_HPP
#define DOGEN_INJECTION_TYPES_HELPERS_CIRCULAR_REFERENCES_VALIDATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_set>
#include <unordered_map>
#include "dogen.injection/types/meta_model/reference_graph_data.hpp"

namespace dogen::injection::helpers {

/**
 * @brief Checks that there are no cycles in the references graph.
 */
class circular_references_validator final {
private:
    static void dfs_visit(const std::string& id,
        const std::unordered_map<std::string, std::list<std::string>>&
        edges_per_model,
        const std::unordered_set<std::string>& visited);

public:
    static void validate(const meta_model::reference_graph_data& rgd);
};

}

#endif
