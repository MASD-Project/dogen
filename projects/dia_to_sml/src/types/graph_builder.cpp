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
#include "dogen/dia/types/enum_parser.hpp"
#include "dogen/dia/types/object_types.hpp"
#include "dogen/dia/io/object_types_io.hpp"
#include "dogen/dia_to_sml/types/building_error.hpp"
#include "dogen/dia_to_sml/types/graph_builder.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dia_to_sml.graph_builder"));

/**
 * @brief String representation of the root vertex ID graph.
 */
const std::string root_id("__root__");

// error messages
const std::string error_add_after_build("Cannot add object after building");
const std::string error_parsing_object_type("Fail to parse object type: ");
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

bool graph_builder::is_relevant(const dia::object& o) const {
    using dia::object_types;
    object_types ot(object_types::invalid);

    try {
        using dogen::dia::enum_parser;
        ot = enum_parser::parse_object_type(o.type());
    } catch(const std::exception& e) {
        std::ostringstream stream;
        stream << error_parsing_object_type << "'" << o.type()
               << "'. Error: " << e.what();

        BOOST_LOG_SEV(lg, error) << stream.str();
        BOOST_THROW_EXCEPTION(building_error(stream.str()));
    }

    return
        ot == object_types::uml_large_package ||
        ot == object_types::uml_generalization ||
        ot == object_types::uml_class;
}

void graph_builder::add(const dia::object& o) {
    ensure_not_built();

    if (!is_relevant(o))
        return;

    const auto v(vertex_for_id(o.id()));
    graph_[v] = o;
}

} }
