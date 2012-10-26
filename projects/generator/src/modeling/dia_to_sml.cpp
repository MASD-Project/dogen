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
#include <boost/range/combine.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm/set_algorithm.hpp>
#include <boost/variant/get.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <boost/graph/depth_first_search.hpp>
#include "dogen/dia/domain/composite.hpp"
#include "dogen/dia/domain/attribute.hpp"
#include "dogen/dia/domain/object_types.hpp"
#include "dogen/dia/domain/stereotypes.hpp"
#include "dogen/dia/io/object_types_io.hpp"
#include "dogen/dia/io/stereotypes_io.hpp"
#include "dogen/dia/utility/dia_utility.hpp"
#include "dogen/dia/io/object_io.hpp"
#include "dogen/dia/io/diagram_io.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/generator/modeling/transformation_error.hpp"
#include "dogen/generator/modeling/dia_object_to_sml_package.hpp"
#include "dogen/generator/modeling/identifier_parser.hpp"
#include "dogen/generator/modeling/dia_to_sml.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dia_to_sml"));

using dogen::generator::modeling::transformation_error;

const std::string empty;
const std::string dia_name("name");
const std::string dia_type("type");
const std::string dia_attributes("attributes");
const std::string dia_uml_attribute("umlattribute");
const std::string dia_string("string");
const std::string dia_composite("composite");
const std::string dia_stereotype("stereotype");
const std::string dia_documentation("comment");

const std::string hash_character("#");
const std::string unexpected_number_of_connections(
    "Expected 2 connections but found: ");
const std::string relationship_target_not_found(
    "Relationship points to object with non-existent ID: ");
const std::string uml_attribute_expected("UML atttribute expected");
const std::string name_attribute_expected("Could not find name attribute");
const std::string type_attribute_expected("Could not find type attribute");
const std::string empty_dia_object_name("Dia object name is empty");
const std::string missing_package_for_id("Missing package for dia object ID: ");
const std::string error_parsing_object_type("Fail to parse object type: ");
const std::string parent_not_found("Object has a parent but its not defined: ");
const std::string root_vertex_id("root");
const std::string unexpected_attribute_value_size(
    "Unexpected attribute value size: ");
const std::string unexpected_attribute_value_type(
    "Did not find expected attribute value type: ");
const std::string unexpected_child_node(
    "Non UML package object has a child node: ");

/**
 * @brief Parses a string representing an object type into its enum.
 *
 * @param s string with an object type
 */
