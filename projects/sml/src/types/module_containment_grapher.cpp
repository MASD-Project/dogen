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
#include "dogen/sml/types/graphing_error.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/types/module_containment_grapher.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("sml.module_containment_grapher"));

const std::string empty;
const std::string graph_already_built("Graph has already been built");
const std::string graph_not_yet_built("Graph has not yet been built");
const std::string root_already_exists("The root enricher already exists");
const std::string root_has_dependencies(
    "The root enricher cannot have dependencies");
const std::string found_cycle_in_graph("Graph has a cycle: ");

}

namespace dogen {
namespace sml {

module_containment_grapher::module_containment_grapher() : built_(false) { }

module_containment_grapher::vertex_descriptor_type
module_containment_grapher::vertex_for_qname(const qname& qn) {
    const auto i(qname_to_vertex_.find(qn));
    if (i != qname_to_vertex_.end()) {
        BOOST_LOG_SEV(lg, debug) << "Vertex already exists: " << qn;
        return i->second;
    }

    const auto r(boost::add_vertex(graph_));
    qname_to_vertex_.insert(std::make_pair(qn, r));
    BOOST_LOG_SEV(lg, debug) << "Created vertex: " << qn;

    return r;
}

void module_containment_grapher::require_not_built() const {
    if (is_built()) {
        BOOST_LOG_SEV(lg, error) << graph_already_built;
        BOOST_THROW_EXCEPTION(graphing_error(graph_already_built));
    }
}

void module_containment_grapher::require_built() const {
    if (!is_built()) {
        BOOST_LOG_SEV(lg, error) << graph_not_yet_built;
        BOOST_THROW_EXCEPTION(graphing_error(graph_not_yet_built));
    }
}

void module_containment_grapher::add(const qname& target,
    const boost::optional<qname>& containing_module) {
    require_not_built();

    const auto v(vertex_for_qname(target));
    graph_[v] = target;

    if (containing_module) {
        const vertex_descriptor_type cmv(vertex_for_qname(*containing_module));
        boost::add_edge(v, cmv, graph_);

        BOOST_LOG_SEV(lg, debug) << "Creating edge between '"
                                 << target.simple_name() << "' and '"
                                 << containing_module->simple_name() << "'";
    }
}

void module_containment_grapher::build() {
    require_not_built();
    built_ = true;
    BOOST_LOG_SEV(lg, debug) << "Built graph.";
}

const module_containment_graph& module_containment_grapher::graph() const {
    return graph_;
}

} }
