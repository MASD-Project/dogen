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
#include <sstream>
#include <boost/lexical_cast.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/io/meta_types_io.hpp"
#include "dogen/sml/io/pod_types_io.hpp"
#include "dogen/cpp/types/building_error.hpp"
#include "dogen/cpp/types/aspect_types.hpp"
#include "dogen/cpp/types/content_descriptor_factory.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("cpp.content_descriptor_factory"));

const std::string invalid_enabled_facets("Invalid enabled facets request: ");
const std::string unsupported_meta_type("Meta type not supported: ");
const std::string must_supply_valid_meta_type(
    "QName has invalid meta type");
const std::string must_supply_valid_category_and_pod_type(
    "QName of type pod requires a valid category type and pod type");
const std::string pod_type_supplied_for_non_pod(
    "Pod type parameter was supplied but meta type is not pod");

}

namespace dogen {
namespace cpp {

content_descriptor_factory::content_descriptor_factory(
    const std::set<config::cpp_facet_types>& enabled_facets) :
    enabled_facets_(enabled_facets) { }

std::set<config::cpp_facet_types> content_descriptor_factory::
enabled_facets(const sml::meta_types mt, const sml::pod_types pt) const {
    using sml::pod_types;
    using sml::meta_types;
    using config::cpp_facet_types;

    switch(mt) {
    case meta_types::pod:
        if (pt == pod_types::value || pt == pod_types::entity)
            return enabled_facets_;
        else if (pt == pod_types::service)
            return std::set<cpp_facet_types> { cpp_facet_types::types };
        break;
    case meta_types::enumeration:
    case meta_types::primitive:
        return enabled_facets_;
        break;
    case meta_types::exception:
        return std::set<cpp_facet_types> { cpp_facet_types::types };
        break;
    default:
        break;
    }

    BOOST_LOG_SEV(lg, error) << invalid_enabled_facets
                             << boost::lexical_cast<std::string>(mt)
                             << boost::lexical_cast<std::string>(pt);

    BOOST_THROW_EXCEPTION(building_error(invalid_enabled_facets +
            boost::lexical_cast<std::string>(mt) + ", " +
            boost::lexical_cast<std::string>(pt)));
}

bool content_descriptor_factory::has_implementation(
    const config::cpp_facet_types ft, const sml::meta_types mt) const {

    using sml::meta_types;
    using config::cpp_facet_types;
    switch(mt) {
    case meta_types::pod:
        return
            ft == cpp_facet_types::types ||
            ft == cpp_facet_types::hash ||
            ft == cpp_facet_types::io ||
            ft == cpp_facet_types::test_data ||
            ft == cpp_facet_types::serialization;
        break;
    case meta_types::exception:
        return false; break;
    case meta_types::enumeration:
        return
            ft == cpp_facet_types::io ||
            ft == cpp_facet_types::test_data;
        break;
    default: break;
    }

    BOOST_LOG_SEV(lg, error) << unsupported_meta_type << mt;
    BOOST_THROW_EXCEPTION(building_error(unsupported_meta_type +
            boost::lexical_cast<std::string>(mt)));
}

bool content_descriptor_factory::has_forward_decls(const config::cpp_facet_types ft,
    const dogen::sml::meta_types mt) const {
    using dogen::sml::meta_types;
    using config::cpp_facet_types;

    switch(mt) {
    case meta_types::pod:
        return
            ft == cpp_facet_types::types ||
            ft == cpp_facet_types::serialization;
        break;
    case meta_types::enumeration:
        return ft == cpp_facet_types::types;
        break;
    case meta_types::exception:
        return ft == cpp_facet_types::types;
        break;
    default: break;
    }

    BOOST_LOG_SEV(lg, error) << unsupported_meta_type << mt;
    BOOST_THROW_EXCEPTION(building_error(unsupported_meta_type +
            boost::lexical_cast<std::string>(mt)));
}

std::list<content_descriptor>
content_descriptor_factory::create(const sml::qname& qn,
    const sml::category_types ct, const sml::pod_types pt) const {
    using dogen::sml::meta_types;
    using sml::category_types;
    using sml::pod_types;

    if (qn.meta_type() == meta_types::invalid) {
        BOOST_LOG_SEV(lg, error) << must_supply_valid_meta_type;
        BOOST_THROW_EXCEPTION(building_error(must_supply_valid_meta_type));
    }

    if (qn.meta_type() != meta_types::pod && pt != pod_types::invalid) {
        BOOST_LOG_SEV(lg, error) << pod_type_supplied_for_non_pod;
        BOOST_THROW_EXCEPTION(building_error(pod_type_supplied_for_non_pod));
    }

    if (qn.meta_type() == meta_types::pod &&
        (ct == category_types::invalid || pt == pod_types::invalid)) {
        BOOST_LOG_SEV(lg, error) << must_supply_valid_category_and_pod_type;
        BOOST_THROW_EXCEPTION(building_error(
                must_supply_valid_category_and_pod_type));
    }

    std::list<content_descriptor> r;
    const auto main(aspect_types::main);
    const auto header(file_types::header);
    if (qn.meta_type() == sml::meta_types::package) {
        const auto ft(config::cpp_facet_types::types);
        r.push_back(content_descriptor(header, ft, main, ct, qn));
        return r;
    }

    const auto mt(qn.meta_type());
    for (const auto ft : enabled_facets(mt, pt)) {
        r.push_back(content_descriptor(header, ft, main, ct, qn));

        const auto implementation(file_types::implementation);
        if (has_implementation(ft, mt))
            r.push_back(content_descriptor(implementation, ft, main, ct, qn));

        const auto forward_decls(aspect_types::forward_decls);
        if (has_forward_decls(ft, mt))
            r.push_back(content_descriptor(header, ft, forward_decls, ct, qn));
    }
    return r;
}

std::list<content_descriptor>
content_descriptor_factory::create(const sml::model& m) const {
    std::list<content_descriptor> r;

    sml::qname qn;
    qn.type_name(m.name());
    qn.external_package_path(m.external_package_path());
    qn.meta_type(sml::meta_types::package);

    using config::cpp_facet_types;
    const auto ft(cpp_facet_types::types);
    const auto at(aspect_types::namespace_doc);
    const auto header(file_types::header);
    const auto ct(sml::category_types::invalid);
    r.push_back(content_descriptor(header, ft, at, ct, qn));

    return r;
}

std::list<content_descriptor>
content_descriptor_factory::create_includer(const sml::qname& qn) const {
    std::list<content_descriptor> r;

    for (const auto ft : enabled_facets_) {
        const auto at(aspect_types::includers);
        const auto header(file_types::header);
        const auto ct(sml::category_types::invalid);
        r.push_back(content_descriptor(header, ft, at, ct, qn));
    }
    return r;
}

} }
