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
#include "dogen.injection/io/entities/reference_graph_data_io.hpp"
#include "dogen.injection/types/helpers/reference_validation_error.hpp"
#include "dogen.injection/types/helpers/references_validator.hpp"

namespace {

const std::string
transform_id("injection.helpers.references_validator");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string found_cycle("References graph has a cycle: ");
const std::string found_duplicate("Duplicate reference: ");
const std::string found_self_reference("Model references itself: ");

inline std::string print_path(std::list<std::string> list) {
    std::ostringstream s;
    bool is_first(true);
    for (const auto& v : list) {
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

void references_validator::dfs_visit(const std::string& vertex,
    const std::unordered_map<std::string, std::list<std::string>>&
    edges_per_model, dfs_data dd) {
    /*
     * Every time we enter this method we are making a copy of the DFS
     * data. This is just so that we keep track of our descent, but
     * once we start back-tracking, we let the multiple copies at each
     * stack level do the hard work of the data back-tracking for us.
     *
     * The list contains the cycle in the order of the descend. This
     * allows us to print it in a way users can understand.
     */
    dd.list.push_back(vertex);
    BOOST_LOG_SEV(lg, trace) << "Entering model: '" << vertex
                             << "'. Stack depth: " << dd.list.size();

    /*
     * We do not expect to see a model name repeated on a given DFS
     * descent.
     */
    const auto inserted(dd.set.insert(vertex).second);
    if (!inserted) {
        const auto p(print_path(dd.list));
        BOOST_LOG_SEV(lg, error) << found_cycle << p;
        BOOST_THROW_EXCEPTION(reference_validation_error(found_cycle + p));
    }

    /*
     * If there are any edges for this model, visit each one of
     * them. While we're at it, check to see if there are any
     * duplicate references.
     */
    const auto i(edges_per_model.find(vertex));
    if (i != edges_per_model.end()) {
        std::unordered_set<std::string> references;
        for(const auto& child_vertex : i->second) {
            BOOST_LOG_SEV(lg, trace) << "Reference: " << child_vertex;

            /*
             * Check for references to "self". This happens sometimes
             * by mistake, and if allowed to continue, could cause
             * really bizarre errors further down the pipeline.
             */
            if (child_vertex == vertex) {
                const auto s(print_path(dd.list));
                BOOST_LOG_SEV(lg, error) << found_self_reference << s;
                BOOST_THROW_EXCEPTION(
                    reference_validation_error(found_self_reference + s));
            }

            const auto inserted(references.insert(child_vertex).second);
            if (!inserted) {
                /*
                 * If we find a duplicate reference, we "force"-push
                 * it into the path, just so we have a nice way to
                 * explain to the user where the duplicate is. This is
                 * useful if it is nested far down in the DFS visit.
                 */
                dd.list.push_back(child_vertex);
                const auto s(print_path(dd.list));
                BOOST_LOG_SEV(lg, error) << found_duplicate << s;
                BOOST_THROW_EXCEPTION(
                    reference_validation_error(found_duplicate + s));
            }

            dfs_visit(child_vertex, edges_per_model, dd);
        }
    } else
        BOOST_LOG_SEV(lg, trace) << "No references found.";

    BOOST_LOG_SEV(lg, trace) << "Exiting model: '" << vertex
                             << "'. Stack depth: " << dd.list.size();
}

void references_validator::
    validate(const entities::reference_graph_data& rgd) {
    BOOST_LOG_SEV(lg, debug) << "Checking reference cycles for " << rgd.root();
    BOOST_LOG_SEV(lg, trace) << "Graph data: " << rgd;

    dfs_visit(rgd.root(), rgd.edges_per_model());
    BOOST_LOG_SEV(lg, debug) << "No cycles found.";
}

}
