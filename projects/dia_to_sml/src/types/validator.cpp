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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/dia_to_sml/types/validation_error.hpp"
#include "dogen/dia_to_sml/types/validator.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dia_to_sml.validator"));

/*
 * Note: we use the terminology "options" and "stereotypes" for error
 * messages - rather than "flags" - to reflect the fact that external
 * clients don't particularly care that we chose to represent the
 * stereotypes as flags.
 */
const std::string no_uml_type("No UML type.");
const std::string too_many_uml_types("Too many UML types.");
const std::string too_many_sml_types("Can only have one SML type set.");
const std::string stereotypes_require_uml_class(
    "Only UML classes can have stereotypes.");

const std::string entity_options_on_a_non_entity(
    "Only SML entities can have entity options.");
const std::string versioning_options_on_non_versionable(
    "Versioning options used on a SML type which does not support it.");
const std::string object_options_on_non_object(
    "Only SML objects can have object options");
const std::string concepts_require_sml_object(
    "Only SML objects can have concepts");

}

namespace dogen {
namespace dia_to_sml {

bool validator::is_entity(const profile& p) const {
    return p.is_entity() || p.is_keyed_entity() ;
}

bool validator::is_versionable(const profile& p) const {
    return
        p.is_entity() || p.is_keyed_entity() ||
        p.is_value_object() || p.is_exception();
}

bool validator::is_object(const profile& p) const {
    return
        p.is_entity() || p.is_keyed_entity() || p.is_value_object() ||
        p.is_exception() || p.is_service() || p.is_factory() ||
        p.is_repository();
}

unsigned int validator::count_sml_versioning_flags(const profile& p) const {
    unsigned int r(0);
    if (p.is_versioned()) ++r;
    return r;
}

unsigned int validator::count_sml_entity_flags(const profile& p) const {
    unsigned int r(0);
    if (p.is_aggregate_root()) ++r;
    return r;
}

unsigned int validator::count_sml_object_flags(const profile& p) const {
    unsigned int r(0);
    if (p.is_non_generatable()) ++r;
    if (p.is_visitable()) ++r;
    if (p.is_immutable()) ++r;
    if (p.is_fluent()) ++r;
    return r;
}

unsigned int validator::count_sml_types(const profile& p) const {
    unsigned int r(0);

    if (p.is_enumeration()) ++r;
    if (p.is_exception()) ++r;
    if (p.is_entity()) ++r;
    if (p.is_keyed_entity()) ++r;
    if (p.is_value_object()) ++r;
    if (p.is_service()) ++r;
    if (p.is_factory()) ++r;
    if (p.is_repository()) ++r;
    if (p.is_concept()) ++r;

    return r;
}

unsigned int validator::count_uml_types(const profile& p) const {
    unsigned int r(0);

    if (p.is_uml_large_package()) ++r;
    if (p.is_uml_class()) ++r;
    if (p.is_uml_generalization()) ++r;
    if (p.is_uml_association()) ++r;
    if (p.is_uml_note()) ++r;
    if (p.is_uml_message()) ++r;
    if (p.is_uml_realization()) ++r;

    return r;
}

void validator::validate_sml(const profile& p) const {
    const auto types(count_sml_types(p));
    const auto object_flags(count_sml_object_flags(p));
    const auto entity_flags(count_sml_entity_flags(p));
    const auto versioning_flags(count_sml_versioning_flags(p));
    const bool has_sml_flags(
        types != 0 || object_flags != 0 || entity_flags != 0 ||
        versioning_flags  != 0 || !p.unknown_stereotypes().empty());

    if (!has_sml_flags)
        return; // nothing to validate.

    /*
     * rule 1: only UML classes are allowed to have SML flags.
     */
    if (!p.is_uml_class()) {
        BOOST_LOG_SEV(lg, error) << stereotypes_require_uml_class;
        BOOST_THROW_EXCEPTION(validation_error(stereotypes_require_uml_class));
    }

    /*
     * rule 2: we can have at most one SML type. Zero is fine as
     * someone above us will provide defaulting.
     */
    if (types > 1) {
        BOOST_LOG_SEV(lg, error) << too_many_sml_types;
        BOOST_THROW_EXCEPTION(validation_error(too_many_sml_types));
    }

    /*
     * rule 3: only SML entities are allowed to have entity flags.
     */
    if (entity_flags > 0 && !is_entity(p)) {
        BOOST_LOG_SEV(lg, error) << entity_options_on_a_non_entity;
        BOOST_THROW_EXCEPTION(validation_error(entity_options_on_a_non_entity));
    }

    /**
     * @brief rule 4: only versionable types are allowed to have
     * versioning flags.
     */
    if (versioning_flags > 0 && !is_versionable(p)) {
        BOOST_LOG_SEV(lg, error) << versioning_options_on_non_versionable;
        BOOST_THROW_EXCEPTION(validation_error(
                versioning_options_on_non_versionable));
    }

    if (is_object(p))
        return; // nothing else to validate for SML objects.

    /*
     * rule 5: non SML objects are not allowed to have object flags.
     */
    if (object_flags > 0) {
        BOOST_LOG_SEV(lg, error) << object_options_on_non_object;
        BOOST_THROW_EXCEPTION(validation_error(object_options_on_non_object));
    }

    /*
     * rule 6: non SML objects are not allowed to have concepts.
     */
    if (!p.unknown_stereotypes().empty()) {
        BOOST_LOG_SEV(lg, error) << concepts_require_sml_object;
        BOOST_THROW_EXCEPTION(validation_error(concepts_require_sml_object));
    }
}

void validator::validate_uml(const profile& p) {
    const auto types(count_uml_types(p));

    if (types == 0) {
        BOOST_LOG_SEV(lg, error) << no_uml_type;
        BOOST_THROW_EXCEPTION(validation_error(no_uml_type));
    }

    if (types > 1) {
        BOOST_LOG_SEV(lg, error) << too_many_uml_types;
        BOOST_THROW_EXCEPTION(validation_error(too_many_uml_types));
    }
}

void validator::validate(const profile& p) {
    validate_uml(p);
    validate_sml(p);
}

} }
