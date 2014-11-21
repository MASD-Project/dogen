/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2013 Kitanda <info@kitanda.co.uk>
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
#include <boost/pointer_cast.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/sml_to_cpp/types/extraction_error.hpp"
#include "dogen/sml_to_cpp/types/extractor.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("sml_to_cpp.extractor"));

const std::string bool_type("bool");
const std::string double_type("double");
const std::string float_type("float");

}

namespace dogen {
namespace sml_to_cpp {

extractor::extractor() : boost_(), std_() { }

relationships extractor::extract_dependency_graph(const sml::object& ao) const {
    BOOST_LOG_SEV(lg, debug) << "Extracting dependency graph for "
                             << sml::string_converter::convert(ao.name());

    relationships r;

    using dogen::sml::relationship_types;
    auto i(ao.relationships().find(relationship_types::parents));
    if (i == ao.relationships().end() || i->second.empty())
        BOOST_LOG_SEV(lg, debug) << "Object has no parents.";
    else {
        for (const auto& parent : i->second)
            r.names().insert(parent);
    }

    i = ao.relationships().find(relationship_types::visited_by);
    if (i == ao.relationships().end() || i->second.empty())
        BOOST_LOG_SEV(lg, debug) << "Object has no vistors.";
    else {
        // FIXME: ignore visitation relationship for non-root
        // objects.
        if (ao.is_parent() && !ao.is_child())
            for (const auto& visitors : i->second)
                r.names().insert(visitors);
    }

    i = ao.relationships().find(relationship_types::visits);
    if (i == ao.relationships().end() || i->second.empty())
        BOOST_LOG_SEV(lg, debug) << "Object does not visit.";
    else {
        for (const auto& visitees : i->second)
            r.names().insert(visitees);
    }

    r.is_parent(ao.is_parent());
    r.is_child(ao.is_child());

    i = ao.relationships().find(relationship_types::leaves);
    if (i != ao.relationships().end() && !i->second.empty())
        r.leaves().insert(i->second.begin(), i->second.end());

    i = ao.relationships().find(relationship_types::hash_container_keys);
    if (i == ao.relationships().end() || i->second.empty())
        BOOST_LOG_SEV(lg, debug) << "Object has no hash container keys.";
    else {
        for (const auto& vk : i->second)
            r.keys().insert(vk);
    }

    i = ao.relationships().find(relationship_types::regular_associations);
    if (i == ao.relationships().end() || i->second.empty())
        BOOST_LOG_SEV(lg, debug) << "Object has no regular associations.";
    else {
        for (const auto& qn : i->second) {
            r.names().insert(qn);

            const auto sn(qn.simple_name());
            if (sn == bool_type || sn == double_type || sn == float_type)
                r.requires_stream_manipulators(true);
            else if (sn == std_.type(std_types::string))
                r.has_std_string(true);
            else if (sn == boost_.type(boost_types::variant))
                r.has_variant(true);
            else if (sn == std_.type(std_types::pair))
                r.has_std_pair(true);
        }
    }

    i = ao.relationships().find(relationship_types::weak_associations);
    if (i == ao.relationships().end() || i->second.empty())
        BOOST_LOG_SEV(lg, debug) << "Object has no pointer associations.";
    else {
        for (const auto& qn : i->second) {
            r.forward_decls().insert(qn);

            const auto sn(qn.simple_name());
            if (sn == bool_type || sn == double_type || sn == float_type)
                r.requires_stream_manipulators(true);
            else if (sn == std_.type(std_types::string))
                r.has_std_string(true);
            else if (sn == boost_.type(boost_types::variant))
                r.has_variant(true);
            else if (sn == std_.type(std_types::pair))
                r.has_std_pair(true);
        }
    }

    for (const auto& n : r.names()) {
        if (r.forward_decls().find(n) != r.forward_decls().end())
            r.forward_decls().erase(n);
    }

    BOOST_LOG_SEV(lg, debug) << "Extracted dependency graph.";
    return r;
}

} }
