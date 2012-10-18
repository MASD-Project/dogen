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
const std::string bool_type("bool");
const std::string versioned_name("versioned_key");
const std::string unversioned_name("unversioned_key");
const std::string vector_include("vector");
const std::string boost_optional_include("boost/optional.hpp");
const std::string pqxx_connection_include("pqxx/connection.hxx");
const std::string boost_format_include("boost/format.hpp");
const std::string boost_nvp("boost/serialization/nvp.hpp");
const std::string boost_export("boost/serialization/export.hpp");
const std::string pqxx_result_include("pqxx/result.hxx");
const std::string pqxx_transaction_include("pqxx/transaction.hxx");
const std::string iosfwd("iosfwd");
const std::string algorithm("algorithm");
const std::string ostream("ostream");
const std::string state_saver("boost/io/ios_state.hpp");
const std::string functional("functional");
const std::string hash_combine("dogen/utility/hash/combine.hpp");
const std::string generator_include("dogen/utility/test_data/generator.hpp");
const std::string sequence_include("dogen/utility/test_data/sequence.hpp");

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
    const sml::qualified_name& name) const {

    cpp_location_request r;
    r.facet_type(ft);
    r.file_type(flt);
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
    const auto rq(location_request_factory(d, h, qn));
    return location_manager_.relative_logical_path(rq).generic_string();
}

std::string cpp_inclusion_manager::
versioned_dependency(cpp_facet_types ft) const {
    sml::qualified_name qn;
    qn.type_name(versioned_name);
    qn.external_package_path(model_.external_package_path());
    qn.model_name(model_.name());

    const auto h(cpp_file_types::header);
    const auto rq(location_request_factory(ft, h, qn));
    return location_manager_.relative_logical_path(rq).generic_string();
}

std::string cpp_inclusion_manager::
domain_header_dependency(const sml::qualified_name& name) const {
    const auto d(cpp_facet_types::domain);
    const auto h(cpp_file_types::header);
    const auto rq(location_request_factory(d, h, name));
    return location_manager_.relative_logical_path(rq).generic_string();
}

std::string cpp_inclusion_manager::header_dependency(
    const sml::qualified_name& name, cpp_facet_types facet_type) const {
    const auto h(cpp_file_types::header);
    const auto rq(location_request_factory(facet_type, h, name));
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
    inclusion_lists& il, const bool is_parent_or_child) const {

    if (settings_.disable_versioning() ||
        at == cpp_aspect_types::unversioned_key ||
        at == cpp_aspect_types::includers)
        return;

    /*
     * rule 1: versioned header depends on unversioned header.
     */
    const bool is_header(flt == cpp_file_types::header);
    const bool is_domain(ft == cpp_facet_types::domain);
    if (at == cpp_aspect_types::versioned_key) {
        if (is_header && is_domain)
            il.user.push_back(unversioned_dependency());
        return;
    }

    cpp_facet_types version_facet(ft);

    /*
     * rule 2: domain implementation needs access to the versioned key
     * IO header file when IO is enabled and we are using integrated
     * IO, or we are in the presence of inheritance.
     */
    const bool is_implementation(flt == cpp_file_types::implementation);
    const bool iio(settings_.use_integrated_io());
    const bool rule2(is_implementation && is_domain && io_enabled_ &&
        (iio || is_parent_or_child));
    if (rule2)
        version_facet = cpp_facet_types::io;

    /*
     * rule 3: io implementation needs access to the versioned key
     * IO header file when IO is enabled and we are not using integrated
     * IO.
     */
    const bool is_io(ft == cpp_facet_types::io);
    const bool rule3(is_implementation && is_io && io_enabled_ && !iio);

    /*
     * rule 4: test data implementation requires access to version in
     * order to generate versioned key objects.
     */
    const bool is_test_data(ft == cpp_facet_types::test_data);
    const bool rule4(is_implementation && is_test_data);

    /*
     * rule 5: serialization and hash headers need versioned key in
     * order to serialise and hash these objects
     * (respectively). Domain needs the version for its property.
     */
    const bool is_hash(ft == cpp_facet_types::hash);
    const bool is_serialization(ft == cpp_facet_types::serialization);
    const bool rule5(is_header && (is_domain || is_hash || is_serialization));

    if (rule2 || rule3 || rule4 || rule5)
        il.user.push_back(versioned_dependency(version_facet));
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

    /*
     * Dogen dependencies
     */
    // hash combine
    if (is_header && is_hash)
        il.user.push_back(hash_combine);

    // generator
    const bool is_test_data(ft == cpp_facet_types::test_data);
    if (is_header && is_test_data)
        il.user.push_back(generator_include);

    // sequence
    if (is_header && is_test_data)
        il.user.push_back(sequence_include);
}

void cpp_inclusion_manager::append_relationship_dependencies(
    const std::list<dogen::sml::qualified_name>& names,
    const cpp_facet_types ft, const cpp_file_types flt,
    inclusion_lists& il) const {

    for(const auto n : names) {
        /*
         * rule 1: headers need the corresponding header file for the
         * dependency.
         */
        const bool is_primitive(n.meta_type() == sml::meta_types::primitive);
        const bool is_header(flt == cpp_file_types::header);

        if (is_header && !is_primitive)
            il.user.push_back(header_dependency(n, ft));
    }
}

void cpp_inclusion_manager::
append_self_dependencies(dogen::sml::qualified_name name,
    const cpp_facet_types ft, const cpp_file_types flt,
    inclusion_lists& il) const {

    /*
     * rule 1: all header files depend on the domain header file,
     * except for the domain header file itself.
     */
    const bool is_header(flt == cpp_file_types::header);
    const bool is_domain(ft == cpp_facet_types::domain);
    if (is_header && !is_domain)
        il.user.push_back(domain_header_dependency(name));

    /*
     * rule 2: all implementation files depend on the domain header file
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

    const auto names(pod_to_qualified_names(pod));
    const bool rsm(requires_stream_manipulators(names));
    const bool pc(is_parent_or_child(pod));
    inclusion_lists r;

    append_versioning_dependencies(ft, flt, at, r, pc);
    append_implementation_dependencies(ft, flt, r, rsm, pc);
    append_relationship_dependencies(names, ft, flt, r);
    append_self_dependencies(pod.name(), ft, flt, r);

    return r;
}

inclusion_lists cpp_inclusion_manager::
includes_for_versioning(const std::string& name, cpp_facet_types ft,
    cpp_file_types flt, cpp_aspect_types at) const {

    inclusion_lists r;
    append_versioning_dependencies(ft, flt, at, r);
    append_implementation_dependencies(ft, flt, r);

    sml::qualified_name n;
    n.external_package_path(model_.external_package_path());
    n.type_name(name);
    n.model_name(model_.name());
    append_self_dependencies(n, ft, flt, r);

    return r;
}

} } } }
