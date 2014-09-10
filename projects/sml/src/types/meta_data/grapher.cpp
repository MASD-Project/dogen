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
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/types/meta_data/root_enricher.hpp"
#include "dogen/sml/types/meta_data/graphing_error.hpp"
#include "dogen/sml/types/meta_data/grapher.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("sml.meta_data.grapher"));

const std::string empty;
const std::string graph_already_built("Graph has already been built");
const std::string graph_not_yet_built("Graph has not yet been built");
const std::string found_cycle_in_graph("Graph has a cycle: ");

}

namespace dogen {
namespace sml {
namespace meta_data {

grapher::grapher() : built_(false), root_vertex_(boost::add_vertex(graph_)),
                     root_(std::make_shared<root_enricher>()) {

    graph_[root_vertex_] = root_;
    id_to_vertex_.insert(std::make_pair(root_->id(), root_vertex_));
}

grapher::vertex_descriptor_type grapher::vertex_for_id(const std::string& id) {
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

void grapher::add(std::shared_ptr<enricher_interface> e) {
    require_not_built();

    const auto v(vertex_for_id(e->id()));
    graph_[v] = e;

    if (e->dependencies().empty())
        orphanage_[e->id()] = v;
    else {
        for (const auto& d : e->dependencies()) {
            const vertex_descriptor_type cv(vertex_for_id(d));
            boost::add_edge(v, cv, graph_);

            BOOST_LOG_SEV(lg, debug) << "Creating edge between '"
                                     << e->id() << "' and '" << d << "'";
        }
    }
}

void grapher::build() {
    require_not_built();

    BOOST_LOG_SEV(lg, debug) << "Processing orphan vertices.";
    for (const auto& pair : orphanage_) {
        BOOST_LOG_SEV(lg, debug) << "Connecting root '" << root_->id()
                                 << "' to '" << pair.first << "'";
        boost::add_edge(root_vertex_, pair.second, graph_);
    }
}

const graph_type& grapher::graph() const {
    require_built();
    return graph_;
}

} } }
