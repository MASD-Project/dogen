/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <string>
#include <algorithm>
#include <functional>
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
#include "dogen/utility/exception/utility_exception.hpp"
#include "dogen/dia/io/object_io.hpp"
#include "dogen/dia/io/diagram_io.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/generator/modeling/dia_to_sml.hpp"

namespace {

static dogen::utility::log::logger
lg(dogen::utility::log::logger_factory("dia_to_sml"));

const char* delimiter = "::";
const std::string dia_name("name");
const std::string dia_type("type");
const std::string dia_attributes("attributes");
const std::string dia_uml_attribute("umlattribute");
const std::string dia_string("string");
const std::string dia_composite("composite");

const std::string hash_character("#");
const std::string uml_attribute_expected("UML atttribute expected");
const std::string expected_attribute_value_not_found("Expected attribute value: ");
const std::string name_attribute_expected("Could not find name attribute");
const std::string type_attribute_expected("Could not find type attribute");
const std::string invalid_dia_object_name("Dia object name is invalid: ");
const std::string root_vertex_id("root");

struct visit_state {
    std::string model_name;
    std::unordered_map<dogen::sml::qualified_name, dogen::sml::pod> pods;
    std::unordered_map<dogen::sml::qualified_name, dogen::sml::primitive>
    primitives;
    std::unordered_map<dogen::sml::qualified_name, dogen::sml::package>
    packages;
    std::list<std::string> package_path;
    std::list<std::string> external_package_path;
    bool verbose;
    bool is_target;
};

class dia_dfs_visitor : public boost::default_dfs_visitor {
public:
    dia_dfs_visitor() = delete;
    dia_dfs_visitor& operator=(const dia_dfs_visitor&) = default;
    dia_dfs_visitor(const dia_dfs_visitor&) = default;
    dia_dfs_visitor(dia_dfs_visitor&&) = default;

public:
    dia_dfs_visitor(std::shared_ptr<visit_state> state,
        std::string model_name, std::string external_package_path,
        bool verbose, bool is_target) :
        state_(state) {
        state_->model_name = model_name;
        state_->external_package_path =
            split_delimited_string(external_package_path);
        state_->verbose = verbose;
        state_->is_target = is_target;
    }

private:
    std::list<std::string> split_delimited_string(std::string str) const {
        const boost::char_separator<char> sep(delimiter);
        boost::tokenizer<boost::char_separator<char> > tokens(str, sep);

        std::list<std::string> r;
        boost::copy(tokens, std::inserter(r, r.end()));
        return r;
    }

public:
    template<typename Vertex, typename Graph>
    void discover_vertex(Vertex u, const Graph& g) {
        update_package_path(g[u]);
    }

    template<typename Vertex, typename Graph>
    void finish_vertex(Vertex u, const Graph& g) {
        process_dia_object(g[u]);
    }

private:

    template<typename AttributeValue>
    AttributeValue
    attribute_value(dogen::dia::attribute a, std::string description) const {
        AttributeValue value;
        try {
            value = boost::get<AttributeValue>(a.value());
        } catch (const boost::bad_get&) {
            using dogen::utility::exception::exception;
            throw exception(expected_attribute_value_not_found + a.name() +
                " (" + description + ")" );
        }
        return value;
    }

    bool is_attribute_value_empty(dogen::dia::attribute a) const {
        const dogen::dia::attribute::attribute_value v(a.value());
        return boost::get<dogen::dia::empty>(&v) != nullptr;
    }

    /**
     * @brief Parses a Dia string attribute, removing any invalid formatting.
     */
    std::string
    transform_string_attribute(dogen::dia::attribute attribute) const;

    /**
     * @brief Converts the Dia attribute into a qualified name.
     *
     * @param attribute Name Dia attribute.
     */
    dogen::sml::qualified_name
    transform_qualified_name(dogen::dia::attribute attribute,
        dogen::sml::meta_types meta_type) const;

    /**
     * @brief Parses a Dia type string, generating an SML qualified
     * name from it.
     */
    dogen::sml::qualified_name
    transform_qualified_name(std::string type_string) const;

    /**
     * @brief Converts a package in Dia format into a package in SML
     * format.
     *
     * @param object Dia object which contains a UML package.
     */
    std::pair<dogen::sml::qualified_name, dogen::sml::package>
    transform_package(dogen::dia::object object);

