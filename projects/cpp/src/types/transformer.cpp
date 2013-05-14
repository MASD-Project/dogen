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
#include <boost/lexical_cast.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/io/pod_types_io.hpp"
#include "dogen/sml/io/meta_types_io.hpp"
#include "dogen/cpp/types/transformation_error.hpp"
#include "dogen/cpp/types/transformer.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("cpp.transformer"));

const std::string invalid_enabled_facets("Invalid enabled facets request: ");

}

namespace dogen {
namespace cpp {

transformer::transformer(const config::cpp_settings& s, const sml::model& m)
    : settings_(s), model_(m) { }

std::set<config::cpp_facet_types> transformer::
facet_types(const sml::meta_types mt, const sml::pod_types pt) const {
    using sml::pod_types;
    using sml::meta_types;
    using config::cpp_facet_types;

    switch(mt) {
    case meta_types::pod:
        if (pt == pod_types::value || pt == pod_types::entity)
            return settings_.enabled_facets();
        else if (pt == sml::pod_types::service)
            return std::set<cpp_facet_types> { cpp_facet_types::types };
        break;
    case meta_types::enumeration:
    case meta_types::primitive:
        return settings_.enabled_facets();
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

    BOOST_THROW_EXCEPTION(transformation_error(invalid_enabled_facets +
            boost::lexical_cast<std::string>(mt) + ", " +
            boost::lexical_cast<std::string>(pt)));

}

std::list<std::string>
transformer::transform_namespaces(const dogen::sml::qname& qn) const {
    std::list<std::string> r(qn.external_package_path());

    if (!qn.model_name().empty())
        r.push_back(qn.model_name());

    const std::list<std::string> pp(qn.package_path());
    r.insert(r.end(), pp.begin(), pp.end());

    if (qn.meta_type() == sml::meta_types::package)
        r.push_back(qn.type_name());

    return r;
}

enumeration_info transformer::
transform_enumeration(const sml::enumeration& e) const {
    enumeration_info r;
    r.name(e.name().type_name());

    const auto ns(transform_namespaces(e.name()));
    r.namespaces(ns);
    r.documentation(e.documentation());
    for (const auto& en : e.enumerators()) {
        enumerator_info ei;
        ei.name(en.name());
        ei.value(en.value());
        ei.documentation(en.documentation());
        r.enumerators().push_back(ei);
    }
    return r;
}

std::list<file_info> transformer::transform(const sml::enumeration&) const {
    std::list<file_info> r;
    return r;
}

} }
