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
const std::string pqxx_connection_include("pqxx/connection.hxx");
const std::string pqxx_result_include("pqxx/result.hxx");
const std::string pqxx_transaction_include("pqxx/transaction.hxx");
const std::string sstream("sstream");
const std::string std_string("string");
const std::string std_vector("vector");
const std::string std_set("set");
const std::string std_deque("deque");
const std::string std_list("list");
const std::string std_unordered_map("unordered_map");
const std::string iosfwd("iosfwd");
const std::string algorithm("algorithm");
const std::string ostream("ostream");
const std::string stdexcept("stdexcept");
const std::string state_saver("boost/io/ios_state.hpp");
const std::string functional("functional");

using dogen::generator::backends::cpp::cpp_facet_types;
bool contains(const std::set<cpp_facet_types>& f, cpp_facet_types ft) {
    return f.find(ft) != f.end();
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
      io_enabled_(contains(settings_.enabled_facets(), cpp_facet_types::io)),
      serialization_enabled_(contains(settings_.enabled_facets(),
              cpp_facet_types::serialization)),
      hash_enabled_(contains(settings_.enabled_facets(),
              cpp_facet_types::hash)), boost_() {

    BOOST_LOG_SEV(lg, debug)
        << "Initial configuration:"
        << " disable_versioning: " << settings_.disable_versioning()
        << " use_integrated_io: " << settings_.use_integrated_io()
        << " io_enabled: " << io_enabled_
        << " serialization_enabled: " << serialization_enabled_
        << " hash_enabled_: " << hash_enabled_
        << " model name: " << model_.name();
}

cpp_location_request cpp_inclusion_manager::
location_request_factory(cpp_facet_types ft, cpp_file_types flt,
    cpp_aspect_types at, const sml::qualified_name& name) const {

    cpp_location_request r;
    r.facet_type(ft);
    r.file_type(flt);
    r.aspect_type(at);
    r.model_name(name.model_name());
    r.package_path(name.package_path());
    r.file_name(name.type_name());
    r.external_package_path(name.external_package_path());
    return r;
}

void cpp_inclusion_manager::register_header(cpp_facet_types ft,
    const boost::filesystem::path& relative_path) {
    headers_for_facet_[ft].push_back(relative_path.generic_string());
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
    const sml::qualified_name& name, cpp_facet_types facet_type,
    const cpp_aspect_types at) const {
    const auto h(cpp_file_types::header);
    const auto main(at);
    const auto rq(location_request_factory(facet_type, h, main, name));
    return location_manager_.relative_logical_path(rq).generic_string();
}

void cpp_inclusion_manager::
recurse_nested_qnames_keys(const dogen::sml::nested_qualified_name& nested_qname,
    std::list<dogen::sml::qualified_name>& keys) const {

    if (nested_qname.type().meta_type() == sml::meta_types::pod) {
        const auto pods(model_.pods());
        const auto i(pods.find(nested_qname.type()));
        if (i != pods.end() && i->second.is_associative_container()) {
            if (nested_qname.children().size() >= 1)
                keys.push_back(nested_qname.children().front().type());
        } else {
            for (const auto nqn : nested_qname.children())
                recurse_nested_qnames_keys(nqn, keys);
        }
    }
}

std::list<dogen::sml::qualified_name>
cpp_inclusion_manager::pod_to_keys(const sml::pod& pod) const {
    std::list<dogen::sml::qualified_name> r;

    for (const auto p : pod.properties())
        recurse_nested_qnames_keys(p.type_name(), r);

    return r;
}

void cpp_inclusion_manager::
recurse_nested_qnames(const dogen::sml::nested_qualified_name& nested_qname,
    std::list<dogen::sml::qualified_name>& qnames) const {

    qnames.push_back(nested_qname.type());
    for (const auto nqn : nested_qname.children())
        recurse_nested_qnames(nqn, qnames);
}

std::list<dogen::sml::qualified_name>
cpp_inclusion_manager::pod_to_qualified_names(const sml::pod& pod) const {
    std::list<dogen::sml::qualified_name> r;

    if (pod.parent_name())
        r.push_back(*pod.parent_name());

    for (const auto p : pod.properties())
        recurse_nested_qnames(p.type_name(), r);

    return r;
}

void cpp_inclusion_manager::
append_implementation_dependencies(const sml::pod& p,
    const cpp_facet_types ft, const cpp_file_types flt, inclusion_lists& il,
    const bool requires_stream_manipulators) const {

    /*
     * STL
     */
    // iosfwd:
    const bool is_header(flt == cpp_file_types::header);
    const bool is_domain(ft == cpp_facet_types::domain);
    const bool is_io(ft == cpp_facet_types::io);

    const bool domain_with_io(is_domain &&
        (settings_.use_integrated_io() || p.parent_name() || p.is_parent()));

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

    /*
     * boost
     */
    // nvp serialisation
    const bool is_serialization(ft == cpp_facet_types::serialization);
    if (is_implementation && is_serialization &&
        !settings_.disable_xml_serialization())
        il.system.push_back(boost_.include(boost_types::nvp));

    // split free serialisation
    if (is_header && is_serialization)
        il.system.push_back(boost_.include(boost_types::split_free));

    // assume abstract
    if (is_header && is_serialization && p.is_parent())
        il.system.push_back(boost_.include(boost_types::assume_abstract));

    // boost virtual base of
    if (is_header && is_serialization && !p.is_parent() && p.parent_name())
        il.system.push_back(boost_.include(boost_types::is_virtual_base_of));

    // boost archive types
    if (is_implementation && is_serialization) {
        if (!settings_.disable_xml_serialization()) {
            il.system.push_back(boost_.include(boost_types::xml_oarchive));
            il.system.push_back(boost_.include(boost_types::xml_iarchive));
        }
        il.system.push_back(boost_.include(boost_types::text_oarchive));
        il.system.push_back(boost_.include(boost_types::text_iarchive));
        il.system.push_back(boost_.include(boost_types::binary_oarchive));
        il.system.push_back(boost_.include(boost_types::binary_iarchive));
        il.system.push_back(boost_.include(boost_types::polymorphic_iarchive));
        il.system.push_back(boost_.include(boost_types::polymorphic_oarchive));
    }

    // state saver
    if (is_implementation && io_enabled_ && requires_stream_manipulators &&
        (domain_with_io || io_without_iio))
        il.system.push_back(boost_.include(boost_types::io_ios_state));
}

void cpp_inclusion_manager::append_boost_dependencies(
    const cpp_facet_types ft, const cpp_file_types flt,
    const dogen::sml::qualified_name& qname,
    inclusion_lists& il) const {

    /*
     * boost::shared_ptr
     */
    const bool is_header(flt == cpp_file_types::header);
    const bool is_domain(ft == cpp_facet_types::domain);
    const bool is_sp(qname.type_name() == boost_.type(boost_types::shared_ptr));
    if (is_header && is_domain && is_sp)
        il.system.push_back(boost_.include(boost_types::shared_ptr));

    const bool is_serialization(ft == cpp_facet_types::serialization);
    const bool is_implementation(flt == cpp_file_types::implementation);
    if (is_implementation && is_serialization && is_sp)
        il.system.push_back(
            boost_.include(boost_types::serialization_shared_ptr));
}

void cpp_inclusion_manager::append_std_dependencies(
    const cpp_facet_types ft, const cpp_file_types flt,
    const dogen::sml::qualified_name& qname,
    inclusion_lists& il) const {

    /*
     * std::string
     */
    const bool is_header(flt == cpp_file_types::header);
    const bool is_domain(ft == cpp_facet_types::domain);
    if (is_header && is_domain && qname.type_name() == std_string)
        il.system.push_back(std_string);

    const bool is_serialization(ft == cpp_facet_types::serialization);
    const bool is_implementation(flt == cpp_file_types::implementation);
    const bool is_string(qname.type_name() == std_string);
    if (is_implementation && is_serialization && is_string)
        il.system.push_back(boost_.include(boost_types::string));

    const bool is_test_data(ft == cpp_facet_types::test_data);
    if (is_implementation && is_test_data && is_string)
        il.system.push_back(sstream);

    /*
     * std::vector
     */
    if (is_header && is_domain && qname.type_name() == std_vector)
        il.system.push_back(std_vector);

    const bool is_vector(qname.type_name() == std_vector);
    if (is_implementation && is_serialization && is_vector)
        il.system.push_back(boost_.include(boost_types::vector));

    /*
     * std::list
     */
    if (is_header && is_domain && qname.type_name() == std_list)
        il.system.push_back(std_list);

    if (is_implementation && is_serialization && qname.type_name() == std_list)
        il.system.push_back(boost_.include(boost_types::list));

    /*
     * std::deque
     */
    if (is_header && is_domain && qname.type_name() == std_deque)
        il.system.push_back(std_deque);

    if (is_implementation && is_serialization && qname.type_name() == std_deque)
        il.system.push_back(boost_.include(boost_types::deque));

    /*
     * std::set
     */
    if (is_header && is_domain && qname.type_name() == std_set)
        il.system.push_back(std_set);

    if (is_implementation && is_serialization && qname.type_name() == std_set)
        il.system.push_back(boost_.include(boost_types::set));

    /*
     * std::unordered_map
     */
    if (is_header && is_domain && qname.type_name() == std_unordered_map)
        il.system.push_back(std_unordered_map);

    // FIXME: massive hack. boost doesn't have support for
    // serialisation so we are using our own hacked header
    std::string private_ser_header("utility/serialization/unordered_map.hpp");
    const auto epp(model_.external_package_path());
    if (!epp.empty())
        private_ser_header = epp.front() + "/" + private_ser_header;

    if (is_implementation && is_serialization &&
        qname.type_name() == std_unordered_map)
        il.user.push_back(private_ser_header);
}

void cpp_inclusion_manager::append_relationship_dependencies(
    const std::list<dogen::sml::qualified_name>& names,
    const std::list<dogen::sml::qualified_name>& keys,
    const std::list<dogen::sml::qualified_name>& leaves,
    const cpp_facet_types ft, const cpp_file_types flt,
    const bool is_parent_or_child, inclusion_lists& il) const {

    for(const auto n : names) {
        // handle all special models first
        if (n.model_name() == std_model) {
            append_std_dependencies(ft, flt, n, il);
            continue;
        } else if (n.model_name() == boost_.model()) {
            append_boost_dependencies(ft, flt, n, il);
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
         * rule 2: domain headers need the corresponding header file
         * for the dependency
         */
        const bool is_header(flt == cpp_file_types::header);
        const bool is_domain(ft == cpp_facet_types::domain);
        const auto main(cpp_aspect_types::main);

        if (is_header && !is_primitive && is_domain)
            il.user.push_back(header_dependency(n, ft, main));

        /*
         * rule 3: hash, IO, serialisation and test data
         * implementations need the corresponding header file for the
         * dependency
         */
        const bool is_implementation(flt == cpp_file_types::implementation);
        const bool is_hash(ft == cpp_facet_types::hash);
        const bool is_io(ft == cpp_facet_types::io);
        const bool is_ser(ft == cpp_facet_types::serialization);
        const bool is_td(ft == cpp_facet_types::test_data);

        if (is_implementation && (is_hash || is_io || is_td || is_ser))
            il.user.push_back(header_dependency(n, ft, main));

        /*
         * rule 4: parents and children with integrated IO require IO
         * headers in domain implementation.
         */
        const bool domain_with_io(is_domain &&
            (settings_.use_integrated_io() || is_parent_or_child));

        if (is_implementation && io_enabled_ && domain_with_io)
            il.user.push_back(header_dependency(n, cpp_facet_types::io, main));
    }

    for (const auto k : keys) {
        // keys from special models can be ignored
        if (k.model_name() == std_model ||
            k.model_name() == boost_.model() ||
            k.model_name() == primitive_model)
            continue;

        /*
         * rule 5: domain headers require hashing for all keys.
         */
        const bool is_header(flt == cpp_file_types::header);
        const bool is_domain(ft == cpp_facet_types::domain);
        const bool is_primitive(k.meta_type() == sml::meta_types::primitive);

        const auto main(cpp_aspect_types::main);
        if (!is_primitive && is_header && hash_enabled_ && is_domain)
            il.user.push_back(header_dependency(k, cpp_facet_types::hash, main));
    }

    for (const auto l : leaves) {
        /*
         * rule 6: leaves require generators in test data.
         */
        const bool is_implementation(flt == cpp_file_types::implementation);
        const bool is_td(ft == cpp_facet_types::test_data);
        const auto main(cpp_aspect_types::main);
        if (is_implementation && is_td)
            il.user.push_back(header_dependency(l, ft, main));

        /*
         * rule 7: base classes require registering all leaves in
         * serialisation implementation.
         */
        const bool is_ser(ft == cpp_facet_types::serialization);
        if (is_implementation && is_ser)
            il.user.push_back(header_dependency(l, ft, main));
    }
}

void cpp_inclusion_manager::
append_self_dependencies(dogen::sml::qualified_name name,
    const cpp_facet_types ft, const cpp_file_types flt,
    const cpp_aspect_types at, const sml::meta_types mt,
    inclusion_lists& il) const {

    const bool is_header(flt == cpp_file_types::header);
    const bool is_domain(ft == cpp_facet_types::domain);
    const auto fwd(cpp_aspect_types::forward_decls);
    if (at == cpp_aspect_types::forward_decls) {
        /*
         * rule 1: non-domain forward declarations depend on the
         * domain header.
         */
        if (is_header && !is_domain)
            il.user.push_back(domain_header_dependency(name, fwd));
        return;
    }

    /*
     * rule 2: if serialisation is enabled, domain headers depend on
     * the serialisation forward declaration headers.
     */
    if (is_header && is_domain && serialization_enabled_
        && mt == sml::meta_types::pod)
        il.user.push_back(header_dependency(name,
                cpp_facet_types::serialization, fwd));

    /*
     * rule 3: all header files depend on the domain header file,
     * except for the domain header file itself.
     */
    const auto main(cpp_aspect_types::main);
    if (is_header && !is_domain)
        il.user.push_back(domain_header_dependency(name, main));

    /*
     * rule 4: all implementation files depend on the domain header file.
     */
    const bool is_implementation(flt == cpp_file_types::implementation);
    if (is_implementation)
        il.user.push_back(header_dependency(name, ft, main));
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

void cpp_inclusion_manager::remove_duplicates(inclusion_lists& il) const {
    il.system.sort();
    il.system.unique();
    il.user.sort();
    il.user.unique();
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
includes_for_enumeration(const sml::enumeration& e, cpp_facet_types ft,
    cpp_file_types flt, cpp_aspect_types at) const {
    inclusion_lists r;

    append_self_dependencies(e.name(), ft, flt, at, e.name().meta_type(), r);

    // functional
    const bool is_header(flt == cpp_file_types::header);
    const bool is_hash(ft == cpp_facet_types::hash);
    if (is_header && is_hash)
        r.system.push_back(functional);

    // nvp serialisation
    const bool is_serialization(ft == cpp_facet_types::serialization);
    if (is_header && is_serialization && !settings_.disable_xml_serialization())
        r.system.push_back(boost_.include(boost_types::nvp));

    // iosfwd
    const bool is_io(ft == cpp_facet_types::io);
    if (is_header && is_io && io_enabled_)
        r.system.push_back(iosfwd);

    // ostream
    const bool is_implementation(flt == cpp_file_types::implementation);
    if (is_implementation && is_io && io_enabled_)
        r.system.push_back(ostream);

    // stdexcept
    if (is_implementation && is_io && io_enabled_)
        r.system.push_back(stdexcept);

    remove_duplicates(r);
    return r;
}

inclusion_lists cpp_inclusion_manager::
includes_for_exception(const sml::exception& e, cpp_facet_types ft,
    cpp_file_types flt, cpp_aspect_types at) const {
    inclusion_lists r;

    append_self_dependencies(e.name(), ft, flt, at, e.name().meta_type(), r);

    // exception info
    const bool is_header(flt == cpp_file_types::header);
    const bool is_domain(ft == cpp_facet_types::domain);
    if (is_header && is_domain)
        r.system.push_back(boost_.include(boost_types::exception_info));

    // string
    if (is_header && is_domain)
        r.system.push_back(std_string);

    remove_duplicates(r);
    return r;
}

inclusion_lists cpp_inclusion_manager::
includes_for_registrar(cpp_file_types flt) const {
    inclusion_lists r;

    if (flt == cpp_file_types::header)
        return r;

    const auto main(cpp_aspect_types::main);
    const auto ft(cpp_facet_types::serialization);
    for (const auto l : model_.leaves())
        r.user.push_back(header_dependency(l, ft, main));

    for (const auto d : model_.dependencies()) {
        // FIXME: we need to check this against system models
        if (d == std_model || d == boost_.model() || d.empty())
            continue;

        sml::qualified_name n;
        n.model_name(d);
        n.type_name("registrar");
        n.external_package_path(model_.external_package_path());
        r.user.push_back(header_dependency(n, ft, main));
    }

    if (!settings_.disable_xml_serialization()) {
        r.system.push_back(boost_.include(boost_types::xml_oarchive));
        r.system.push_back(boost_.include(boost_types::xml_iarchive));
    }
    r.system.push_back(boost_.include(boost_types::text_oarchive));
    r.system.push_back(boost_.include(boost_types::text_iarchive));
    r.system.push_back(boost_.include(boost_types::binary_oarchive));
    r.system.push_back(boost_.include(boost_types::binary_iarchive));
    r.system.push_back(boost_.include(boost_types::polymorphic_iarchive));
    r.system.push_back(boost_.include(boost_types::polymorphic_oarchive));

    return r;
}

inclusion_lists cpp_inclusion_manager::
includes_for_pod(const sml::pod& pod, cpp_facet_types ft, cpp_file_types flt,
    cpp_aspect_types at) const {

    inclusion_lists r;
    const auto n(pod.name());
    if (at == cpp_aspect_types::forward_decls) {
        append_self_dependencies(n, ft, flt, at, n.meta_type(), r);
        return r;
    }

    const auto names(pod_to_qualified_names(pod));
    const auto keys(pod_to_keys(pod));
    const bool rsm(requires_stream_manipulators(names));
    const bool pc(is_parent_or_child(pod));

    append_implementation_dependencies(pod, ft, flt, r, rsm);
    append_relationship_dependencies(names, keys, pod.leaves(), ft, flt, pc, r);
    append_self_dependencies(n, ft, flt, at, n.meta_type(), r);

    remove_duplicates(r);
    return r;
}

} } } }
