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
#include <list>
#include <sstream>
#include <unordered_set>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/sml/io/meta_types_io.hpp"
#include "dogen/sml/io/pod_types_io.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/types/nested_qualified_name.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/generator/backends/cpp/view_models/registrar_view_model.hpp"
#include "dogen/generator/backends/cpp/view_models/nested_type_view_model.hpp"
#include "dogen/generator/backends/cpp/view_models/transformation_error.hpp"
#include "dogen/generator/backends/cpp/view_models/sml_to_cpp_view_model.hpp"

using namespace dogen::utility::log;

typedef boost::error_info<struct tag_sml_to_cpp_view_model, std::string>
errmsg_sml_to_cpp_view_model;

namespace {

auto lg(logger_factory("sml_to_view_model"));

const std::string pod_not_found("pod not found in pod container: ");

const std::string empty;
const std::list<std::string> empty_package_path;
const std::string dot(".");
const std::string comma(",");
const std::string space(" ");
const std::string less_than("<");
const std::string more_than(">");
const std::string separator("_");
const std::string extension("HPP");
const std::string namespace_separator("::");

const std::string parent_view_model_not_found(
    "Parent view model not found for pod: ");
const std::string view_model_not_found("View model not found: ");
const std::string unsupported_meta_type("Meta type not supported: ");
const std::string invalid_enabled_facets("Invalid enabled facets request: ");
const std::string failed_to_process_type("Failed to process type: ");

const std::string includer_name("all");
const std::string registrar_name("registrar");
const std::string versioned_name("versioned_key");
const std::string unversioned_name("unversioned_key");
const std::string id_name("id");
const std::string version_name("version");

const std::string bool_type("bool");
const std::string string_type("std::string");
const std::string char_type("char");
const std::string uchar_type("unsigned char");
const std::string short_type("short");
const std::string ushort_type("unsigned short");
const std::string int_type("int");
const std::string uint_type("unsigned int");
const std::string long_type("long");
const std::string ulong_type("unsigned long");
const std::string long_long_type("long long");
const std::string ulong_long_type("unsigned long long");
const std::string double_type("double");
const std::string float_type("float");
const std::string optional_type("boost::optional");
const std::string variant_type("boost::variant");

const std::string int8_t_type("std::int8_t");
const std::string int16_t_type("std::int16_t");
const std::string int32_t_type("std::int32_t");
const std::string int64_t_type("std::int64_t");
const std::string uint8_t_type("std::uint8_t");
const std::string uint16_t_type("std::uint16_t");
const std::string uint32_t_type("std::uint32_t");
const std::string uint64_t_type("std::uint64_t");

bool is_char_like(const std::string& type_name) {
    return
        type_name == char_type || type_name == uchar_type ||
        type_name == int8_t_type || type_name == uint8_t_type;
}

bool is_string_like(const std::string& type_name) {
    return is_char_like(type_name) || type_name == string_type;
}

bool is_optional_like(const std::string& type_name) {
    return type_name == optional_type;
}

bool is_variant_like(const std::string& type_name) {
    return type_name == variant_type;
}

bool is_int_like(const std::string& type_name) {
    return
        type_name == short_type ||
        type_name == ushort_type ||
        type_name == int_type ||
        type_name == uint_type ||
        type_name == long_type ||
        type_name == ulong_type ||
        type_name == long_long_type ||
        type_name == ulong_long_type ||
        type_name == double_type ||
        type_name == float_type ||
        type_name == int16_t_type ||
        type_name == int32_t_type ||
        type_name == int64_t_type ||
        type_name == uint16_t_type ||
        type_name == uint32_t_type ||
        type_name == uint64_t_type;
}

/**
 * @brief Flattens all the SML namespace information stored in
 * qualified name into a list of strings with C++ namespaces.
 */
std::list<std::string> join_namespaces(const dogen::sml::qname& name) {
    std::list<std::string> result(name.external_package_path());

    if (!name.model_name().empty())
        result.push_back(name.model_name());

    std::list<std::string> package_path(name.package_path());
    result.insert(result.end(), package_path.begin(), package_path.end());
    return result;
}

/**
 * @brief Returns the identifier to be used for this name on a
 * database context.
 */
std::string database_name(const dogen::sml::qname& name) {
    std::ostringstream stream;

    if (!name.model_name().empty())
        stream << name.model_name() << "_";

    for (const auto p : name.package_path())
        stream << p << "_";

    stream << name.type_name();

    return stream.str();
}

class sml_dfs_visitor : public boost::default_dfs_visitor {
private:
    typedef std::unordered_map<
    dogen::sml::qname,
    dogen::generator::backends::cpp::view_models::class_view_model>
    qname_to_class_view_model_type;
    typedef std::unordered_map<dogen::sml::qname, dogen::sml::pod>
    pod_map_type;

