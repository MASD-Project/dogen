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
#include <sstream>
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/erase.hpp>
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.utility/types/io/unordered_map_io.hpp"
#include "masd.dogen.variability/io/meta_model/configuration_io.hpp"
#include "masd.dogen.variability/io/meta_model/binding_type_io.hpp"
#include "masd.dogen.variability/types/helpers/value_factory.hpp"
#include "masd.dogen.variability/types/helpers/building_exception.hpp"
#include "masd.dogen.variability/types/helpers/configuration_factory.hpp"

namespace {

using namespace masd::dogen::utility::log;
static logger lg(logger_factory("variability.helpers.configuration_factory"));

const std::string expected_binding_type(" Expected binding type: ");
const std::string actual_binding_type(" Actual binding type: ");
const std::string duplicate_feature("Feature already inserted: ");
const std::string duplicate_key("Key already inserted: ");
const std::string too_many_values("More than one value supplied against key: ");
const std::string feature_not_found("Type not found: ");
const std::string invalid_binding_for_point("Incorrect binding type: ");

}

namespace masd::dogen::variability::helpers {

configuration_factory::configuration_factory(
    const archetypes::location_repository& alrp,
    const meta_model::feature_model& fm, const bool compatibility_mode)
    : archetype_location_repository_(alrp), feature_model_(fm),
      compatibility_mode_(compatibility_mode) {}

boost::optional<meta_model::feature>
configuration_factory::try_obtain_feature(const std::string& qn) const {
    /*
     * First try a full match; if it exists, return the feature.
     */
    const auto& bn(feature_model_.by_name());
    const auto i(bn.find(qn));
    if (i != bn.end())
        return i->second;

    /*
     * Now try the partial matches. Note that we can be sure there
     * will only be one match due to the logic of partial matching, as
     * two features cannot have the same name.
     */
    for (const auto& pair : feature_model_.partially_matchable()) {
        const auto& fqn(pair.first);
        const auto& t(pair.second);
        if (boost::starts_with(qn, fqn))
            return t;
    }

    return boost::optional<meta_model::feature>();
}

void configuration_factory::validate_binding(const meta_model::feature& f,
    const meta_model::binding_type bt) const {
    using meta_model::binding_type;

    const auto fbt(f.binding_type());
    if (fbt != binding_type::any &&
        fbt != binding_type::not_applicable && fbt != bt) {

        std::stringstream s;
        s << invalid_binding_for_point << f.name().qualified()
          << expected_binding_type << f.binding_type()
          << actual_binding_type << bt;
        BOOST_LOG_SEV(lg, error) << s.str();
        BOOST_THROW_EXCEPTION(building_exception(s.str()));
    }
}

meta_model::configuration
configuration_factory::create_configuration(const meta_model::binding_type bt,
    const std::unordered_map<std::string, std::list<std::string>>&
    aggregated_entries) const {

    meta_model::configuration r;
    r.binding_type(bt);

    value_factory factory;
    std::unordered_map<std::string, boost::shared_ptr<meta_model::value>>
        entries;
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>>
        all_kvps;
    for (auto kvp : aggregated_entries) {
        const auto& k(kvp.first);
        const auto of(try_obtain_feature(k));

        if (!of) {
            /*
             * No feature matches the qualified name (key) requested.
             */
            if (compatibility_mode_) {
                /*
                 * If we're in compatibility mode, skip any features for which
                 * we do not have a definition. This is for forward
                 * compatibility purposes - i.e. diagrams using features that
                 * we do not yet know about.
                 */
                BOOST_LOG_SEV(lg, warn) << "Ignoring unsupported feature: "
                                        << k;
                continue;
            }

            /*
             * If we are not in compatibility mode and nothing
             * matches, we need to throw.
             */
            BOOST_LOG_SEV(lg, error) << feature_not_found << k;
            BOOST_THROW_EXCEPTION(building_exception(feature_not_found + k));
        }

        /*
         * Ensure the entry is valid with regards to the binding type.
         */
        const auto& f(*of);
        validate_binding(f, bt);

        const auto& v(kvp.second);
        if (f.value_type() == meta_model::value_type::key_value_pair) {
            BOOST_LOG_SEV(lg, debug) << "Adding kvp for key: " << k;
            if (v.size() != 1) {
                BOOST_LOG_SEV(lg, debug) << too_many_values << k;
                BOOST_THROW_EXCEPTION(building_exception(too_many_values + k));
            }

            const auto& qn(f.name().qualified());
            const auto new_key(boost::erase_first_copy(k, qn + "."));
            BOOST_LOG_SEV(lg, debug) << "Actual key: " << new_key;

            const auto pair(std::make_pair(new_key, v.front()));
            const auto inserted(all_kvps[qn].insert(pair).second);
            if (!inserted) {
                BOOST_LOG_SEV(lg, debug) << duplicate_key << new_key;
                BOOST_THROW_EXCEPTION(
                    building_exception(duplicate_key + new_key));
            }
        } else {
            meta_model::configuration_point cp;
            cp.name().qualified(k);
            cp.value(factory.make(f, v));
            r.configuration_points()[k] = cp;
        }
    }

    for (const auto& pair : all_kvps) {
        BOOST_LOG_SEV(lg, debug) << "Processing kvp:: " << pair;

        const auto k(pair.first);
        const auto kvps(pair.second);

        meta_model::configuration_point cp;
        cp.name().qualified(k);
        cp.value(factory.make_kvp(kvps));
        r.configuration_points()[k] = cp;
    }

    return r;
}

std::unordered_map<std::string, std::list<std::string>>
configuration_factory::aggregate_entries(
    const std::list<std::pair<std::string, std::string>>& entries) const {
    std::unordered_map<std::string, std::list<std::string> > r;

    for (const auto& entry : entries)
        r[entry.first].push_front(entry.second);

    return r;
}

meta_model::configuration configuration_factory::make(
    const std::list<std::pair<std::string, std::string>>& entries,
    const meta_model::binding_type bt) const {
    auto aggregated_entries(aggregate_entries(entries));
    const auto r(create_configuration(bt, aggregated_entries));
    return r;
}

}
