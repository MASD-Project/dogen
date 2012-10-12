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
#include <string>
#include <sstream>
#include <algorithm>
#include <functional>
#include <boost/lexical_cast.hpp>
#include <boost/optional.hpp>
#include <boost/tokenizer.hpp>
#include <boost/range/combine.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm/set_algorithm.hpp>
#include <boost/variant/get.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <boost/graph/depth_first_search.hpp>
#include "dogen/dia/domain/composite.hpp"
#include "dogen/dia/domain/attribute.hpp"
#include "dogen/dia/utility/dia_utility.hpp"
#include "dogen/dia/io/object_io.hpp"
#include "dogen/dia/io/diagram_io.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/generator/modeling/transformation_error.hpp"
#include "dogen/generator/modeling/dia_to_sml.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dia_to_sml"));

using dogen::generator::modeling::transformation_error;

const char* delimiter = "::";
const std::string dia_name("name");
const std::string dia_type("type");
const std::string dia_attributes("attributes");
const std::string dia_uml_attribute("umlattribute");
const std::string dia_string("string");
const std::string dia_composite("composite");

const std::string hash_character("#");
const std::string unexpected_number_of_connections(
    "Expected 2 connections but found: ");
const std::string relationship_target_not_found(
    "Relationship points to object with non-existent ID: ");
const std::string uml_attribute_expected("UML atttribute expected");
const std::string name_attribute_expected("Could not find name attribute");
const std::string type_attribute_expected("Could not find type attribute");
const std::string empty_dia_object_name("Dia object name is empty");
const std::string error_parsing_object_type("Fail to parse object type: ");
const std::string parent_not_found("Object has a parent but its not defined: ");
const std::string root_vertex_id("root");
const std::string unexpected_attribute_value_size(
    "Unexpected attribute value size: ");
const std::string unexpected_attribute_value_type(
    "Did not find expected attribute value type: ");

class dia_dfs_visitor : public boost::default_dfs_visitor {
private:
    struct visit_state {
        visit_state(const std::string& model_name,
            const std::list<std::string>& external_package_path,
            bool verbose, bool is_target,
            const std::unordered_map<std::string, std::string> child_to_parent)
            : model_name_(model_name),
              external_package_path_(external_package_path),
              verbose_(verbose), is_target_(is_target),
              child_to_parent_(child_to_parent) { }

        const std::string model_name_;
        std::unordered_map<dogen::sml::qualified_name, dogen::sml::pod> pods_;
        std::unordered_map<dogen::sml::qualified_name, dogen::sml::primitive>
        primitives_;
        std::unordered_map<dogen::sml::qualified_name, dogen::sml::package>
        packages_;
        std::list<std::string> package_path_;
        const std::list<std::string> external_package_path_;
        const bool verbose_;
        const bool is_target_;
        const std::unordered_map<std::string, std::string> child_to_parent_;
        std::unordered_map<std::string, dogen::sml::qualified_name>
        dia_id_to_qname_;
    };

public:
    dia_dfs_visitor() = delete;
    dia_dfs_visitor& operator=(const dia_dfs_visitor&) = default;
    dia_dfs_visitor(const dia_dfs_visitor&) = default;
    dia_dfs_visitor(dia_dfs_visitor&&) = default;

public:
    dia_dfs_visitor(const std::string& model_name,
        const std::string& external_package_path,
        bool verbose, bool is_target,
        const std::vector<dogen::dia::object>& relationships)
        : state_(new visit_state(model_name,
                split_delimited_string(external_package_path), verbose,
                is_target, setup_child_to_parent(relationships))) { }

private:
    std::unordered_map<std::string, std::string>
    setup_child_to_parent(
        const std::vector<dogen::dia::object>& relationships) const {

        std::unordered_map<std::string, std::string> r;
        for (const auto relationship : relationships) {
            using dogen::dia::object_types;
            object_types ot(parse_object_type(relationship.type()));
            if (ot == object_types::uml_generalization) {
                const auto connections(relationship.connections());
                const auto parent(connections.front());
                const auto child(connections.back());

                r.insert(std::make_pair(child.to(), parent.to()));
            }
        }
        return r;
    }

