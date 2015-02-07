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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/cpp/io/formattables/content_types_io.hpp"
#include "dogen/cpp/io/formattables/content_descriptor_io.hpp"
#include "dogen/cpp/types/formattables/aspect_types.hpp"
#include "dogen/cpp/types/formattables/building_error.hpp"
#include "dogen/cpp/types/formattables/content_descriptor_factory.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("cpp.content_descriptor_factory"));

const std::string invalid_enabled_facets("Invalid enabled facets request: ");
const std::string unsupported_content_type("Content type not supported: ");

}

namespace dogen {
namespace cpp {
namespace formattables {

content_descriptor_factory::content_descriptor_factory(
    const std::set<config::cpp_facet_types>& enabled_facets) :
    enabled_facets_(enabled_facets) { }

std::set<config::cpp_facet_types> content_descriptor_factory::
enabled_facets(const content_types ct) const {
    using config::cpp_facet_types;

    switch(ct) {
    case content_types::user_defined_service:
    case content_types::visitor:
    case content_types::key_extractor:
    case content_types::repository:
    case content_types::factory:
    case content_types::exception:
        return std::set<cpp_facet_types> { cpp_facet_types::types };

    case content_types::unversioned_key:
    case content_types::versioned_key:
    case content_types::value_object:
    case content_types::entity:
    case content_types::keyed_entity:
    case content_types::enumeration:
    case content_types::primitive:
        return enabled_facets_;
        break;

    default:
        break;
    }

    BOOST_LOG_SEV(lg, error) << invalid_enabled_facets
                             << boost::lexical_cast<std::string>(ct);

    BOOST_THROW_EXCEPTION(building_error(invalid_enabled_facets +
            boost::lexical_cast<std::string>(ct)));
}

bool content_descriptor_factory::has_implementation(
    const config::cpp_facet_types ft, const content_types ct) const {

    using config::cpp_facet_types;
    switch(ct) {
    case content_types::versioned_key:
    case content_types::unversioned_key:
    case content_types::value_object:
    case content_types::entity:
    case content_types::keyed_entity:
        return
            ft == cpp_facet_types::types ||
            ft == cpp_facet_types::hash ||
            ft == cpp_facet_types::io ||
            ft == cpp_facet_types::test_data ||
            ft == cpp_facet_types::serialization;
        break;

    case content_types::user_defined_service:
    case content_types::visitor:
    case content_types::key_extractor:
    case content_types::repository:
    case content_types::factory:
        return ft == cpp_facet_types::types;
        break;

    case content_types::exception:
        return false; break;
    case content_types::enumeration:
        return
            ft == cpp_facet_types::io ||
            ft == cpp_facet_types::test_data;
        break;
    default: break;
    }

    BOOST_LOG_SEV(lg, error) << unsupported_content_type << ct;
    BOOST_THROW_EXCEPTION(building_error(unsupported_content_type +
            boost::lexical_cast<std::string>(ct)));
}

bool content_descriptor_factory::has_forward_decls(
    const config::cpp_facet_types ft, const content_types ct) const {
    using config::cpp_facet_types;

    switch(ct) {
    case content_types::unversioned_key:
    case content_types::versioned_key:
    case content_types::value_object:
    case content_types::entity:
    case content_types::keyed_entity:
        return
            ft == cpp_facet_types::types ||
            ft == cpp_facet_types::serialization;
        break;

    case content_types::user_defined_service:
    case content_types::visitor:
    case content_types::key_extractor:
    case content_types::repository:
    case content_types::factory:
    case content_types::enumeration:
    case content_types::exception:
        return ft == cpp_facet_types::types;
        break;
    case content_types::primitive:
        return false;
        break;
    default: break;
    }

    BOOST_LOG_SEV(lg, error) << unsupported_content_type << ct;
    BOOST_THROW_EXCEPTION(building_error(unsupported_content_type +
            boost::lexical_cast<std::string>(ct)));
}

std::list<content_descriptor> content_descriptor_factory::
create(const sml::qname& qn, const content_types ct) const {
    BOOST_LOG_SEV(lg, debug) << "Creating descriptors: "
                             << sml::string_converter::convert(qn)
                             << " content type: " << ct;

    std::list<content_descriptor> r;
    const auto header(file_types::header);
    const auto main(aspect_types::main);
    if (ct == content_types::namespace_doc) {
        const auto ft(config::cpp_facet_types::types);

        // FIXME: hack to handle model name.
        if (qn.simple_name() == qn.model_name()) {
            auto new_qn(qn);
            new_qn.simple_name(qn.model_name());
            r.push_back(content_descriptor(header, ft, main, new_qn, ct));
        } else {
            // content descriptors for modules must take into account the
            // module name itself as they are used to name the files.
            // if we didn't do this we'd place the file outside the
            // module folder.
            auto new_qn(qn);
            new_qn.module_path().push_back(qn.simple_name());
            r.push_back(content_descriptor(header, ft, main, new_qn, ct));
        }
        return r;
    }

    for (const auto ft : enabled_facets(ct)) {
        r.push_back(content_descriptor(header, ft, main, qn, ct));

        const auto implementation(file_types::implementation);
        if (has_implementation(ft, ct))
            r.push_back(content_descriptor(implementation, ft, main, qn, ct));

        const auto forward_decls(aspect_types::forward_decls);
        if (has_forward_decls(ft, ct))
            r.push_back(content_descriptor(header, ft, forward_decls, qn, ct));
    }

    BOOST_LOG_SEV(lg, debug) << "Descriptors: " << r;
    return r;
}

std::list<content_descriptor>
content_descriptor_factory::create(const sml::model& m) const {
    std::list<content_descriptor> r;

    using config::cpp_facet_types;
    const auto ft(cpp_facet_types::types);
    const auto at(aspect_types::main);
    const auto header(file_types::header);
    const auto ct(content_types::namespace_doc);
    r.push_back(content_descriptor(header, ft, at, m.name(), ct));

    return r;
}

std::list<content_descriptor>
content_descriptor_factory::create_includer(const sml::qname& qn) const {
    std::list<content_descriptor> r;

    for (const auto ft : enabled_facets_) {
        const auto at(aspect_types::main);
        const auto header(file_types::header);
        const auto ct(content_types::includer);
        r.push_back(content_descriptor(header, ft, at, qn, ct));
    }
    return r;
}

std::list<content_descriptor>
content_descriptor_factory::create_registrar(const sml::qname& qn) const {
    std::list<content_descriptor> r;

    const auto ft(config::cpp_facet_types::serialization);
    if (enabled_facets_.find(ft) == enabled_facets_.end())
        return r;

    const auto at(aspect_types::main);
    const auto header(file_types::header);
    const auto ct(content_types::registrar);
    r.push_back(content_descriptor(header, ft, at, qn, ct));

    const auto implementation(file_types::implementation);
    r.push_back(content_descriptor(implementation, ft, at, qn, ct));

    return r;
}

std::list<content_descriptor>
content_descriptor_factory::create_visitor(const sml::qname& qn) const {
    std::list<content_descriptor> r;

    const auto ft(config::cpp_facet_types::types);
    const auto at(aspect_types::main);
    const auto header(file_types::header);
    const auto ct(content_types::visitor);
    r.push_back(content_descriptor(header, ft, at, qn, ct));

    return r;
}

} } }
