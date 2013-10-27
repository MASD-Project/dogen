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
#include <boost/algorithm/string/predicate.hpp>
#include <boost/range/algorithm/find_first_of.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/config/io/cpp_settings_io.hpp"
#include "dogen/config/io/cpp_facet_types_io.hpp"
#include "dogen/sml_to_cpp/types/includer.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("sml_to_cpp.includer"));

const std::string empty;
const std::string hardware_model("hardware_model");
const std::string bool_type("bool");
const std::string double_type("double");
const std::string float_type("float");

bool contains(const std::set<dogen::config::cpp_facet_types>& f,
    dogen::config::cpp_facet_types ft) {
    return f.find(ft) != f.end();
}

}

namespace dogen {
namespace sml_to_cpp {

includer::includer(includer&& rhs)
    : model_(std::move(rhs.model_)),
      locator_(std::move(rhs.locator_)),
      settings_(std::move(rhs.settings_)),
      io_enabled_(std::move(rhs.io_enabled_)),
      serialization_enabled_(std::move(rhs.serialization_enabled_)),
      hash_enabled_(std::move(rhs.hash_enabled_)),
      headers_for_facet_(std::move(rhs.headers_for_facet_)),
      boost_(std::move(rhs.boost_)),
      std_(std::move(rhs.std_)) { }

includer::includer(const sml::model& model,
    const locator& locator,
    const config::cpp_settings& settings)
    : model_(model), locator_(locator), settings_(settings),
      io_enabled_(contains(settings_.enabled_facets(),
              config::cpp_facet_types::io)),
      serialization_enabled_(contains(settings_.enabled_facets(),
              config::cpp_facet_types::serialization)),
      hash_enabled_(contains(settings_.enabled_facets(),
              config::cpp_facet_types::hash)), boost_(), std_() {

    BOOST_LOG_SEV(lg, debug) << "Initial configuration: " << settings_;
}

void includer::register_header(config::cpp_facet_types ft,
    const boost::filesystem::path& relative_path) {
    BOOST_LOG_SEV(lg, debug) << "Registering header: "
                             << relative_path.generic_string()
                             << " for facet: " << ft;

    headers_for_facet_[ft].push_back(relative_path.generic_string());
}

std::string includer::domain_header_dependency(const sml::qname& name,
    const cpp::aspect_types at) const {
    return header_dependency(name, config::cpp_facet_types::types, at);
}

std::string includer::header_dependency(
    const sml::qname& name, config::cpp_facet_types facet_type,
    const cpp::aspect_types at) const {
    cpp::content_descriptor cd;
    using cpp::file_types;
    cd.file_type(file_types::header);
    cd.facet_type(facet_type);
    cd.aspect_type(at);
    cd.name(name);
    return locator_.relative_logical_path(cd).generic_string();
}

void includer::
append_implementation_dependencies(const relationships& rel,
    const cpp::content_descriptor& cd, inclusion_lists& il) const {

    using config::cpp_facet_types;
    using cpp::file_types;

    /*
     * STL
     */
    // iosfwd:
    const bool is_header(cd.file_type() == file_types::header);
    const bool is_types(cd.facet_type() == cpp_facet_types::types);
    const bool is_io(cd.facet_type() == cpp_facet_types::io);
    const bool domain_with_io(is_types &&
        (settings_.use_integrated_io() || rel.is_parent() || rel.is_child()));

    if (is_header && io_enabled_ && (domain_with_io || is_io))
        il.system().push_back(std_.include(std_types::iosfwd));

    // algorithm: domain headers need it for the swap function.
    if (is_header && is_types)
        il.system().push_back(std_.include(std_types::algorithm));

    // ostream:
    const bool is_implementation(cd.file_type() == file_types::implementation);
    const bool io_without_iio(is_io && !settings_.use_integrated_io());
    if (is_implementation && io_enabled_ && (domain_with_io || io_without_iio))
        il.system().push_back(std_.include(std_types::ostream));

    // functional
    const bool is_hash(cd.facet_type() == cpp_facet_types::hash);
    if (is_header && is_hash)
        il.system().push_back(std_.include(std_types::functional));

    /*
     * boost
     */
    // nvp serialisation
    const auto ser(cpp_facet_types::serialization);
    const bool is_serialization(cd.facet_type() == ser);
    if (is_implementation && is_serialization &&
        !settings_.disable_xml_serialization())
        il.system().push_back(boost_.include(boost_types::nvp));

    // split free serialisation
    if (is_header && is_serialization)
        il.system().push_back(boost_.include(boost_types::split_free));

    // assume abstract
    if (is_header && is_serialization && rel.is_parent())
        il.system().push_back(boost_.include(boost_types::assume_abstract));

    // boost virtual base of
    if (is_header && is_serialization && !rel.is_parent() && rel.is_child())
        il.system().push_back(boost_.include(boost_types::is_virtual_base_of));

    // boost archive types
    if (is_implementation && is_serialization) {
        if (!settings_.disable_xml_serialization()) {
            il.system().push_back(boost_.include(boost_types::xml_oarchive));
            il.system().push_back(boost_.include(boost_types::xml_iarchive));
        }
        il.system().push_back(boost_.include(boost_types::text_oarchive));
        il.system().push_back(boost_.include(boost_types::text_iarchive));
        il.system().push_back(boost_.include(boost_types::binary_oarchive));
        il.system().push_back(boost_.include(boost_types::binary_iarchive));
        il.system().push_back(
            boost_.include(boost_types::polymorphic_iarchive));
        il.system().push_back(
            boost_.include(boost_types::polymorphic_oarchive));
    }

    // state saver
    const auto rsm(rel.requires_stream_manipulators());
    if (is_implementation && io_enabled_ && rsm
        && (domain_with_io || io_without_iio))
        il.system().push_back(boost_.include(boost_types::io_ios_state));

    // boost string algorithm
    if (is_implementation && io_enabled_ && (domain_with_io || io_without_iio)
        && rel.has_std_string())
        il.system().push_back(boost_.include(boost_types::string_algorithm));

    // apply visitor
    if (is_implementation && io_enabled_ && (domain_with_io || io_without_iio)
        && rel.has_variant())
        il.system().push_back(boost_.include(boost_types::apply_visitor));

    if (is_implementation && is_hash && rel.has_variant())
        il.system().push_back(boost_.include(boost_types::apply_visitor));

    // pair dependencies
    if (is_implementation && is_serialization && rel.has_std_pair())
        il.system().push_back(boost_.include(boost_types::serialization_pair));
}

void includer::append_boost_dependencies(const relationships& rel,
    const cpp::content_descriptor& cd, inclusion_lists& il) const {

    const auto sn(cd.name().simple_name());
    using config::cpp_facet_types;
    using cpp::file_types;

    const bool is_serialization(
        cd.facet_type() == cpp_facet_types::serialization);
    const bool is_implementation(cd.file_type() == file_types::implementation);

    // FIXME: massive hack. boost doesn't have support for
    // serialisation so we are using our own hacked headers
    auto lambda([&](const std::string& type) {
            std::string private_ser_header("utility/serialization/");
            private_ser_header+= type + ".hpp";
            const auto epp(model_.name().external_module_path());
            if (!epp.empty())
                private_ser_header = epp.front() + "/" + private_ser_header;

            if (is_implementation && is_serialization && sn == type)
                il.user().push_back(private_ser_header);
        });

    /*
     * boost::shared_ptr
     */
    const bool is_header(cd.file_type() == file_types::header);
    const bool is_types(cd.facet_type() == cpp_facet_types::types);
    const bool is_sp(sn == boost_.type(boost_types::shared_ptr));
    if (is_header && is_types && is_sp)
        il.system().push_back(boost_.include(boost_types::shared_ptr));

    if (is_implementation && is_serialization && is_sp)
        il.system().push_back(
            boost_.include(boost_types::serialization_shared_ptr));

    /*
     * boost::optional
     */
    const bool is_opt(sn == boost_.type(boost_types::optional));
    if (is_header && is_types && is_opt)
        il.system().push_back(boost_.include(boost_types::optional));

    if (is_implementation && is_serialization && is_opt)
        il.system().push_back(
            boost_.include(boost_types::serialization_optional));

    /*
     * boost::variant
     */
    const bool is_variant(sn == boost_.type(boost_types::variant));
    if (is_header && is_types && is_variant)
        il.system().push_back(boost_.include(boost_types::variant));

    if (is_implementation && is_serialization && is_variant)
        il.system().push_back(
            boost_.include(boost_types::serialization_variant));

    /*
     * boost::filesystem::path
     */
    const bool is_path(sn == boost_.type(boost_types::filesystem_path));
    if (is_header && is_types && is_path)
        il.system().push_back(boost_.include(boost_types::filesystem_path));
    lambda(boost_.type(boost_types::filesystem_path));

    const bool is_test_data(cd.facet_type() == cpp_facet_types::test_data);
    if (is_implementation && is_test_data && is_path)
        il.system().push_back(std_.include(std_types::sstream));

    const bool is_io(cd.facet_type() == cpp_facet_types::io);
    const bool domain_with_io(is_types &&
        (settings_.use_integrated_io() || rel.is_parent() || rel.is_child()));
    const bool io_without_iio(is_io && !settings_.use_integrated_io());

    /*
     * boost::gregorian::date
     */
    const bool is_date(sn == boost_.type(boost_types::gregorian_date));
    if (is_header && is_types && is_date)
        il.system().push_back(boost_.include(boost_types::gregorian_date));

    if (is_date && is_implementation && io_enabled_ &&
        (domain_with_io || io_without_iio))
        il.system().push_back(boost_.include(boost_types::io_gregorian_date));

    if (is_implementation && is_serialization && is_date) {
        il.system().push_back(boost_.include(boost_types::io_gregorian_date));
        il.system().push_back(
            boost_.include(boost_types::serialization_gregorian_date));
    }

    /*
     * boost::posix_time::ptime
     */
    const bool is_time(sn == boost_.type(boost_types::ptime));
    if (is_header && is_types && is_time)
        il.system().push_back(boost_.include(boost_types::ptime));

    if (is_time && is_implementation && io_enabled_ &&
        (domain_with_io || io_without_iio))
        il.system().push_back(boost_.include(boost_types::io_time));

    if (is_implementation && is_serialization && is_time) {
        il.system().push_back(boost_.include(boost_types::io_time));
        il.system().push_back(boost_.include(boost_types::serialization_ptime));
    }

    /*
     * boost::posix_time::time_duration
     */
    const bool is_duration(sn == boost_.type(boost_types::time_duration));
    if (is_header && is_types && is_duration)
        il.system().push_back(boost_.include(boost_types::time_duration));

    if (is_duration && is_implementation && io_enabled_ &&
        (domain_with_io || io_without_iio))
        il.system().push_back(boost_.include(boost_types::io_time));

    if (is_implementation && is_serialization && is_duration) {
        il.system().push_back(boost_.include(boost_types::io_time));
        il.system().push_back(
            boost_.include(boost_types::serialization_time_duration));
    }

    /*
     * boost::property_tree::ptree
     */
    const bool is_ptree(sn == boost_.type(boost_types::ptree));
    if (is_header && is_types && is_ptree)
        il.system().push_back(boost_.include(boost_types::ptree));

    if (is_ptree && is_implementation && io_enabled_ &&
        (domain_with_io || io_without_iio))
        il.system().push_back(boost_.include(boost_types::io_ptree));

    if (is_implementation && is_serialization && is_ptree) {
        il.system().push_back(boost_.include(boost_types::io_ptree));
        il.system().push_back(boost_.include(boost_types::serialization_ptree));
    }
}

void includer::append_std_dependencies(const cpp::content_descriptor& cd,
    inclusion_lists& il) const {

    const std::string sn(cd.name().simple_name());
    using config::cpp_facet_types;
    using cpp::file_types;

    /*
     * std::string
     */
    const bool is_header(cd.file_type() == file_types::header);
    const bool is_types(cd.facet_type() == cpp_facet_types::types);
    const bool is_string(sn == std_.type(std_types::string));
    if (is_header && is_types && is_string)
        il.system().push_back(std_.include(std_types::string));

    const auto ser(cpp_facet_types::serialization);
    const bool is_serialization(cd.facet_type() == ser);
    const bool is_implementation(cd.file_type() == file_types::implementation);
    if (is_implementation && is_serialization && is_string)
        il.system().push_back(boost_.include(boost_types::string));

    const bool is_test_data(cd.facet_type() == cpp_facet_types::test_data);
    if (is_implementation && is_test_data && is_string)
        il.system().push_back(std_.include(std_types::sstream));

    /*
     * std::vector
     */
    const bool is_vector(sn == std_.type(std_types::vector));
    if (is_header && is_types && is_vector)
        il.system().push_back(std_.include(std_types::vector));

    if (is_implementation && is_serialization && is_vector)
        il.system().push_back(boost_.include(boost_types::vector));

    /*
     * std::list
     */
    const bool is_list(sn == std_.type(std_types::list));
    if (is_header && is_types && is_list)
        il.system().push_back(std_.include(std_types::list));

    if (is_implementation && is_serialization && is_list)
        il.system().push_back(boost_.include(boost_types::list));

    /*
     * std::deque
     */
    const bool is_deque(sn == std_.type(std_types::deque));
    if (is_header && is_types && is_deque)
        il.system().push_back(std_.include(std_types::deque));

    if (is_implementation && is_serialization && is_deque)
        il.system().push_back(boost_.include(boost_types::deque));

    /*
     * std::set
     */
    const bool is_set(sn == std_.type(std_types::set));
    if (is_header && is_types && is_set)
        il.system().push_back(std_.include(std_types::set));

    if (is_implementation && is_serialization && is_set)
        il.system().push_back(boost_.include(boost_types::set));

    // FIXME: massive hack. boost doesn't have support for
    // serialisation so we are using our own hacked headers
    auto lambda([&](const std::string& type) {
        std::string private_ser_header("utility/serialization/");
        private_ser_header+= type + ".hpp";
        const auto epp(model_.name().external_module_path());
        if (!epp.empty())
            private_ser_header = epp.front() + "/" + private_ser_header;

        if (is_implementation && is_serialization && sn == type)
            il.user().push_back(private_ser_header);
        });

    /*
     * std::unordered_map
     */
    const bool is_umap(sn == std_.type(std_types::unordered_map));
    if (is_header && is_types && is_umap)
        il.system().push_back(std_.include(std_types::unordered_map));
    lambda(std_.type(std_types::unordered_map));

    /*
     * std::unordered_set
     */
    const bool is_uset(sn == std_.type(std_types::unordered_set));
    if (is_header && is_types && is_uset)
        il.system().push_back(std_.include(std_types::unordered_set));
    lambda(std_.type(std_types::unordered_set));

    /*
     * primitives
     */
    if (is_header && is_types && std_.is_primitive(sn)) {
        const auto t(std_.string_to_type(sn));
        il.system().push_back(std_.include(t));
    }

    /*
     * std::pair
     */
    const bool is_pair(sn == std_.type(std_types::pair));
    if (is_header && is_types && is_pair)
        il.system().push_back(std_.include(std_types::pair));
}

void includer::append_relationship_dependencies(const relationships& rel,
    const cpp::content_descriptor& cd, inclusion_lists& il) const {

    auto names(rel.names());
    using config::cpp_facet_types;
    using cpp::file_types;
    using cpp::aspect_types;
    using cpp::content_types;

    const bool is_header(cd.file_type() == file_types::header);
    const bool is_types(cd.facet_type() == cpp_facet_types::types);
    for(const auto n : rel.forward_decls()) {
        const bool is_primitive(cd.content_type() == content_types::primitive);
        const bool header_and_domain(is_header && is_types);

        if (n.model_name() == std_.model() ||
            n.model_name() == boost_.model() || !header_and_domain) {
            names.insert(n);
            continue;
        } else if (n.model_name() == hardware_model || is_primitive)
            continue;

        /*
         * rule 1: domain headers that depend on a domain type
         * which can be forward declared will forward declare it.
         */
        const auto fwd(aspect_types::forward_decls);
        il.user().push_back(header_dependency(n, cd.facet_type(), fwd));
    }

    const auto impl(file_types::implementation);
    const bool is_implementation(cd.file_type() == impl);
    for(const auto n : names) {
        auto cd2(cd);
        cd2.name(n);

        // handle all special models first
        if (n.model_name() == std_.model()) {
            append_std_dependencies(cd2, il);
            continue;
        } else if (n.model_name() == boost_.model()) {
            append_boost_dependencies(rel, cd2, il);
            continue;
        } else if (n.model_name() == hardware_model ||
            n.model_name().empty())
            continue;

        /*
         * rule 2: primitives never require header files. Not quite
         * sure when this could happen, as they should be part of a
         * special model.
         */
        const bool is_primitive(cd.content_type() == content_types::primitive);
        if (is_primitive)
            continue; // primitve on non-primitives model

        /*
         * rule 3: domain headers need the corresponding header file
         * for the dependency
         */
        const auto main(aspect_types::main);
        if (is_header && !is_primitive && is_types)
            il.user().push_back(header_dependency(n, cd.facet_type(), main));

        /*
         * rule 4: odb headers need the corresponding header file
         * for the dependency
         */
        const bool is_odb(cd.facet_type() == cpp_facet_types::odb);
        // FIXME: massive hack
        const bool is_visitor(
            boost::contains(n.simple_name(), "visitor") &&
            !boost::contains(n.simple_name(), "visitor_info"));
        if (!is_visitor && is_header && !is_primitive && is_odb)
            il.user().push_back(header_dependency(n, cd.facet_type(), main));

        /*
         * rule 5: hash, IO, serialisation, and test data
         * implementations need the corresponding header file for the
         * dependency
         */
        const bool is_hash(cd.facet_type() == cpp_facet_types::hash);
        const bool is_io(cd.facet_type() == cpp_facet_types::io);
        const bool is_ser(cd.facet_type() == cpp_facet_types::serialization);
        const bool is_td(cd.facet_type() == cpp_facet_types::test_data);
        const bool is_non_domain(is_hash || is_io || is_td || is_ser);

        if (!is_visitor && is_implementation && is_non_domain)
            il.user().push_back(header_dependency(n, cd.facet_type(), main));

        /*
         * rule 6: Domain implementation needs to include any files
         * that the domain header forwarded.
         */
        const bool forwarded(rel.forward_decls().find(n) !=
            rel.forward_decls().end());
        if (is_implementation && is_types && forwarded)
            il.user().push_back(header_dependency(n, cd.facet_type(), main));

        /*
         * rule 7: parents and children with integrated IO require IO
         * headers in domain implementation.
         */
        const bool domain_with_io(is_types &&
            (settings_.use_integrated_io() || rel.is_parent() ||
                rel.is_child()));

        const auto io(cpp_facet_types::io);
        if (!is_visitor && is_implementation && io_enabled_ && domain_with_io)
            il.user().push_back(header_dependency(n, io, main));
    }

    for (const auto k : rel.keys()) {
        // keys from special models can be ignored
        if (k.model_name() == std_.model() ||
            k.model_name() == boost_.model() ||
            k.model_name() == hardware_model)
            continue;

        /*
         * rule 8: domain headers require hashing for all keys.
         */
        const bool is_header(cd.file_type() == file_types::header);
        const bool is_types(cd.facet_type() == cpp_facet_types::types);
        const bool is_primitive(model_.primitives().find(k) !=
            model_.primitives().end());

        const auto main(aspect_types::main);
        const auto hash(cpp_facet_types::hash);
        if (!is_primitive && is_header && hash_enabled_ && is_types)
            il.user().push_back(header_dependency(k, hash, main));
    }

    for (const auto l : rel.leaves() ) {
        /*
         * rule 9: leaves require generators in test data.
         */
        const bool is_td(cd.facet_type() == cpp_facet_types::test_data);
        const auto main(aspect_types::main);
        if (is_implementation && is_td)
            il.user().push_back(header_dependency(l, cd.facet_type(), main));

        /*
         * rule 10: base classes require registering all leaves in
         * serialisation implementation.
         */
        const bool is_ser(cd.facet_type() == cpp_facet_types::serialization);
        if (is_implementation && is_ser)
            il.user().push_back(header_dependency(l, cd.facet_type(), main));
    }

    if (rel.visitor()) {
        /*
         * rule 11: leaves require generators in test data.
         */
        const bool header_and_domain(is_header && is_types);
        const auto main(aspect_types::main);
        if (header_and_domain)
            il.user().push_back(header_dependency(*rel.visitor(), cd.facet_type(), main));
    }
}

void includer::append_self_dependencies(const cpp::content_descriptor& cd,
    inclusion_lists& il) const {
    using config::cpp_facet_types;
    using cpp::file_types;
    using cpp::aspect_types;
    using cpp::content_types;

    const bool is_header(cd.file_type() == file_types::header);
    const bool is_types(cd.facet_type() == cpp_facet_types::types);
    const auto fwd(aspect_types::forward_decls);
    if (cd.aspect_type() == aspect_types::forward_decls) {
        /*
         * rule 1: non-domain forward declarations depend on the
         * domain header.
         */
        if (is_header && !is_types)
            il.user().push_back(domain_header_dependency(cd.name(), fwd));
        return;
    }

    /*
     * rule 2: if serialisation is enabled, domain headers depend on
     * the serialisation forward declaration headers.
     */
    const auto is_serialisable(
        cd.content_type() == content_types::unversioned_key ||
        cd.content_type() == content_types::versioned_key ||
        cd.content_type() == content_types::value_object ||
        cd.content_type() == content_types::entity ||
        cd.content_type() == content_types::keyed_entity);
    const auto ser(cpp_facet_types::serialization);
    if (is_header && is_types && serialization_enabled_ && is_serialisable)
        il.user().push_back(header_dependency(cd.name(), ser, fwd));

    /*
     * rule 3: all header files depend on the domain header file,
     * except for the domain header file itself.
     */
    const auto main(aspect_types::main);
    if (is_header && !is_types)
        il.user().push_back(domain_header_dependency(cd.name(), main));

    /*
     * rule 4: all implementation files depend on the domain header file.
     */
    const bool is_implementation(cd.file_type() == file_types::implementation);
    if (is_implementation)
        il.user().push_back(header_dependency(cd.name(), cd.facet_type(), main));
}

void includer::remove_duplicates(inclusion_lists& il) const {
    il.system().sort();
    il.system().unique();
    il.user().sort();
    il.user().unique();
}

inclusion_lists includer::
includes_for_includer_files(const cpp::content_descriptor& cd) const {
    inclusion_lists r;
    const auto i(headers_for_facet_.find(cd.facet_type()));
    if (i != headers_for_facet_.end())
        r.user(i->second);
    return r;
}

inclusion_lists includer::
includes_for_enumeration(const cpp::content_descriptor& cd) const {
    inclusion_lists r;

    using cpp::file_types;

    const auto ft(cd.facet_type());
    const auto flt(cd.file_type());
    append_self_dependencies(cd, r);

    // functional
    using config::cpp_facet_types;
    const bool is_header(flt == file_types::header);
    const bool is_hash(ft == cpp_facet_types::hash);
    if (is_header && is_hash)
        r.system().push_back(std_.include(std_types::functional));

    // nvp serialisation
    const bool is_serialization(ft == cpp_facet_types::serialization);
    if (is_header && is_serialization && !settings_.disable_xml_serialization())
        r.system().push_back(boost_.include(boost_types::nvp));

    // iosfwd
    const bool is_io(ft == cpp_facet_types::io);
    if (is_header && is_io && io_enabled_)
        r.system().push_back(std_.include(std_types::iosfwd));

    // ostream
    const bool is_implementation(flt == file_types::implementation);
    if (is_implementation && is_io && io_enabled_)
        r.system().push_back(std_.include(std_types::ostream));

    // stdexcept
    if (is_implementation && is_io && io_enabled_)
        r.system().push_back(std_.include(std_types::stdexcept));

    remove_duplicates(r);
    return r;
}

inclusion_lists includer::
includes_for_exception(const cpp::content_descriptor& cd) const {
    inclusion_lists r;

    const auto ft(cd.facet_type());
    const auto flt(cd.file_type());
    append_self_dependencies(cd, r);

    // exception info
    using config::cpp_facet_types;
    using cpp::file_types;
    const bool is_header(flt == file_types::header);
    const bool is_types(ft == cpp_facet_types::types);
    if (is_header && is_types)
        r.system().push_back(boost_.include(boost_types::exception_info));

    // string
    if (is_header && is_types)
        r.system().push_back(std_.include(std_types::string));

    remove_duplicates(r);
    return r;
}

inclusion_lists
includer::includes_for_registrar(const cpp::content_descriptor& cd) const {
    inclusion_lists r;

    using cpp::file_types;
    const auto flt(cd.file_type());
    if (flt == file_types::header)
        return r;

    using config::cpp_facet_types;
    using cpp::aspect_types;
    const auto main(aspect_types::main);
    const auto ft(cpp_facet_types::serialization);
    for (const auto& l : model_.leaves())
        r.user().push_back(header_dependency(l, ft, main));

    for (const auto& pair : model_.references()) {
        const auto origin_type(pair.second);
        if (origin_type == sml::origin_types::system)
            continue;

        const auto ref(pair.first);
        sml::qname n;
        n.model_name(ref.model_name());
        n.simple_name("registrar");
        n.external_module_path(ref.external_module_path());
        r.user().push_back(header_dependency(n, ft, main));
    }

    if (!settings_.disable_xml_serialization()) {
        r.system().push_back(boost_.include(boost_types::xml_oarchive));
        r.system().push_back(boost_.include(boost_types::xml_iarchive));
    }
    r.system().push_back(boost_.include(boost_types::text_oarchive));
    r.system().push_back(boost_.include(boost_types::text_iarchive));
    r.system().push_back(boost_.include(boost_types::binary_oarchive));
    r.system().push_back(boost_.include(boost_types::binary_iarchive));
    r.system().push_back(boost_.include(boost_types::polymorphic_iarchive));
    r.system().push_back(boost_.include(boost_types::polymorphic_oarchive));

    return r;
}

inclusion_lists includer::includes_for_visitor(const cpp::content_descriptor& cd,
    const relationships& rel) const {
    inclusion_lists r;
    using cpp::aspect_types;
    const auto ft(cd.facet_type());
    for(const auto n : rel.names()) {
        // we need to override the aspect requested by the content
        // descriptor because we do not need an include of the visitor
        // itself but of the forward declarations of the types in
        // question.
        const auto fwd(aspect_types::forward_decls);
        r.user().push_back(header_dependency(n, ft, fwd));
    }
    return r;
}

inclusion_lists includer::includes_for_object(
    const cpp::content_descriptor& cd, const relationships& rel) const {
    inclusion_lists r;
    using cpp::aspect_types;
    if (cd.aspect_type() == aspect_types::forward_decls) {
        append_self_dependencies(cd, r);
        return r;
    }

    append_implementation_dependencies(rel, cd, r);
    append_relationship_dependencies(rel, cd, r);
    append_self_dependencies(cd, r);

    remove_duplicates(r);
    return r;
}

} }
