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
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <boost/graph/depth_first_search.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/dia_to_sml/types/enum_parser.hpp"
#include "dogen/dia_to_sml/io/object_types_io.hpp"
#include "dogen/dia_to_sml/types/building_error.hpp"
#include "dogen/dia_to_sml/types/graph_builder.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dia_to_sml.graph_builder"));

const std::string empty;
const std::string root_id("__root__");

// FIXME: hacks just to read the package name
const std::string hash_character("#");
const std::string dia_name("name");
const std::string dia_string("string");

const std::string unexpected_attribute_value_type(
    "Did not find expected attribute value type: ");

template<typename AttributeValue, typename Variant>
AttributeValue
attribute_value(const Variant& v, const std::string& desc) {

    AttributeValue r;
    try {
        r = boost::get<AttributeValue>(v);
    } catch (const boost::bad_get&) {
        BOOST_LOG_SEV(lg, error) << unexpected_attribute_value_type << desc;

        BOOST_THROW_EXCEPTION(
            dogen::dia_to_sml::building_error(
                unexpected_attribute_value_type + desc));
    }
    return r;
}
// FIXME: end hacks just to read the package name

// error messages
const std::string error_add_after_build("Cannot add object after building");
const std::string error_not_built("Graph has not yet been built");
const std::string error_parsing_object_type("Fail to parse object type: ");
const std::string unexpected_number_of_connections(
    "Expected 2 connections but found: ");
const std::string found_cycle_in_graph("Graph has a cycle: ");
const std::string unexpected_attribute_value_size(
    "Unexpected attribute value size: ");

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

        BOOST_THROW_EXCEPTION(building_error(found_cycle_in_graph +
                boost::lexical_cast<std::string>(g[target(e, g)].id())));
    }

    const std::string sexp() { return state_->stream_.str(); }

private:
    std::shared_ptr<state> state_;
};

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
    if (i != id_to_vertex_.end()) {
        BOOST_LOG_SEV(lg, debug) << "Vertex already exists: " << id;
        return i->second;
    }

    const auto r(boost::add_vertex(graph_));
    id_to_vertex_.insert(std::make_pair(id, r));
    BOOST_LOG_SEV(lg, debug) << "Created vertex: " << id;

    return r;
}

void graph_builder::ensure_not_built() const {
    if (built_)
        throw building_error(error_add_after_build);
}

void graph_builder::ensure_built() const {
    if (!built_)
        throw building_error(error_not_built);
}

object_types graph_builder::object_type(const dia::object& o) const {
    object_types r(object_types::invalid);

    try {
        r = enum_parser::parse_object_type(o.type());
    } catch(const std::exception& e) {
        std::ostringstream stream;
        stream << error_parsing_object_type << "'" << o.type()
               << "'. Error: " << e.what();

        BOOST_LOG_SEV(lg, error) << stream.str();
        BOOST_THROW_EXCEPTION(building_error(stream.str()));
    }
    return r;
}

std::string graph_builder::object_name(const dia::object& o) const {
    for (auto a : o.attributes()) {
        BOOST_LOG_SEV(lg, debug) << "Found attribute: " << a.name();

        // FIXME: Quick hack just to be able to build package list.
        if (a.name() == dia_name) {
            const auto values(a.values());
            if (values.size() != 1) {
                BOOST_LOG_SEV(lg, error) << "Expected attribute to have one"
                                         << " value but found "
                                         << values.size();

                BOOST_THROW_EXCEPTION(
                    building_error(unexpected_attribute_value_size +
                        boost::lexical_cast<std::string>(values.size())));
            }

            using dia::string;
            const auto v(attribute_value<string>(values.front(), dia_string));
            std::string name(v.value());
            boost::erase_first(name, hash_character);
            boost::erase_last(name, hash_character);
            boost::trim(name);
            return name;
        }
    }
    return empty;
}

bool graph_builder::is_relevant(const object_types ot) const {
    return
        ot == object_types::uml_large_package ||
        ot == object_types::uml_generalization ||
        ot == object_types::uml_class;
}

void graph_builder::
process_child_node(const vertex_descriptor_type& v, const dia::object& o) {
    if (o.child_node()) {
        const std::string id(o.child_node()->parent());
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

void graph_builder::process_connections(const dia::object& o) {
    const auto connections(o.connections());
    if (connections.size() != 2) {
        const auto size(boost::lexical_cast<std::string>(connections.size()));
        BOOST_LOG_SEV(lg, error) << unexpected_number_of_connections << size;
        BOOST_THROW_EXCEPTION(
            building_error(unexpected_number_of_connections + size));
    }

    const auto parent(connections.front());
    const auto child(connections.back());
    BOOST_LOG_SEV(lg, debug) << "Processing connections for object: '"
                             << o.id() << "' of type: '" << o.type() << "'";

    const auto parent_vertex(vertex_for_id(parent.to()));
    const auto child_vertex(vertex_for_id(child.to()));
    parent_ids_.insert(parent.to());
    connected_ids_.insert(parent.to());
    boost::add_edge(child_vertex, parent_vertex, graph_);
    BOOST_LOG_SEV(lg, debug) << "Created edge between '" << child.to()
                             << "' and: '" << parent.to() << "'";

    const auto pair(std::make_pair(child.to(), parent.to()));
    const bool key_exists(!child_to_parent_.insert(pair).second);

    if (key_exists) {
        std::ostringstream ss;
        ss << "Child has more than one parent: '"
           << child.to() << "'. Multiple inheritance "
           << "is not supported.";

        BOOST_LOG_SEV(lg, error) << ss.str();
        BOOST_THROW_EXCEPTION(building_error(ss.str()));
    }

    if (connected_ids_.find(child.to()) == connected_ids_.end()) {
        orphanage_.insert(std::make_pair(child.to(), parent_vertex));
        BOOST_LOG_SEV(lg, debug) << "Vertex for object joined orphanage: "
                                 << o.id();
    }

    const auto k(orphanage_.find(parent.to()));
    if (k != orphanage_.end()) {
        BOOST_LOG_SEV(lg, debug) << "Object is no longer orphan: "
                                 << k->first << "'";
        orphanage_.erase(k);
    }
}

void graph_builder::add(const dia::object& o) {
    ensure_not_built();

    const auto ot(object_type(o));
    if (!is_relevant(ot))
        return;

    if (ot == object_types::uml_large_package && !o.child_node())
        top_level_package_names_.insert(object_name(o));

    if (o.connections().empty()) {
        const auto v(vertex_for_id(o.id()));
        graph_[v] = o;
        process_child_node(v, o);
        return;
    }
    process_connections(o);
}

const graph_type& graph_builder::graph() const {
    ensure_built();
    return graph_;
}

const std::unordered_map<std::string, std::string>& graph_builder::
child_to_parent() const {
    ensure_built();
    return child_to_parent_;
}

const std::unordered_set<std::string>& graph_builder::parent_ids() const {
    ensure_built();
    return parent_ids_;
}

const std::unordered_set<std::string>& graph_builder::
top_level_package_names() const {
    ensure_built();
    return top_level_package_names_;
}

void graph_builder::build() {
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