    struct visit_state {
        visit_state(const std::string& schema_name, pod_map_type pods)
            : pods_(pods), schema_name_(schema_name) { }

        qname_to_class_view_model_type class_view_models_;
        pod_map_type pods_;
        const std::string schema_name_;
    };

public:
    sml_dfs_visitor& operator=(const sml_dfs_visitor&) = default;
    sml_dfs_visitor(const sml_dfs_visitor&) = default;
    sml_dfs_visitor(sml_dfs_visitor&&) = default;

public:
    explicit sml_dfs_visitor(const std::string& schema_name, pod_map_type pods)
        : state_(new visit_state(schema_name, pods)) { }

public:
    template<typename Vertex, typename Graph>
    void discover_vertex(const Vertex& u, const Graph& g) {
        process_sml_pod(g[u]);
    }

    template<typename Vertex, typename Graph>
    void finish_vertex(const Vertex& /*u*/, const Graph& /*g*/) {}

private:
    /**
     * @brief Returns true if the type will require stream
     * manipulators, false otherwise.
     */
    bool requires_stream_manipulators(const std::string type_name) const;

    /**
     * @brief Converts a qualified type name to a name that can be
     * used as an identifier.
     */
    std::string to_identifiable_name(const std::string n) const;

    /**
     * @brief Transforms a nested qualified name into a view model
     * type name.
     */
    void transform_nested_qualified_name(
        const dogen::sml::nested_qualified_name& nqn,
        dogen::generator::backends::cpp::view_models::nested_type_view_model&
        name, std::string& complete_name,
        bool& requires_stream_manipulators) const;

