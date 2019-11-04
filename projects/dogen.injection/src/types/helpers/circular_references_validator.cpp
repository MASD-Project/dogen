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
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.injection/types/helpers/circular_references_exception.hpp"
#include "dogen.injection/types/helpers/circular_references_validator.hpp"

namespace {

const std::string
transform_id("injection.helpers.circular_references_validator");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string found_cycle_in_graph("Graph has a cycle: ");

}

namespace dogen::injection::helpers {

void dfs_visit(const std::string& id,
    const std::unordered_map<std::string, std::list<std::string>>&
    edges_per_model,
    const std::unordered_set<std::string>& visited) {
    const auto i(edges_per_model.find(id));
    if (i == edges_per_model.end())
        return;

    for(const auto& child_id : i->second) {
        std::unordered_set<std::string> child_visited(visited);
        const auto inserted(child_visited.insert(child_id).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << "Detected a cycle with:" << child_id;
            BOOST_THROW_EXCEPTION(
                circular_references_exception(found_cycle_in_graph + child_id));
        }

        dfs_visit(child_id, edges_per_model, child_visited);
    }
}

void circular_references_validator::
    validate(const meta_model::reference_graph_data& rgd) {
    BOOST_LOG_SEV(lg, error) << "Checking reference cycles for " << rgd.root();
    const std::unordered_set<std::string> visited({rgd.root()});
    dfs_visit(rgd.root(), rgd.edges_per_model(), visited);
    BOOST_LOG_SEV(lg, error) << "No cycles found.";
}

}
