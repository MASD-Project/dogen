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
#include <boost/make_shared.hpp>
#include <boost/graph/depth_first_search.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/dynamic/expansion/types/graphing_error.hpp"
#include "dogen/dynamic/expansion/types/grapher.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dynamic.expansion.grapher"));

const std::string root_id("__root__");
const std::string graph_already_built("Graph has already been built");
const std::string graph_not_yet_built("Graph has not yet been built");
const std::string root_already_exists("The root enricher already exists");
const std::string found_cycle_in_graph("Graph has a cycle: ");

}

namespace dogen {
namespace dynamic {
namespace expansion {

// FIXME: hack for now
class root_expander : public expander_interface {
public:
    std::string name() const override { return ::root_id; }

    const std::forward_list<std::string>& dependencies() const override {
        static auto r = std::forward_list<std::string> {};
        return r;
    }

    void setup(const expansion_context&) override { }

    void expand(const sml::qname&, const schema::scope_types&,
        schema::object&) const override { }
};

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
        const auto id(g[u]->name());
        state_->stream_ << "(" << id;
    }

    void back_edge(graph_type::edge_descriptor e, const graph_type& g) {
        const auto id(g[target(e, g)]->name());
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

grapher::grapher()
    : built_(false), root_vertex_(boost::add_vertex(graph_)) {
    graph_[root_vertex_] = boost::make_shared<root_expander>();
    expander_name_to_vertex_.insert(std::make_pair(::root_id, root_vertex_));
}

grapher::vertex_descriptor_type
grapher::vertex_for_expander(const std::string& n) {
    const auto i(expander_name_to_vertex_.find(n));
    if (i != expander_name_to_vertex_.end()) {
        BOOST_LOG_SEV(lg, debug) << "Vertex already exists: " << n;
        return i->second;
    }

    const auto r(boost::add_vertex(graph_));
    expander_name_to_vertex_.insert(std::make_pair(n, r));
    BOOST_LOG_SEV(lg, debug) << "Created vertex: " << n;
    return r;
}

void grapher::require_not_built() const {
    if (is_built()) {
        BOOST_LOG_SEV(lg, error) << graph_already_built;
        BOOST_THROW_EXCEPTION(graphing_error(graph_already_built));
    }
}

void grapher::require_built() const {
    if (!is_built()) {
        BOOST_LOG_SEV(lg, error) << graph_not_yet_built;
        BOOST_THROW_EXCEPTION(graphing_error(graph_not_yet_built));
    }
}

void grapher::add(boost::shared_ptr<expander_interface> e) {
    require_not_built();

    const auto v(vertex_for_expander(e->name()));
    graph_[v] = e;

    const auto i(non_orphans_.find(e->name()));
    if (i == non_orphans_.end()) {
        orphanage_.insert(std::make_pair(e->name(), v));
    }

    for (const auto d : e->dependencies()) {
        non_orphans_.insert(d);
        const auto k(orphanage_.find(d));
        if (k != orphanage_.end()) {
            orphanage_.erase(k);
        }

        const vertex_descriptor_type dv(vertex_for_expander(d));
        boost::add_edge(v, dv, graph_);

        BOOST_LOG_SEV(lg, debug) << "Creating edge between '"
                                 << e->name() << "' and '" << d << "'";
    }
}

void grapher::generate() {
    BOOST_LOG_SEV(lg, debug) << "Building graph.";
    require_not_built();

    BOOST_LOG_SEV(lg, debug) << "Processing orphan vertices.";
    for (const auto& pair : orphanage_) {
        BOOST_LOG_SEV(lg, debug) << "Connecting root to '" << pair.first << "'";
        boost::add_edge(root_vertex_, pair.second, graph_);
    }

    cycle_detector v;
    boost::depth_first_search(graph_, boost::visitor(v));
    BOOST_LOG_SEV(lg, debug) << "Graph has no cycles. Sexp: " << v.sexp();
    built_ = true;

    BOOST_LOG_SEV(lg, debug) << "Built graph.";
}

const graph_type& grapher::graph() const {
    return graph_;
}

} } }
