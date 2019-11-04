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
#include <sstream>
#include <iostream>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.injection/io/meta_model/reference_graph_data_io.hpp"
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

void circular_references_validator::dfs_visit(const std::string& id,
    const std::unordered_map<std::string, std::list<std::string>>&
    edges_per_model,
    const std::unordered_set<std::string>& visited_map,
    const std::stack<std::string>& visited_stack) {
    BOOST_LOG_SEV(lg, trace) << "Model: " << id;
    const auto i(edges_per_model.find(id));
    if (i == edges_per_model.end()) {
        BOOST_LOG_SEV(lg, trace) << "No references found.";
        return;
    }

    for(const auto& child_id : i->second) {
        BOOST_LOG_SEV(lg, trace) << "Reference: " << child_id;
        std::stack<std::string> child_visited_stack(visited_stack);
        child_visited_stack.push(child_id);
        BOOST_LOG_SEV(lg, trace) << "Stack depth: "
                                 << child_visited_stack.size();
        std::unordered_set<std::string> child_visited_map(visited_map);
        const auto inserted(child_visited_map.insert(child_id).second);
        if (!inserted) {
            std::ostringstream s;
            while(!child_visited_stack.empty()) {
                s << child_visited_stack.top();
                child_visited_stack.pop();
                if (!child_visited_stack.empty())
                    s << " -> ";
            }

            const auto msg(s.str());
            BOOST_LOG_SEV(lg, error) << "Detected a references cycle: " << msg;
            BOOST_THROW_EXCEPTION(
                circular_references_exception(found_cycle_in_graph + msg));
        }

        dfs_visit(child_id, edges_per_model, child_visited_map, child_visited_stack);
    }
}

void circular_references_validator::
    validate(const meta_model::reference_graph_data& rgd) {
    BOOST_LOG_SEV(lg, debug) << "Checking reference cycles for " << rgd.root();
    BOOST_LOG_SEV(lg, trace) << "Graph data: " << rgd;

    const std::unordered_set<std::string> visited_map({rgd.root()});
    std::stack<std::string> visited_stack;
    visited_stack.push(rgd.root());
    dfs_visit(rgd.root(), rgd.edges_per_model(), visited_map, visited_stack);
    BOOST_LOG_SEV(lg, debug) << "No cycles found.";
}

}
