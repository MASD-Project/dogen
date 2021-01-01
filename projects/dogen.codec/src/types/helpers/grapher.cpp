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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <boost/graph/depth_first_search.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.codec/types/helpers/graphing_error.hpp"
#include "dogen.codec/types/helpers/grapher.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("codec.helpers..grapher"));

const std::string empty;
const std::string root_id("__root__");
const std::string graph_already_generated("Graph has already been generated");
const std::string graph_not_yet_generated("Graph has not yet been generated");
const std::string found_cycle_in_graph("Graph has a cycle: ");

}

namespace dogen::codec::helpers {

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
        state_->stream_ << "(" << g[u].id();
    }

    void back_edge(graph_type::edge_descriptor e, const graph_type& g) {
        const auto id(g[target(e, g)].id());
        state_->stream_ << "(" << id;
        BOOST_LOG_SEV(lg, error) << found_cycle_in_graph
                                 << id << ". Graph as sexp: "
                                 << state_->stream_.str();

        BOOST_THROW_EXCEPTION(graphing_error(found_cycle_in_graph + id));
    }

    const std::string sexp() { return state_->stream_.str(); }

private:
    std::shared_ptr<state> state_;
};

}

grapher::grapher()
    : generated_(false), root_vertex_(boost::add_vertex(graph_)) {
    entities::object root;
    root.id(::root_id);
    graph_[root_vertex_] = root;
    id_to_vertex_.insert(std::make_pair(::root_id, root_vertex_));
}

std::string grapher::root_id() {
    return ::root_id;
}

grapher::vertex_descriptor_type
grapher::vertex_for_id(const std::string& id) {
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

void grapher::require_not_generated() const {
    if (is_generated()) {
        BOOST_LOG_SEV(lg, error) << graph_already_generated;
        BOOST_THROW_EXCEPTION(graphing_error(graph_already_generated));
    }
}

void grapher::require_generated() const {
    if (!is_generated()) {
        BOOST_LOG_SEV(lg, error) << graph_not_yet_generated;
        BOOST_THROW_EXCEPTION(graphing_error(graph_not_yet_generated));
    }
}

void grapher::
process_child_node(const vertex_descriptor_type& v, const entities::object& o) {
    if (!o.container_id().empty()) {
        const std::string id(o.container_id());
        const auto cv(vertex_for_id(id));
        boost::add_edge(v, cv, graph_);
        BOOST_LOG_SEV(lg, debug) << "Creating edge between '"
                                 << o.id() << "' and '" << id << "'";

        const auto k(orphanage_.find(id));
        if (k != orphanage_.end()) {
            BOOST_LOG_SEV(lg, debug) << "Object is no longer orphan: "
                                     << id << "'";
            orphanage_.erase(k);
        }
        connected_ids_.insert(id);
    }

    if (connected_ids_.find(o.id()) == connected_ids_.end()) {
        orphanage_.insert(std::make_pair(o.id(), v));
        BOOST_LOG_SEV(lg, debug) << "Vertex for object joined orphanage: "
                                 << o.id();
    }
}

void grapher::process_connections(const entities::object& o) {
    BOOST_LOG_SEV(lg, debug) << "Processing connections for object: '"
                             << o.id() << "' of type: '"
                             << o.object_type() << "'";

    const auto parent_id(o.connection()->first);
    const auto child_id(o.connection()->second);

    const auto parent_vertex(vertex_for_id(parent_id));
    const auto child_vertex(vertex_for_id(child_id));
    connected_ids_.insert(parent_id);
    boost::add_edge(child_vertex, parent_vertex, graph_);
    BOOST_LOG_SEV(lg, debug) << "Created edge between '" << child_id
                             << "' and: '" << parent_id << "'";

    parent_id_to_child_ids_[parent_id].push_back(child_id);
    if (connected_ids_.find(child_id) == connected_ids_.end()) {
        orphanage_.insert(std::make_pair(child_id, child_vertex));
        BOOST_LOG_SEV(lg, debug) << "Vertex for object joined orphanage: "
                                 << child_id;
    }

    const auto k(orphanage_.find(parent_id));
    if (k != orphanage_.end()) {
        BOOST_LOG_SEV(lg, debug) << "Object is no longer orphan: "
                                 << k->first << "'";
        orphanage_.erase(k);
    }
}

void grapher::add(const entities::object& po) {
    require_not_generated();

    if (po.connection()) {
        process_connections(po);
        return;
    }

    const auto v(vertex_for_id(po.id()));
    graph_[v] = po;
    process_child_node(v, po);
}

const graph_type& grapher::graph() const {
    require_generated();
    return graph_;
}

const std::unordered_map<std::string, std::list<std::string>>&
grapher::parent_id_to_child_ids() const {
    require_generated();
    return parent_id_to_child_ids_;
}

void grapher::generate() {
    BOOST_LOG_SEV(lg, debug) << "Generating graph.";
    require_not_generated();

    BOOST_LOG_SEV(lg, debug) << "Processing orphan vertices.";
    for (const auto& pair : orphanage_) {
        BOOST_LOG_SEV(lg, debug) << "Connecting root to '" << pair.first << "'";
        boost::add_edge(root_vertex_, pair.second, graph_);
    }

    cycle_detector cd;
    boost::depth_first_search(graph_, boost::visitor(cd));
    BOOST_LOG_SEV(lg, debug) << "Graph has no cycles. Sexp: " << cd.sexp();
    generated_ = true;

    BOOST_LOG_SEV(lg, debug) << "Generated graph.";
}

}
