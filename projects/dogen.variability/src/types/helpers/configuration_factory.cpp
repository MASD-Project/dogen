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
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <unordered_set>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.utility/types/io/unordered_map_io.hpp"
#include "dogen.variability/io/meta_model/configuration_io.hpp"
#include "dogen.variability/io/meta_model/binding_point_io.hpp"
#include "dogen.variability/types/helpers/value_factory.hpp"
#include "dogen.variability/types/helpers/building_exception.hpp"
#include "dogen.variability/types/helpers/configuration_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("variability.helpers.configuration_factory"));

const std::string expected_binding_point(" Expected binding point: ");
const std::string actual_binding_point(" Actual binding point: ");
const std::string duplicate_feature("Feature already inserted: ");
const std::string duplicate_key("Key already inserted: ");
const std::string too_many_values("More than one value supplied against key: ");
const std::string feature_not_found("Feature not found: ");
const std::string invalid_binding_for_point("Incorrect binding type: ");

}

namespace dogen::variability::helpers {

namespace {

/**
 * @brief Responsible for converting aggregated entries into the right
 * layout for variability KVPs.
 *
 * KVP processing is done as a two step process. If we take a walke
 * KVP as an example:
 *
 * masd.stitch.wale.kvp.helper.family=Pair
 *
 * The "masd.stitch.wale.kvp" part of the key is the feature name;
 * anything following it is the real key (e.g. "helper.family"). The
 * value is as per normal entries (e.g. "Pair"). So, the first step is
 * to remove the feature name portion of the original key and to store
 * it in a new collection of entries. This is the job of the
 * processor. Afterwards, we process these just like we would process
 * regular entries - but this is done on the main method below.
 */
class kvp_gatherer {
public:
    void gather(const meta_model::feature& f, const std::string& key,
        const std::list<std::string>& value,
        const std::list<std::string>& override_value);

public:
    const std::unordered_map<std::string,
                             std::list<std::pair<std::string, std::string>>>&
    result();

private:
    std::unordered_map<std::string, std::set<std::string>> keys_;
    std::unordered_map<std::string,
                       std::list<std::pair<std::string, std::string>>> result_;
};

const std::unordered_map<std::string,
                         std::list<std::pair<std::string, std::string>>>&
kvp_gatherer::result() {
    return result_;
}

void kvp_gatherer::gather(const meta_model::feature& f,
    const std::string& key, const std::list<std::string>& value,
    const std::list<std::string>& override_value) {

    BOOST_LOG_SEV(lg, debug) << "Adding kvp for key: " << key;
    if (value.size() != 1) {
        BOOST_LOG_SEV(lg, debug) << too_many_values << key;
        BOOST_THROW_EXCEPTION(building_exception(too_many_values + key));
    }

    const auto& qn(f.name().qualified());
    const auto new_key(boost::erase_first_copy(key, qn + "."));
    BOOST_LOG_SEV(lg, debug) << "Actual key: " << new_key;

    /*
     * Handle the override scenario, where the override value takes
     * over the value supplied in model.
     */
    const auto has_overrides(!override_value.empty());
    const auto v(has_overrides ? override_value.front() : value.front());
    const auto pair(std::make_pair(new_key, v));
    const auto inserted(keys_[qn].insert(new_key).second);
    if (!inserted) {
        BOOST_LOG_SEV(lg, debug) << duplicate_key << new_key;
        BOOST_THROW_EXCEPTION(building_exception(duplicate_key + new_key));
    }
    result_[qn].push_front(pair);
}

}

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
    const meta_model::binding_point bp) const {

    const auto fbt(f.binding_point());
    if (fbt != meta_model::binding_point::any && fbt != bp) {
        std::stringstream s;
        s << invalid_binding_for_point << f.name().qualified()
          << expected_binding_point << f.binding_point()
          << actual_binding_point << bp;

        BOOST_LOG_SEV(lg, error) << s.str();
        BOOST_THROW_EXCEPTION(building_exception(s.str()));
    }
}

std::unordered_map<std::string, std::list<std::string>>
configuration_factory::aggregate_entries(
    const std::list<std::pair<std::string, std::string>>& entries) const {
    std::unordered_map<std::string, std::list<std::string> > r;

    for (const auto& entry : entries)
        r[entry.first].push_back(entry.second);

    return r;
}

void configuration_factory::populate_configuration(
    const meta_model::binding_point bp,
    const std::unordered_map<std::string, std::list<std::string>>&
    aggregated_entries,
    const std::unordered_map<std::string, std::list<std::string>>&
    aggregated_override_entries, meta_model::configuration& cfg) const {

    cfg.source_binding_point(bp);

    kvp_gatherer kvpg;
    value_factory factory;
    std::unordered_map<std::string,
                       boost::shared_ptr<meta_model::value>> entries;
    std::unordered_set<std::string> applied_overrides;
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
                BOOST_LOG_SEV(lg, warn) << "Ignoring missing feature: " << k;
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
        validate_binding(f, bp);

        /*
         * Check to see if we have any overrides for this entry, and
         * if so, mark the override as processed.
         */
        const auto ovs(
            [&]() {
                const auto i(aggregated_override_entries.find(k));
                if (i != aggregated_override_entries.end()) {
                    applied_overrides.insert(k);
                    return i->second;
                }
                return std::list<std::string>();
            }());
        const bool has_overrides(!ovs.empty());

        const auto& v(kvp.second);
        using meta_model::value_type;
        const auto vt(f.value_type());
        if (vt == value_type::key_value_pair) {
            /*
             * Gather KVP details.
             */
            kvpg.gather(f, k, v, ovs);
        } else {
            meta_model::configuration_point cp;
            cp.name().qualified(k);

            /*
             * Handle the override scenario, where the override value
             * takes over the value supplied in model. Note that the
             * factory handles both the collection and the scalar use
             * case (v is then expected to contain a single value).
             */
            cp.value(factory.make(f, has_overrides ? ovs : v));
            cfg.configuration_points()[k] = cp;
        }
    }

    /*
     * Now process all of the KVPs that we gathered on the first step.
     */
    for (const auto& pair : kvpg.result()) {
        BOOST_LOG_SEV(lg, debug) << "Processing kvp:: " << pair;

        const auto k(pair.first);
        const auto kvps(pair.second);

        meta_model::configuration_point cp;
        cp.name().qualified(k);
        cp.value(factory.make_kvp(kvps));
        cfg.configuration_points()[k] = cp;
    }
}

meta_model::configuration configuration_factory::make(
    const std::list<std::pair<std::string, std::string>>& entries,
    const std::list<std::pair<std::string, std::string>>& override_entries,
    const meta_model::binding_point bp) const {
    const auto ae(aggregate_entries(entries));
    const auto aoe(aggregate_entries(override_entries));
    meta_model::configuration r;
    populate_configuration(bp, ae, aoe, r);
    return r;
}

boost::shared_ptr<meta_model::configuration>
configuration_factory::make_shared_ptr(
    const std::list<std::pair<std::string, std::string>>& entries,
    const std::list<std::pair<std::string, std::string>>& override_entries,
    const meta_model::binding_point bp) const {
    const auto ae(aggregate_entries(entries));
    const auto aoe(aggregate_entries(override_entries));
    auto r(boost::make_shared<meta_model::configuration>());
    populate_configuration(bp, ae, aoe, *r);
    return r;
}

}