    /**
     * @brief Converts a Dia composite storing the UML attribute into
     * an SML property
     *
     * @param uml_attribute the Dia UML attribute
     */
    dogen::sml::property
    transform_property(dogen::dia::composite uml_attribute) const;

    /**
     * @brief Converts a class in Dia format into a pod in SML
     * format.
     *
     * @param object Dia object which contains a UML class.
     */
    std::pair<dogen::sml::qualified_name, dogen::sml::pod>
    transform_pod(dogen::dia::object object);

    /**
     * @brief Processes any type of Dia object.
     *
     * @param object Any Dia object, including the dummy root object.
     */
    void process_dia_object(dogen::dia::object object);

    /**
     * @brief Changes package path to reflect the current object.
     *
     * @param object Any Dia object, including the dummy root object.
     */
    void update_package_path(dogen::dia::object object);

private:
    std::shared_ptr<visit_state> state_;
};

std::string dia_dfs_visitor::
transform_string_attribute(dogen::dia::attribute a) const {
    const auto v(attribute_value<dogen::dia::string>(a, dia_string));
    std::string name(v.value());
    boost::erase_all(name, hash_character);
    boost::trim(name);
    return name;
}

dogen::sml::qualified_name
dia_dfs_visitor::transform_qualified_name(std::string type_string) const {
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
transform_qualified_name(dogen::dia::attribute a,
    dogen::sml::meta_types meta_type) const {
    if (a.name() != dia_name) {
        using dogen::utility::exception::exception;
        throw exception(name_attribute_expected);
    }

    dogen::sml::qualified_name name;
    name.model_name(state_->model_name);
    name.meta_type(meta_type);
    name.external_package_path(state_->external_package_path);
    name.package_path(state_->package_path);

    name.type_name(transform_string_attribute(a));
    if (name.type_name().empty()) {
        using dogen::utility::exception::exception;
        throw exception(invalid_dia_object_name);
    }
    return name;
}

std::pair<dogen::sml::qualified_name, dogen::sml::package>
dia_dfs_visitor::transform_package(dogen::dia::object o) {
    dogen::sml::package package;

    for (auto a : o.attributes()) {
        if (a.name() == dia_name) {
            using dogen::sml::meta_types;
            package.name(transform_qualified_name(a, meta_types::package));
        }
    }

    if (package.name().type_name().empty()) {
        using dogen::utility::exception::exception;
        throw exception(name_attribute_expected + o.id());
    }
    return std::make_pair(package.name(), package);
}

dogen::sml::property dia_dfs_visitor::
transform_property(dogen::dia::composite uml_attribute) const {
    dogen::sml::property property;
    typedef boost::shared_ptr<dogen::dia::attribute> attribute_ptr;

    for (const attribute_ptr a : uml_attribute.value()) {
        if (a->name() == dia_name)
            property.name(transform_string_attribute(*a));

        if (a->name() == dia_type) {
            const std::string s(transform_string_attribute(*a));
            property.type_name(transform_qualified_name(s));
        }
    }

    using dogen::utility::exception::exception;
    if (property.name().empty())
        throw exception(name_attribute_expected);

    if (property.type_name().type_name().empty())
        throw exception(type_attribute_expected);

    return property;
}

std::pair<dogen::sml::qualified_name, dogen::sml::pod>
dia_dfs_visitor::transform_pod(dogen::dia::object o) {
    dogen::sml::pod pod;

    pod.generate(state_->is_target);
    for (auto attribute : o.attributes()) {
        using namespace dogen::utility::log;
        BOOST_LOG_SEV(lg, debug) << "\t\tFound attribute: " << attribute.name();

        if (attribute.name() == dia_name) {
            using dogen::sml::meta_types;
            pod.name(transform_qualified_name(attribute, meta_types::pod));
        }

        if (attribute.name() == dia_attributes) {
            if (is_attribute_value_empty(attribute)) {
                BOOST_LOG_SEV(lg, debug) << "\t\t\tattribute is empty";
                continue;
            }

            typedef std::vector<dogen::dia::composite> composites;
            const auto uml_attributes(attribute_value<composites>(
                    attribute, dia_composite));

            std::vector<dogen::sml::property> properties;
            for (auto uml_attribute : uml_attributes) {
                BOOST_LOG_SEV(lg, debug) << "\t\t\tattribute has type: "
                                         << attribute.name();
                if (uml_attribute.type() != dia_uml_attribute) {
                    using dogen::utility::exception::exception;
                    throw exception(uml_attribute_expected);
                }
                properties.push_back(transform_property(uml_attribute));
            }
            pod.properties(properties);
        }
    }

    if (pod.name().type_name().empty()) {
        using dogen::utility::exception::exception;
        throw exception(name_attribute_expected + o.id());
    }
    return std::make_pair(pod.name(), pod);
}

void dia_dfs_visitor::update_package_path(dogen::dia::object o) {
    if (o.id() == root_vertex_id)
        return; // root is a dummy object, ignore it.

    using dogen::dia::utility::parse_object_type;
    const auto type(parse_object_type(o.type()));

    using dogen::dia::object_types;
    if (type != object_types::uml_large_package)
        return; // only packages contribute to the package path

    bool found_name(false);
    for (auto a : o.attributes()) {
        found_name = a.name() == dia_name;
        if (found_name) {
            using namespace dogen::utility::log;
            BOOST_LOG_SEV(lg, debug) << "Updating package_path: " << o.id();
            state_->package_path.push_back(transform_string_attribute(a));
            break;
        }
    }

    if (!found_name) {
        using dogen::utility::exception::exception;
        throw exception(name_attribute_expected + o.id());
    }
}

void dia_dfs_visitor::process_dia_object(dogen::dia::object o) {
    if (o.id() == root_vertex_id)
        return; // root is a dummy object, ignore it.

    using dogen::dia::utility::parse_object_type;
    const auto type(parse_object_type(o.type()));

    using dogen::dia::object_types;
    using namespace dogen::utility::log;
    if (type == object_types::uml_large_package) {
        BOOST_LOG_SEV(lg, debug) << "Processing uml_large_package: "
                                 << o.id();
        state_->package_path.pop_back();
        state_->packages.insert(transform_package(o));
    } else if (type == object_types::uml_class) {
        BOOST_LOG_SEV(lg, debug) << "\tProcessing uml_class: " << o.id();
        state_->pods.insert(transform_pod(o));
    }
}

}

namespace dogen {
namespace generator {
namespace modeling {

dia_to_sml::dia_to_sml(dia::diagram diagram, std::string model_name,
    std::string external_package_path, bool is_target, bool verbose)
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

void dia_to_sml::populate_graph(std::vector<dia::object> objects) {
    auto find_or_add([&](std::string id) {
            const auto i(id_to_vertex_.find(id));
            if (i != id_to_vertex_.end())
                return i->second;

            const auto vertex(boost::add_vertex(graph_));
            id_to_vertex_.insert(std::make_pair(id, vertex));
            return vertex;
        });

    for (const auto o : objects) {
        const vertex_descriptor_type vertex(find_or_add(o.id()));
        graph_[vertex] = o;
        if (!o.child_node()) {
            boost::add_edge(root_vertex_, vertex, graph_);
            continue;
        }
        const std::string parent_id(o.child_node()->parent());
        const vertex_descriptor_type parent_vertex(find_or_add(parent_id));
        boost::add_edge(parent_vertex, vertex, graph_);
        using namespace dogen::utility::log;
        BOOST_LOG_SEV(lg, debug) << "Adding object to graph: " << o.id()
                                 << " Parent ID: " << parent_id;
    }
}

sml::model dia_to_sml::transform() {
    using namespace dogen::utility::log;
    BOOST_LOG_SEV(lg, info) << "Transforming diagram: " << model_name_;
    BOOST_LOG_SEV(lg, debug) << "Contents: " << diagram_;
    for (dia::layer layer : diagram_.layers())
        populate_graph(layer.objects());

    std::shared_ptr<visit_state> s(new visit_state);
    const std::string epp(external_package_path_);
    dia_dfs_visitor visitor(s, model_name_, epp, verbose_, is_target_);
    boost::depth_first_search(graph_, boost::visitor(visitor));

    using sml::model;
    return model(model_name_, s->packages, s->pods, s->primitives,
        s->external_package_path);
}

} } }
