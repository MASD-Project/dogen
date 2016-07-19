/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#include <utility>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/io/languages_io.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/traits.hpp"
#include "dogen/quilt.cpp/types/properties/name_builder.hpp"
#include "dogen/quilt.cpp/types/properties/building_error.hpp"
#include "dogen/quilt.cpp/io/properties/helper_properties_io.hpp"
#include "dogen/quilt.cpp/io/settings/helper_settings_io.hpp"
#include "dogen/quilt.cpp/types/properties/helper_properties_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(
    logger_factory("quilt.cpp.properties.helper_properties_factory"));

const std::string qn_missing("Could not find qualified name for language.");
const std::string empty_identifiable(
    "Identifiable was not generated correctly and is empty.");
const std::string descriptor_expected(
    "Child name tree has no associated helper descriptor");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

template<typename Qualified>
inline std::string get_qualified(const Qualified& iaq) {
    const auto i(iaq.qualified().find(yarn::languages::cpp));
    if (i == iaq.qualified().end()) {
        BOOST_LOG_SEV(lg, error) << qn_missing << yarn::languages::cpp;
        BOOST_THROW_EXCEPTION(building_error(qn_missing));
    }
    return i->second;
}

helper_properties_factory::helper_properties_factory(
    const std::unordered_set<std::string>& primitive_ids,
    const std::unordered_map<std::string, std::unordered_set<std::string>>&
    facets_for_family,
    const settings::helper_settings_repository& hsrp,
    const settings::streaming_settings_repository& ss)
    : primitive_ids_(primitive_ids), facets_for_family_(facets_for_family),
      helper_settings_(hsrp), streaming_settings_(ss) { }

bool helper_properties_factory::
requires_hashing_helper(const std::string& family) const {
    /*
     * If there is no entry on the container for this family, we
     * don't need a helper for hashing.
     */
    const auto i(facets_for_family_.find(family));
    if (i == facets_for_family_.end())
        return false;

    /*
     * If the hash facet is not present in the helpers for this family
     * then the family does not require hashing support.
     */
    const auto j(i->second.find(formatters::hash::traits::facet_name()));
    return j != i->second.end();
}

boost::optional<settings::helper_settings> helper_properties_factory::
helper_settings_for_id(const std::string& id) const {
    const auto i(helper_settings_.by_id().find(id));
    if (i == helper_settings_.by_id().end()) {
        BOOST_LOG_SEV(lg, debug) << "No helper settings for type: " << id;
        return boost::optional<settings::helper_settings>();
    }

    BOOST_LOG_SEV(lg, debug) << "Found helper settings for type: " << id
                             << ". Settings: " << i->second;
    return i->second;
}

bool helper_properties_factory::is_primitive(const std::string& id) const {
    const auto i(primitive_ids_.find(id));
    return i != primitive_ids_.end();
}

boost::optional<settings::streaming_settings> helper_properties_factory::
streaming_settings_for_id(const std::string& id) const {
    const auto i(streaming_settings_.by_id().find(id));
    if (i == streaming_settings_.by_id().end())
        return boost::optional<settings::streaming_settings>();

    return i->second;
}

