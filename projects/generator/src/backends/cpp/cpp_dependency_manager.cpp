/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include "dogen/generator/backends/cpp/cpp_dependency_manager.hpp"

namespace {

const std::string empty;
const std::string versioned_name("versioned_key");
const std::string unversioned_name("unversioned_key");

}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {

cpp_dependency_manager::cpp_dependency_manager(sml::model model,
    cpp_location_manager location_manager, bool disable_keys,
    bool use_integrated_io, bool disable_io)
    : model_(model), location_manager_(location_manager),
      disable_keys_(disable_keys), use_integrated_io_(use_integrated_io),
      disable_io_(disable_io) { }

cpp_location_request cpp_dependency_manager::
location_request_factory(cpp_facet_types ft, cpp_file_types flt,
    sml::qualified_name name,
    bool ignore_external_package_path) const {

    cpp_location_request r;
    r.facet_type(ft);
    r.file_type(flt);
    r.model_name(model_.name());
    r.package_path(name.package_path());
    r.file_name(name.type_name());
    if (!ignore_external_package_path)
        r.external_package_path(name.external_package_path());
    return r;
}

void cpp_dependency_manager::register_header(cpp_facet_types ft,
    boost::filesystem::path relative_path) {
    headers_for_facet_[ft].push_back(relative_path.generic_string());
}

std::list<std::string> cpp_dependency_manager::
system(std::string /*name*/, cpp_facet_types /*ft*/,
    cpp_file_types /*flt*/, cpp_aspect_types /*at*/) const {
    std::list<std::string> r;
    return r;
}

std::list<std::string> cpp_dependency_manager::
system(sml::pod /*pod*/, cpp_facet_types /*ft*/,
    cpp_file_types /*flt*/, cpp_aspect_types /*at*/) const {
    std::list<std::string> r;
    return r;
}

std::string cpp_dependency_manager::unversioned_dependency() const {
    sml::qualified_name qn;
    qn.type_name(unversioned_name);
    qn.external_package_path(model_.external_package_path());
    qn.model_name(model_.name());

    const auto d(cpp_facet_types::domain);
    const auto h(cpp_file_types::header);
    const auto rq(location_request_factory(d, h, qn));
    return location_manager_.relative_path(rq).generic_string();
}

bool cpp_dependency_manager::
has_versioned_dependency(cpp_facet_types ft, cpp_file_types flt) const {
    if (disable_keys_)
        return false;

    const bool is_implementation(flt == cpp_file_types::implementation);
    if (is_implementation && (ft == cpp_facet_types::hash ||
            ft == cpp_facet_types::io ||
            ft == cpp_facet_types::serialization ||
            ft == cpp_facet_types::database))
        return false;

    if (is_implementation && ft == cpp_facet_types::domain &&
        (use_integrated_io_ || disable_io_))
        return false;

    const bool is_header(flt == cpp_file_types::header);
    if (is_header && (ft == cpp_facet_types::test_data ||
            ft == cpp_facet_types::database ||
            ft == cpp_facet_types::io))
        return false;

    return true;
}

std::string cpp_dependency_manager::
versioned_dependency(cpp_facet_types ft, cpp_file_types flt) const {
    const bool is_implementation(flt == cpp_file_types::implementation);
    cpp_facet_types actual_facet(ft);
    if (is_implementation && ft == cpp_facet_types::domain)
        actual_facet = cpp_facet_types::io;

    sml::qualified_name qn;
    qn.type_name(versioned_name);
    qn.external_package_path(model_.external_package_path());
    qn.model_name(model_.name());

    const auto h(cpp_file_types::header);
    const auto rq(location_request_factory(actual_facet, h, qn));
    return location_manager_.relative_path(rq).generic_string();
}

std::string cpp_dependency_manager::
domain_header_dependency(sml::qualified_name name) const {
    const auto d(cpp_facet_types::domain);
    const auto h(cpp_file_types::header);
    const auto rq(location_request_factory(d, h, name));
    return location_manager_.relative_path(rq).generic_string();
}

std::string cpp_dependency_manager::header_dependency(
    sml::qualified_name name, cpp_facet_types facet_type) const {
    const auto h(cpp_file_types::header);
    const auto rq(location_request_factory(facet_type, h, name));
    return location_manager_.relative_path(rq).generic_string();
}

std::list<std::string> cpp_dependency_manager::
user(sml::qualified_name name, cpp_facet_types facet_type,
    cpp_file_types file_type, cpp_aspect_types aspect_type) const {

    if (aspect_type == cpp_aspect_types::includers) {
        const auto i(headers_for_facet_.find(facet_type));
        if (i != headers_for_facet_.end())
            return i->second;
    }

    typedef std::list<std::string> return_type;
    const bool is_header(file_type == cpp_file_types::header);
    const bool is_domain(facet_type == cpp_facet_types::domain);
    const bool is_versioned(aspect_type == cpp_aspect_types::versioned_key);

    if (is_versioned && is_header && is_domain)
        return return_type { unversioned_dependency() };

    if (is_header && !is_domain)
        return return_type { domain_header_dependency(name) };

    if (file_type == cpp_file_types::implementation)
        return return_type { header_dependency(name, facet_type) };

    return return_type { };
}

std::list<std::string>
cpp_dependency_manager::user(std::string name, cpp_facet_types ft,
    cpp_file_types flt, cpp_aspect_types at) const {

    sml::qualified_name qn;
    qn.external_package_path(model_.external_package_path());
    qn.type_name(name);
    qn.model_name(model_.name());
    return user(qn, ft, flt, at);
}

std::list<std::string> cpp_dependency_manager::
user(sml::pod pod, cpp_facet_types ft, cpp_file_types flt,
    cpp_aspect_types at) const {
    std::list<std::string> r(user(pod.name(), ft, flt, at));

    if (has_versioned_dependency(ft, flt))
        r.push_back(versioned_dependency(ft, flt));

    // FIXME: handle properties etc.
    return r;
}

} } } }
