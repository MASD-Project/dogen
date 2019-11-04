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

const std::string found_cycle("References graph has a cycle: ");

inline std::string print_cycle(std::stack<std::string> stack) {
    /*
     * Stack contains the cycle but its in reverse order of
     * dependencies. We need to revert it first in order to print it
     * in a way users can understand.
     */
    std::list<std::string> reverse;
    while(!stack.empty()) {
        reverse.push_front(stack.top());
        stack.pop();
    }

    std::ostringstream s;
    bool is_first(true);
    for (const auto& v : reverse) {
        if (!is_first)
            s << " -> ";
        else
            is_first = false;
        s << v;
    }

    return s.str();
}

}

namespace dogen::injection::helpers {

void circular_references_validator::dfs_visit(const std::string& vertex,
    const std::unordered_map<std::string, std::list<std::string>>&
    edges_per_model, dfs_data dd) {
    /*
     * Every time we enter this method we are making a copy of the DFS
     * data. This is just so that we keep track of our descent, but
     * once we start back-tracking, we let the multiple copies at each
     * stack level do the back-tracking for us.
     */
    dd.stack.push(vertex);
    BOOST_LOG_SEV(lg, trace) << "Entering model: " << vertex
                             << ". Stack depth: " << dd.stack.size();

    /*
     * We do not expect to see a model name repeated on a given DFS
     * descent.
     */
    const auto inserted(dd.set.insert(vertex).second);
    if (!inserted) {
        const auto s(print_cycle(dd.stack));
        BOOST_LOG_SEV(lg, error) << "Detected a references cycle: " << s;
        BOOST_THROW_EXCEPTION(circular_references_exception(found_cycle + s));
    }

    /*
     * Now, if there are any edges for this model, visit each one of
     * them.
     */
    const auto i(edges_per_model.find(vertex));
    if (i != edges_per_model.end()) {
        for(const auto& child_id : i->second) {
            BOOST_LOG_SEV(lg, trace) << "Reference: " << child_id;
            dfs_visit(child_id, edges_per_model, dd);
        }
    } else
        BOOST_LOG_SEV(lg, trace) << "No references found.";

    BOOST_LOG_SEV(lg, trace) << "Exiting model: " << vertex << " Stack depth: "
                             << dd.stack.size();
}

void circular_references_validator::
    validate(const meta_model::reference_graph_data& rgd) {
    BOOST_LOG_SEV(lg, debug) << "Checking reference cycles for " << rgd.root();
    BOOST_LOG_SEV(lg, trace) << "Graph data: " << rgd;

    dfs_visit(rgd.root(), rgd.edges_per_model());
    BOOST_LOG_SEV(lg, debug) << "No cycles found.";
}

}
