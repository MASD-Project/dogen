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
#include "dogen/dia_to_sml/types/building_error.hpp"
#include "dogen/dia_to_sml/types/graph_builder.hpp"

namespace {

/**
 * @brief String representation of the root vertex ID graph.
 */
const std::string root_id("__root__");
const std::string error_add_after_build("Cannot add object after building");

}

namespace dogen {
namespace dia_to_sml {

graph_builder::graph_builder()
    : built_(false), root_vertex_(boost::add_vertex(graph_)) {
    dia::object root;
    root.id(::root_id);
    graph_[root_vertex_] = root;
    id_to_vertex_.insert(std::make_pair(::root_id, root_vertex_));
}

std::string graph_builder::root_id() {
    return ::root_id;
}

graph_builder::vertex_descriptor_type
graph_builder::vertex_for_id(const std::string& id) {
    const auto i(id_to_vertex_.find(id));
    if (i != id_to_vertex_.end())
        return i->second;

    const auto r(boost::add_vertex(graph_));
    id_to_vertex_.insert(std::make_pair(id, r));
    return r;
}

const graph_type& graph_builder::build() {
    built_ = true;
    return graph_;
}

void graph_builder::ensure_not_built() const {
    if (built_)
        throw building_error(error_add_after_build);
}

void graph_builder::add(const dia::object& o) {
    ensure_not_built();
    const auto v(vertex_for_id(o.id()));
    graph_[v] = o;
}

} }
