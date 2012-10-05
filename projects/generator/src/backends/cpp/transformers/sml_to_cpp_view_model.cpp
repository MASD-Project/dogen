/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <list>
#include <sstream>
#include <boost/tuple/tuple.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/generator/backends/cpp/transformers/sml_to_cpp_view_model.hpp"

namespace {

static dogen::utility::log::logger
lg(dogen::utility::log::logger_factory("sml_to_view_model"));

const std::string empty;
const std::list<std::string> empty_package_path;
const std::string dot(".");
const std::string separator("_");
const std::string extension("HPP");
const std::string namespace_separator("::");
const std::string unammed_model("unnamed_model");

const std::string includer_name("all");
const std::string versioned_name("versioned_key");
const std::string unversioned_name("unversioned_key");
const std::string id_name("id");
const std::string version_name("version");
const std::string uint_name("unsigned int");
const std::string bool_type("bool");

}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace transformers {

sml_to_cpp_view_model::
sml_to_cpp_view_model(cpp_location_manager location_manager,
    std::set<cpp_facet_types> facet_types,
    sml::model model, bool disable_facet_includers,
    bool disable_keys, bool use_integrated_io, bool disable_io) :
    location_manager_(location_manager),
    facet_types_(facet_types),
    model_(model), disable_facet_includers_(disable_facet_includers),
    disable_keys_(disable_keys),
    dependency_manager_(model, location_manager, disable_keys,
        use_integrated_io, disable_io) { }

void sml_to_cpp_view_model::log_keys() const {
    using namespace dogen::utility::log;
    if (disable_keys_)
        BOOST_LOG_SEV(lg, warn) << "Keys are NOT enabled, "
                                << "NOT generating views for them.";
    else
        BOOST_LOG_SEV(lg, info) << "Keys are enabled, "
                                << "so generating views for them.";
}

void sml_to_cpp_view_model::log_includers() const {
    using namespace dogen::utility::log;
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
    using namespace dogen::utility::log;
    BOOST_LOG_SEV(lg, debug) << "Generating file view model. "
                             << "facet type: " << facet
                             << " aspect type: " << aspect
                             << " file type: " << ft
                             << " name: " << name;
}


void sml_to_cpp_view_model::log_started() const {
    using namespace dogen::utility::log;
    BOOST_LOG_SEV(lg, info) << "Started transforming.";
}

void sml_to_cpp_view_model::log_finished(unsigned int count) const {
    using namespace dogen::utility::log;
    BOOST_LOG_SEV(lg, info) << "Finished transforming. "
                            << "Generated files count: " << count;
}

std::list<std::string> sml_to_cpp_view_model::
join_namespaces(sml::qualified_name name) const {
    std::list<std::string> result(name.external_package_path());

    if (!name.model_name().empty())
        result.push_back(name.model_name());

    std::list<std::string> package_path(name.package_path());
    result.insert(result.end(), package_path.begin(), package_path.end());
    return result;
}

std::string sml_to_cpp_view_model::
database_name(sml::qualified_name name) const {
    std::ostringstream stream;

    if (!name.model_name().empty())
        stream << name.model_name() << "_";

    for (const auto p : name.package_path())
        stream << p << "_";

    stream << name.type_name();

    return stream.str();
}

std::string sml_to_cpp_view_model::
to_header_guard_name(boost::filesystem::path relative_path) const {
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

view_models::class_view_model sml_to_cpp_view_model::transform_class(
    sml::pod pod, std::list<std::string> namespaces) const {
    const sml::qualified_name name(pod.name());
    view_models::class_view_model r(name.type_name());
    r.namespaces(namespaces);
    r.database_name(database_name(name));
    r.schema_name(model_.schema_name());

    std::list<view_models::property_view_model> properties_vm;
    bool has_primitive_properties(false);
    bool has_boolean_properties(false);
    for(const auto p : pod.properties()) {
        std::list<std::string> ns_list(join_namespaces(p.type_name()));
        ns_list.push_back(p.type_name().type_name());

        using boost::algorithm::join;
        const std::string ns(join(ns_list, namespace_separator));
        view_models::property_view_model k(p.name());
        k.type(ns);
        k.is_primitive(p.type_name().meta_type() ==
            sml::meta_types::primitive);
        if (k.is_primitive()) {
            has_primitive_properties = true;
            if (k.type() == bool_type)
                has_boolean_properties = true;
        }

        properties_vm.push_back(k);
    }

    if (!disable_keys_) {
        sml::qualified_name vn;
        vn.type_name(versioned_name);
        vn.model_name(name.model_name());
        vn.external_package_path(name.external_package_path());

        std::list<std::string> ns_list(join_namespaces(vn));
        ns_list.push_back(versioned_name);

        using boost::algorithm::join;
        const std::string ns(join(ns_list, namespace_separator));
        view_models::property_view_model k(versioned_name);
        k.type(ns);
        k.is_primitive(false);

        properties_vm.push_back(k);
    }

    r.properties(properties_vm);
    r.has_primitive_properties(has_primitive_properties);
    r.has_boolean_properties(has_boolean_properties);
    return r;
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

view_models::file_view_model sml_to_cpp_view_model::
transform_file(cpp_facet_types ft, cpp_file_types flt, sml::pod pod) {
    const sml::qualified_name name(pod.name());
    const std::list<std::string> ns(join_namespaces(name));

    view_models::file_view_model r;
    r.facet_type(ft);
    r.file_type(flt);
    r.aspect_type(cpp_aspect_types::main);
    r.class_vm(transform_class(pod, ns));

    r.file_path(
        location_manager_.absolute_path(
            location_request_factory(ft, flt, name)));

    if (flt == cpp_file_types::header) {
        const auto rp(location_manager_.relative_logical_path(
                location_request_factory(ft, flt, name)));
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

std::vector<view_models::file_view_model> sml_to_cpp_view_model::
transform_pods() {
    std::vector<view_models::file_view_model> r;

    auto lambda([&](cpp_facet_types f, cpp_file_types ft, sml::pod p) {
            const std::string n(p.name().type_name());
            log_generating_file(f, cpp_aspect_types::main, ft, n);
            r.push_back(transform_file(f, ft, p));
        });

    for (auto pair : model_.pods()) {
        const sml::pod pod(pair.second);

        if (!pod.generate())
            continue;

        for (cpp_facet_types facet_type : facet_types_) {
            lambda(facet_type, cpp_file_types::header, pod);

            if (has_implementation(facet_type))
                lambda(facet_type, cpp_file_types::implementation, pod);
        }
    }
    return r;
}

view_models::class_view_model
sml_to_cpp_view_model::create_key_class_view_model(bool is_versioned) const {
    const std::string name(is_versioned ? versioned_name : unversioned_name);
    view_models::class_view_model r;
    r.name(name);

    sml::qualified_name qn;
    qn.type_name(name);
    qn.model_name(model_.name());
    qn.external_package_path(model_.external_package_path());

    const std::list<std::string> ns(join_namespaces(qn));
    r.namespaces(ns);

    auto lambda([](std::string name, std::string type) {
            view_models::property_view_model r(name);
            r.type(type);
            r.is_primitive(true);
            return r;
        });

    std::list<view_models::property_view_model> properties;
    properties.push_back(lambda(id_name, uint_name));
    if (is_versioned)
        properties.push_back(lambda(version_name, uint_name));
    r.properties(properties);
    r.has_primitive_properties(true);
    return r;
}

view_models::file_view_model sml_to_cpp_view_model::
create_key_file_view_model(cpp_facet_types ft, cpp_file_types flt,
    cpp_aspect_types at) {

    view_models::file_view_model r;
    r.facet_type(ft);
    r.file_type(flt);
    r.aspect_type(at);

    const bool is_versioned(at == cpp_aspect_types::versioned_key);
    r.class_vm(create_key_class_view_model(is_versioned));

    const std::string name(r.class_vm()->name());
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

    log_generating_file(ft, at, flt, name);
    return r;
}

std::vector<view_models::file_view_model>
sml_to_cpp_view_model::transform_keys() {
    std::vector<view_models::file_view_model> r;

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

std::vector<view_models::file_view_model>
sml_to_cpp_view_model::transform_facet_includers() const {
    std::vector<view_models::file_view_model> r;
    const cpp_file_types file_type(cpp_file_types::header);
    const auto aspect_type(cpp_aspect_types::includers);

    for (cpp_facet_types ft : facet_types_) {
        sml::qualified_name qn;
        const auto n(includer_name);
        qn.type_name(n);
        qn.external_package_path(model_.external_package_path());
        const auto rq(location_request_factory(ft, file_type, qn));

        view_models::file_view_model vm;
        vm.facet_type(ft);
        vm.file_path(location_manager_.absolute_path(rq));
        vm.file_type(file_type);

        const auto a(cpp_aspect_types::includers);
        vm.system_dependencies(dependency_manager_.system(n, ft, file_type, a));
        vm.user_dependencies(dependency_manager_.user(n, ft, file_type, a));
        vm.aspect_type(a);

        log_generating_file(ft, aspect_type, file_type, n);
        r.push_back(vm);
    }
    return r;
}

std::vector<view_models::file_view_model>
sml_to_cpp_view_model::transform() {
    log_started();
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