    std::list<std::string>
    split_delimited_string(const std::string& str) const {
        const boost::char_separator<char> sep(delimiter);
        boost::tokenizer<boost::char_separator<char> > tokens(str, sep);

        std::list<std::string> r;
        boost::copy(tokens, std::inserter(r, r.end()));
        return r;
    }

public:
    template<typename Vertex, typename Graph>
    void discover_vertex(const Vertex& u, const Graph& g) {
        process_dia_object(g[u]);
    }

    template<typename Vertex, typename Graph>
    void finish_vertex(const Vertex& u, const Graph& g) {
        pop_package_path(g[u]);
    }

public:
    std::unordered_map<dogen::sml::qualified_name, dogen::sml::pod>
    pods() const {
        return state_->pods_;
    }

    std::unordered_map<dogen::sml::qualified_name, dogen::sml::primitive>
    primitives() const {
        return state_->primitives_;
    }

    std::unordered_map<dogen::sml::qualified_name, dogen::sml::package>
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
    template<typename AttributeValue>
    AttributeValue
    attribute_value(const dogen::dia::attribute::attribute_value& v,
        const std::string& description) const {

        AttributeValue r;
        try {
            r = boost::get<AttributeValue>(v);
        } catch (const boost::bad_get&) {
            BOOST_LOG_SEV(lg, error) << unexpected_attribute_value_type
                                     << description;
            throw transformation_error(unexpected_attribute_value_type +
                description);
        }
        return r;
    }

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
    dogen::sml::qualified_name
    transform_qualified_name(const dogen::dia::attribute& attribute,
        dogen::sml::meta_types meta_type) const;

    /**
     * @brief Parses a Dia type string, generating an SML qualified
     * name from it.
     */
    dogen::sml::qualified_name
    transform_qualified_name(const std::string& type_string) const;

    /**
     * @brief Converts a package in Dia format into a package in SML
     * format.
     *
     * @param object Dia object which contains a UML package.
     */
    std::pair<dogen::sml::qualified_name, dogen::sml::package>
    transform_package(const dogen::dia::object& object);

    /**
     * @brief Converts a Dia composite storing the UML attribute into
     * an SML property
     *
     * @param uml_attribute the Dia UML attribute
     */
    dogen::sml::property
    transform_property(const dogen::dia::composite& uml_attribute) const;

    /**
     * @brief Converts a class in Dia format into a pod in SML
     * format.
     *
     * @param object Dia object which contains a UML class.
     */
    std::pair<dogen::sml::qualified_name, dogen::sml::pod>
    transform_pod(const dogen::dia::object& object) const;

    /**
     * @brief Processes any type of Dia object.
     *
     * @param object Any Dia object, including the dummy root object.
     */
    void process_dia_object(const dogen::dia::object& object);

    /**
     * @brief If the object is a package, pushes its name to the
     * package path.
     *
     * @param object Any Dia object, including the dummy root object.
     */
    void push_package_path(const dogen::dia::object& object);

    /**
     * @brief If the object is a package, pops its name from the
     * package path.
     *
     * @param object Any Dia object, including the dummy root object.
     */
    void pop_package_path(const dogen::dia::object& object);

    /**
     * @brief Parses a string representing an object type into its enum.
     *
     * @param s string with an object type
     */
    dogen::dia::object_types parse_object_type(const std::string s) const;

private:
    std::shared_ptr<visit_state> state_;
};

std::string dia_dfs_visitor::
transform_string_attribute(const dogen::dia::attribute& a) const {
    const auto values(a.values());
    if (values.size() != 1) {
        BOOST_LOG_SEV(lg, error) << "Expected attribute to have one"
                                 << " value but found " << values.size();
        throw transformation_error(unexpected_attribute_value_size +
            boost::lexical_cast<std::string>(values.size()));
    }

    using dogen::dia::string;
    const auto v(attribute_value<string>(values.front(), dia_string));
    std::string name(v.value());
    boost::erase_all(name, hash_character);
    boost::trim(name);
    return name;
}

