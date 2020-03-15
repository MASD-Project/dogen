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
#include <set>
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
const std::string overrides_not_supported("Feature cannot be overridden: ");

}

namespace dogen::variability::helpers {

namespace {

/**
 * @brief Responsible for gathering information to compose non-scalar
 * type such as collections and key-value-pairs.
 *
This is the job of the
 * processor. Afterwards, we process these just like we would process
 * regular entries - but this is done on the main method below.
 */
class gatherer {
public:
    /**
     * @brief Responsible for gathering KVPs.
     *
     * Keys in KVPs actually encode _two_ sets of keys. Taking a wale
     * KVP as an example:
     *
     * @e masd.stitch.wale.kvp.helper.family=Pair
     *
     * The "masd.stitch.wale.kvp" part of the key is the feature name;
     * anything following it is the "real" key ("helper.family"). The
     * value is as per normal entries ("Pair"). So, gather is
     * responsible for removing the feature name portion of the
     * original key and to store it in a new collection of entries.
     */
    void gather_kvp(const meta_model::feature& f, const std::string& key,
        const std::string& value);

    /**
     * @brief Gathers all elements of a collection.
     */
    void gather_collection(const std::string& key, const std::string& value);

public:
    /**
     * @brief Returns the KVPs that were gathered.
     */
    const std::unordered_map<std::string,
                             std::list<std::pair<std::string, std::string>>>&
    kvps();

    /**
     * @brief Returns all of the collections that were gathered.
     */
    const std::unordered_map<std::string, std::list<std::string>>& collections();

private:
    std::unordered_map<std::string, std::set<std::string>> keys_;
    std::unordered_map<std::string,
                       std::list<std::pair<std::string, std::string>>> kvps_;
    std::unordered_map<std::string, std::list<std::string>> collections_;

};

const std::unordered_map<std::string,
                         std::list<std::pair<std::string, std::string>>>&
gatherer::kvps() {
    return kvps_;
}

const std::unordered_map<std::string, std::list<std::string>>&
gatherer::collections() {
    return collections_;
}

void gatherer::gather_kvp(const meta_model::feature& f,
    const std::string& key, const std::string& value) {
    /*
     * Compute a new key by removing the prefix.
     */
    const auto& qn(f.name().qualified());
    const auto new_key(boost::erase_first_copy(key, qn + "."));
    BOOST_LOG_SEV(lg, debug) << "New key: " << new_key;

    /*
     * Ensure we haven't seen this key before.
     */
    const auto inserted(keys_[qn].insert(new_key).second);
    if (!inserted) {
        BOOST_LOG_SEV(lg, debug) << duplicate_key << new_key;
        BOOST_THROW_EXCEPTION(building_exception(duplicate_key + new_key));
    }

    /*
     * Insert the pair.
     */
    kvps_[qn].push_back(std::make_pair(new_key, value));
}

void gatherer::gather_collection(const std::string& key,
    const std::string& value) {
    collections_[key].push_back(value);
}

}

configuration_factory::configuration_factory(
    const meta_model::feature_model& fm, const bool compatibility_mode)
    : feature_model_(fm), compatibility_mode_(compatibility_mode) {}

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
        BOOST_LOG_SEV(lg, warn) << "Ignoring missing feature: " << qn;
        return boost::optional<meta_model::feature>();
    }

    /*
     * If we are not in compatibility mode and nothing
     * matches, we need to throw.
     */
    BOOST_LOG_SEV(lg, error) << feature_not_found << qn;
    BOOST_THROW_EXCEPTION(building_exception(feature_not_found + qn));
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
    std::unordered_map<std::string, std::list<std::string>> r;

    for (const auto& entry : entries)
        r[entry.first].push_back(entry.second);

    return r;
}

