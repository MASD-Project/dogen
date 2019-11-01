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
#include <boost/graph/depth_first_search.hpp>
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

namespace {

/**
 * @brief Detects cycles in the graph.
 */
class cycle_detector : public boost::default_dfs_visitor {
private:
    struct state {
        std::ostringstream stream_;
    };

public:
    cycle_detector() : state_(new state()) { }

public:
    template<typename Vertex, typename Graph>
    void finish_vertex(const Vertex&, const Graph&) {
        state_->stream_ << ")";
    }

    template<typename Vertex, typename Graph>
    void discover_vertex(const Vertex& u, const Graph& g) {
        state_->stream_ << "(" << g[u];
    }

    void back_edge(graph_type::edge_descriptor e, const graph_type& g) {
        const auto id(g[target(e, g)]);
        state_->stream_ << "(" << id;
        BOOST_LOG_SEV(lg, error) << found_cycle_in_graph
                                 << id << ". Graph as sexp: "
                                 << state_->stream_.str();

        BOOST_THROW_EXCEPTION(
            circular_references_exception(found_cycle_in_graph + id));
    }

    const std::string sexp() { return state_->stream_.str(); }

private:
    std::shared_ptr<state> state_;
};

}

std::unordered_map<std::string, std::list<std::string>>
circular_references_validator::
obtain_references_for_model(const meta_model::model_set& ms) const {
    std::unordered_map<std::string, std::list<std::string>> r;
    r[ms.target().name()] = ms.target().references();
    for (const auto& m : ms.references())
        r[m.name()] = m.references();

    return r;
}

circular_references_validator::vertex_descriptor_type
circular_references_validator::vertex_for_id(const std::string& id) {
    const auto i(id_to_vertex_.find(id));
    if (i != id_to_vertex_.end()) {
        BOOST_LOG_SEV(lg, debug) << "Vertex already exists: " << id;
        return i->second;
    }

    const auto r(boost::add_vertex(graph_));
    id_to_vertex_.insert(std::make_pair(id, r));
    BOOST_LOG_SEV(lg, debug) << "Created vertex: " << id;

    return r;
}


void circular_references_validator::
add_to_graph(const std::string& id,
    const std::unordered_map<std::string, std::list<std::string>>&
    references_for_model) {
    const auto v(vertex_for_id(id));
    const auto i(references_for_model.find(id));
    if (i == references_for_model.end())
        return;

    for(const auto& child_id : i->second) {
        const auto cv(vertex_for_id(child_id));
        boost::add_edge(v, cv, graph_);
        BOOST_LOG_SEV(lg, debug) << "Creating edge between '"
                                 << id << "' and '" << child_id << "'";
        add_to_graph(child_id, references_for_model);
    }
}

void circular_references_validator::validate(const meta_model::model_set& ms) {
    /*
     * Collate all references by model name in this model set.
     */
    const auto rfm(obtain_references_for_model(ms));

    /*
     * Build the graph
     */
    const auto id(ms.target().name());
    add_to_graph(id, rfm);

    /*
     * Check for cycles.
     */
    cycle_detector cd;
    boost::depth_first_search(graph_, boost::visitor(cd));
    BOOST_LOG_SEV(lg, debug) << "Graph has no cycles. Sexp: " << cd.sexp();
}

}