boost::optional<helper_descriptor>
helper_properties_factory::make(const bool in_inheritance_relationship,
    const yarn::name_tree& nt, const bool is_top_level,
    std::unordered_set<std::string>& done,
    std::list<helper_properties>& properties) const {
    const auto id(nt.current().id());
    BOOST_LOG_SEV(lg, debug) << "Processing type: " << id;

    /*
     * Top-level name trees should only be processed if they have a
     * type that requires a helper. If not, we can safely ignore the
     * whole attribute.
     */
    const auto hs(helper_settings_for_id(id));
    const bool requires_helper(hs);

    if (is_top_level && !requires_helper) {
        BOOST_LOG_SEV(lg, debug) << "Helper not required for type: "
                                 << id << ". Ignoring attribute.";
        return boost::optional<helper_descriptor>();
    }

    helper_descriptor r;
    properties::name_builder b;
    r.namespaces(b.namespace_list(nt.current()));
    r.is_primitive(is_primitive(id));

    /*
     * Note: we log conditionally for both settings to make
     * troubleshooting slightly easier.
     */
    const auto ss(streaming_settings_for_id(id));
    if (ss) {
        r.streaming_settings(ss);
        BOOST_LOG_SEV(lg, debug) << "Adding streaming settings for: " << id;
    }

    /*
     * Child name trees may not have helper settings (as they may not
     * need helpers). We still need descriptors for them though, even
     * with blank settings. This is so we can build the direct
     * descendants.
     */
    if (requires_helper) {
        r.helper_settings(hs);
        BOOST_LOG_SEV(lg, debug) << "Adding helper settings for: " << id;

        r.requires_hashing_helper(requires_hashing_helper(hs->family()));
    }

    r.name_identifiable(nt.current().identifiable());
    r.name_qualified(get_qualified(nt.current()));
    r.name_tree_identifiable(nt.identifiable());
    r.name_tree_qualified(get_qualified(nt));

    helper_properties hp;
    hp.current(r);

    const auto iir(in_inheritance_relationship);
    hp.in_inheritance_relationship(iir);

    /*
     * Note that we are processing the children even though the parent
     * may not require a helper. This is over-caution and may even be
     * wrong. We are basically saying that in a name tree, there may
     * be nodes which do not require helpers followed by nodes that
     * do.
     */
    for (const auto c : nt.children()) {
        /*
         * We need to remember the descriptors of the direct
         * descendants (and just the direct descendants, not its
         * children). If we have a child, we must have a descriptor.
         */
        const auto dd(make(iir, c, false /*is_top_level*/, done, properties));
        if (!dd) {
            BOOST_LOG_SEV(lg, error) << descriptor_expected;
            BOOST_THROW_EXCEPTION(building_error(descriptor_expected));
        }

        const auto ident(dd->name_tree_identifiable());
        if (ident.empty()) {
            BOOST_LOG_SEV(lg, error) << empty_identifiable;
            BOOST_THROW_EXCEPTION(building_error(empty_identifiable));
        }
        hp.direct_descendants().push_back(*dd);
    }
    BOOST_LOG_SEV(lg, debug) << "Helper properties: " << hp;

    /*
     * Only add the helper property if we requre it. This is only
     * applicable to child name trees as we are recursively called,
     * since we've already check for this at entry.
     */
    if (requires_helper) {
        /*
         * Ensure we have not yet created a helper for this name
         * tree. Note that we must still do the processing above in
         * order to ensure the direct descendants are computed, even
         * though the helper itself may not be required. As an
         * example, take the case of a map of string to string. We
         * need the helper for the map to have two direct descendants
         * (one per string), but we do not want to generate two helper
         * methods for the strings.
         */
        const auto ident(nt.identifiable());
        if (ident.empty()) {
            BOOST_LOG_SEV(lg, error) << empty_identifiable;
            BOOST_THROW_EXCEPTION(building_error(empty_identifiable));
        }

        if (done.find(ident) == done.end())
            properties.push_back(hp);
        else {
            BOOST_LOG_SEV(lg, debug) << "Name tree already processed: "
                                     << ident;
        }
    }
    return r;
}

std::list<helper_properties> helper_properties_factory::
make(const bool in_inheritance_relationship,
    const std::list<yarn::attribute>& attributes) const {
    if (attributes.empty()) {
        BOOST_LOG_SEV(lg, debug) << "No properties found.";
        return std::list<helper_properties>();
    }

    BOOST_LOG_SEV(lg, debug) << "Properties found: " << attributes.size();
    std::list<helper_properties> properties;
    std::unordered_set<std::string> done;
    for (const auto a : attributes) {
        const auto iir(in_inheritance_relationship);
        make(iir, a.parsed_type(), true/*is_top_level*/, done, properties);
    }

    std::list<helper_properties> r;
    if (properties.empty()) {
        BOOST_LOG_SEV(lg, debug) << "No helper properties found.";
        return r;
    }

    for (const auto& i : properties) {
        const auto ident(i.current().name_tree_identifiable());
        if (ident.empty()) {
            BOOST_LOG_SEV(lg, error) << empty_identifiable;
            BOOST_THROW_EXCEPTION(building_error(empty_identifiable));
        }

        if (done.find(ident) != done.end()) {
            BOOST_LOG_SEV(lg, debug) << "Name tree already processed: "
                                     << ident;
            continue;
        }
        done.insert(ident);
        r.push_back(i);
    }

    return r;
}

} } } }
