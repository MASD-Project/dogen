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
#include <boost/throw_exception.hpp>
#include <boost/pointer_cast.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/unordered_map_io.hpp"
#include "dogen.variability/types/entities/key_value_pair.hpp"
#include "dogen.variability/types/entities/text_collection.hpp"
#include "dogen.variability/io/entities/configuration_point_io.hpp"
#include "dogen.variability/types/helpers/merging_exception.hpp"
#include "dogen.variability/types/helpers/configuration_point_merger.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "variability.helpers.configuration_point_merger"));

const std::string merge_inconsistent(
    "Attempting to merge different value types.");

}

namespace dogen::variability::helpers {

/**
 * @brief Attempts to merge the two configuration points as if the
 * values were text collections.
 *
 * @return true if the merge was successful, false otherwise.
 */
template<typename CollectionType>
inline bool try_merging_as_collection(entities::configuration_point& lhs,
    const entities::configuration_point& rhs) {

    using boost::dynamic_pointer_cast;
    auto lhs_value(dynamic_pointer_cast<CollectionType>(lhs.value()));
    auto rhs_value(dynamic_pointer_cast<CollectionType>(rhs.value()));

    /*
     * Simplest case: the types are not text collection. Nothing to do.
     */
    if (!lhs_value && !rhs_value) {
        BOOST_LOG_SEV(lg, trace) << "Both casts failed.";
        return false;
    }

    /*
     * One of the casts failed, but the other succeeded. Something
     * very strange is going on, best just throw.
     */
    if (!lhs_value || !rhs_value) {
        BOOST_LOG_SEV(lg, error) << merge_inconsistent;
        BOOST_THROW_EXCEPTION(merging_exception(merge_inconsistent));
    }

    /*
     * Types match so copy across the content of rhs into lhs.
     */
    BOOST_LOG_SEV(lg, trace) << "Both casts succeeded, merging.";
    for (const auto& s : rhs_value->content())
        lhs_value->content().push_back(s);

    return true;
}

std::unordered_map<std::string, entities::configuration_point>
configuration_point_merger::merge(
    const std::string& lhs_name, const std::unordered_map<std::string,
    entities::configuration_point>& lhs, const std::string& rhs_name,
    const std::unordered_map<std::string,
    entities::configuration_point>& rhs) const {
    BOOST_LOG_SEV(lg, debug) << "Merging configurations."
                             << " lhs: " << lhs_name
                             << " rhs: " << rhs_name;
    BOOST_LOG_SEV(lg, trace) << "lhs: " << lhs;
    BOOST_LOG_SEV(lg, trace) << "rhs: " << rhs;

    std::unordered_map<std::string, entities::configuration_point> r(lhs);
    for (const auto& rhs_pair : rhs) {
        /*
         * If there are no entries in lhs that match rhs, we can just
         * go ahead and insert regardless of the type of the value.
         */
        const auto i(r.find(rhs_pair.first));
        if (i == r.end()) {
            BOOST_LOG_SEV(lg, trace) << "Merged rhs as key was missing in lhs.";
            r.insert(rhs_pair);
            continue;
        }

        /*
         * There are already entries in lhs; we need to figure out
         * their type. If its a collection, merge the collections.
         */
        auto lhs(i->second);
        auto rhs(rhs_pair.second);
        if (try_merging_as_collection<entities::text_collection>(lhs, rhs)) {
            BOOST_LOG_SEV(lg, trace) << "Merged as a text collection.";
            continue;
        }

        if (try_merging_as_collection<entities::key_value_pair>(lhs, rhs)) {
            BOOST_LOG_SEV(lg, trace) << "Merged as a KVP collection.";
            continue;
        }

        /*
         * Since we could not merge it as a collection, it means it
         * must be a scalar type. If so, lhs takes precedence and we
         * should just ignore rhs altogether.
         */
        BOOST_LOG_SEV(lg, trace) << "Dropped rhs as key exists in lhs.";
    }

    BOOST_LOG_SEV(lg, debug) << "Merged configurations. ";
    BOOST_LOG_SEV(lg, trace) << "Result: " << r;
    return r;
}

}
