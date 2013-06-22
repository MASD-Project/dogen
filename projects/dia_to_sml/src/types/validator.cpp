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

const std::string too_many_type_flags_set("Too many type flags have been set.");
const std::string no_type_flags_set("A type must be set.");
const std::string stereotypes_require_uml_class(
    "Only UML classes can have stereotypes.");
const std::string too_many_type_related_stereotypes(
    "Can only have one type related stereotype set.");
const std::string type_does_not_support_further_stereotypes(
    "Type does not support further stereotypes.");

}

namespace dogen {
namespace dia_to_sml {

unsigned int validator::
count_stereotypes_non_types(const profile& p) const {
    unsigned int r(0);

    if (p.is_non_generatable()) ++r;
    if (p.is_versioned()) ++r;
    if (p.is_keyed()) ++r;

    return r;
}

unsigned int validator::count_stereotypes_types(const profile& p) const {
    unsigned int r(0);

    if (p.is_enumeration()) ++r;
    if (p.is_exception()) ++r;
    if (p.is_entity()) ++r;
    if (p.is_value()) ++r;
    if (p.is_service()) ++r;

    return r;
}

void validator::validate_stereotypes(const profile& p) const {
    const auto types(count_stereotypes_types(p));
    const auto non_types(count_stereotypes_non_types(p));

    if (!p.is_uml_class() && (types != 0 || non_types != 0)) {
        BOOST_LOG_SEV(lg, error) << stereotypes_require_uml_class;
        BOOST_THROW_EXCEPTION(validation_error(stereotypes_require_uml_class));
    }

    if (types > 1) {
        BOOST_LOG_SEV(lg, error) << too_many_type_related_stereotypes;
        BOOST_THROW_EXCEPTION(
            validation_error(too_many_type_related_stereotypes));
    }

    if ((p.is_enumeration() || p.is_exception() || p.is_service()) &&
        non_types > 0) {
        BOOST_LOG_SEV(lg, error) << type_does_not_support_further_stereotypes;

        BOOST_THROW_EXCEPTION(
            validation_error(type_does_not_support_further_stereotypes));
    }
}

unsigned int validator::count_types(const profile& p) const {
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

void validator::validate_type(const profile& p) {
    const auto types(count_types(p));

    if (types == 0) {
        BOOST_LOG_SEV(lg, error) << no_type_flags_set;
        BOOST_THROW_EXCEPTION(validation_error(no_type_flags_set));
    }

    if (types > 1) {
        BOOST_LOG_SEV(lg, error) << too_many_type_flags_set;
        BOOST_THROW_EXCEPTION(validation_error(too_many_type_flags_set));
    }
}

void validator::validate(const profile& p) {
    validate_type(p);
    validate_stereotypes(p);
}

} }
