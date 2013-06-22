/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/utility/log/logger.hpp"
#include "dogen/dia_to_sml/io/object_types_io.hpp"
#include "dogen/dia_to_sml/types/graphing_error.hpp"
#include "dogen/dia_to_sml/types/grapher.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dia_to_sml.grapher"));

const std::string empty;
const std::string root_id("__root__");
const std::string error_add_after_build("Cannot add object after building");
const std::string error_not_built("Graph has not yet been built");
const std::string found_cycle_in_graph("Graph has a cycle: ");

}

namespace dogen {
namespace dia_to_sml {

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
        state_->stream_ << "(" << g[target(e, g)].id();
        BOOST_LOG_SEV(lg, error) << found_cycle_in_graph
                                 << g[target(e, g)].id() << ". Graph as sexp: "
                                 << state_->stream_.str();

        BOOST_THROW_EXCEPTION(graphing_error(found_cycle_in_graph +
                boost::lexical_cast<std::string>(g[target(e, g)].id())));
    }

    const std::string sexp() { return state_->stream_.str(); }

private:
    std::shared_ptr<state> state_;
};

grapher::grapher()
    : built_(false), root_vertex_(boost::add_vertex(graph_)) {
    processed_object root;
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

void grapher::ensure_not_built() const {
    if (built_) {
        BOOST_LOG_SEV(lg, error) << error_add_after_build;
        BOOST_THROW_EXCEPTION(graphing_error(error_add_after_build));
    }
}

void grapher::ensure_built() const {
    if (!built_) {
        BOOST_LOG_SEV(lg, error) << error_not_built;
        BOOST_THROW_EXCEPTION(graphing_error(error_not_built));
    }
}

bool grapher::is_relevant(const object_types ot) const {
    return
        ot == object_types::uml_large_package ||
        ot == object_types::uml_generalization ||
        ot == object_types::uml_class ||
        ot == object_types::uml_note;
}

void grapher::
process_child_node(const vertex_descriptor_type& v, const processed_object& o) {
    if (!o.child_node_id().empty()) {
        const std::string id(o.child_node_id());
        const vertex_descriptor_type cv(vertex_for_id(id));
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

void grapher::process_connections(const processed_object& o) {
    BOOST_LOG_SEV(lg, debug) << "Processing connections for object: '"
                             << o.id() << "' of type: '"
                             << o.object_type() << "'";

    const auto parent_id(o.connection()->first);
    const auto child_id(o.connection()->second);

    const auto parent_vertex(vertex_for_id(parent_id));
    const auto child_vertex(vertex_for_id(child_id));
    parent_ids_.insert(parent_id);
    connected_ids_.insert(parent_id);
    boost::add_edge(child_vertex, parent_vertex, graph_);
    BOOST_LOG_SEV(lg, debug) << "Created edge between '" << child_id
                             << "' and: '" << parent_id << "'";

    auto i(child_to_parents_.find(child_id));
    if (i == child_to_parents_.end()) {
        std::list<std::string> l = { parent_id };
        child_to_parents_.insert(std::make_pair(child_id, l));
        BOOST_LOG_SEV(lg, debug) << "First parent for Child: " << child_id;

    } else {
        i->second.push_back(parent_id);
        BOOST_LOG_SEV(lg, debug) << "Child has more than one parent: "
                                 << child_id;
    }

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

void grapher::add(const processed_object& o) {
    ensure_not_built();

    if (!is_relevant(o.object_type()))
        return;

    const bool is_package(o.object_type() == object_types::uml_large_package);
    if (is_package && o.child_node_id().empty())
        top_level_module_names_.insert(o.name());

    if (o.connection()) {
        process_connections(o);
        return;
    }

    const auto v(vertex_for_id(o.id()));
    graph_[v] = o;
    process_child_node(v, o);
}

const graph_type& grapher::graph() const {
    ensure_built();
    return graph_;
}

const grapher::child_to_parents_type& grapher::
child_to_parents() const {
    ensure_built();
    return child_to_parents_;
}

const std::unordered_set<std::string>& grapher::parent_ids() const {
    ensure_built();
    return parent_ids_;
}

const std::unordered_set<std::string>& grapher::
top_level_module_names() const {
    ensure_built();
    return top_level_module_names_;
}

void grapher::build() {
    BOOST_LOG_SEV(lg, debug) << "Processing orphan vertices.";
    for (const auto& pair : orphanage_) {
        BOOST_LOG_SEV(lg, debug) << "Connecting root to '" << pair.first << "'";
        boost::add_edge(root_vertex_, pair.second, graph_);
    }

    cycle_detector v;
    boost::depth_first_search(graph_, boost::visitor(v));
    BOOST_LOG_SEV(lg, debug) << "Graph has no cycles. Sexp: " << v.sexp();
    built_ = true;
}

} }
