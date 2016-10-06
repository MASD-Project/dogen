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
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/yarn.dia/types/validation_error.hpp"
#include "dogen/yarn.dia/types/validator.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.dia.validator"));

/*
 * Note: we use the terminology "options" and "stereotypes" for error
 * messages - rather than "flags" - to reflect the fact that external
 * clients don't particularly care that we chose to represent the
 * stereotypes as flags.
 */
const std::string no_uml_type("No UML type.");
const std::string too_many_uml_types("Too many UML types.");
const std::string too_many_yarn_types("Can only have one yarn type set.");
const std::string stereotypes_require_uml_class(
    "Only UML classes can have stereotypes.");

const std::string object_options_on_non_object(
    "Only yarn objects can have object options");
const std::string concepts_require_yarn_object(
    "Only yarn objects can have concepts");

}

namespace dogen {
namespace yarn {
namespace dia {

bool validator::is_object(const profile& p) const {
    return
        p.is_value_object() || p.is_exception() || p.is_service();
}

unsigned int validator::count_yarn_object_flags(const profile& p) const {
    unsigned int r(0);
    if (p.is_non_generatable()) ++r;
    if (p.is_visitable()) ++r;
    if (p.is_immutable()) ++r;
    if (p.is_fluent()) ++r;
    return r;
}

unsigned int validator::count_yarn_types(const profile& p) const {
    unsigned int r(0);

    if (p.is_enumeration()) ++r;
    if (p.is_exception()) ++r;
    if (p.is_value_object()) ++r;
    if (p.is_service()) ++r;
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

void validator::validate_yarn(const profile& p) const {
    const auto types(count_yarn_types(p));
    const auto object_flags(count_yarn_object_flags(p));
    const bool has_yarn_flags(
        types != 0 || object_flags != 0 || !p.unknown_stereotypes().empty());

    if (!has_yarn_flags)
        return; // nothing to validate.

    /*
     * only UML classes are allowed to have YARN flags.
     */
    if (!p.is_uml_class()) {
        BOOST_LOG_SEV(lg, error) << stereotypes_require_uml_class;
        BOOST_THROW_EXCEPTION(validation_error(stereotypes_require_uml_class));
    }

    /*
     *  we can have at most one YARN type. Zero is fine as
     * someone above us will provide defaulting.
     */
    if (types > 1) {
        BOOST_LOG_SEV(lg, error) << too_many_yarn_types;
        BOOST_THROW_EXCEPTION(validation_error(too_many_yarn_types));
    }

    if (is_object(p))
        return; // nothing else to validate for YARN objects.

    /*
     * non YARN objects are not allowed to have object flags.
     */
    if (object_flags > 0) {
        BOOST_LOG_SEV(lg, error) << object_options_on_non_object;
        BOOST_THROW_EXCEPTION(validation_error(object_options_on_non_object));
    }

    /*
     *  non YARN objects are not allowed to have concepts.
     */
    if (!p.unknown_stereotypes().empty()) {
        BOOST_LOG_SEV(lg, error) << concepts_require_yarn_object << ": "
                                 << p.unknown_stereotypes();
        BOOST_THROW_EXCEPTION(validation_error(concepts_require_yarn_object));
    }
}

void validator::validate_uml(const profile& p) const {
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

void validator::validate(const profile& p) const {
    validate_uml(p);
    validate_yarn(p);
}

void validator::validate(const std::list<profiled_object>& pos) const {
    for (const auto& po : pos)
        validate(po.profile());
}

} } }
