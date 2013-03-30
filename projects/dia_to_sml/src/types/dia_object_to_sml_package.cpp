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
#include <boost/variant/get.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/dia/types/enum_parser.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/dia_to_sml/types/transformation_error.hpp"
#include "dogen/dia_to_sml/types/dia_object_to_sml_package.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dia_to_sml.dia_object_to_sml_package"));

using dogen::dia_to_sml::transformation_error;

const std::string root_vertex_id("root");
const std::string hash_character("#");
const std::string dia_string("string");
const std::string dia_name("name");
const std::string dia_uml_attribute("umlattribute");
const std::string uml_attribute_expected("UML atttribute expected");
const std::string empty_dia_object_name("Dia object name is empty");
const std::string name_attribute_expected("Could not find name attribute");
const std::string error_parsing_object_type("Fail to parse object type: ");
const std::string unexpected_attribute_value_size(
    "Unexpected attribute value size: ");
const std::string unexpected_attribute_value_type(
    "Did not find expected attribute value type: ");

/**
 * @brief Parses a string representing an object type into its enum.
 *
 * @param s string with an object type
 */
dogen::dia::object_types parse_object_type(const std::string s) {
    dogen::dia::object_types r;
    try {
        using dogen::dia::enum_parser;
        r = enum_parser::parse_object_type(s);
    } catch(const std::exception& e) {
        std::ostringstream stream;
        stream << error_parsing_object_type << "'" << s
               << "'. Error: " << e.what();
        BOOST_LOG_SEV(lg, error) << stream.str();
        BOOST_THROW_EXCEPTION(transformation_error(stream.str()));
    }
    return r;
}

class dia_dfs_visitor : public boost::default_dfs_visitor {
private:
    struct visit_state {
        visit_state(const std::string& model_name,
            const std::list<std::string>& external_package_path,
            bool verbose)
            : model_name_(model_name),
              external_package_path_(external_package_path),
              verbose_(verbose) { }

        const std::string model_name_;
        std::unordered_map<std::string, dogen::sml::package> packages_;
        std::list<std::string> package_path_;
        const std::list<std::string> external_package_path_;
        const bool verbose_;
    };

public:
    dia_dfs_visitor() = delete;
    dia_dfs_visitor& operator=(const dia_dfs_visitor&) = default;
    dia_dfs_visitor(const dia_dfs_visitor&) = default;
    dia_dfs_visitor(dia_dfs_visitor&&) = default;

public:
    dia_dfs_visitor(const std::string& model_name,
        const std::list<std::string>& external_package_path,
        bool verbose)
        : state_(new visit_state(model_name, external_package_path, verbose)) {
    }

public:
    template<typename Vertex, typename Graph>
    void discover_vertex(const Vertex& u, const Graph& g) {
        push_package_path(g[u]);
    }

    template<typename Vertex, typename Graph>
    void finish_vertex(const Vertex& u, const Graph& g) {
        pop_package_path(g[u]);
    }

public:
    std::unordered_map<std::string,  dogen::sml::package>
    packages() const {
        return state_->packages_;
    }

    std::list<std::string> package_path() const {
        return state_->package_path_;
    }

    std::list<std::string> external_package_path() const {
        return state_->external_package_path_;
    }

private:
    /**
     * @brief Parses a Dia string attribute, removing any invalid formatting.
     */
    std::string
    transform_string_attribute(const dogen::dia::attribute& attribute) const;

    /**
     * @brief Converts the Dia attribute into a qualified name.
     *
     * @param attribute Name Dia attribute.
     */
    dogen::sml::qname
    transform_qname(const dogen::dia::attribute& attribute,
        dogen::sml::meta_types meta_type) const;

    /**
     * @brief Converts a package in Dia format into a package in SML
     * format.
     *
     * @param object Dia object which contains a UML package.
     */
    dogen::sml::package transform_package(const dogen::dia::object& object);

    /**
     * @brief Pushes the object's name to the package path.
     *
     * @param object Either the dummy root object or a UML package.
     */
    void push_package_path(const dogen::dia::object& object);

    /**
     * @brief Pops the last name from the package path.
     *
     * @param object Either the dummy root object or a UML package.
     */
    void pop_package_path(const dogen::dia::object& object);

private:
    std::shared_ptr<visit_state> state_;
};

std::string dia_dfs_visitor::
transform_string_attribute(const dogen::dia::attribute& a) const {
    const auto v(a.values());
    if (v.size() != 1) {
        BOOST_LOG_SEV(lg, error) << "Expected attribute to have one"
                                 << " value but found " << v.size();
        BOOST_THROW_EXCEPTION(transformation_error(unexpected_attribute_value_size +
            boost::lexical_cast<std::string>(v.size())));
    }

    dogen::dia::string s;
    try {
        s = boost::get<dogen::dia::string>(v.front());
        std::string name(s.value());
        boost::erase_first(name, hash_character);
        boost::erase_last(name, hash_character);
        boost::trim(name);
        return name;

    } catch (const boost::bad_get&) {
        BOOST_LOG_SEV(lg, error) << unexpected_attribute_value_type
                                 << dia_string;
        BOOST_THROW_EXCEPTION(transformation_error(unexpected_attribute_value_type +
            dia_string));
    }
}

