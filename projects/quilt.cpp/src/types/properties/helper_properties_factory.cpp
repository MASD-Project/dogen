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

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

helper_properties_factory::helper_properties_factory(
    const settings::helper_settings_repository& hsrp) : helper_settings_(hsrp) {
}

boost::optional<helper_descriptor> helper_properties_factory::make(
    const yarn::name_tree& nt, std::list<helper_properties>& properties) const {
    const auto id(nt.current().id());
    BOOST_LOG_SEV(lg, debug) << "Processing type: " << id;

    /*
     * Does the top-level type require any helpers? If not, we don't
     * need to do any work.
     */
    const auto& hsbn(helper_settings_.by_id());
    const auto i(hsbn.find(id));
    if (i == hsbn.end()) {
        BOOST_LOG_SEV(lg, debug) << "No settings for type.";
        return boost::optional<helper_descriptor>();
    }

    /*
     * If the top-level type has any children, we must remember them
     * as associated helpers. This basically means that the helper
     * needs to delegate to other helpers.
     */
    helper_properties hp;
    for (const auto c : nt.children()) {
        const auto child_descriptors(make(c, properties));
        if (!child_descriptors)
            continue;

        /*
         * At present we are possibly adding duplicates in the type
         * variables.
         */
        hp.associated_helpers().push_back(*child_descriptors);
    }

    const auto& hs(i->second);
    hp.settings(hs);

    helper_descriptor r;
    properties::name_builder b;
    r.namespaces(b.namespace_list(nt.current()));
    r.name_tree(nt);

    hp.descriptor(r);
    BOOST_LOG_SEV(lg, debug) << "Helper properties: " << hp;

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
        make(a.parsed_type(), properties);

    std::list<helper_properties> r;
    if (properties.empty()) {
        BOOST_LOG_SEV(lg, debug) << "No helper properties found.";
        return r;
    }

    std::unordered_set<std::string> done;
    for (const auto& i : properties) {
        const auto in(i.descriptor().name_tree().identifiable());
        if (done.find(in) != done.end()) {
            BOOST_LOG_SEV(lg, debug) << "Name tree already processed: " << in;
            continue;
        }

        r.push_back(i);
        done.insert(in);
    }

    return r;
}

} } } }
