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
#include <unordered_set>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/io/languages_io.hpp"
#include "dogen/quilt.cpp/types/properties/name_builder.hpp"
#include "dogen/quilt.cpp/types/properties/building_error.hpp"
#include "dogen/quilt.cpp/io/properties/helper_properties_io.hpp"
#include "dogen/quilt.cpp/types/properties/helper_properties_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(
    logger_factory("quilt.cpp.properties.helper_properties_factory"));

const std::string qn_missing("Could not find qualified name for language.");
const std::string descriptor_expected(
    "Child name tree has no associated helper descriptor");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

template<typename IdentifiableAndQualified>
inline std::pair<std::string, std::string>
get_identifiable_and_qualified(const IdentifiableAndQualified& iaq) {
    const auto i(iaq.qualified().find(yarn::languages::cpp));
    if (i == iaq.qualified().end()) {
        BOOST_LOG_SEV(lg, error) << qn_missing << yarn::languages::cpp;
        BOOST_THROW_EXCEPTION(building_error(qn_missing));
    }

    return std::make_pair(iaq.identifiable(), i->second);
}

helper_properties_factory::helper_properties_factory(
    const settings::helper_settings_repository& hsrp) : helper_settings_(hsrp) {
}

boost::optional<helper_descriptor>
helper_properties_factory::make(
    const yarn::name_tree& nt, const bool is_top_level,
    std::list<helper_properties>& properties) const {
    const auto id(nt.current().id());
    BOOST_LOG_SEV(lg, debug) << "Processing type: " << id;

    /*
     * Top-level name trees should only be processed if they have a
     * type that requires a helper. If not, we can safely ignore the
     * whole attribute.
     */
    const auto& hsbn(helper_settings_.by_id());
    const auto i(hsbn.find(id));
    const auto requires_helper(i != hsbn.end());
    if (is_top_level && !requires_helper) {
        BOOST_LOG_SEV(lg, debug) << "No helper settings for type: "
                                 << id << ". Ignoring attribute.";
        return boost::optional<helper_descriptor>();
    }

    helper_descriptor r;
    properties::name_builder b;
    r.namespaces(b.namespace_list(nt.current()));

    /*
     * Child name trees may not have helper settings (as they may not
     * need helpers). We still need descriptors for them though, even
     * with blank settings. This is so we can build the direct
     * descendants.
     */
    if (i != hsbn.end()) {
        r.settings(i->second);
        BOOST_LOG_SEV(lg, debug) << "Adding settings for: " << id;
    }

    const auto p1(get_identifiable_and_qualified(nt.current()));
    r.name_identifiable(p1.first);
    r.name_qualified(p1.second);

    const auto p2(get_identifiable_and_qualified(nt));
    r.name_tree_identifiable(p2.first);
    r.name_tree_qualified(p2.second);

    helper_properties hp;
    hp.current(r);

    /*
     * Note that we are processing the children even though the parent
     * may not require a helper. This is overcaution and may even be
     * wrong. We are basically saying that in a name tree, there may
     * be nodes which do not require helpers followed by nodes that
     * do.
     */
    std::unordered_set<std::string> done;
    for (const auto c : nt.children()) {
        /*
         * We need to remember the descriptors of the direct
         * descendants (and just the direct descendants, not its
         * children). If we have a child, we must have a descriptor.
         */
        const auto dd(make(c, false /*is_top_level*/, properties));
        if (!dd) {
            BOOST_LOG_SEV(lg, error) << descriptor_expected;
            BOOST_THROW_EXCEPTION(building_error(descriptor_expected));
        }

        /*
         * We want to make sure we only process each distinct name
         * tree once, even for children. This means that a pair of two
         * strings should collapse to just one helper for string.
         */
        const auto ident(dd->name_tree_identifiable());
        if (done.find(ident) != done.end()) {
            BOOST_LOG_SEV(lg, debug) << "Name tree already processed: "
                                     << ident;
            continue;
        }
        done.insert(ident);
        hp.direct_descendants().push_back(*dd);
    }
    BOOST_LOG_SEV(lg, debug) << "Helper properties: " << hp;

    /*
     * Only add the helper property if we requre it. This is only
     * applicable to child name trees, really, since we've already
     * check for this at the top-level.
     */
    if (requires_helper)
        properties.push_back(hp);

    return r;
}

std::list<helper_properties> helper_properties_factory::
make(const std::list<yarn::attribute>& attributes) const {
    if (attributes.empty()) {
        BOOST_LOG_SEV(lg, debug) << "No properties found.";
        return std::list<helper_properties>();
    }

    BOOST_LOG_SEV(lg, debug) << "Properties found: " << attributes.size();
    std::list<helper_properties> properties;
    for (const auto a : attributes)
        make(a.parsed_type(), true/*is_top_level*/, properties);

    std::list<helper_properties> r;
    if (properties.empty()) {
        BOOST_LOG_SEV(lg, debug) << "No helper properties found.";
        return r;
    }

    std::unordered_set<std::string> done;
    for (const auto& i : properties) {
        const auto ident(i.current().name_tree_identifiable());
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