dogen::sml::qualified_name
dia_dfs_visitor::transform_qualified_name(const std::string& type_string) const {
    dogen::sml::qualified_name result;

    if (std::string::npos == type_string.find(delimiter)) {
        result.type_name(type_string);
        return result;
    }

    const boost::char_separator<char> sep(delimiter);
    boost::tokenizer<boost::char_separator<char> > tokens(type_string, sep);

    std::list<std::string> token_list;
    std::copy(tokens.begin(), tokens.end(), std::back_inserter(token_list));

    result.model_name(token_list.back());
    token_list.pop_back();

    result.type_name(token_list.front());
    token_list.pop_front();

    if (!token_list.empty())
        result.package_path(token_list);

    return result;
}

dogen::sml::qualified_name dia_dfs_visitor::
transform_qualified_name(const dogen::dia::attribute& a,
    dogen::sml::meta_types meta_type) const {
    if (a.name() != dia_name) {
        BOOST_LOG_SEV(lg, error) << name_attribute_expected;
        throw transformation_error(name_attribute_expected);
    }

    dogen::sml::qualified_name name;
    name.model_name(state_->model_name_);
    name.meta_type(meta_type);
    name.external_package_path(state_->external_package_path_);
    name.package_path(state_->package_path_);

    name.type_name(transform_string_attribute(a));
    if (name.type_name().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_dia_object_name;
        throw transformation_error(empty_dia_object_name);
    }
    return name;
}

std::pair<dogen::sml::qualified_name, dogen::sml::package>
dia_dfs_visitor::transform_package(const dogen::dia::object& o) {
    dogen::sml::package package;

    for (auto a : o.attributes()) {
        if (a.name() == dia_name) {
            using dogen::sml::meta_types;
            package.name(transform_qualified_name(a, meta_types::package));
        }
    }

    if (package.name().type_name().empty()) {
        throw transformation_error(name_attribute_expected + o.id());
        BOOST_LOG_SEV(lg, error) << name_attribute_expected + o.id();
    }

    return std::make_pair(package.name(), package);
}

dogen::sml::property dia_dfs_visitor::
transform_property(const dogen::dia::composite& uml_attribute) const {
    dogen::sml::property property;
    typedef boost::shared_ptr<dogen::dia::attribute> attribute_ptr;

    for (const attribute_ptr a : uml_attribute.value()) {
        if (a->name() == dia_name)
            property.name(transform_string_attribute(*a));
        else if (a->name() == dia_type) {
            const std::string s(transform_string_attribute(*a));
            property.type_name(transform_qualified_name(s));
        } else {
            BOOST_LOG_SEV(lg, warn) << "Ignoring unexpected attribute: "
                                    << a->name();
        }
    }

    if (property.name().empty()) {
        BOOST_LOG_SEV(lg, error) << "Could not find a name attribute.";
        throw transformation_error(name_attribute_expected);
    }

    if (property.type_name().type_name().empty()) {
        BOOST_LOG_SEV(lg, error) << "Could not find a type attribute.";
        throw transformation_error(type_attribute_expected);
    }

    return property;
}

