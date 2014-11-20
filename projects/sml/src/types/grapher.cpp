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
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/graph/depth_first_search.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/sml/types/graphing_error.hpp"
#include "dogen/sml/types/grapher.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("sml.grapher"));

const std::string empty;
const std::string graph_already_built("Graph has already been built");
const std::string graph_not_yet_built("Graph has not yet been built");
const std::string root_already_exists("The root enricher already exists");
const std::string root_has_dependencies(
    "The root enricher cannot have dependencies");
const std::string found_cycle_in_graph("Graph has a cycle: ");
const std::string scope_operator("::");

}

namespace dogen {
namespace sml {

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
    std::list<std::string> to_list(const sml::qname& qn) const {
        std::list<std::string> r(qn.external_module_path());

        if (!qn.model_name().empty())
            r.push_back(qn.model_name());

        const auto mp(qn.module_path());
        r.insert(r.end(), mp.begin(), mp.end());
        r.push_back(qn.simple_name());

        return r;
    }

    std::string name_as_string(const sml::qname& qn) const {
        std::list<std::string> l(to_list(qn));
        return boost::algorithm::join(l, scope_operator);
    }


    template<typename Vertex, typename Graph>
    void finish_vertex(const Vertex&, const Graph&) {
        state_->stream_ << ")";
    }

    template<typename Vertex, typename Graph>
    void discover_vertex(const Vertex& u, const Graph& g) {
        const auto id(name_as_string(g[u]));
        state_->stream_ << "(" << id;
    }

    void back_edge(graph_type::edge_descriptor e, const graph_type& g) {
        const auto id(name_as_string(g[target(e, g)]));
        state_->stream_ << "(" << id;
        BOOST_LOG_SEV(lg, error) << found_cycle_in_graph
                                 << id << ". Graph as sexp: "
                                 << state_->stream_.str();

        BOOST_THROW_EXCEPTION(graphing_error(found_cycle_in_graph +
                boost::lexical_cast<std::string>(id)));
    }

    const std::string sexp() { return state_->stream_.str(); }

private:
    std::shared_ptr<state> state_;
};

grapher::grapher() : built_(false) { }

grapher::vertex_descriptor_type
grapher::vertex_for_qname(const qname& qn) {
    const auto i(qname_to_vertex_.find(qn));
    if (i != qname_to_vertex_.end()) {
        BOOST_LOG_SEV(lg, debug) << "Vertex already exists: "
                                 << sml::string_converter::convert(qn);
        return i->second;
    }

    const auto r(boost::add_vertex(graph_));
    qname_to_vertex_.insert(std::make_pair(qn, r));
    BOOST_LOG_SEV(lg, debug) << "Created vertex: "
                             << sml::string_converter::convert(qn);

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

void grapher::add(const qname& target,
    const boost::optional<qname>& containing_module) {
    require_not_built();

    const auto v(vertex_for_qname(target));
    graph_[v] = target;

    if (containing_module) {
        const auto& cm(*containing_module);
        const vertex_descriptor_type cmv(vertex_for_qname(cm));
        boost::add_edge(v, cmv, graph_);

        using sml::string_converter;
        BOOST_LOG_SEV(lg, debug) << "Creating edge between '"
                                 << string_converter::convert(target)
                                 << "' and '" << string_converter::convert(cm)
                                 << "'";
    }
}

void grapher::build() {
    BOOST_LOG_SEV(lg, debug) << "Building graph.";
    require_not_built();

    cycle_detector v;
    boost::depth_first_search(graph_, boost::visitor(v));
    BOOST_LOG_SEV(lg, debug) << "Graph has no cycles. Sexp: " << v.sexp();
    built_ = true;

    BOOST_LOG_SEV(lg, debug) << "Built graph.";
}

const graph_type& grapher::graph() const {
    return graph_;
}

} }