    /**
     * @brief Transforms an SML pod into a C++ class view.
     */
    void process_sml_pod(const dogen::sml::pod& pod);

public:
    qname_to_class_view_model_type class_view_models() {
        return state_->class_view_models_;
    }

private:
    std::shared_ptr<visit_state> state_;
};

std::string sml_dfs_visitor::to_identifiable_name(const std::string n) const {
    std::string r(n);

    boost::replace_all(r, namespace_separator, separator);
    boost::replace_all(r, space, separator);
    boost::replace_all(r, comma, empty);
    boost::replace_all(r, less_than, separator);
    boost::replace_all(r, more_than, empty);

    return r;
}

bool sml_dfs_visitor::
requires_stream_manipulators(const std::string type_name) const {
    return
        type_name == bool_type ||
        type_name == double_type ||
        type_name == float_type;
}

void sml_dfs_visitor::transform_nested_qualified_name(
    const dogen::sml::nested_qualified_name& nqn,
    dogen::generator::backends::cpp::view_models::nested_type_view_model&
    vm, std::string& complete_name,
    bool& requires_stream_manipulators) const {

    const auto qn(nqn.type());
    std::list<std::string> ns_list(join_namespaces(qn));
    vm.namespaces(ns_list);
    ns_list.push_back(qn.type_name());

    using boost::algorithm::join;
    std::string ns(join(ns_list, namespace_separator));
    vm.name(ns);

    using dogen::sml::meta_types;
    vm.is_enumeration(qn.meta_type() == meta_types::enumeration);
    vm.is_primitive(qn.meta_type() == meta_types::primitive);
    if (vm.is_primitive()) {
        if (this->requires_stream_manipulators(vm.name()))
            requires_stream_manipulators = true;

        vm.is_char_like(is_char_like(vm.name()));
        vm.is_int_like(is_int_like(vm.name()));
    }
    vm.is_string_like(is_string_like(vm.name()));
    vm.is_optional_like(is_optional_like(vm.name()));
    vm.is_variant_like(is_variant_like(vm.name()));

    if (qn.meta_type() == meta_types::pod) {
        const auto i(state_->pods_.find(qn));
        if (i == state_->pods_.end()) {
            using dogen::generator::backends::cpp::view_models::transformation_error;
            BOOST_LOG_SEV(lg, error) << pod_not_found << qn.type_name();
            BOOST_THROW_EXCEPTION(transformation_error(pod_not_found +
                qn.type_name()));
        }
        const auto pt(i->second.pod_type());
        using dogen::sml::pod_types;
        vm.is_sequence_container(pt == pod_types::sequence_container);
        vm.is_associative_container(pt == pod_types::associative_container);
        vm.is_smart_pointer(pt == pod_types::smart_pointer);
    }

    using dogen::generator::backends::cpp::view_models::nested_type_view_model;
    const auto nqn_children(nqn.children());

    std::string my_complete_name(vm.name());
    auto lambda([&](char c) {
            if (!nqn_children.empty()) {
                if (my_complete_name[my_complete_name.length() - 1] == c)
                    my_complete_name += " ";
                my_complete_name += c;
            }
        });

    std::list<nested_type_view_model> children;
    lambda('<');
    bool is_first(true);
    for (const auto c : nqn.children()) {
        if (!is_first)
            my_complete_name += ", ";

        nested_type_view_model cvm;
        transform_nested_qualified_name(c, cvm, my_complete_name,
            requires_stream_manipulators);
        children.push_back(cvm);
        is_first = false;
    }
    lambda('>');

    vm.identifiable_name(to_identifiable_name(ns));
    vm.complete_identifiable_name(to_identifiable_name(my_complete_name));
    vm.complete_name(my_complete_name);
    vm.children(children);
    complete_name += my_complete_name;
}

void sml_dfs_visitor::process_sml_pod(const dogen::sml::pod& pod) {
    const dogen::sml::qname name(pod.name());
    const std::list<std::string> ns(join_namespaces(name));

    using namespace dogen::generator::backends::cpp::view_models;
    class_view_model cvm(name.type_name());
    std::list<property_view_model> all_props_vm;

    if (pod.parent_name()) {
        const auto pqn(*pod.parent_name());
        BOOST_LOG_SEV(lg, debug) << "Class '" << name.type_name()
                                 << "' has parent '" << pqn.type_name() << "'";

        const auto i(state_->class_view_models_.find(pqn));
        if (i == state_->class_view_models_.end()) {
            BOOST_LOG_SEV(lg, error) << parent_view_model_not_found
                                     << name.type_name();

            BOOST_LOG_SEV(lg, error) << parent_view_model_not_found << name.type_name();
            BOOST_THROW_EXCEPTION(transformation_error(parent_view_model_not_found +
                name.type_name()));
        }

        parent_view_model parent(pqn.type_name());
        parent.properties(i->second.all_properties());
        all_props_vm.splice(all_props_vm.end(), i->second.all_properties());
        parent.namespaces(i->second.namespaces());

        std::list<parent_view_model> parents;
        parents.push_back(parent);
        cvm.parents(parents);
    }

    cvm.namespaces(ns);
    cvm.database_name(database_name(name));
    cvm.schema_name(state_->schema_name_);
    cvm.is_parent(pod.is_parent());
    cvm.documentation(pod.documentation());

    std::list<property_view_model> props_vm;
    bool has_primitive_properties(false);
    bool requires_stream_manipulators(false);
    bool requires_manual_move_constructor(false);
    bool requires_manual_default_constructor(false);
    for(const auto p : pod.properties()) {
        property_view_model k(p.name());
        k.documentation(p.documentation());

        nested_type_view_model type_vm;
        std::string complete_name;
        if (p.type_name().type().type_name() == "optional" ||
            p.type_name().type().type_name() == "variant")
            requires_manual_move_constructor = true;

        transform_nested_qualified_name(p.type_name(), type_vm, complete_name,
            requires_stream_manipulators);
        if (type_vm.is_primitive()) {
            has_primitive_properties = true;
            requires_manual_default_constructor = true;
        } else if (type_vm.is_enumeration())
            requires_manual_default_constructor = true;

        type_vm.complete_name(complete_name);
        k.type(type_vm);

        props_vm.push_back(k);
    }

    all_props_vm.insert(all_props_vm.end(), props_vm.begin(), props_vm.end());
    cvm.properties(props_vm);
    cvm.all_properties(all_props_vm);
    cvm.has_primitive_properties(has_primitive_properties);
    cvm.requires_stream_manipulators(requires_stream_manipulators);
    cvm.requires_manual_move_constructor(requires_manual_move_constructor);
    cvm.requires_manual_default_constructor(requires_manual_default_constructor);

    const auto opn(pod.original_parent_name());
    if (opn) {
        std::list<std::string> opn_name(join_namespaces(*opn));
        opn_name.push_back(opn->type_name());
        using boost::join;
        cvm.original_parent_name(join(opn_name, namespace_separator));
    }

    std::list<std::string> leaves;
    for (const auto l : pod.leaves()) {
        std::list<std::string> leaf_name(join_namespaces(l));
        leaf_name.push_back(l.type_name());
        using boost::join;
        leaves.push_back(join(leaf_name, namespace_separator));
    }
    cvm.leaves(leaves);
    state_->class_view_models_.insert(std::make_pair(name, cvm));
}

}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace view_models {

sml_to_cpp_view_model::
sml_to_cpp_view_model(const cpp_location_manager& location_manager,
    const cpp_inclusion_manager& inclusion_manager,
    const config::cpp_settings& settings,
    const sml::model& model) :
    location_manager_(location_manager),
    inclusion_manager_(inclusion_manager),
    settings_(settings),
    model_(model),
    root_vertex_(boost::add_vertex(graph_)) { }

void sml_to_cpp_view_model::log_includers() const {
    if (settings_.disable_facet_includers())
        BOOST_LOG_SEV(lg, warn) << "Includers are NOT enabled, "
                                << "NOT generating views for them.";
    else
        BOOST_LOG_SEV(lg, info) << "Includers are enabled, "
                                << "so generating views for them.";
}

void sml_to_cpp_view_model::
log_generating_file(cpp_facet_types facet, cpp_aspect_types aspect,
    cpp_file_types ft, std::string name, sml::meta_types mt) const {
    BOOST_LOG_SEV(lg, debug) << "Generating file view model. "
                             << "facet type: " << facet
                             << " aspect type: " << aspect
                             << " file type: " << ft
                             << " meta type: " << mt
                             << " name: " << name;
}

void sml_to_cpp_view_model::log_started() const {
    BOOST_LOG_SEV(lg, info) << "Started transforming.";
}

void sml_to_cpp_view_model::log_finished(unsigned int count) const {
    BOOST_LOG_SEV(lg, info) << "Finished transforming. "
                            << "Generated files count: " << count;
}

std::string sml_to_cpp_view_model::
to_header_guard_name(const boost::filesystem::path& relative_path) const {
    bool is_first(true);
    std::ostringstream stream;
    for (auto p : relative_path) {
        std::string str(p.string());
        boost::replace_all(str, dot, separator);
        boost::to_upper(str);
        stream << (is_first ? empty : separator) << str;
        is_first = false;
    }
    return stream.str();
}

cpp_location_request sml_to_cpp_view_model::
location_request_factory(cpp_facet_types ft, cpp_file_types flt,
    cpp_aspect_types at, const sml::qname& n) const {

    cpp_location_request r;
    r.facet_type(ft);
    r.file_type(flt);
    r.aspect_type(at);
    r.model_name(model_.name());
    r.package_path(n.package_path());
    r.file_name(n.type_name());
    r.external_package_path(n.external_package_path());
    return r;
}

file_view_model sml_to_cpp_view_model::
create_file(cpp_facet_types ft, cpp_file_types flt, cpp_aspect_types at,
    const sml::qname& name) {
    file_view_model r;
    r.facet_type(ft);
    r.file_type(flt);
    r.aspect_type(at);

    auto rq(location_request_factory(ft, flt, at, name));
    r.file_path(location_manager_.absolute_path(rq));

    if (flt == cpp_file_types::header) {
        rq = location_request_factory(ft, flt, at, name);
        const auto rp(location_manager_.relative_logical_path(rq));
        r.header_guard(to_header_guard_name(rp));
        if (at == cpp_aspect_types::main)
            inclusion_manager_.register_header(ft, rp);
    }

    return r;
}

file_view_model sml_to_cpp_view_model::
transform_file(cpp_facet_types ft, cpp_file_types flt, cpp_aspect_types at,
    const sml::pod& p) {
    const sml::qname name(p.name());
    const std::list<std::string> ns(join_namespaces(name));

    file_view_model r(create_file(ft, flt, at, name));
    r.category_type(p.category_type());
    r.meta_type(p.name().meta_type());

    if (at != cpp_aspect_types::forward_decls &&
        p.generation_type() == sml::generation_types::partial_generation)
        r.aspect_type(cpp_aspect_types::null_aspect);

    const auto i(qname_to_class_.find(name));
    if (i == qname_to_class_.end()) {
        BOOST_LOG_SEV(lg, error) << view_model_not_found
                                 << name.type_name();

        BOOST_LOG_SEV(lg, error) << view_model_not_found << name.type_name();
        BOOST_THROW_EXCEPTION(transformation_error(view_model_not_found + name.type_name()));
    }
    r.class_vm(i->second);

    const auto includes(inclusion_manager_.includes_for_pod(p, ft, flt, at));
    r.system_includes(includes.system);
    r.user_includes(includes.user);
    return r;
}

file_view_model sml_to_cpp_view_model::
transform_file(cpp_facet_types ft, cpp_file_types flt, cpp_aspect_types at,
    const sml::enumeration& e) {
    const sml::qname name(e.name());
    const std::list<std::string> ns(join_namespaces(name));

    file_view_model r(create_file(ft, flt, at, name));
    r.category_type(sml::category_types::user_defined);
    r.meta_type(e.name().meta_type());

    const auto i(qname_to_enumeration_.find(name));
    if (i == qname_to_enumeration_.end()) {
        BOOST_LOG_SEV(lg, error) << view_model_not_found
                                 << name.type_name();

        BOOST_THROW_EXCEPTION(transformation_error(view_model_not_found +
                name.type_name()));
    }
    r.enumeration_vm(i->second);

    const auto in(inclusion_manager_.includes_for_enumeration(e, ft, flt, at));
    r.system_includes(in.system);
    r.user_includes(in.user);
    return r;
}

file_view_model sml_to_cpp_view_model::
transform_file(cpp_facet_types ft, cpp_file_types flt, cpp_aspect_types at,
    const sml::exception& e) {
    const sml::qname name(e.name());
    const std::list<std::string> ns(join_namespaces(name));

    file_view_model r(create_file(ft, flt, at, name));
    r.category_type(sml::category_types::user_defined);
    r.meta_type(e.name().meta_type());

    const auto i(qname_to_exception_.find(name));
    if (i == qname_to_exception_.end()) {
        BOOST_LOG_SEV(lg, error) << view_model_not_found
                                 << name.type_name();

        BOOST_THROW_EXCEPTION(transformation_error(view_model_not_found + name.type_name()));
    }
    r.exception_vm(i->second);

    const auto in(inclusion_manager_.includes_for_exception(e, ft, flt, at));
    r.system_includes(in.system);
    r.user_includes(in.user);
    return r;
}

bool sml_to_cpp_view_model::has_implementation(const cpp_facet_types ft,
    const dogen::sml::meta_types mt) const {
    using dogen::sml::meta_types;
    if (mt == meta_types::pod) {
        return
            ft == cpp_facet_types::types ||
            ft == cpp_facet_types::hash ||
            ft == cpp_facet_types::io ||
            ft == cpp_facet_types::test_data ||
            ft == cpp_facet_types::serialization;
    } else if (mt == meta_types::enumeration) {
        return
            ft == cpp_facet_types::io ||
            ft == cpp_facet_types::test_data;
    } else if (mt == meta_types::enumeration)
        return false;

    std::ostringstream s;
    s << unsupported_meta_type << mt;
    BOOST_LOG_SEV(lg, error) << s.str();
    BOOST_THROW_EXCEPTION(transformation_error(s.str()));
}

bool sml_to_cpp_view_model::has_forward_decls(const cpp_facet_types ft,
    const dogen::sml::meta_types mt) const {
    using dogen::sml::meta_types;
    if (mt == meta_types::pod) {
        return
            ft == cpp_facet_types::types ||
            ft == cpp_facet_types::serialization;
    } else if (mt == meta_types::enumeration) {
        return ft == cpp_facet_types::types;
    } else if (mt == meta_types::exception) {
        return ft == cpp_facet_types::types;
    }

    std::ostringstream s;
    s << unsupported_meta_type << mt;
    BOOST_LOG_SEV(lg, error) << s.str();
    BOOST_THROW_EXCEPTION(transformation_error(s.str()));
}

void sml_to_cpp_view_model::create_class_view_models() {
    const auto pods(model_.pods());
    BOOST_LOG_SEV(lg, debug) << "Transforming pods: " << pods.size();

    auto lambda([&](const sml::qname& n) -> vertex_descriptor_type {
            const auto i(qname_to_vertex_.find(n));
            if (i != qname_to_vertex_.end())
                return i->second;

            const auto vertex(boost::add_vertex(graph_));
            qname_to_vertex_.insert(std::make_pair(n, vertex));
            return vertex;
        });

    for (const auto pair : pods) {
        const vertex_descriptor_type vertex(lambda(pair.first));
        const auto pod(pair.second);
        graph_[vertex] = pod;

        if (pod.parent_name()) {
            const vertex_descriptor_type parent_vertex(lambda(*pod.parent_name()));
            boost::add_edge(parent_vertex, vertex, graph_);
        } else
            boost::add_edge(root_vertex_, vertex, graph_);
    }

    sml_dfs_visitor v(model_.schema_name(), pods);
    boost::depth_first_search(graph_, boost::visitor(v));
    qname_to_class_ = v.class_view_models();
}


void sml_to_cpp_view_model::create_enumeration_view_models() {
    const auto enumerations(model_.enumerations());
    BOOST_LOG_SEV(lg, debug) << "Transforming enumerations: "
                             << enumerations.size();

    for (const auto pair : enumerations) {
        const auto e(pair.second);
        const dogen::sml::qname name(e.name());
        const std::list<std::string> ns(join_namespaces(name));

        enumeration_view_model vm;
        vm.name(e.name().type_name());
        vm.namespaces(ns);
        vm.documentation(e.documentation());
        std::list<enumerator_view_model> enumerators;
        for (const auto en : e.enumerators()) {
            enumerator_view_model evm;
            evm.name(en.name());
            evm.value(en.value());
            evm.documentation(en.documentation());
            enumerators.push_back(evm);
        }
        vm.enumerators(enumerators);
        // vm.database_name(database_name(name));
        // vm.schema_name(schema_name_);
        qname_to_enumeration_.insert(std::make_pair(e.name(), vm));
    }
}

void sml_to_cpp_view_model::create_exception_view_models() {
    const auto exceptions(model_.exceptions());
    BOOST_LOG_SEV(lg, debug) << "Transforming exceptions: "
                             << exceptions.size();

    for (const auto pair : exceptions) {
        const auto e(pair.second);
        const dogen::sml::qname name(e.name());
        const std::list<std::string> ns(join_namespaces(name));

        exception_view_model vm;
        vm.name(e.name().type_name());
        vm.namespaces(ns);
        vm.documentation(e.documentation());
        // vm.database_name(database_name(name));
        // vm.schema_name(schema_name_);
        qname_to_exception_.insert(std::make_pair(e.name(), vm));
    }
}

std::set<cpp_facet_types> sml_to_cpp_view_model::
enabled_facet_types(const sml::meta_types mt, const sml::pod_types pt) const {
    if (mt == sml::meta_types::pod) {
        if (pt == sml::pod_types::value || pt == sml::pod_types::entity)
            return settings_.enabled_facets();
        else if (pt == sml::pod_types::service)
            return std::set<cpp_facet_types> { cpp_facet_types::types };
    } else if (mt == sml::meta_types::enumeration ||
        mt == sml::meta_types::primitive) {
        return settings_.enabled_facets();
    } else if (mt == sml::meta_types::exception) {
        return std::set<cpp_facet_types> { cpp_facet_types::types };
    }

    BOOST_LOG_SEV(lg, error) << invalid_enabled_facets << boost::lexical_cast<std::string>(mt) << boost::lexical_cast<std::string>(pt);
    BOOST_THROW_EXCEPTION(transformation_error(invalid_enabled_facets +
            boost::lexical_cast<std::string>(mt) + ", " +
            boost::lexical_cast<std::string>(pt)));
}

std::vector<file_view_model> sml_to_cpp_view_model::transform_pods() {
    std::vector<file_view_model> r;
    auto lambda([&](cpp_facet_types ft, cpp_file_types flt, cpp_aspect_types at,
            const sml::pod& p) {
            const std::string n(p.name().type_name());
            log_generating_file(ft, at, flt, n, p.name().meta_type());
            r.push_back(transform_file(ft, flt, at, p));
        });

    const auto pods(model_.pods());
    for (const auto pair : pods) {
        const sml::pod p(pair.second);

        if (p.generation_type() == sml::generation_types::no_generation)
            continue;

        try {
            const auto header(cpp_file_types::header);
            const auto implementation(cpp_file_types::implementation);
            const auto main(cpp_aspect_types::main);
            const auto forward_decls(cpp_aspect_types::forward_decls);
            const auto pod_mt(sml::meta_types::pod);
            const auto facets(enabled_facet_types(pod_mt, p.pod_type()));

            for (const auto ft: facets) {
                lambda(ft, header, main, p);

                if (has_implementation(ft, pod_mt))
                    lambda(ft, implementation, main, p);

                if (has_forward_decls(ft, pod_mt))
                    lambda(ft, header, forward_decls, p);
            }
        } catch (boost::exception& e) {
            e << errmsg_sml_to_cpp_view_model(failed_to_process_type +
                boost::lexical_cast<std::string>(p.name()));
            throw;
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Transformed pods: " << pods.size();
    return r;
}

std::vector<file_view_model> sml_to_cpp_view_model::transform_enumerations() {
    std::vector<file_view_model> r;
    auto lambda([&](cpp_facet_types ft, cpp_file_types flt, cpp_aspect_types at,
            const sml::enumeration& e) {
            const std::string n(e.name().type_name());
            log_generating_file(ft, at, flt, n, e.name().meta_type());
            r.push_back(transform_file(ft, flt, at, e));
        });

    for (auto pair : model_.enumerations()) {
        const sml::enumeration e(pair.second);

        if (e.generation_type() == sml::generation_types::no_generation)
            continue;

        try {
            const auto header(cpp_file_types::header);
            const auto implementation(cpp_file_types::implementation);
            const auto main(cpp_aspect_types::main);
            const auto forward_decls(cpp_aspect_types::forward_decls);
            const auto enum_mt(sml::meta_types::enumeration);
            const auto facets(enabled_facet_types(enum_mt));

            for (const auto ft: facets) {
                lambda(ft, header, main, e);

                if (has_implementation(ft, enum_mt))
                    lambda(ft, implementation, main, e);

                if (has_forward_decls(ft, enum_mt))
                    lambda(ft, header, forward_decls, e);
            }
        } catch (boost::exception& ex) {
            ex << errmsg_sml_to_cpp_view_model(failed_to_process_type +
                boost::lexical_cast<std::string>(e.name()));
            throw;
        }
    }
    return r;
}

std::vector<file_view_model> sml_to_cpp_view_model::transform_exceptions() {
    std::vector<file_view_model> r;
    auto lambda([&](cpp_facet_types ft, cpp_file_types flt, cpp_aspect_types at,
            const sml::exception& e) {
            const std::string n(e.name().type_name());
            log_generating_file(ft, at, flt, n, e.name().meta_type());
            r.push_back(transform_file(ft, flt, at, e));
        });

    for (auto pair : model_.exceptions()) {
        const sml::exception e(pair.second);

        if (e.generation_type() == sml::generation_types::no_generation)
            continue;

        try {
            const auto header(cpp_file_types::header);
            const auto main(cpp_aspect_types::main);
            const auto forward_decls(cpp_aspect_types::forward_decls);
            const auto exception_mt(sml::meta_types::exception);
            const auto facets(enabled_facet_types(exception_mt));

            for (const auto ft : facets) {
                lambda(ft, header, main, e);

                if (has_forward_decls(ft, sml::meta_types::exception))
                    lambda(ft, header, forward_decls, e);
            }
        } catch (boost::exception& ex) {
            ex << errmsg_sml_to_cpp_view_model(failed_to_process_type +
                boost::lexical_cast<std::string>(e.name()));
            throw;
        }
    }
    return r;
}

std::vector<file_view_model>
sml_to_cpp_view_model::transform_facet_includers() const {
    std::vector<file_view_model> r;
    const cpp_file_types file_type(cpp_file_types::header);
    const auto at(cpp_aspect_types::includers);

    for (cpp_facet_types ft : settings_.enabled_facets()) {
        sml::qname qn;
        const auto n(includer_name);
        log_generating_file(ft, at, file_type, n, sml::meta_types::invalid);
        qn.type_name(n);
        qn.external_package_path(model_.external_package_path());
        const auto rq(location_request_factory(ft, file_type, at, qn));

        file_view_model vm;
        vm.facet_type(ft);
        vm.file_path(location_manager_.absolute_path(rq));
        vm.file_type(file_type);
        vm.aspect_type(at);

        const auto includes(inclusion_manager_.includes_for_includer_files(ft));
        vm.system_includes(includes.system);
        vm.user_includes(includes.user);

        r.push_back(vm);
    }
    return r;
}

/**
 * @brief Transforms the serialisation registrar
 */
std::vector<file_view_model>
sml_to_cpp_view_model::transform_registrar() const {
    std::vector<file_view_model> r;
    const auto facets(settings_.enabled_facets());
    if (facets.find(cpp_facet_types::serialization) == facets.end()) {
        BOOST_LOG_SEV(lg, warn) << "Serialisaton not enabled"
                                << " so NOT generating registrar";
        return r;
    }

    BOOST_LOG_SEV(lg, debug) << "Transforming serialisaton registrar";

    sml::qname qn;
    qn.model_name(model_.name());
    qn.external_package_path(model_.external_package_path());

    registrar_view_model rvm;
    rvm.namespaces(join_namespaces(qn));
    BOOST_LOG_SEV(lg, debug) << "Added namespaces: " << rvm.namespaces();

    std::list<std::string> deps;
    for (const auto& pair : model_.dependencies()) {
        const auto d(pair.second);
        if (!d.is_system())
            deps.push_back(d.model_name());
    }
    rvm.model_dependencies(deps);
    BOOST_LOG_SEV(lg, debug) << "Added dependencies: "
                             << rvm.model_dependencies();

    std::list<std::string> leaves;
    using boost::join;
    for (const auto& l : model_.leaves()) {
        auto ns(join_namespaces(l));
        ns.push_back(l.type_name());
        leaves.push_back(join(ns, namespace_separator));
    }
    leaves.sort();
    rvm.leaves(leaves);
    BOOST_LOG_SEV(lg, debug) << "Added leaves: " << rvm.leaves();

    auto lambda([&](const cpp_file_types flt) ->  file_view_model {
            file_view_model fvm;
            const auto ft(cpp_facet_types::serialization);
            const auto at(cpp_aspect_types::registrar);
            const auto n(registrar_name);
            log_generating_file(ft, at, flt, n, sml::meta_types::invalid);
            qn.type_name(n);
            qn.external_package_path(model_.external_package_path());
            const auto rq(location_request_factory(ft, flt, at, qn));

            fvm.facet_type(ft);
            fvm.file_path(location_manager_.absolute_path(rq));
            fvm.file_type(flt);
            fvm.aspect_type(at);
            fvm.registrar_vm(rvm);

            const auto includes(inclusion_manager_.includes_for_registrar(flt));
            fvm.system_includes(includes.system);
            fvm.user_includes(includes.user);

            return fvm;
        });

    r.push_back(lambda(cpp_file_types::header));
    r.push_back(lambda(cpp_file_types::implementation));
    return r;
}

std::vector<file_view_model> sml_to_cpp_view_model::transform() {
    log_started();
    create_class_view_models();
    create_enumeration_view_models();
    create_exception_view_models();

    std::vector<file_view_model> r;
    auto p(transform_pods());
    auto e(transform_enumerations());
    auto ex(transform_exceptions());
    auto reg(transform_registrar());

    r.reserve(p.size() + e.size() + ex.size() + reg.size());
    r.insert(r.end(), p.begin(), p.end());
    r.insert(r.end(), e.begin(), e.end());
    r.insert(r.end(), ex.begin(), ex.end());
    r.insert(r.end(), reg.begin(), reg.end());

    log_includers();
    if (settings_.disable_facet_includers())
        return r;

    const auto fi(transform_facet_includers());
    r.insert(r.end(), fi.begin(), fi.end());
    log_finished(r.size());
    return r;
}

} } } } }