void configuration_factory::populate_configuration(
    const meta_model::binding_point bp,
    const std::list<std::pair<std::string, std::string>>& tagged_values,
    const std::unordered_map<std::string, std::list<std::string>>&
    aggregated_override_entries, meta_model::configuration& cfg) const {

    cfg.source_binding_point(bp);

    gatherer g;
    value_factory factory;
    for (auto pair : tagged_values) {
        /*
         * Try to obtain a feature for this key, if it exists.
         */
        const auto& k(pair.first);
        const auto of(try_obtain_feature(k));
        if (!of)
            continue;

        /*
         * Ensure the entry is valid with regards to the binding point.
         */
        const auto& f(*of);
        validate_binding(f, bp);

        /*
         * Check to see if we have any overrides for this entry,
         * and if so, mark the override as processed.
         */
        const auto ovs(
            [&]() {
                const auto i(aggregated_override_entries.find(k));
                if (i != aggregated_override_entries.end())
                    return i->second;
                return std::list<std::string>{};
            }());
        const auto has_overrides(!ovs.empty());

        /*
         * Overrides are only supported for scalars.
         */
        using meta_model::value_type;
        const auto vt(f.value_type());
        const bool is_scalar(vt != value_type::key_value_pair &&
            vt != value_type::text_collection);
        if (!is_scalar && has_overrides) {
            BOOST_LOG_SEV(lg, error) << overrides_not_supported << k;
            BOOST_THROW_EXCEPTION(
                building_exception(overrides_not_supported + k));
        }

        /*
         * Process the tagged value.
         */
        const auto& v(pair.second);
        if (vt == value_type::key_value_pair)
            g.gather_kvp(f, k, v);
        else if (vt == value_type::text_collection)
            g.gather_collection(k, v);
        else {
            /*
             * Handle the scalar case; these we can process on the
             * first pass.
             */
            meta_model::configuration_point cp;
            cp.name().qualified(k);

            /*
             * Handle the override scenario, where the override value
             * takes over the value supplied in model. This is only
             * supported for scalars at present.
             */
            if (has_overrides)
                cp.value(factory.make(f, ovs));
            else
                cp.value(factory.make(f, std::list<std::string> { v }));

            cfg.configuration_points()[k] = cp;
        }
    }

    /*
     * Now process all of the KVPs that we gathered on the first step.
     */
    for (const auto& pair : g.kvps()) {
        BOOST_LOG_SEV(lg, debug) << "Processing kvp: " << pair;

        const auto k(pair.first);
        const auto kvps(pair.second);

        meta_model::configuration_point cp;
        cp.name().qualified(k);
        cp.value(factory.make_kvp(kvps));
        cfg.configuration_points()[k] = cp;
    }

    /*
     * Now process all of the collections.
     */
    for (const auto& pair : g.collections()) {
        const auto k(pair.first);
        const auto values(pair.second);

        BOOST_LOG_SEV(lg, debug) << "Processing collection: " << k;

        meta_model::configuration_point cp;
        cp.name().qualified(k);
        cp.value(factory.make_text_collection(values));
        cfg.configuration_points()[k] = cp;
    }
}

meta_model::configuration configuration_factory::make(
    const std::list<std::pair<std::string, std::string>>& tagged_values,
    const std::list<std::pair<std::string, std::string>>&
    tagged_values_overrides, const meta_model::binding_point bp) const {
    const auto& tv(tagged_values);
    const auto atvo(aggregate_entries(tagged_values_overrides));
    meta_model::configuration r;
    populate_configuration(bp, tv, atvo, r);
    return r;
}

boost::shared_ptr<meta_model::configuration>
configuration_factory::make_shared_ptr(
    const std::list<std::pair<std::string, std::string>>& tagged_values,
    const std::list<std::pair<std::string, std::string>>&
    tagged_values_overrides, const meta_model::binding_point bp) const {
    const auto& tv(tagged_values);
    const auto atvo(aggregate_entries(tagged_values_overrides));
    auto r(boost::make_shared<meta_model::configuration>());
    populate_configuration(bp, tv, atvo, *r);
    return r;
}

}