std::pair<dogen::sml::qualified_name, dogen::sml::pod>
dia_dfs_visitor::transform_pod(const dogen::dia::object& o) const {
    dogen::sml::pod pod;

    pod.generate(state_->is_target_);
    for (auto attribute : o.attributes()) {
        BOOST_LOG_SEV(lg, debug) << "Found attribute: " << attribute.name();

        if (attribute.name() == dia_name) {
            using dogen::sml::meta_types;
            pod.name(transform_qualified_name(attribute, meta_types::pod));
        }

        if (attribute.name() == dia_attributes) {
            const auto values(attribute.values());

            if (values.empty()) {
                BOOST_LOG_SEV(lg, debug) << "Attribute is empty.";
                continue;
            }

            std::vector<dogen::sml::property> properties;
            for (auto v : values) {
                using dogen::dia::composite;
                const auto c(attribute_value<composite>(v, dia_composite));

                if (c.type() != dia_uml_attribute) {
                    BOOST_LOG_SEV(lg, error) << "Expected composite type "
                                             << " to be " << dia_uml_attribute
                                             << "but was " << c.type();
                    throw transformation_error(uml_attribute_expected);
                }
                BOOST_LOG_SEV(lg, debug) << "Found composite of type "
                                         << c.type();
                properties.push_back(transform_property(c));
            }
            pod.properties(properties);
        }
    }

    if (pod.name().type_name().empty()) {
        BOOST_LOG_SEV(lg, error) << name_attribute_expected + o.id();
        throw transformation_error(name_attribute_expected + o.id());
    }

    const auto i(state_->child_to_parent_.find(o.id()));
    if (i != state_->child_to_parent_.end()) {
        const auto j(state_->dia_id_to_qname_.find(i->second));
        if (j == state_->dia_id_to_qname_.end()) {
            BOOST_LOG_SEV(lg, error) << "Object has a parent but "
                                     << " there is no QName mapping defined."
                                     << " Child ID: '" << o.id()
                                     << "' Parent ID: '" << i->second << "'";
            throw transformation_error(parent_not_found + o.id());
        }
        pod.parent_name(j->second);
    }
    return std::make_pair(pod.name(), pod);
}

dogen::dia::object_types dia_dfs_visitor::
parse_object_type(const std::string s) const {
    dogen::dia::object_types r;
    try {
        using dogen::dia::utility::parse_object_type;
        r = parse_object_type(s);
    } catch(const std::exception& e) {
        std::ostringstream stream;
        stream << error_parsing_object_type << "'" << s
               << "'. Error: " << e.what();
        BOOST_LOG_SEV(lg, error) << stream.str();
        throw transformation_error(stream.str());
    }
    return r;
}

void dia_dfs_visitor::push_package_path(const dogen::dia::object& o) {
    if (o.id() == root_vertex_id)
        return; // root is a dummy object, ignore it.

    using dogen::dia::object_types;
    object_types ot(parse_object_type(o.type()));
    if (ot != object_types::uml_large_package)
        return; // only packages contribute to the package path

    bool found_name(false);
    for (auto a : o.attributes()) {
        found_name = a.name() == dia_name;
        if (found_name) {
            BOOST_LOG_SEV(lg, debug) << "Updating package_path: " << o.id();
            state_->package_path_.push_back(transform_string_attribute(a));
            break;
        }
    }

    if (!found_name) {
        BOOST_LOG_SEV(lg, error) << name_attribute_expected + o.id();
        throw transformation_error(name_attribute_expected + o.id());
    }
}

void dia_dfs_visitor::pop_package_path(const dogen::dia::object& o) {
    if (o.id() == root_vertex_id)
        return; // root is a dummy object, ignore it.

    using dogen::dia::object_types;
    object_types ot(parse_object_type(o.type()));
    if (ot != object_types::uml_large_package)
        return; // only packages contribute to the package path

    state_->package_path_.pop_back();
}

void dia_dfs_visitor::process_dia_object(const dogen::dia::object& o) {
    if (o.id() == root_vertex_id)
        return; // root is a dummy object, ignore it.

    using dogen::dia::object_types;
    object_types ot(parse_object_type(o.type()));
    if (ot == object_types::uml_large_package) {
        BOOST_LOG_SEV(lg, debug) << "Processing uml_large_package: "
                                 << o.id();
        state_->packages_.insert(transform_package(o));
        push_package_path(o);
    } else if (ot == object_types::uml_class) {
        BOOST_LOG_SEV(lg, debug) << "Processing uml_class: " << o.id();
        const auto p(transform_pod(o));
        state_->pods_.insert(p);
        state_->dia_id_to_qname_.insert(std::make_pair(o.id(), p.first));
    }
}

}

