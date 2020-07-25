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
#include <boost/algorithm/string.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.logical/types/helpers/validation_error.hpp"
#include "dogen.logical/types/helpers/mappings_validator.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("logical.helpers.mappings_validator"));

const std::string default_mapping_set_name("default.mapping_set");

const std::string invalid_agnostic_id("Agnostic ID is not valid: ");
const std::string empty_mapping_set("Mapping set has no entries: ");
const std::string missing_default_mapping_set(
    "Could not find the default mapping set: " + default_mapping_set_name);
const std::string invalid_technical_space("Cannot map agnostic to itself.");
const std::string missing_default_value(
    "Default value must be supplied when translating.");
const std::string unexpected_default_value(
    "Erase mapping action does not require a default value.");

}

namespace dogen::logical::helpers {

void mappings_validator::
validate(const identification::entities::technical_space ts,
    const mapping_value& mv) const {
    /*
     * Cannot map agnostic technical space to itself.
     */
    if (ts == identification::entities::technical_space::agnostic) {
        BOOST_LOG_SEV(lg, error) << invalid_technical_space;
        BOOST_THROW_EXCEPTION(validation_error(invalid_agnostic_id));
    }

    /*
     * Translations require a defaut value.
     */
    const auto& dn(mv.default_name());
    const auto ma(mv.mapping_action());
    if (ma == mapping_actions::translate && !dn) {
        BOOST_LOG_SEV(lg, error) << missing_default_value;
        BOOST_THROW_EXCEPTION(validation_error(missing_default_value));
    }

    /*
     * Erasing does not require a defaut value.
     */
    if (ma == mapping_actions::erase && dn) {
        BOOST_LOG_SEV(lg, error) << unexpected_default_value;
        BOOST_THROW_EXCEPTION(validation_error(unexpected_default_value));
    }
}

void mappings_validator::validate(const mapping& m) const {
    BOOST_LOG_SEV(lg, trace) << "Started validating mapping.";

    const auto id(m.agnostic_id());
    BOOST_LOG_SEV(lg, trace) << "Validating agnostic ID: " << id;

    /*
     * Agnostic ID must not be empty.
     */
    if (id.empty()) {
        BOOST_LOG_SEV(lg, error) << invalid_agnostic_id << id;
        BOOST_THROW_EXCEPTION(validation_error(invalid_agnostic_id + id));
    }

    for (const auto& pair : m.by_technical_space())
        validate(pair.first, pair.second);

    BOOST_LOG_SEV(lg, trace) << "Finished validating mapping.";
}

void mappings_validator::validate(const std::unordered_map<std::string,
    std::list<mapping>>& mappings_by_set_name) const {
    BOOST_LOG_SEV(lg, debug) << "Started mappings validation.";
    BOOST_LOG_SEV(lg, debug) << "Mapping sets found: "
                             << mappings_by_set_name.size();


    bool has_default(false);
    for (const auto& pair : mappings_by_set_name) {
        const auto& n(pair.first);
        BOOST_LOG_SEV(lg, trace) << "Started validating mapping set: " << n;

        if (n == default_mapping_set_name)
            has_default = true;

        const auto& mappings(pair.second);

        /*
         * Mapping set must have at least one mapping.
         */
        if (mappings.empty()) {
            BOOST_LOG_SEV(lg, error) << empty_mapping_set << n;
            BOOST_THROW_EXCEPTION(validation_error(empty_mapping_set + n));
        }

        for (const auto& mapping : mappings)
            validate(mapping);

        BOOST_LOG_SEV(lg, trace) << "Finished validating mapping set.";
    }

    /*
     * The default mapping set must be present.
     */
    if (!has_default) {
        BOOST_LOG_SEV(lg, error) << missing_default_mapping_set;
        BOOST_THROW_EXCEPTION(validation_error(missing_default_mapping_set));
    }

    BOOST_LOG_SEV(lg, debug) << "Finished mappings validation.";
}

}
