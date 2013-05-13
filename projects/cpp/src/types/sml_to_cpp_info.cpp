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
#include "dogen/sml/types/nested_qname.hpp"
#include "dogen/config/io/cpp_facet_types_io.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/cpp/types/registrar_info.hpp"
#include "dogen/cpp/types/nested_type_info.hpp"
#include "dogen/cpp/types/transformation_error.hpp"
#include "dogen/cpp/io/aspect_types_io.hpp"
#include "dogen/cpp/io/file_types_io.hpp"
#include "dogen/cpp/types/extractor.hpp"
#include "dogen/cpp/io/file_info_io.hpp"
#include "dogen/cpp/types/sml_to_cpp_info.hpp"

using namespace dogen::utility::log;

typedef boost::error_info<struct tag_sml_to_cpp_info, std::string>
errmsg_sml_to_cpp_info;

namespace {

auto lg(logger_factory("cpp.sml_to_info"));

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

const std::string parent_info_not_found(
    "Parent view model not found for pod: ");
const std::string info_not_found("View model not found: ");
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
const std::string filesystem_path_type("boost::filesystem::path");
const std::string gregorian_date_type("boost::gregorian::date");
const std::string ptime_type("boost::posix_time::ptime");
const std::string time_duration_type("boost::posix_time::time_duration");
const std::string pair_type("std::pair");

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

bool is_pair(const std::string& type_name) {
    return type_name == pair_type;
}

bool is_filesystem_path(const std::string& type_name) {
    return type_name == filesystem_path_type;
}

bool is_gregorian_date(const std::string& type_name) {
    return type_name == gregorian_date_type;
}

bool is_ptime(const std::string& type_name) {
    return type_name == ptime_type;
}

bool is_time_duration(const std::string& type_name) {
    return type_name == time_duration_type;
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
 * @brief Flattens all the SML namespace information stored in qname
 * into a list of strings with C++ namespaces.
 */
std::list<std::string> join_namespaces(const dogen::sml::qname& name) {
    std::list<std::string> result(name.external_package_path());

    if (!name.model_name().empty())
        result.push_back(name.model_name());

    std::list<std::string> package_path(name.package_path());
    result.insert(result.end(), package_path.begin(), package_path.end());

    if (name.meta_type() == dogen::sml::meta_types::package)
        result.push_back(name.type_name());

    return result;
}

class sml_dfs_visitor : public boost::default_dfs_visitor {
private:
    typedef std::unordered_map<
    dogen::sml::qname,
    dogen::cpp::class_info>
    qname_to_class_info_type;
    typedef std::unordered_map<dogen::sml::qname, dogen::sml::pod>
    pod_map_type;
    typedef std::unordered_map<
        dogen::sml::qname,
        dogen::cpp::visitor_info>
    qname_to_visitor_info_type;

    struct visit_state {
        visit_state(pod_map_type pods) : pods_(pods) { }

        qname_to_class_info_type class_infos_;
        pod_map_type pods_; // FIXME: reference to pods?
        qname_to_visitor_info_type visitor_infos_;
    };

public:
    sml_dfs_visitor& operator=(const sml_dfs_visitor&) = default;
    sml_dfs_visitor(const sml_dfs_visitor&) = default;
    sml_dfs_visitor(sml_dfs_visitor&&) = default;

public:
    explicit sml_dfs_visitor(pod_map_type pods)
    : state_(new visit_state(pods)) { }

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
     * @brief Transforms a nested qname into a view model type name.
     */
    void transform_nested_qname(
        const dogen::sml::nested_qname& nqn,
        dogen::cpp::nested_type_info&
        name, std::string& complete_name,
        bool& requires_stream_manipulators) const;

    /**
     * @brief Transforms an SML pod into a C++ class view.
     */
    void process_sml_pod(const dogen::sml::pod& pod);

public:
    qname_to_class_info_type class_infos() {
        return state_->class_infos_;
    }

    qname_to_visitor_info_type visitor_infos() {
        return state_->visitor_infos_;
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

void sml_dfs_visitor::transform_nested_qname(
    const dogen::sml::nested_qname& nqn,
    dogen::cpp::nested_type_info& nti, std::string& complete_name,
    bool& requires_stream_manipulators) const {

    const auto qn(nqn.type());
    std::list<std::string> ns_list(join_namespaces(qn));
    nti.namespaces(ns_list);
    ns_list.push_back(qn.type_name());

    using boost::algorithm::join;
    std::string ns(join(ns_list, namespace_separator));
    nti.name(ns);

    using dogen::sml::meta_types;
    nti.is_enumeration(qn.meta_type() == meta_types::enumeration);
    nti.is_primitive(qn.meta_type() == meta_types::primitive);
    if (nti.is_primitive()) {
        if (this->requires_stream_manipulators(nti.name()))
            requires_stream_manipulators = true;

        nti.is_char_like(is_char_like(nti.name()));
        nti.is_int_like(is_int_like(nti.name()));
    }
    nti.is_string_like(is_string_like(nti.name()));
    nti.is_optional_like(is_optional_like(nti.name()));
    nti.is_pair(is_pair(nti.name()));
    nti.is_variant_like(is_variant_like(nti.name()));
    nti.is_filesystem_path(is_filesystem_path(nti.name()));
    nti.is_date(is_gregorian_date(nti.name()));
    nti.is_ptime(is_ptime(nti.name()));
    nti.is_time_duration(is_time_duration(nti.name()));

    if (qn.meta_type() == meta_types::pod) {
        const auto i(state_->pods_.find(qn));
        if (i == state_->pods_.end()) {
            using dogen::cpp::transformation_error;
            BOOST_LOG_SEV(lg, error) << pod_not_found << qn.type_name();
            BOOST_THROW_EXCEPTION(transformation_error(pod_not_found +
                qn.type_name()));
        }
        const auto pt(i->second.pod_type());
        using dogen::sml::pod_types;
        nti.is_sequence_container(pt == pod_types::sequence_container);
        nti.is_associative_container(pt == pod_types::associative_container);
        nti.is_smart_pointer(pt == pod_types::smart_pointer);
    }

    using dogen::cpp::nested_type_info;
    const auto nqn_children(nqn.children());

    std::string my_complete_name(nti.name());
    auto lambda([&](char c) {
            if (!nqn_children.empty()) {
                if (my_complete_name[my_complete_name.length() - 1] == c)
                    my_complete_name += " ";
                my_complete_name += c;
            }
        });

    std::list<nested_type_info> children;
    lambda('<');
    bool is_first(true);
    for (const auto c : nqn.children()) {
        if (!is_first)
            my_complete_name += ", ";

        nested_type_info ci;
        transform_nested_qname(c, ci, my_complete_name,
            requires_stream_manipulators);
        children.push_back(ci);
        is_first = false;
    }
    lambda('>');

    nti.identifiable_name(to_identifiable_name(ns));
    nti.complete_identifiable_name(to_identifiable_name(my_complete_name));
    nti.complete_name(my_complete_name);
    nti.children(children);
    complete_name += my_complete_name;
}

void sml_dfs_visitor::process_sml_pod(const dogen::sml::pod& pod) {
    const dogen::sml::qname name(pod.name());
    const std::list<std::string> ns(join_namespaces(name));

    using namespace dogen::cpp;
    class_info ci;
    ci.name(name.type_name());
    std::list<property_info> all_props;

    if (pod.parent_name()) {
        const auto pqn(*pod.parent_name());
        BOOST_LOG_SEV(lg, debug) << "Class '" << name.type_name()
                                 << "' has parent '" << pqn.type_name() << "'";

        const auto i(state_->class_infos_.find(pqn));
        if (i == state_->class_infos_.end()) {
            BOOST_LOG_SEV(lg, error) << parent_info_not_found
                                     << name.type_name();

            BOOST_LOG_SEV(lg, error) << parent_info_not_found
                                     << name.type_name();
            BOOST_THROW_EXCEPTION(
                transformation_error(parent_info_not_found +
                    name.type_name()));
        }

        parent_info parent;
        parent.name(pqn.type_name());
        parent.properties(i->second.all_properties());
        // FIXME: quick hack to avoid modifying source.
        auto tmp(i->second.all_properties());
        all_props.splice(all_props.end(), tmp);
        parent.namespaces(i->second.namespaces());

        std::list<parent_info> parents;
        parents.push_back(parent);
        ci.parents(parents);
    }

    ci.namespaces(ns);
    ci.is_parent(pod.is_parent());
    ci.documentation(pod.documentation());
    ci.is_immutable(pod.is_immutable());
    ci.is_visitable(pod.is_visitable());

    if (pod.is_visitable()) {
        BOOST_LOG_SEV(lg, debug) << "Pod '" << name.type_name()
                                 << "' is visitable so generating visitor";

        visitor_info vi;
        vi.name(ci.name() + "_visitor");
        vi.namespaces(ns);

        std::list<std::string> fqn(ns);
        fqn.push_back(ci.name());
        using boost::join;
        vi.types().push_back(join(fqn, namespace_separator));
        state_->visitor_infos_.insert(std::make_pair(pod.name(), vi));
    }

    std::list<property_info> props;
    bool has_primitive_properties(false);
    bool requires_stream_manipulators(false);
    bool requires_manual_move_constructor(false);
    bool requires_manual_default_constructor(false);
    for(const auto p : pod.properties()) {
        property_info k;
        k.name(p.name());
        k.documentation(p.documentation());
        k.is_immutable(pod.is_immutable());
        k.is_fluent(pod.is_fluent());

        nested_type_info nti;
        std::string complete_name;
        if (p.type_name().type().type_name() == "optional" ||
            p.type_name().type().type_name() == "path" ||
            p.type_name().type().type_name() == "variant")
            requires_manual_move_constructor = true;

        transform_nested_qname(p.type_name(), nti, complete_name,
            requires_stream_manipulators);
        if (nti.is_primitive()) {
            has_primitive_properties = true;
            requires_manual_default_constructor = true;
        } else if (nti.is_enumeration())
            requires_manual_default_constructor = true;

        nti.complete_name(complete_name);
        k.type(nti);
        k.implementation_specific_parameters(
            p.implementation_specific_parameters());

        props.push_back(k);
    }

    all_props.insert(all_props.end(), props.begin(), props.end());
    ci.properties(props);
    ci.all_properties(all_props);
    ci.has_primitive_properties(has_primitive_properties);
    ci.requires_stream_manipulators(requires_stream_manipulators);
    ci.requires_manual_move_constructor(requires_manual_move_constructor);
    ci.requires_manual_default_constructor(
        requires_manual_default_constructor);
    ci.implementation_specific_parameters(
        pod.implementation_specific_parameters());

    const auto opn(pod.original_parent_name());
    if (opn) {
        std::list<std::string> opn_name(join_namespaces(*opn));
        opn_name.push_back(opn->type_name());
        using boost::join;
        ci.original_parent_name_qualified(join(opn_name, namespace_separator));
        ci.original_parent_name(opn->type_name());

        const auto i(state_->visitor_infos_.find(*opn));
        if (i != state_->visitor_infos_.end()) {
            std::list<std::string> fqn(ns);
            fqn.push_back(ci.name());
            i->second.types().push_back(join(fqn, namespace_separator));
            ci.is_original_parent_visitable(true);
        }
    }

    std::list<std::string> leaves;
    for (const auto l : pod.leaves()) {
        std::list<std::string> leaf_name(join_namespaces(l));
        leaf_name.push_back(l.type_name());
        using boost::join;
        leaves.push_back(join(leaf_name, namespace_separator));
    }
    ci.leaves(leaves);
    state_->class_infos_.insert(std::make_pair(name, ci));
}

}

namespace dogen {
namespace cpp {

sml_to_cpp_info::
sml_to_cpp_info(const locator& locator,
    const includer& includer,
    const config::cpp_settings& settings,
    const sml::model& model) :
    locator_(locator),
    includer_(includer),
    settings_(settings),
    model_(model),
    root_vertex_(boost::add_vertex(graph_)) { }

void sml_to_cpp_info::log_includers() const {
    if (settings_.disable_facet_includers())
        BOOST_LOG_SEV(lg, warn) << "Includers are NOT enabled, "
                                << "NOT generating views for them.";
    else
        BOOST_LOG_SEV(lg, info) << "Includers are enabled, "
                                << "so generating views for them.";
}

void sml_to_cpp_info::
log_generating_file(config::cpp_facet_types facet, aspect_types aspect,
    file_types ft, std::string name, sml::meta_types mt) const {
    BOOST_LOG_SEV(lg, debug) << "Generating file view model. "
                             << "facet type: " << facet
                             << " aspect type: " << aspect
                             << " file type: " << ft
                             << " meta type: " << mt
                             << " name: " << name;
}

void sml_to_cpp_info::log_started() const {
    BOOST_LOG_SEV(lg, info) << "Started transforming.";
}

void sml_to_cpp_info::log_finished(unsigned int count) const {
    BOOST_LOG_SEV(lg, info) << "Finished transforming. "
                            << "Generated files count: " << count;
}

std::string sml_to_cpp_info::
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

location_request sml_to_cpp_info::
location_request_factory(config::cpp_facet_types ft, file_types flt,
    aspect_types at, const sml::qname& n) const {

    location_request r;
    r.facet_type(ft);
    r.file_type(flt);
    r.aspect_type(at);
    r.model_name(model_.name());
    r.package_path(n.package_path());
    r.file_name(n.type_name());
    r.external_package_path(n.external_package_path());
    return r;
}

file_info sml_to_cpp_info::
create_file(config::cpp_facet_types ft, file_types flt, aspect_types at,
    const sml::qname& name) {
    file_info r;
    r.facet_type(ft);
    r.file_type(flt);
    r.aspect_type(at);

    auto rq(location_request_factory(ft, flt, at, name));
    r.file_path(locator_.absolute_path(rq));

    if (flt == file_types::header) {
        rq = location_request_factory(ft, flt, at, name);
        const auto rp(locator_.relative_logical_path(rq));
        r.header_guard(to_header_guard_name(rp));
        if (at == aspect_types::main)
            includer_.register_header(ft, rp);
    }

    return r;
}

file_info sml_to_cpp_info::
transform_file(config::cpp_facet_types ft, file_types flt,
    aspect_types at, const sml::pod& p) {
    const sml::qname name(p.name());
    const std::list<std::string> ns(join_namespaces(name));

    file_info r(create_file(ft, flt, at, name));
    r.category_type(p.category_type());
    r.meta_type(p.name().meta_type());

    if (at != aspect_types::forward_decls &&
        p.generation_type() == sml::generation_types::partial_generation)
        r.aspect_type(aspect_types::null_aspect);

    const auto i(qname_to_class_.find(name));
    if (i == qname_to_class_.end()) {
        BOOST_LOG_SEV(lg, error) << info_not_found
                                 << name.type_name();

        BOOST_LOG_SEV(lg, error) << info_not_found << name.type_name();
        BOOST_THROW_EXCEPTION(transformation_error(info_not_found +
                name.type_name()));
    }
    r.class_info(i->second);

    const auto includes(includer_.includes_for_pod(p, ft, flt, at));
    r.system_includes(includes.system);
    r.user_includes(includes.user);
    return r;
}

file_info sml_to_cpp_info::
transform_file(config::cpp_facet_types ft, file_types flt,
    aspect_types at, const sml::service& s) {
    const sml::qname name(s.name());
    const std::list<std::string> ns(join_namespaces(name));

    file_info r(create_file(ft, flt, at, name));
    r.category_type(sml::category_types::user_defined);
    r.meta_type(s.name().meta_type());

    if (at != aspect_types::forward_decls &&
        s.generation_type() == sml::generation_types::partial_generation)
        r.aspect_type(aspect_types::null_aspect);

    const auto i(qname_to_class_.find(name));
    if (i == qname_to_class_.end()) {
        BOOST_LOG_SEV(lg, error) << info_not_found
                                 << name.type_name();

        BOOST_LOG_SEV(lg, error) << info_not_found << name.type_name();
        BOOST_THROW_EXCEPTION(transformation_error(info_not_found +
                name.type_name()));
    }
    r.class_info(i->second);

    // FIXME
    // const auto includes(includer_.includes_for_pod(s, ft, flt, at));
    // r.system_includes(includes.system);
    // r.user_includes(includes.user);
    return r;
}

file_info sml_to_cpp_info::
transform_file(config::cpp_facet_types ft, file_types flt,
    aspect_types at, const sml::enumeration& e) {
    const sml::qname name(e.name());
    const std::list<std::string> ns(join_namespaces(name));

    file_info r(create_file(ft, flt, at, name));
    r.category_type(sml::category_types::user_defined);
    r.meta_type(e.name().meta_type());

    const auto i(qname_to_enumeration_.find(name));
    if (i == qname_to_enumeration_.end()) {
        BOOST_LOG_SEV(lg, error) << info_not_found
                                 << name.type_name();

        BOOST_THROW_EXCEPTION(transformation_error(info_not_found +
                name.type_name()));
    }
    r.enumeration_info(i->second);

    const auto in(includer_.includes_for_enumeration(e, ft, flt, at));
    r.system_includes(in.system);
    r.user_includes(in.user);
    return r;
}

file_info sml_to_cpp_info::
transform_file(config::cpp_facet_types ft, file_types flt,
    aspect_types at, const sml::exception& e) {
    const sml::qname name(e.name());
    const std::list<std::string> ns(join_namespaces(name));

    file_info r(create_file(ft, flt, at, name));
    r.category_type(sml::category_types::user_defined);
    r.meta_type(e.name().meta_type());

    const auto i(qname_to_exception_.find(name));
    if (i == qname_to_exception_.end()) {
        BOOST_LOG_SEV(lg, error) << info_not_found
                                 << name.type_name();

        BOOST_THROW_EXCEPTION(transformation_error(info_not_found +
                name.type_name()));
    }
    r.exception_info(i->second);

    const auto in(includer_.includes_for_exception(e, ft, flt, at));
    r.system_includes(in.system);
    r.user_includes(in.user);
    return r;
}

bool sml_to_cpp_info::has_implementation(const config::cpp_facet_types ft,
    const dogen::sml::meta_types mt) const {
    using dogen::sml::meta_types;
    using config::cpp_facet_types;
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

bool sml_to_cpp_info::has_forward_decls(const config::cpp_facet_types ft,
    const dogen::sml::meta_types mt) const {
    using dogen::sml::meta_types;
    using config::cpp_facet_types;
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

void sml_to_cpp_info::create_class_infos() {
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
            const vertex_descriptor_type
                parent_vertex(lambda(*pod.parent_name()));
            boost::add_edge(parent_vertex, vertex, graph_);
        } else
            boost::add_edge(root_vertex_, vertex, graph_);
    }

    sml_dfs_visitor v(pods);
    boost::depth_first_search(graph_, boost::visitor(v));
    qname_to_class_ = v.class_infos();
    qname_to_visitor_ = v.visitor_infos();
}

void sml_to_cpp_info::create_enumeration_infos() {
    const auto enumerations(model_.enumerations());
    BOOST_LOG_SEV(lg, debug) << "Transforming enumerations: "
                             << enumerations.size();

    for (const auto pair : enumerations) {
        const auto e(pair.second);
        const dogen::sml::qname name(e.name());
        const std::list<std::string> ns(join_namespaces(name));

        enumeration_info ei;
        ei.name(e.name().type_name());
        ei.namespaces(ns);
        ei.documentation(e.documentation());
        std::list<enumerator_info> enumerators;
        for (const auto en : e.enumerators()) {
            enumerator_info ei;
            ei.name(en.name());
            ei.value(en.value());
            ei.documentation(en.documentation());
            enumerators.push_back(ei);
        }
        ei.enumerators(enumerators);
        qname_to_enumeration_.insert(std::make_pair(e.name(), ei));
    }
}

void sml_to_cpp_info::create_exception_infos() {
    const auto exceptions(model_.exceptions());
    BOOST_LOG_SEV(lg, debug) << "Transforming exceptions: "
                             << exceptions.size();

    for (const auto pair : exceptions) {
        const auto e(pair.second);
        const dogen::sml::qname name(e.name());
        const std::list<std::string> ns(join_namespaces(name));

        exception_info ei;
        ei.name(e.name().type_name());
        ei.namespaces(ns);
        ei.documentation(e.documentation());
        qname_to_exception_.insert(std::make_pair(e.name(), ei));
    }
}

std::set<config::cpp_facet_types> sml_to_cpp_info::
enabled_facet_types(const sml::meta_types mt, const sml::pod_types pt) const {
    // FIXME: services hack
    // using config::cpp_facet_types;
    // using sml::meta_types;
    // if (mt == meta_types::pod) {
    //     if (pt == sml::pod_types::value || pt == sml::pod_types::entity)
    //         return settings_.enabled_facets();
    // } else if (mt == meta_types::enumeration || mt == meta_types::primitive)
    //     return settings_.enabled_facets();
    // else if (mt == meta_types::exception || mt == meta_types::service)
    //     return std::set<cpp_facet_types> { cpp_facet_types::types };
    using config::cpp_facet_types;
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

    BOOST_LOG_SEV(lg, error) << invalid_enabled_facets
                             << boost::lexical_cast<std::string>(mt)
                             << boost::lexical_cast<std::string>(pt);

    BOOST_THROW_EXCEPTION(transformation_error(invalid_enabled_facets +
            boost::lexical_cast<std::string>(mt) + ", " +
            boost::lexical_cast<std::string>(pt)));
}

std::vector<file_info> sml_to_cpp_info::transform_pods() {
    std::vector<file_info> r;
    using config::cpp_facet_types;
    auto lambda([&](cpp_facet_types ft, file_types flt, aspect_types at,
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
            const auto header(file_types::header);
            const auto implementation(file_types::implementation);
            const auto main(aspect_types::main);
            const auto forward_decls(aspect_types::forward_decls);
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
            e << errmsg_sml_to_cpp_info(failed_to_process_type +
                boost::lexical_cast<std::string>(p.name()));
            throw;
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Transformed pods: " << pods.size();
    return r;
}

std::vector<file_info> sml_to_cpp_info::transform_services() {
    std::vector<file_info> r;
    using config::cpp_facet_types;
    auto lambda([&](cpp_facet_types ft, file_types flt, aspect_types at,
            const sml::service& s) {
            const std::string n(s.name().type_name());
            log_generating_file(ft, at, flt, n, s.name().meta_type());
            r.push_back(transform_file(ft, flt, at, s));
        });

    for (const auto& pair : model_.services()) {
        const auto& s(pair.second);

        if (s.generation_type() == sml::generation_types::no_generation)
            continue;

        try {
            const auto header(file_types::header);
            const auto implementation(file_types::implementation);
            const auto main(aspect_types::main);
            const auto forward_decls(aspect_types::forward_decls);
            const auto pod_mt(sml::meta_types::pod);
            const auto facets(enabled_facet_types(pod_mt));

            for (const auto ft: facets) {
                lambda(ft, header, main, s);

                if (has_implementation(ft, pod_mt))
                    lambda(ft, implementation, main, s);

                if (has_forward_decls(ft, pod_mt))
                    lambda(ft, header, forward_decls, s);
            }
        } catch (boost::exception& e) {
            e << errmsg_sml_to_cpp_info(failed_to_process_type +
                boost::lexical_cast<std::string>(s.name()));
            throw;
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Transformed services: "
                             << model_.services().size();
    return r;
}

std::vector<file_info> sml_to_cpp_info::transform_enumerations() {
    std::vector<file_info> r;
    using config::cpp_facet_types;
    auto lambda([&](cpp_facet_types ft, file_types flt, aspect_types at,
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
            const auto header(file_types::header);
            const auto implementation(file_types::implementation);
            const auto main(aspect_types::main);
            const auto forward_decls(aspect_types::forward_decls);
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
            ex << errmsg_sml_to_cpp_info(failed_to_process_type +
                boost::lexical_cast<std::string>(e.name()));
            throw;
        }
    }
    return r;
}

std::vector<file_info> sml_to_cpp_info::transform_packages() {
    std::vector<file_info> r;
    if (!model_.documentation().empty()) {
        sml::qname qn;
        qn.type_name(model_.name());
        qn.external_package_path(model_.external_package_path());
        qn.meta_type(sml::meta_types::package);

        using config::cpp_facet_types;
        const auto ft(cpp_facet_types::types);
        const auto at(aspect_types::namespace_doc);
        const file_types file_type(file_types::header);

        log_generating_file(ft, at, file_type, qn.type_name(), qn.meta_type());
        const std::list<std::string> ns(join_namespaces(qn));

        const auto rq(location_request_factory(ft, file_type, at, qn));
        const auto rp(locator_.relative_logical_path(rq));

        file_info fi;
        fi.header_guard(to_header_guard_name(rp));
        fi.facet_type(ft);
        fi.file_path(locator_.absolute_path(rq));
        fi.file_type(file_type);
        fi.aspect_type(at);
        fi.meta_type(qn.meta_type());

        namespace_info ni;
        ni.documentation(model_.documentation());
        ni.namespaces(ns);
        fi.namespace_info(ni);
        r.push_back(fi);
    }

    for (const auto& p : model_.packages()) {
        if (p.second.documentation().empty())
            continue;

        using config::cpp_facet_types;
        const auto ft(cpp_facet_types::types);
        const auto at(aspect_types::namespace_doc);
        const file_types file_type(file_types::header);
        sml::qname qn(p.second.name());
        qn.package_path().push_back(p.second.name().type_name());
        // FIXME: for some reason this line causes AVs on Win32
        // log_generating_file(ft, at, file_type, qn.type_name(), qn.meta_type());
        const auto rq(location_request_factory(ft, file_type, at, qn));
        const auto rp(locator_.relative_logical_path(rq));

        qn = p.second.name();
        const std::list<std::string> ns(join_namespaces(qn));

        file_info fi;
        fi.header_guard(to_header_guard_name(rp));
        fi.facet_type(ft);
        fi.file_path(locator_.absolute_path(rq));
        fi.file_type(file_type);
        fi.aspect_type(at);
        fi.meta_type(qn.meta_type());

        namespace_info ni;
        ni.documentation(p.second.documentation());
        ni.namespaces(ns);
        fi.namespace_info(ni);

        r.push_back(fi);
    }

    BOOST_LOG_SEV(lg, debug) << "Transformed packages: "
                             << model_.packages().size();

    return r;
}

std::vector<file_info> sml_to_cpp_info::transform_exceptions() {
    std::vector<file_info> r;
    using config::cpp_facet_types;
    auto lambda([&](cpp_facet_types ft, file_types flt, aspect_types at,
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
            const auto header(file_types::header);
            const auto main(aspect_types::main);
            const auto forward_decls(aspect_types::forward_decls);
            const auto exception_mt(sml::meta_types::exception);
            const auto facets(enabled_facet_types(exception_mt));

            for (const auto ft : facets) {
                lambda(ft, header, main, e);

                if (has_forward_decls(ft, sml::meta_types::exception))
                    lambda(ft, header, forward_decls, e);
            }
        } catch (boost::exception& ex) {
            ex << errmsg_sml_to_cpp_info(failed_to_process_type +
                boost::lexical_cast<std::string>(e.name()));
            throw;
        }
    }
    return r;
}

std::vector<file_info>
sml_to_cpp_info::transform_facet_includers() const {
    std::vector<file_info> r;
    const file_types file_type(file_types::header);
    const auto at(aspect_types::includers);

    using config::cpp_facet_types;
    for (cpp_facet_types ft : settings_.enabled_facets()) {
        sml::qname qn;
        const auto n(includer_name);
        log_generating_file(ft, at, file_type, n, sml::meta_types::invalid);
        qn.type_name(n);
        qn.external_package_path(model_.external_package_path());
        const auto rq(location_request_factory(ft, file_type, at, qn));

        file_info fi;
        fi.facet_type(ft);
        fi.file_path(locator_.absolute_path(rq));
        fi.file_type(file_type);
        fi.aspect_type(at);

        const auto includes(includer_.includes_for_includer_files(ft));
        fi.system_includes(includes.system);
        fi.user_includes(includes.user);

        r.push_back(fi);
    }
    return r;
}

std::vector<file_info> sml_to_cpp_info::transform_visitors() {
    std::vector<file_info> r;
    const file_types file_type(file_types::header);
    const auto at(aspect_types::visitor);
    const auto ft(config::cpp_facet_types::types);

    for (const auto& v : qname_to_visitor_) {
        const auto n(v.first.type_name());
        log_generating_file(ft, at, file_type, n, sml::meta_types::invalid);
        sml::qname qn;
        qn.type_name(n);
        qn.external_package_path(v.first.external_package_path());
        const auto rq(location_request_factory(ft, file_type, at, qn));

        file_info fi;
        fi.facet_type(ft);
        fi.file_path(locator_.absolute_path(rq));
        fi.file_type(file_type);
        fi.aspect_type(at);
        fi.visitor_info(v.second);

        // FIXME: hack to solve ordering issues
        fi.visitor_info()->types().sort();

        const auto rp(locator_.relative_logical_path(rq));
        fi.header_guard(to_header_guard_name(rp));

        const auto includes(includer_.includes_for_visitor(v.first));
        fi.system_includes(includes.system);
        fi.user_includes(includes.user);

        r.push_back(fi);
    }
    return r;
}

std::vector<file_info>
sml_to_cpp_info::transform_registrar() const {
    std::vector<file_info> r;
    const auto facets(settings_.enabled_facets());
    using config::cpp_facet_types;
    if (facets.find(cpp_facet_types::serialization) == facets.end()) {
        BOOST_LOG_SEV(lg, warn) << "Serialisaton not enabled"
                                << " so NOT generating registrar";
        return r;
    }

    BOOST_LOG_SEV(lg, debug) << "Transforming serialisaton registrar";

    sml::qname qn;
    qn.model_name(model_.name());
    qn.external_package_path(model_.external_package_path());

    registrar_info ri;
    ri.namespaces(join_namespaces(qn));
    BOOST_LOG_SEV(lg, debug) << "Added namespaces: " << ri.namespaces();

    std::list<std::string> deps;
    for (const auto& pair : model_.dependencies()) {
        const auto d(pair.second);
        if (!d.is_system())
            deps.push_back(d.model_name());
    }
    ri.model_dependencies(deps);
    BOOST_LOG_SEV(lg, debug) << "Added dependencies: "
                             << ri.model_dependencies();

    std::list<std::string> leaves;
    using boost::join;
    for (const auto& l : model_.leaves()) {
        auto ns(join_namespaces(l));
        ns.push_back(l.type_name());
        leaves.push_back(join(ns, namespace_separator));
    }
    leaves.sort();
    ri.leaves(leaves);
    BOOST_LOG_SEV(lg, debug) << "Added leaves: " << ri.leaves();

    using config::cpp_facet_types;
    auto lambda([&](const file_types flt) ->  file_info {
            file_info fi;
            const auto ft(cpp_facet_types::serialization);
            const auto at(aspect_types::registrar);
            const auto n(registrar_name);
            log_generating_file(ft, at, flt, n, sml::meta_types::invalid);
            qn.type_name(n);
            qn.external_package_path(model_.external_package_path());
            const auto rq(location_request_factory(ft, flt, at, qn));

            fi.facet_type(ft);
            fi.file_path(locator_.absolute_path(rq));
            fi.file_type(flt);
            fi.aspect_type(at);
            fi.registrar_info(ri);

            const auto includes(includer_.includes_for_registrar(flt));
            fi.system_includes(includes.system);
            fi.user_includes(includes.user);

            return fi;
        });

    r.push_back(lambda(file_types::header));
    r.push_back(lambda(file_types::implementation));
    return r;
}

std::vector<file_info> sml_to_cpp_info::transform() {
    log_started();
    create_class_infos();
    create_enumeration_infos();
    create_exception_infos();

    std::vector<file_info> r;
    auto p(transform_pods());
    auto e(transform_enumerations());
    auto ex(transform_exceptions());
    auto reg(transform_registrar());
    auto pkg(transform_packages());
    auto vis(transform_visitors());
    // auto ser(transform_services()); // FIXME: services hack

    r.reserve(p.size() + e.size() + ex.size() + reg.size() + pkg.size());
    r.insert(r.end(), p.begin(), p.end());
    r.insert(r.end(), e.begin(), e.end());
    r.insert(r.end(), ex.begin(), ex.end());
    r.insert(r.end(), reg.begin(), reg.end());
    r.insert(r.end(), pkg.begin(), pkg.end());
    r.insert(r.end(), vis.begin(), vis.end());
    // r.insert(r.end(), ser.begin(), ser.end()); // FIXME: services hack

    log_includers();
    if (settings_.disable_facet_includers())
        return r;

    const auto fi(transform_facet_includers());
    r.insert(r.end(), fi.begin(), fi.end());
    log_finished(r.size());
    return r;
}

} }
