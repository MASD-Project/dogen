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
const std::string primitive_model("primitive_model");
const std::string bool_type("bool");
const std::string double_type("double");
const std::string float_type("float");

bool contains(const std::set<dogen::config::cpp_facet_types>& f,
    dogen::config::cpp_facet_types ft) {
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
      io_enabled_(contains(settings_.enabled_facets(),
              config::cpp_facet_types::io)),
      serialization_enabled_(contains(settings_.enabled_facets(),
              config::cpp_facet_types::serialization)),
      hash_enabled_(contains(settings_.enabled_facets(),
              config::cpp_facet_types::hash)), boost_(), std_(),
      dependency_extractor_(model_.pods(), boost_, std_) {

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
location_request_factory(config::cpp_facet_types ft, cpp_file_types flt,
    cpp_aspect_types at, const sml::qname& name) const {

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

void cpp_inclusion_manager::register_header(config::cpp_facet_types ft,
    const boost::filesystem::path& relative_path) {
    headers_for_facet_[ft].push_back(relative_path.generic_string());
}

std::string cpp_inclusion_manager::
domain_header_dependency(const sml::qname& name,
    const cpp_aspect_types at) const {
    const auto d(config::cpp_facet_types::types);
    const auto h(cpp_file_types::header);
    const auto rq(location_request_factory(d, h, at, name));
    return location_manager_.relative_logical_path(rq).generic_string();
}

std::string cpp_inclusion_manager::header_dependency(
    const sml::qname& name, config::cpp_facet_types facet_type,
    const cpp_aspect_types at) const {
    const auto h(cpp_file_types::header);
    const auto main(at);
    const auto rq(location_request_factory(facet_type, h, main, name));
    return location_manager_.relative_logical_path(rq).generic_string();
}

void cpp_inclusion_manager::
append_implementation_dependencies( const dependency_details& dd,
    const config::cpp_facet_types ft, const cpp_file_types flt,
    inclusion_lists& il) const {

    using config::cpp_facet_types;

    /*
     * STL
     */
    // iosfwd:
    const bool is_header(flt == cpp_file_types::header);
    const bool is_domain(ft == cpp_facet_types::types);
    const bool is_io(ft == cpp_facet_types::io);

    const bool domain_with_io(is_domain &&
        (settings_.use_integrated_io() || dd.is_parent_or_child()));

    if (is_header && io_enabled_ && (domain_with_io || is_io))
        il.system.push_back(std_.include(std_types::iosfwd));

    // algorithm: domain headers need it for the swap function.
    if (is_header && is_domain)
        il.system.push_back(std_.include(std_types::algorithm));

    // ostream:
    const bool is_implementation(flt == cpp_file_types::implementation);
    const bool io_without_iio(is_io && !settings_.use_integrated_io());
    if (is_implementation && io_enabled_ && (domain_with_io || io_without_iio))
        il.system.push_back(std_.include(std_types::ostream));

    // functional
    const bool is_hash(ft == cpp_facet_types::hash);
    if (is_header && is_hash)
        il.system.push_back(std_.include(std_types::functional));

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
    if (is_header && is_serialization && dd.is_parent())
        il.system.push_back(boost_.include(boost_types::assume_abstract));

    // boost virtual base of
    if (is_header && is_serialization && !dd.is_parent() && dd.is_child())
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
    if (is_implementation && io_enabled_ && dd.requires_stream_manipulators() &&
        (domain_with_io || io_without_iio))
        il.system.push_back(boost_.include(boost_types::io_ios_state));

    // boost string algorithm
    if (is_implementation && io_enabled_ && (domain_with_io || io_without_iio)
        && dd.has_std_string())
        il.system.push_back(boost_.include(boost_types::string_algorithm));

    // apply visitor
    if (is_implementation && io_enabled_ && (domain_with_io || io_without_iio)
        && dd.has_variant())
        il.system.push_back(boost_.include(boost_types::apply_visitor));

    if (is_implementation && is_hash && dd.has_variant())
        il.system.push_back(boost_.include(boost_types::apply_visitor));
}

void cpp_inclusion_manager::append_boost_dependencies(
    const config::cpp_facet_types ft, const cpp_file_types flt,
    const dogen::sml::qname& qname,
    inclusion_lists& il) const {

    const std::string type_name(qname.type_name());
    using config::cpp_facet_types;

    /*
     * boost::shared_ptr
     */
    const bool is_header(flt == cpp_file_types::header);
    const bool is_domain(ft == cpp_facet_types::types);
    const bool is_sp(type_name == boost_.type(boost_types::shared_ptr));
    if (is_header && is_domain && is_sp)
        il.system.push_back(boost_.include(boost_types::shared_ptr));

    const bool is_serialization(ft == cpp_facet_types::serialization);
    const bool is_implementation(flt == cpp_file_types::implementation);
    if (is_implementation && is_serialization && is_sp)
        il.system.push_back(
            boost_.include(boost_types::serialization_shared_ptr));

    /*
     * boost::optional
     */
    const bool is_opt(type_name == boost_.type(boost_types::optional));
    if (is_header && is_domain && is_opt)
        il.system.push_back(boost_.include(boost_types::optional));

    if (is_implementation && is_serialization && is_opt)
        il.system.push_back(
            boost_.include(boost_types::serialization_optional));

    /*
     * boost::variant
     */
    const bool is_variant(type_name == boost_.type(boost_types::variant));
    if (is_header && is_domain && is_variant)
        il.system.push_back(boost_.include(boost_types::variant));

    if (is_implementation && is_serialization && is_variant)
        il.system.push_back(boost_.include(boost_types::serialization_variant));

    /*
     * boost::filesystem::path
     */
    const bool is_path(type_name == boost_.type(boost_types::filesystem_path));
    if (is_header && is_domain && is_path)
        il.system.push_back(boost_.include(boost_types::filesystem_path));

    const bool is_test_data(ft == cpp_facet_types::test_data);
    if (is_implementation && is_test_data && is_path)
        il.system.push_back(std_.include(std_types::sstream));

    const bool is_io(ft == cpp_facet_types::io);
    // FIXME: removed  || p.parent_name() || p.is_parent()
    const bool domain_with_io(is_domain && (settings_.use_integrated_io()));
    const bool io_without_iio(is_io && !settings_.use_integrated_io());

    /*
     * boost::gregorian::date
     */
    const bool is_date(type_name == boost_.type(boost_types::gregorian_date));
    if (is_header && is_domain && is_date)
        il.system.push_back(boost_.include(boost_types::gregorian_date));

    if (is_date && is_implementation && io_enabled_ &&
        (domain_with_io || io_without_iio))
        il.system.push_back(boost_.include(boost_types::io_gregorian_date));

    if (is_implementation && is_serialization && is_date) {
        il.system.push_back(boost_.include(boost_types::io_gregorian_date));
        il.system.push_back(
            boost_.include(boost_types::serialization_gregorian_date));
    }

    /*
     * boost::posix_time::ptime
     */
    const bool is_time(type_name == boost_.type(boost_types::ptime));
    if (is_header && is_domain && is_time)
        il.system.push_back(boost_.include(boost_types::ptime));

    if (is_time && is_implementation && io_enabled_ &&
        (domain_with_io || io_without_iio))
        il.system.push_back(boost_.include(boost_types::io_time));

    if (is_implementation && is_serialization && is_time) {
        il.system.push_back(boost_.include(boost_types::io_time));
        il.system.push_back(boost_.include(boost_types::serialization_ptime));
    }

    /*
     * boost::posix_time::time_duration
     */
    const bool is_duration(
        type_name == boost_.type(boost_types::time_duration));
    if (is_header && is_domain && is_duration)
        il.system.push_back(boost_.include(boost_types::time_duration));

    if (is_duration && is_implementation && io_enabled_ &&
        (domain_with_io || io_without_iio))
        il.system.push_back(boost_.include(boost_types::io_time));

    if (is_implementation && is_serialization && is_duration) {
        il.system.push_back(boost_.include(boost_types::io_time));
        il.system.push_back(
            boost_.include(boost_types::serialization_time_duration));
    }
}

void cpp_inclusion_manager::append_std_dependencies(
    const config::cpp_facet_types ft, const cpp_file_types flt,
    const dogen::sml::qname& qname,
    inclusion_lists& il) const {

    const std::string type_name(qname.type_name());
    using config::cpp_facet_types;

    /*
     * std::string
     */
    const bool is_header(flt == cpp_file_types::header);
    const bool is_domain(ft == cpp_facet_types::types);
    const bool is_string(type_name == std_.type(std_types::string));
    if (is_header && is_domain && is_string)
        il.system.push_back(std_.include(std_types::string));

    const bool is_serialization(ft == cpp_facet_types::serialization);
    const bool is_implementation(flt == cpp_file_types::implementation);
    if (is_implementation && is_serialization && is_string)
        il.system.push_back(boost_.include(boost_types::string));

    const bool is_test_data(ft == cpp_facet_types::test_data);
    if (is_implementation && is_test_data && is_string)
        il.system.push_back(std_.include(std_types::sstream));

    /*
     * std::vector
     */
    const bool is_vector(type_name == std_.type(std_types::vector));
    if (is_header && is_domain && is_vector)
        il.system.push_back(std_.include(std_types::vector));

    if (is_implementation && is_serialization && is_vector)
        il.system.push_back(boost_.include(boost_types::vector));

    /*
     * std::list
     */
    const bool is_list(type_name == std_.type(std_types::list));
    if (is_header && is_domain && is_list)
        il.system.push_back(std_.include(std_types::list));

    if (is_implementation && is_serialization && is_list)
        il.system.push_back(boost_.include(boost_types::list));

    /*
     * std::deque
     */
    const bool is_deque(type_name == std_.type(std_types::deque));
    if (is_header && is_domain && is_deque)
        il.system.push_back(std_.include(std_types::deque));

    if (is_implementation && is_serialization && is_deque)
        il.system.push_back(boost_.include(boost_types::deque));

    /*
     * std::set
     */
    const bool is_set(type_name == std_.type(std_types::set));
    if (is_header && is_domain && is_set)
        il.system.push_back(std_.include(std_types::set));

    if (is_implementation && is_serialization && is_set)
        il.system.push_back(boost_.include(boost_types::set));

    // FIXME: massive hack. boost doesn't have support for
    // serialisation so we are using our own hacked headers
    auto lambda([&](const std::string& type) {
        std::string private_ser_header("utility/serialization/");
        private_ser_header+= type + ".hpp";
        const auto epp(model_.external_package_path());
        if (!epp.empty())
            private_ser_header = epp.front() + "/" + private_ser_header;

        if (is_implementation && is_serialization && qname.type_name() == type)
            il.user.push_back(private_ser_header);
        });

    /*
     * std::unordered_map
     */
    const bool is_umap(type_name == std_.type(std_types::unordered_map));
    if (is_header && is_domain && is_umap)
        il.system.push_back(std_.include(std_types::unordered_map));
    lambda(std_.type(std_types::unordered_map));

    /*
     * std::unordered_set
     */
    const bool is_uset(type_name == std_.type(std_types::unordered_set));
    if (is_header && is_domain && is_uset)
        il.system.push_back(std_.include(std_types::unordered_set));
    lambda(std_.type(std_types::unordered_set));

    /*
     * primitives
     */
    if (is_header && is_domain && std_.is_primitive(qname.type_name())) {
        const auto t(std_.string_to_type(type_name));
        il.system.push_back(std_.include(t));
    }
}

void cpp_inclusion_manager::append_relationship_dependencies(
    const dependency_details& dd, const config::cpp_facet_types ft,
    const cpp_file_types flt, inclusion_lists& il) const {

    auto names(dd.names());
    using config::cpp_facet_types;
    const bool is_header(flt == cpp_file_types::header);
    const bool is_domain(ft == cpp_facet_types::types);
    for(const auto n : dd.forward_decls()) {
        const bool is_primitive(n.meta_type() == sml::meta_types::primitive);
        const bool header_and_domain(is_header && is_domain);

        if (n.model_name() == std_.model() ||
            n.model_name() == boost_.model() || !header_and_domain) {
            names.insert(n);
            continue;
        } else if (n.model_name() == primitive_model || is_primitive)
            continue;

        /*
         * rule 1: domain headers that depend on a domain type
         * which can be forward declared will forward declare it.
         */
        const auto fwd(cpp_aspect_types::forward_decls);
        il.user.push_back(header_dependency(n, ft, fwd));
    }

    for(const auto n : names) {
        // handle all special models first
        if (n.model_name() == std_.model()) {
            append_std_dependencies(ft, flt, n, il);
            continue;
        } else if (n.model_name() == boost_.model()) {
            append_boost_dependencies(ft, flt, n, il);
            continue;
        } else if (n.model_name() == primitive_model)
            continue;

        /*
         * rule 2: primitives never require header files. Not quite
         * sure when this could happen, as they should be part of a
         * special model.
         */
        const bool is_primitive(n.meta_type() == sml::meta_types::primitive);
        if (is_primitive)
            continue; // primitve on non-primitives model

        /*
         * rule 3: domain headers need the corresponding header file
         * for the dependency
         */
        const auto main(cpp_aspect_types::main);
        if (is_header && !is_primitive && is_domain)
            il.user.push_back(header_dependency(n, ft, main));

        /*
         * rule 4: hash, IO, serialisation and test data
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
         * rule 5: Domain implementation needs to include any files
         * that the domain header forwarded.
         */
        const bool forwarded(dd.forward_decls().find(n) !=
            dd.forward_decls().end());
        if (is_implementation && is_domain && forwarded)
            il.user.push_back(header_dependency(n, ft, main));

        /*
         * rule 6: parents and children with integrated IO require IO
         * headers in domain implementation.
         */
        const bool domain_with_io(is_domain &&
            (settings_.use_integrated_io() || dd.is_parent_or_child()));

        if (is_implementation && io_enabled_ && domain_with_io)
            il.user.push_back(header_dependency(n, cpp_facet_types::io, main));
    }

    for (const auto k : dd.keys()) {
        // keys from special models can be ignored
        if (k.model_name() == std_.model() ||
            k.model_name() == boost_.model() ||
            k.model_name() == primitive_model)
            continue;

        /*
         * rule 7: domain headers require hashing for all keys.
         */
        const bool is_header(flt == cpp_file_types::header);
        const bool is_domain(ft == cpp_facet_types::types);
        const bool is_primitive(k.meta_type() == sml::meta_types::primitive);

        const auto main(cpp_aspect_types::main);
        if (!is_primitive && is_header && hash_enabled_ && is_domain)
            il.user.push_back(header_dependency(k, cpp_facet_types::hash, main));
    }

    for (const auto l : dd.leaves() ) {
        /*
         * rule 8: leaves require generators in test data.
         */
        const bool is_implementation(flt == cpp_file_types::implementation);
        const bool is_td(ft == cpp_facet_types::test_data);
        const auto main(cpp_aspect_types::main);
        if (is_implementation && is_td)
            il.user.push_back(header_dependency(l, ft, main));

        /*
         * rule 9: base classes require registering all leaves in
         * serialisation implementation.
         */
        const bool is_ser(ft == cpp_facet_types::serialization);
        if (is_implementation && is_ser)
            il.user.push_back(header_dependency(l, ft, main));
    }
}

void cpp_inclusion_manager::
append_self_dependencies(dogen::sml::qname name,
    const config::cpp_facet_types ft, const cpp_file_types flt,
    const cpp_aspect_types at, const sml::meta_types mt,
    inclusion_lists& il) const {

    using config::cpp_facet_types;
    const bool is_header(flt == cpp_file_types::header);
    const bool is_domain(ft == cpp_facet_types::types);
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

void cpp_inclusion_manager::remove_duplicates(inclusion_lists& il) const {
    il.system.sort();
    il.system.unique();
    il.user.sort();
    il.user.unique();
}

inclusion_lists cpp_inclusion_manager::
includes_for_includer_files(config::cpp_facet_types ft) const {
    inclusion_lists r;
    const auto i(headers_for_facet_.find(ft));
    if (i != headers_for_facet_.end())
        r.user = i->second;
    return r;
}

inclusion_lists cpp_inclusion_manager::
includes_for_enumeration(const sml::enumeration& e, config::cpp_facet_types ft,
    cpp_file_types flt, cpp_aspect_types at) const {
    inclusion_lists r;

    using config::cpp_facet_types;
    append_self_dependencies(e.name(), ft, flt, at, e.name().meta_type(), r);

    // functional
    const bool is_header(flt == cpp_file_types::header);
    const bool is_hash(ft == cpp_facet_types::hash);
    if (is_header && is_hash)
        r.system.push_back(std_.include(std_types::functional));

    // nvp serialisation
    const bool is_serialization(ft == cpp_facet_types::serialization);
    if (is_header && is_serialization && !settings_.disable_xml_serialization())
        r.system.push_back(boost_.include(boost_types::nvp));

    // iosfwd
    const bool is_io(ft == cpp_facet_types::io);
    if (is_header && is_io && io_enabled_)
        r.system.push_back(std_.include(std_types::iosfwd));

    // ostream
    const bool is_implementation(flt == cpp_file_types::implementation);
    if (is_implementation && is_io && io_enabled_)
        r.system.push_back(std_.include(std_types::ostream));

    // stdexcept
    if (is_implementation && is_io && io_enabled_)
        r.system.push_back(std_.include(std_types::stdexcept));

    remove_duplicates(r);
    return r;
}

inclusion_lists cpp_inclusion_manager::
includes_for_exception(const sml::exception& e, config::cpp_facet_types ft,
    cpp_file_types flt, cpp_aspect_types at) const {
    inclusion_lists r;

    using config::cpp_facet_types;
    append_self_dependencies(e.name(), ft, flt, at, e.name().meta_type(), r);

    // exception info
    const bool is_header(flt == cpp_file_types::header);
    const bool is_domain(ft == cpp_facet_types::types);
    if (is_header && is_domain)
        r.system.push_back(boost_.include(boost_types::exception_info));

    // string
    if (is_header && is_domain)
        r.system.push_back(std_.include(std_types::string));

    remove_duplicates(r);
    return r;
}

inclusion_lists cpp_inclusion_manager::
includes_for_registrar(cpp_file_types flt) const {
    inclusion_lists r;

    if (flt == cpp_file_types::header)
        return r;

    using config::cpp_facet_types;
    const auto main(cpp_aspect_types::main);
    const auto ft(cpp_facet_types::serialization);
    for (const auto& l : model_.leaves())
        r.user.push_back(header_dependency(l, ft, main));

    for (const auto& d : model_.dependencies()) {
        const auto ref(d.second);
        if (ref.is_system())
            continue;

        sml::qname n;
        n.model_name(ref.model_name());
        n.type_name("registrar");
        n.external_package_path(ref.external_package_path());
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
includes_for_pod(const sml::pod& pod, config::cpp_facet_types ft,
    cpp_file_types flt, cpp_aspect_types at) const {

    inclusion_lists r;
    const auto n(pod.name());
    if (at == cpp_aspect_types::forward_decls) {
        append_self_dependencies(n, ft, flt, at, n.meta_type(), r);
        return r;
    }

    const auto details(dependency_extractor_.extract(pod));

    append_implementation_dependencies(details, ft, flt, r);
    append_relationship_dependencies(details, ft, flt, r);
    append_self_dependencies(n, ft, flt, at, n.meta_type(), r);

    remove_duplicates(r);
    return r;
}

} } } }
