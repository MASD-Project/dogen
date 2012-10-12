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
#include <boost/tuple/tuple.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/graph/depth_first_search.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/generator/backends/cpp/view_models/transformation_error.hpp"
#include "dogen/generator/backends/cpp/view_models/sml_to_cpp_view_model.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("sml_to_view_model"));

const std::string empty;
const std::list<std::string> empty_package_path;
const std::string dot(".");
const std::string separator("_");
const std::string extension("HPP");
const std::string namespace_separator("::");

const std::string parent_view_model_not_found(
    "Parent view model not found for pod: ");
const std::string view_model_not_found("View model not found for pod: ");
const std::string includer_name("all");
const std::string versioned_name("versioned_key");
const std::string unversioned_name("unversioned_key");
const std::string id_name("id");
const std::string version_name("version");
const std::string uint_name("unsigned int");
const std::string bool_type("bool");

/**
 * @brief Flattens all the SML namespace information stored in
 * qualified name into a list of strings with C++ namespaces.
 */
std::list<std::string> join_namespaces(const dogen::sml::qualified_name& name) {
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
std::string database_name(const dogen::sml::qualified_name& name) {
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
    dogen::sml::qualified_name,
    dogen::generator::backends::cpp::view_models::class_view_model>
    qname_to_class_view_model_type;

    struct visit_state {
        visit_state(const std::string& schema_name, bool disable_keys,
            const std::unordered_set<dogen::sml::qualified_name>& parent_names)
            : schema_name_(schema_name), disable_keys_(disable_keys),
              parent_names_(parent_names) { }

        qname_to_class_view_model_type class_view_models_;
        const std::string schema_name_;
        const bool disable_keys_;
        const std::unordered_set<dogen::sml::qualified_name> parent_names_;
    };

public:
    sml_dfs_visitor& operator=(const sml_dfs_visitor&) = default;
    sml_dfs_visitor(const sml_dfs_visitor&) = default;
    sml_dfs_visitor(sml_dfs_visitor&&) = default;

public:
    sml_dfs_visitor(const std::string& schema_name, bool disable_keys,
        const std::unordered_set<dogen::sml::qualified_name>& parent_names)
        : state_(new visit_state(schema_name, disable_keys, parent_names)) { }

public:
    template<typename Vertex, typename Graph>
    void discover_vertex(const Vertex& u, const Graph& g) {
        process_sml_pod(g[u]);
    }

    template<typename Vertex, typename Graph>
    void finish_vertex(const Vertex& /*u*/, const Graph& /*g*/) {
    }

private:
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

void sml_dfs_visitor::process_sml_pod(const dogen::sml::pod& pod) {
    const dogen::sml::qualified_name name(pod.name());
    const std::list<std::string> ns(join_namespaces(name));

    using namespace dogen::generator::backends::cpp::view_models;
    class_view_model cvm(name.type_name());

    if (pod.parent_name()) {
        const auto pqn(*pod.parent_name());
        BOOST_LOG_SEV(lg, debug) << "Class '" << name.type_name()
                                 << "' has parent '" << pqn.type_name() << "'";

        const auto i(state_->class_view_models_.find(pqn));
        if (i == state_->class_view_models_.end()) {
            throw transformation_error(parent_view_model_not_found +
                name.type_name());
        }

        parent_view_model parent(pqn.type_name());
        parent.properties(i->second.properties());
        parent.namespaces(i->second.namespaces());

        std::list<parent_view_model> parents;
        parents.push_back(parent);
        cvm.parents(parents);
    }

    cvm.namespaces(ns);
    cvm.database_name(database_name(name));
    cvm.schema_name(state_->schema_name_);

    const auto pn(state_->parent_names_);
    cvm.is_parent(pn.find(name) != pn.end());

    std::list<property_view_model> properties_vm;
    bool has_primitive_properties(false);
    bool has_boolean_properties(false);
    for(const auto p : pod.properties()) {
        std::list<std::string> ns_list(join_namespaces(p.type_name()));
        ns_list.push_back(p.type_name().type_name());

        using boost::algorithm::join;
        const std::string ns(join(ns_list, namespace_separator));
        property_view_model k(p.name());
        k.type(ns);

        using dogen::sml::meta_types;
        k.is_primitive(p.type_name().meta_type() == meta_types::primitive);
        if (k.is_primitive()) {
            has_primitive_properties = true;
            if (k.type() == bool_type)
                has_boolean_properties = true;
        }
        properties_vm.push_back(k);
    }

    if (!state_->disable_keys_) {
        dogen::sml::qualified_name vn;
        vn.type_name(versioned_name);
        vn.model_name(name.model_name());
        vn.external_package_path(name.external_package_path());

        std::list<std::string> ns_list(join_namespaces(vn));
        ns_list.push_back(versioned_name);

        using boost::algorithm::join;
        const std::string ns(join(ns_list, namespace_separator));
        property_view_model k(versioned_name);
        k.type(ns);
        k.is_primitive(false);
        properties_vm.push_back(k);
    }

    cvm.properties(properties_vm);
    cvm.has_primitive_properties(has_primitive_properties);
    cvm.has_boolean_properties(has_boolean_properties);
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
    const std::set<cpp_facet_types>& facet_types,
    const sml::model& model, bool disable_facet_includers,
    bool disable_keys, bool use_integrated_io, bool disable_io) :
    location_manager_(location_manager),
    facet_types_(facet_types),
    model_(model), disable_facet_includers_(disable_facet_includers),
    disable_keys_(disable_keys),
    dependency_manager_(model, location_manager, disable_keys,
        use_integrated_io, disable_io),
    root_vertex_(boost::add_vertex(graph_)) { }

void sml_to_cpp_view_model::log_keys() const {
    if (disable_keys_)
        BOOST_LOG_SEV(lg, warn) << "Keys are NOT enabled, "
                                << "NOT generating views for them.";
    else
        BOOST_LOG_SEV(lg, info) << "Keys are enabled, "
                                << "so generating views for them.";
}

void sml_to_cpp_view_model::log_includers() const {
    if (disable_facet_includers_)
        BOOST_LOG_SEV(lg, warn) << "Includers are NOT enabled, "
                                << "NOT generating views for them.";
    else
        BOOST_LOG_SEV(lg, info) << "Includers are enabled, "
                                << "so generating views for them.";
}

void sml_to_cpp_view_model::
log_generating_file(cpp_facet_types facet, cpp_aspect_types aspect,
    cpp_file_types ft, std::string name) const {
    BOOST_LOG_SEV(lg, debug) << "Generating file view model. "
                             << "facet type: " << facet
                             << " aspect type: " << aspect
                             << " file type: " << ft
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
location_request_factory(cpp_facet_types facet_type, cpp_file_types file_type,
    sml::qualified_name name) const {

    cpp_location_request r;
    r.facet_type(facet_type);
    r.file_type(file_type);
    r.model_name(model_.name());
    r.package_path(name.package_path());
    r.file_name(name.type_name());
    r.external_package_path(name.external_package_path());
    return r;
}

file_view_model sml_to_cpp_view_model::
transform_file(cpp_facet_types ft, cpp_file_types flt, const sml::pod& pod) {
    const sml::qualified_name name(pod.name());
    const std::list<std::string> ns(join_namespaces(name));

    file_view_model r;
    r.facet_type(ft);
    r.file_type(flt);
    r.aspect_type(cpp_aspect_types::main);

    const auto i(qname_to_class_.find(name));
    if (i == qname_to_class_.end())
        throw transformation_error(view_model_not_found + name.type_name());

    r.class_vm(i->second);
    auto rq(location_request_factory(ft, flt, name));
    r.file_path(location_manager_.absolute_path(rq));

    if (flt == cpp_file_types::header) {
        rq = location_request_factory(ft, flt, name);
        const auto rp(location_manager_.relative_logical_path(rq));
        r.header_guard(to_header_guard_name(rp));
        dependency_manager_.register_header(ft, rp);
    }

    const cpp_aspect_types at(cpp_aspect_types::main);
    r.system_dependencies(dependency_manager_.system(pod, ft, flt, at));
    r.user_dependencies(dependency_manager_.user(pod, ft, flt, at));
    return r;
}

bool sml_to_cpp_view_model::
has_implementation(cpp_facet_types facet_type) const {
    return
        facet_type == cpp_facet_types::domain ||
        facet_type == cpp_facet_types::io ||
        facet_type == cpp_facet_types::database ||
        facet_type == cpp_facet_types::test_data;
}

void sml_to_cpp_view_model::setup_qualified_name_to_class_view_model_map() {
    const auto pods(model_.pods());
    BOOST_LOG_SEV(lg, debug) << "Transforming pods: " << pods.size();

    auto pi([&](const sml::qualified_name& qname) -> vertex_descriptor_type {
            const auto i(qname_to_vertex_.find(qname));
            if (i != qname_to_vertex_.end())
                return i->second;

            const auto vertex(boost::add_vertex(graph_));
            qname_to_vertex_.insert(std::make_pair(qname, vertex));
            return vertex;
        });

    std::unordered_set<dogen::sml::qualified_name> parent_names;
    for (const auto pair : model_.pods()) {
        const vertex_descriptor_type vertex(pi(pair.first));
        const auto pod(pair.second);
        graph_[vertex] = pod;

        if (pod.parent_name()) {
            const vertex_descriptor_type parent_vertex(pi(*pod.parent_name()));
            boost::add_edge(parent_vertex, vertex, graph_);
            parent_names.insert(*pod.parent_name());
        } else
            boost::add_edge(root_vertex_, vertex, graph_);
    }

    sml_dfs_visitor v(model_.schema_name(), disable_keys_, parent_names);
    boost::depth_first_search(graph_, boost::visitor(v));
    qname_to_class_ = v.class_view_models();
}

std::vector<file_view_model> sml_to_cpp_view_model::transform_pods() {
    std::vector<file_view_model> r;
    auto lambda([&](cpp_facet_types f, cpp_file_types ft, sml::pod p) {
            const std::string n(p.name().type_name());
            log_generating_file(f, cpp_aspect_types::main, ft, n);
            r.push_back(transform_file(f, ft, p));
        });

    const auto pods(model_.pods());
    for (auto pair : pods) {
        const sml::pod p(pair.second);

        if (!p.generate())
            continue;

        for (const auto ft: facet_types_) {
            lambda(ft, cpp_file_types::header, p);

            if (has_implementation(ft))
                lambda(ft, cpp_file_types::implementation, p);
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Transformed pods: " << pods.size();
    return r;
}

class_view_model
sml_to_cpp_view_model::create_key_class_view_model(bool is_versioned) const {
    const std::string name(is_versioned ? versioned_name : unversioned_name);
    BOOST_LOG_SEV(lg, debug) << "Creating key class" << name;

    class_view_model r;
    r.name(name);

    sml::qualified_name qn;
    qn.type_name(name);
    qn.model_name(model_.name());
    qn.external_package_path(model_.external_package_path());

    const std::list<std::string> ns(join_namespaces(qn));
    r.namespaces(ns);

    auto lambda([](std::string name, std::string type) -> property_view_model {
            property_view_model r(name);
            r.type(type);
            r.is_primitive(true);
            return r;
        });

    std::list<property_view_model> properties;
    properties.push_back(lambda(id_name, uint_name));
    if (is_versioned)
        properties.push_back(lambda(version_name, uint_name));
    r.properties(properties);
    r.has_primitive_properties(true);

    BOOST_LOG_SEV(lg, debug) << "Created key class" << name;
    return r;
}

file_view_model sml_to_cpp_view_model::
create_key_file_view_model(cpp_facet_types ft, cpp_file_types flt,
    cpp_aspect_types at) {
    file_view_model r;
    r.facet_type(ft);
    r.file_type(flt);
    r.aspect_type(at);

    const bool is_versioned(at == cpp_aspect_types::versioned_key);
    r.class_vm(create_key_class_view_model(is_versioned));

    const std::string name(r.class_vm()->name());
    log_generating_file(ft, at, flt, name);
    r.system_dependencies(dependency_manager_.system(name, ft, flt, at));
    r.user_dependencies(dependency_manager_.user(name, ft, flt, at));

    sml::qualified_name qn;
    qn.external_package_path(model_.external_package_path());
    qn.type_name(name);
    qn.model_name(model_.name());

    if (flt == cpp_file_types::header) {
        const auto rq(location_request_factory(ft, flt, qn));
        const auto rp(location_manager_.relative_logical_path(rq));
        r.header_guard(to_header_guard_name(rp));
        dependency_manager_.register_header(ft, rp);
    }

    const auto rq(location_request_factory(ft, flt, qn));
    r.file_path(location_manager_.absolute_path(rq));
    return r;
}

std::vector<file_view_model>
sml_to_cpp_view_model::transform_keys() {
    std::vector<file_view_model> r;

    const auto h(cpp_file_types::header);
    const auto i(cpp_file_types::implementation);
    const auto v(cpp_aspect_types::versioned_key);
    const auto u(cpp_aspect_types::unversioned_key);

    for (cpp_facet_types ft : facet_types_) {
        if (ft == cpp_facet_types::database)
            continue;

        r.push_back(create_key_file_view_model(ft, h, v));
        r.push_back(create_key_file_view_model(ft, h, u));

        if (has_implementation(ft)) {
            r.push_back(create_key_file_view_model(ft, i, v));
            r.push_back(create_key_file_view_model(ft, i, u));
        }
    }
    return r;
}

std::vector<file_view_model>
sml_to_cpp_view_model::transform_facet_includers() const {
    std::vector<file_view_model> r;
    const cpp_file_types file_type(cpp_file_types::header);
    const auto aspect_type(cpp_aspect_types::includers);

    for (cpp_facet_types ft : facet_types_) {
        sml::qualified_name qn;
        const auto n(includer_name);
        log_generating_file(ft, aspect_type, file_type, n);
        qn.type_name(n);
        qn.external_package_path(model_.external_package_path());
        const auto rq(location_request_factory(ft, file_type, qn));

        file_view_model vm;
        vm.facet_type(ft);
        vm.file_path(location_manager_.absolute_path(rq));
        vm.file_type(file_type);

        const auto a(cpp_aspect_types::includers);
        vm.system_dependencies(dependency_manager_.system(n, ft, file_type, a));
        vm.user_dependencies(dependency_manager_.user(n, ft, file_type, a));
        vm.aspect_type(a);

        r.push_back(vm);
    }
    return r;
}

std::vector<file_view_model> sml_to_cpp_view_model::transform() {
    log_started();
    setup_qualified_name_to_class_view_model_map();
    auto r(transform_pods());

    log_keys();
    if (!disable_keys_) {
        const auto k(transform_keys());
        r.insert(r.end(), k.begin(), k.end());
    }

    log_includers();
    if (disable_facet_includers_)
        return r;

    const auto fi(transform_facet_includers());
    r.insert(r.end(), fi.begin(), fi.end());
    log_finished(r.size());
    return r;
}

} } } } }
