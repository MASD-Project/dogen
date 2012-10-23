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
#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm/find_first_of.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/generator/backends/cpp/cpp_inclusion_manager.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("inclusion_manager"));

const std::string empty;
const std::string std_model("std");
const std::string primitive_model("primitive_model");
const std::string bool_type("bool");
const std::string versioned_name("versioned_key");
const std::string unversioned_name("unversioned_key");
const std::string vector_include("vector");
const std::string boost_optional_include("boost/optional.hpp");
const std::string pqxx_connection_include("pqxx/connection.hxx");
const std::string boost_format_include("boost/format.hpp");
const std::string boost_nvp("boost/serialization/nvp.hpp");
const std::string boost_export("boost/serialization/export.hpp");
const std::string boost_string("boost/serialization/string.hpp");
const std::string pqxx_result_include("pqxx/result.hxx");
const std::string pqxx_transaction_include("pqxx/transaction.hxx");
const std::string sstream("sstream");
const std::string std_string("string");
const std::string iosfwd("iosfwd");
const std::string algorithm("algorithm");
const std::string ostream("ostream");
const std::string state_saver("boost/io/ios_state.hpp");
const std::string functional("functional");

using dogen::generator::backends::cpp::cpp_facet_types;
bool io_enabled(const std::set<cpp_facet_types>& f) {
    return f.find(cpp_facet_types::io) != f.end();
}

}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {

cpp_inclusion_manager::cpp_inclusion_manager(const sml::model& model,
    const cpp_location_manager& location_manager,
    const config::cpp_settings& settings)
    : model_(model), location_manager_(location_manager), settings_(settings),
      io_enabled_(io_enabled(settings_.enabled_facets())) {

    BOOST_LOG_SEV(lg, debug)
        << "Initial configuration:"
        << " disable_versioning: " << settings_.disable_versioning()
        << " use_integrated_io: " << settings_.use_integrated_io()
        << " io_enabled: " << io_enabled_
        << " model name: " << model_.name();
}

cpp_location_request cpp_inclusion_manager::
location_request_factory(cpp_facet_types ft, cpp_file_types flt,
    cpp_aspect_types at, const sml::qualified_name& name) const {

    cpp_location_request r;
    r.facet_type(ft);
    r.file_type(flt);
    r.aspect_type(at);
    r.model_name(model_.name());
    r.package_path(name.package_path());
    r.file_name(name.type_name());
    r.external_package_path(name.external_package_path());
    return r;
}

void cpp_inclusion_manager::register_header(cpp_facet_types ft,
    const boost::filesystem::path& relative_path) {
    headers_for_facet_[ft].push_back(relative_path.generic_string());
}

std::string cpp_inclusion_manager::unversioned_dependency() const {
    sml::qualified_name qn;
    qn.type_name(unversioned_name);
    qn.external_package_path(model_.external_package_path());
    qn.model_name(model_.name());

    const auto d(cpp_facet_types::domain);
    const auto h(cpp_file_types::header);
    const auto rq(location_request_factory(d, h, cpp_aspect_types::main, qn));
    return location_manager_.relative_logical_path(rq).generic_string();
}

std::string cpp_inclusion_manager::
versioned_dependency(cpp_facet_types ft) const {
    sml::qualified_name qn;
    qn.type_name(versioned_name);
    qn.external_package_path(model_.external_package_path());
    qn.model_name(model_.name());

    const auto h(cpp_file_types::header);
    const auto rq(location_request_factory(ft, h, cpp_aspect_types::main, qn));
    return location_manager_.relative_logical_path(rq).generic_string();
}

std::string cpp_inclusion_manager::
domain_header_dependency(const sml::qualified_name& name,
    const cpp_aspect_types at) const {
    const auto d(cpp_facet_types::domain);
    const auto h(cpp_file_types::header);
    const auto rq(location_request_factory(d, h, at, name));
    return location_manager_.relative_logical_path(rq).generic_string();
}

std::string cpp_inclusion_manager::header_dependency(
    const sml::qualified_name& name, cpp_facet_types facet_type) const {
    const auto h(cpp_file_types::header);
    const auto main(cpp_aspect_types::main);
    const auto rq(location_request_factory(facet_type, h, main, name));
    return location_manager_.relative_logical_path(rq).generic_string();
}

std::list<dogen::sml::qualified_name>
cpp_inclusion_manager::pod_to_qualified_names(const sml::pod& pod) const {
    std::list<dogen::sml::qualified_name> r;

    if (pod.parent_name())
        r.push_back(*pod.parent_name());

    for(const auto p : pod.properties())
        r.push_back(p.type_name());

    return r;
}

void cpp_inclusion_manager::append_versioning_dependencies(
    const cpp_facet_types ft, const cpp_file_types flt, cpp_aspect_types at,
    const sml::category_types ct, inclusion_lists& il) const {

    if (settings_.disable_versioning())
        return;

    /*
     * rule 1: domain versioned header depends on domain unversioned
     * header.
     */
    const bool is_header(flt == cpp_file_types::header);
    const bool is_domain(ft == cpp_facet_types::domain);
    const bool is_main(at == cpp_aspect_types::main);
    const bool is_versioned_key(ct == sml::category_types::versioned_key);
    if (is_versioned_key && is_main && is_header && is_domain)
        il.user.push_back(unversioned_dependency());
}

void cpp_inclusion_manager::
append_implementation_dependencies(const cpp_facet_types ft,
    const cpp_file_types flt, inclusion_lists& il,
    const bool requires_stream_manipulators,
    const bool is_parent_or_child) const {

    /*
     * STL
     */
    // iosfwd:
    const bool is_header(flt == cpp_file_types::header);
    const bool is_domain(ft == cpp_facet_types::domain);
    const bool is_io(ft == cpp_facet_types::io);
    const bool domain_with_io(is_domain &&
        (settings_.use_integrated_io() || is_parent_or_child));

    if (is_header && io_enabled_ && (domain_with_io || is_io))
        il.system.push_back(iosfwd);

    // algorithm: domain headers need it for the swap function.
    if (is_header && is_domain)
        il.system.push_back(algorithm);

    // ostream:
    const bool is_implementation(flt == cpp_file_types::implementation);
    const bool io_without_iio(is_io && !settings_.use_integrated_io());
    if (is_implementation && io_enabled_ && (domain_with_io || io_without_iio))
        il.system.push_back(ostream);

    // functional
    const bool is_hash(ft == cpp_facet_types::hash);
    if (is_header && is_hash)
        il.system.push_back(functional);

    // vector
    const bool is_database(ft == cpp_facet_types::database);
    if (is_header && is_database)
        il.system.push_back(vector_include);

    /*
     * boost
     */
    // optional
    if (is_header && is_database)
        il.system.push_back(boost_optional_include);

    // format
    if (is_implementation && is_database)
        il.system.push_back(boost_format_include);

    // nvp serialisation
    const bool is_serialization(ft == cpp_facet_types::serialization);
    if (is_header && is_serialization && !settings_.disable_xml_serialization())
        il.system.push_back(boost_nvp);

    // boost serialisation export
    if (is_header && is_serialization && is_parent_or_child)
        il.system.push_back(boost_export);

    // state saver
    if (is_implementation && io_enabled_ && requires_stream_manipulators &&
        (domain_with_io || io_without_iio))
        il.system.push_back(state_saver);

    /*
     * pqxx
     */
    // connection
    if (is_header && is_database)
        il.system.push_back(pqxx_connection_include);

    // result
    if (is_implementation && is_database)
        il.system.push_back(pqxx_result_include);

    // transaction
    if (is_implementation && is_database)
        il.system.push_back(pqxx_transaction_include);
}

void cpp_inclusion_manager::append_std_dependencies(
    const cpp_facet_types ft, const cpp_file_types flt,
    const dogen::sml::qualified_name& qname,
    inclusion_lists& il) const {

    const bool is_header(flt == cpp_file_types::header);
    const bool is_domain(ft == cpp_facet_types::domain);
    if (is_header && is_domain && qname.type_name() == std_string)
        il.system.push_back(std_string);

    const bool is_serialization(ft == cpp_facet_types::serialization);
    if (is_header && is_serialization && qname.type_name() == std_string)
        il.system.push_back(boost_string);

    const bool is_implementation(flt == cpp_file_types::implementation);
    const bool is_test_data(ft == cpp_facet_types::test_data);
    if (is_implementation && is_test_data && qname.type_name() == std_string)
        il.system.push_back(sstream);
}

void cpp_inclusion_manager::append_relationship_dependencies(
    const std::list<dogen::sml::qualified_name>& names,
    const cpp_facet_types ft, const cpp_file_types flt,
    const bool is_parent_or_child, inclusion_lists& il) const {

    for(const auto n : names) {
        // handle all special models first
        if (n.model_name() == std_model) {
            append_std_dependencies(ft, flt, n, il);
            continue;
        } else if (n.model_name() == primitive_model)
            continue;

        /*
         * rule 1: primitives never require header files. Not quite
         * sure when this could happen, as they should be part of a
         * special model.
         */
        const bool is_primitive(n.meta_type() == sml::meta_types::primitive);
        if (is_primitive)
            continue; // primitve on non-primitives model

        /*
         * rule 2: domain and serialisation headers need the
         * corresponding header file for the dependency
         */
        const bool is_header(flt == cpp_file_types::header);
        const bool is_domain(ft == cpp_facet_types::domain);
        const bool is_ser(ft == cpp_facet_types::serialization);

        if (is_header && !is_primitive && (is_domain || is_ser))
            il.user.push_back(header_dependency(n, ft));

        /*
         * rule 3: hash, IO and test data implementations need the
         * corresponding header file for the dependency
         */
        const bool is_implementation(flt == cpp_file_types::implementation);
        const bool is_hash(ft == cpp_facet_types::hash);
        const bool is_io(ft == cpp_facet_types::io);
        const bool is_td(ft == cpp_facet_types::test_data);

        if (is_implementation && (is_hash || is_io || is_td))
            il.user.push_back(header_dependency(n, ft));

        /*
         * rule 4: parents and children and integrated IO require IO
         * headers in domain implementation.
         */
        const bool domain_with_io(is_domain &&
            (settings_.use_integrated_io() || is_parent_or_child));

        if (is_implementation && io_enabled_ && domain_with_io)
            il.user.push_back(header_dependency(n, cpp_facet_types::io));
    }
}

void cpp_inclusion_manager::
append_self_dependencies(dogen::sml::qualified_name name,
    const cpp_facet_types ft, const cpp_file_types flt,
    cpp_aspect_types at, inclusion_lists& il) const {

    if (at == cpp_aspect_types::forward_decls) {
        /*
         * rule 1: non-domain forward declarations depend on the
         * domain header.
         */
        const bool is_header(flt == cpp_file_types::header);
        const bool is_domain(ft == cpp_facet_types::domain);
        const auto fwd(cpp_aspect_types::forward_decls);
        if (is_header && !is_domain)
            il.user.push_back(domain_header_dependency(name, fwd));

        return;
    }

    /*
     * rule 2: all header files depend on the domain header file,
     * except for the domain header file itself.
     */
    const bool is_header(flt == cpp_file_types::header);
    const bool is_domain(ft == cpp_facet_types::domain);
    const auto main(cpp_aspect_types::main);
    if (is_header && !is_domain)
        il.user.push_back(domain_header_dependency(name, main));

    /*
     * rule 3: all implementation files depend on the domain header file.
     */
    const bool is_implementation(flt == cpp_file_types::implementation);
    if (is_implementation)
        il.user.push_back(header_dependency(name, ft));
}

bool cpp_inclusion_manager::requires_stream_manipulators(
    const std::list<dogen::sml::qualified_name>& names) const {
    using dogen::sml::qualified_name;
    for (const auto n : names) {
        if (n.type_name() == bool_type)
            return true;
    }
    return false;
}

bool cpp_inclusion_manager::is_parent_or_child(const dogen::sml::pod& p) const {
    return p.parent_name() || p.is_parent();
}

inclusion_lists
cpp_inclusion_manager::includes_for_includer_files(cpp_facet_types ft) const {
    inclusion_lists r;
    const auto i(headers_for_facet_.find(ft));
    if (i != headers_for_facet_.end())
        r.user = i->second;
    return r;
}

inclusion_lists cpp_inclusion_manager::
includes_for_pod(const sml::pod& pod, cpp_facet_types ft, cpp_file_types flt,
    cpp_aspect_types at) const {

    inclusion_lists r;
    if (at == cpp_aspect_types::forward_decls) {
        append_self_dependencies(pod.name(), ft, flt, at, r);
        return r;
    }

    const auto names(pod_to_qualified_names(pod));
    const bool rsm(requires_stream_manipulators(names));
    const bool pc(is_parent_or_child(pod));

    append_versioning_dependencies(ft, flt, at, pod.category_type(), r);
    append_implementation_dependencies(ft, flt, r, rsm, pc);
    append_relationship_dependencies(names, ft, flt, pc, r);
    append_self_dependencies(pod.name(), ft, flt, at, r);

    return r;
}

} } } }