dogen::sml::qname dia_dfs_visitor::
transform_qname(const dogen::dia::attribute& a,
    dogen::sml::meta_types meta_type) const {
    if (a.name() != dia_name) {
        BOOST_LOG_SEV(lg, error) << name_attribute_expected;
        BOOST_THROW_EXCEPTION(transformation_error(name_attribute_expected));
    }

    dogen::sml::qname name;
    name.model_name(state_->model_name_);
    name.meta_type(meta_type);
    name.external_package_path(state_->external_package_path_);
    name.package_path(state_->package_path_);

    name.type_name(transform_string_attribute(a));
    if (name.type_name().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_dia_object_name;
        BOOST_THROW_EXCEPTION(transformation_error(empty_dia_object_name));
    }
    return name;
}

dogen::sml::package
dia_dfs_visitor::transform_package(const dogen::dia::object& o) {
    dogen::sml::package package;

    for (auto a : o.attributes()) {
        if (a.name() == dia_name) {
            using dogen::sml::meta_types;
            package.name(transform_qname(a, meta_types::package));
        }
    }

    if (package.name().type_name().empty()) {
        BOOST_THROW_EXCEPTION(transformation_error(name_attribute_expected + o.id()));
        BOOST_LOG_SEV(lg, error) << name_attribute_expected + o.id();
    }

    return package;
}

void dia_dfs_visitor::push_package_path(const dogen::dia::object& o) {
    if (o.id() == root_vertex_id)
        return; // root is a dummy object, ignore it.

    bool found_name(false);
    for (auto a : o.attributes()) {
        found_name = a.name() == dia_name;
        if (found_name) {
            const auto pkg_name(transform_string_attribute(a));
            BOOST_LOG_SEV(lg, debug) << "Creating package: " << pkg_name;

            dogen::sml::package p;
            using dogen::sml::meta_types;
            p.name(transform_qname(a, meta_types::package));
            state_->packages_.insert(std::make_pair(o.id(), p));

            BOOST_LOG_SEV(lg, debug) << "Updating package_path: " << o.id();
            state_->package_path_.push_back(pkg_name);
            break;
        }
    }

    if (!found_name) {
        BOOST_LOG_SEV(lg, error) << name_attribute_expected + o.id();
        BOOST_THROW_EXCEPTION(transformation_error(name_attribute_expected + o.id()));
    }

}

void dia_dfs_visitor::pop_package_path(const dogen::dia::object& o) {
    if (o.id() == root_vertex_id)
        return; // root is a dummy object, ignore it.

    state_->package_path_.pop_back();
}

}

namespace dogen {
namespace dia_to_sml {

dia_object_to_sml_package::dia_object_to_sml_package(
    const std::string& model_name,
    const std::list<std::string>& external_package_path, bool verbose)
    : model_name_(model_name), external_package_path_(external_package_path),
      root_vertex_(boost::add_vertex(graph_)), verbose_(verbose) {

    dia::object root;
    root.id(root_vertex_id);
    graph_[root_vertex_] = root;
}

bool dia_object_to_sml_package::is_processable(const dia::object& o) const {
    using dogen::dia::object_types;
    object_types ot(parse_object_type(o.type()));
    return ot == object_types::uml_large_package;
}

void dia_object_to_sml_package::add_object(const dia::object& o) {
    BOOST_LOG_SEV(lg, debug) << "Adding package object: " << o.id();

    if (!is_processable(o)) {
        BOOST_LOG_SEV(lg, error) << "Expected composite type "
                                 << " to be " << dia_uml_attribute
                                 << "but was " << o.type();
        BOOST_THROW_EXCEPTION(transformation_error(uml_attribute_expected));

    }

    auto lambda([&](const std::string& id) -> vertex_descriptor_type {
            const auto i(id_to_vertex_.find(id));
            if (i != id_to_vertex_.end())
                return i->second;

            const auto vertex(boost::add_vertex(graph_));
            id_to_vertex_.insert(std::make_pair(id, vertex));
            return vertex;
        });

    const vertex_descriptor_type vertex(lambda(o.id()));
    graph_[vertex] = o;
    if (!o.child_node()) {
        BOOST_LOG_SEV(lg, debug) << "Connecting root to '" << o.id() << "'";
        boost::add_edge(root_vertex_, vertex, graph_);
        return;
    }

    const std::string parent_id(o.child_node()->parent());
    const vertex_descriptor_type parent_vertex(lambda(parent_id));
    boost::add_edge(parent_vertex, vertex, graph_);
    BOOST_LOG_SEV(lg, debug) << "Adding object to graph: " << o.id()
                             << " Parent ID: " << parent_id;
}

std::unordered_map<std::string, sml::package>
dia_object_to_sml_package::transform() {
    BOOST_LOG_SEV(lg, info) << "Transforming packages for diagram: "
                            << model_name_;

    dia_dfs_visitor v(model_name_, external_package_path_, verbose_);
    boost::depth_first_search(graph_, boost::visitor(v));

    return v.packages();
}

} }