namespace dogen {
namespace generator {
namespace modeling {

dia_to_sml::
dia_to_sml(const dia::diagram& diagram, const std::string& model_name,
    const std::string& external_package_path, bool is_target, bool verbose)
    : diagram_(diagram),
      model_name_(model_name),
      external_package_path_(external_package_path),
      root_vertex_(boost::add_vertex(graph_)),
      is_target_(is_target),
      verbose_(verbose) {

    id_to_vertex_.insert(std::make_pair(root_vertex_id, root_vertex_));
    dia::object root;
    root.id(root_vertex_id);
    graph_[root_vertex_] = root;
}

void dia_to_sml::
setup_data_structures(const std::vector<dia::object>& objects) {
    auto lambda([&](const std::string& id) -> vertex_descriptor_type {
            const auto i(id_to_vertex_.find(id));
            if (i != id_to_vertex_.end())
                return i->second;

            const auto vertex(boost::add_vertex(graph_));
            id_to_vertex_.insert(std::make_pair(id, vertex));
            return vertex;
        });

    std::unordered_map<std::string, vertex_descriptor_type> orphans;
    for (const auto o : objects) {
        if (!o.connections().empty()) {
            relationships_.push_back(o);
            continue;
        }

        const vertex_descriptor_type vertex(lambda(o.id()));
        graph_[vertex] = o;
        if (!o.child_node()) {
            orphans.insert(std::make_pair(o.id(), vertex));
            continue;
        }

        const std::string parent_id(o.child_node()->parent());
        const vertex_descriptor_type parent_vertex(lambda(parent_id));
        boost::add_edge(parent_vertex, vertex, graph_);
        BOOST_LOG_SEV(lg, debug) << "Adding object to graph: " << o.id()
                                 << " Parent ID: " << parent_id;
    }

    for (const auto o : relationships_) {
        BOOST_LOG_SEV(lg, debug) << "Processing connections for object: '"
                                 << o.id() << "' of type: '"
                                 << o.type()
                                 << "'";

        const auto connections(o.connections());
        if (connections.size() != 2) {
            BOOST_LOG_SEV(lg, error) << unexpected_number_of_connections
                                     << connections.size();

            throw transformation_error(unexpected_number_of_connections +
                boost::lexical_cast<std::string>(connections.size()));
        }

        const auto parent(connections.front());
        const auto p(id_to_vertex_.find(parent.to()));
        if (p == id_to_vertex_.end()) {
            BOOST_LOG_SEV(lg, error) << relationship_target_not_found
                                     << parent.to();

            throw transformation_error(relationship_target_not_found +
                parent.to());
        }

        const auto child(connections.back());
        const auto c(id_to_vertex_.find(child.to()));
        if (c == id_to_vertex_.end()) {
            BOOST_LOG_SEV(lg, error) << relationship_target_not_found
                                     << child.to();

            throw transformation_error(relationship_target_not_found +
                child.to());
        }

        BOOST_LOG_SEV(lg, debug) << "Connecting parent '"
                                 << parent.to() << "' to child: '"
                                 << child.to()
                                 << "'";
        boost::add_edge(p->second, c->second, graph_);

        const auto k(orphans.find(child.to()));
        if (k != orphans.end()) {
            BOOST_LOG_SEV(lg, debug) << "Object is no longer orphan: "
                                     << k->first << "'";
            orphans.erase(k);
        }
    }

    for (const auto o : orphans) {
        BOOST_LOG_SEV(lg, debug) << "Connecting root to '" << o.first << "'";
        boost::add_edge(root_vertex_, o.second, graph_);
    }
}

sml::model dia_to_sml::transform() {
    BOOST_LOG_SEV(lg, info) << "Transforming diagram: " << model_name_;
    BOOST_LOG_SEV(lg, debug) << "Contents: " << diagram_;

    for (dia::layer layer : diagram_.layers())
        setup_data_structures(layer.objects());

    const std::string epp(external_package_path_);
    dia_dfs_visitor v(model_name_, epp, verbose_, is_target_, relationships_);
    boost::depth_first_search(graph_, boost::visitor(v));

    using sml::model;
    return model(model_name_, v.packages(), v.pods(), v.primitives(),
        v.external_package_path());
}

} } }