dogen::dia::object_types parse_object_type(const std::string s) {
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

/**
 * @brief Parses a string representing a stereotype into its enum
 *
 * @param s string with a stereotype
 */
dogen::dia::stereotypes parse_stereotype(const std::string s) {
    dogen::dia::stereotypes r;
    try {
        using dogen::dia::utility::parse_stereotype;
        r = parse_stereotype(s);
    } catch(const std::exception& e) {
        std::ostringstream stream;
        stream << error_parsing_object_type << "'" << s
               << "'. Error: " << e.what();
        BOOST_LOG_SEV(lg, error) << stream.str();
        throw transformation_error(stream.str());
    }
    return r;
}

class dia_dfs_visitor : public boost::default_dfs_visitor {
private:
    struct visit_state {
        visit_state(const std::string& model_name,
            const std::list<std::string>& external_package_path,
            bool verbose, bool is_target,
            const std::unordered_map<std::string, std::string>& child_to_parent,
            const std::unordered_set<std::string>& parent_ids,
            const std::unordered_map<std::string, dogen::sml::package>&
            packages_by_id)
            : model_name_(model_name),
              external_package_path_(external_package_path),
              verbose_(verbose), is_target_(is_target),
              child_to_parent_(child_to_parent),
              parent_ids_(parent_ids),
              packages_by_id_(packages_by_id) { }

        const std::string model_name_;
        std::unordered_map<dogen::sml::qualified_name, dogen::sml::pod> pods_;
        std::unordered_map<dogen::sml::qualified_name, dogen::sml::primitive>
        primitives_;
        const std::list<std::string> external_package_path_;
        const bool verbose_;
        const bool is_target_;
        const std::unordered_map<std::string, std::string> child_to_parent_;
        const std::unordered_set<std::string> parent_ids_;
        const std::unordered_map<std::string, dogen::sml::package>
        packages_by_id_;
        std::unordered_map<std::string, dogen::sml::qualified_name>
        dia_id_to_qname_;
    };

public:
    dia_dfs_visitor() = delete;
    dia_dfs_visitor& operator=(const dia_dfs_visitor&) = default;
    dia_dfs_visitor(const dia_dfs_visitor&) = default;
    dia_dfs_visitor(dia_dfs_visitor&&) = default;

private:
    typedef dogen::generator::modeling::identifier_parser identifier_parser;

public:
    dia_dfs_visitor(const std::string& model_name,
        const std::string& external_package_path,
        bool verbose, bool is_target,
        const std::unordered_map<std::string, std::string>& child_to_parent,
        const std::unordered_set<std::string>& parent_ids,
        const std::unordered_map<std::string, dogen::sml::package>&
        packages_by_id)
        : state_(new visit_state(model_name,
                identifier_parser::parse_scoped_name(external_package_path),
                verbose, is_target, child_to_parent, parent_ids,
                packages_by_id)) { }

public:
    template<typename Vertex, typename Graph>
    void discover_vertex(const Vertex& u, const Graph& g) {
        process_dia_object(g[u]);
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
        dogen::sml::meta_types meta_type, const std::string& pkg_id) const;

    /**
     * @brief Parses a Dia type string, generating an SML qualified
     * name from it.
     */
    dogen::sml::qualified_name
    transform_qualified_name(const std::string& type_string) const;

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

dogen::sml::qualified_name dia_dfs_visitor::
transform_qualified_name(const dogen::dia::attribute& a,
    dogen::sml::meta_types meta_type, const std::string& pkg_id) const {
    if (a.name() != dia_name) {
        BOOST_LOG_SEV(lg, error) << name_attribute_expected;
        throw transformation_error(name_attribute_expected);
    }

    dogen::sml::qualified_name name;
    name.model_name(state_->model_name_);
    name.meta_type(meta_type);
    name.external_package_path(state_->external_package_path_);

    if (!pkg_id.empty()) {
        const auto i(state_->packages_by_id_.find(pkg_id));
        if (i == state_->packages_by_id_.end()) {
            BOOST_LOG_SEV(lg, error) << missing_package_for_id << pkg_id;
            throw transformation_error(missing_package_for_id + pkg_id);
        }
        auto pp(i->second.name().package_path());
        pp.push_back(i->second.name().type_name());
        name.package_path(pp);
    }

    name.type_name(transform_string_attribute(a));
    if (name.type_name().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_dia_object_name;
        throw transformation_error(empty_dia_object_name);
    }
    return name;
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
            property.type_name(identifier_parser::parse_qualified_name(s));
        } else if (a->name() == dia_documentation) {
            const std::string doc(transform_string_attribute(*a));
            property.documentation(doc);
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
    pod.category_type(dogen::sml::category_types::user_defined);
    for (auto attribute : o.attributes()) {
        BOOST_LOG_SEV(lg, debug) << "Found attribute: " << attribute.name();

        if (attribute.name() == dia_name) {
            const std::string pkg_id(o.child_node() ?
                o.child_node()->parent() : empty);
            using dogen::sml::meta_types;
            pod.name(transform_qualified_name(attribute, meta_types::pod,
                    pkg_id));
        }

        if (attribute.name() == dia_documentation) {
            const std::string doc(transform_string_attribute(attribute));
            pod.documentation(doc);
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

    const auto j(state_->parent_ids_.find(o.id()));
    pod.is_parent(j != state_->parent_ids_.end());

    return std::make_pair(pod.name(), pod);
}

void dia_dfs_visitor::process_dia_object(const dogen::dia::object& o) {
    if (o.id() == root_vertex_id)
        return; // root is a dummy object, ignore it.

    using dogen::dia::object_types;
    object_types ot(parse_object_type(o.type()));
    if (ot == object_types::uml_class) {
        BOOST_LOG_SEV(lg, debug) << "Processing uml_class: " << o.id();

        for (auto a : o.attributes()) {
            if (a.name() == dia_stereotype) {
                using dogen::dia::stereotypes;
                const std::string v(transform_string_attribute(a));
                if (!v.empty()) {
                    const auto st(parse_stereotype(v));
                    if (st == stereotypes::enumeration) {
                        BOOST_LOG_SEV(lg, debug) << "Class is an enumeration.";
                        return;
                    }
                }
            }
        }
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
      verbose_(verbose),
      package_transformer_(model_name_, external_package_path_, verbose_) {

    BOOST_LOG_SEV(lg, debug) << "Initialised with configuration:"
                             << " model_name: " << model_name_
                             << " external_package_path: "
                             << external_package_path_
                             << " is_target: " << is_target_
                             << " verbose: " << verbose_;

    id_to_vertex_.insert(std::make_pair(root_vertex_id, root_vertex_));
    dia::object root;
    root.id(root_vertex_id);
    graph_[root_vertex_] = root;
}

void dia_to_sml::
setup_data_structures(const std::vector<dia::object>& objects) {
    BOOST_LOG_SEV(lg, debug) << "Setting up data structures";

    auto lambda([&](const std::string& id) -> vertex_descriptor_type {
            const auto i(id_to_vertex_.find(id));
            if (i != id_to_vertex_.end())
                return i->second;

            const auto vertex(boost::add_vertex(graph_));
            id_to_vertex_.insert(std::make_pair(id, vertex));
            return vertex;
        });

    std::unordered_map<std::string, vertex_descriptor_type> orphans;
    std::vector<dogen::dia::object> relationships;
    for (const auto o : objects) {
        if (package_transformer_.is_uml_package(o)) {
            package_transformer_.add_object(o);
            continue;
        }

        if (!o.connections().empty()) {
            relationships.push_back(o);
            continue;
        }

        const vertex_descriptor_type vertex(lambda(o.id()));
        graph_[vertex] = o;
        orphans.insert(std::make_pair(o.id(), vertex));
    }

    for (const auto r : relationships) {
        BOOST_LOG_SEV(lg, debug) << "Processing connections for object: '"
                                 << r.id() << "' of type: '"
                                 << r.type()
                                 << "'";

        using dogen::dia::object_types;
        object_types ot(parse_object_type(r.type()));
        if (ot != object_types::uml_generalization) {
            BOOST_LOG_SEV(lg, warn) << "Ignoring type: '" << r.type() << "'";
            continue;
        }

        const auto connections(r.connections());
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
        parent_dia_ids_.insert(parent.to());

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
        const auto pair(std::make_pair(child.to(), parent.to()));
        const bool key_exists(!child_to_parent_dia_ids_.insert(pair).second);

        if (key_exists) {
            std::ostringstream ss;
            ss << "Child has more than one parent: '"
               << child.to() << "'. Multiple inheritance "
               << "is not supported.";

            BOOST_LOG_SEV(lg, error) << ss.str();
            throw transformation_error(ss.str());
        }

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
    packages_by_id_ = package_transformer_.transform();

    const std::string epp(external_package_path_);
    dia_dfs_visitor v(model_name_, epp, verbose_, is_target_,
        child_to_parent_dia_ids_, parent_dia_ids_, packages_by_id_);
    boost::depth_first_search(graph_, boost::visitor(v));

    std::unordered_map<dogen::sml::qualified_name, dogen::sml::package>
        packages;
    for (const auto p : packages_by_id_)
        packages.insert(std::make_pair(p.second.name(), p.second));

    // FIXME
    std::unordered_map<dogen::sml::qualified_name, dogen::sml::enumeration>
        enumerations;

    using sml::model;
    return model(model_name_, packages, v.pods(), v.primitives(), enumerations,
        v.external_package_path());
}

} } }
