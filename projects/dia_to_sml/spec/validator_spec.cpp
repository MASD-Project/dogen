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
#include <sstream>
#include <boost/test/unit_test.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/asserter.hpp"
#include "dogen/dia_to_sml/types/validator.hpp"
#include "dogen/dia_to_sml/io/object_profile_io.hpp"
#include "dogen/dia_to_sml/types/validation_error.hpp"
#include "dogen/utility/test/exception_checkers.hpp"

using dogen::utility::test::asserter;

namespace  {

const std::string empty;
const std::string test_module("dia_to_sml");
const std::string test_suite("validator_spec");

const std::string too_many_type_flags_set("Too many type flags");
const std::string no_type_flags_set("A type must be");
const std::string stereotypes_require_uml_class("Only UML classes can");
const std::string type_related_stereotype(
    "Can only have one type related stereotype");

}

using dogen::utility::test::contains_checker;
using dogen::dia_to_sml::validation_error;

BOOST_AUTO_TEST_SUITE(validator)

BOOST_AUTO_TEST_CASE(default_profile_throws) {
    SETUP_TEST_LOG_SOURCE("default_profile_throws");
    dogen::dia_to_sml::validator v;
    dogen::dia_to_sml::object_profile op;
    BOOST_LOG_SEV(lg, debug) << "input: " << op;

    contains_checker<validation_error> cc(no_type_flags_set);
    BOOST_CHECK_EXCEPTION(v.validate(op), validation_error, cc);
}

BOOST_AUTO_TEST_CASE(setting_more_than_one_type_throws) {
    SETUP_TEST_LOG_SOURCE("setting_more_than_one_type_throws");
    dogen::dia_to_sml::validator v;
    dogen::dia_to_sml::object_profile op1;
    op1.is_uml_large_package(true);
    op1.is_uml_class(true);
    BOOST_LOG_SEV(lg, debug) << "input op1: " << op1;

    contains_checker<validation_error> cc(too_many_type_flags_set);
    BOOST_CHECK_EXCEPTION(v.validate(op1), validation_error, cc);

    dogen::dia_to_sml::object_profile op2;
    op2.is_uml_note(true);
    op2.is_uml_message(true);
    op2.is_uml_realization(true);

    BOOST_LOG_SEV(lg, debug) << "input op2: " << op2;
    BOOST_CHECK_EXCEPTION(v.validate(op2), validation_error, cc);

    dogen::dia_to_sml::object_profile op3;
    op3.is_uml_generalization(true);
    op3.is_uml_association(true);

    BOOST_LOG_SEV(lg, debug) << "input op3: " << op3;
    BOOST_CHECK_EXCEPTION(v.validate(op3), validation_error, cc);
}

BOOST_AUTO_TEST_CASE(setting_stereotypes_for_non_uml_classes_throws) {
    SETUP_TEST_LOG_SOURCE("setting_stereotypes_for_non_uml_classes_throws");
    dogen::dia_to_sml::validator v;
    dogen::dia_to_sml::object_profile op1;
    op1.is_uml_large_package(true);
    op1.is_enumeration(true);
    BOOST_LOG_SEV(lg, debug) << "input op1: " << op1;

    contains_checker<validation_error> cc(stereotypes_require_uml_class);
    BOOST_CHECK_EXCEPTION(v.validate(op1), validation_error, cc);

    dogen::dia_to_sml::object_profile op2;
    op2.is_uml_note(true);
    op2.is_keyed(true);
    op2.is_versioned(true);

    BOOST_LOG_SEV(lg, debug) << "input op2: " << op2;
    BOOST_CHECK_EXCEPTION(v.validate(op2), validation_error, cc);

    dogen::dia_to_sml::object_profile op3;
    op3.is_uml_generalization(true);
    op3.is_exception(true);
    op3.is_service(true);

    BOOST_LOG_SEV(lg, debug) << "input op3: " << op3;
    BOOST_CHECK_EXCEPTION(v.validate(op3), validation_error, cc);
}

BOOST_AUTO_TEST_CASE(setting_more_than_one_type_related_stereotype_throws) {
    SETUP_TEST_LOG_SOURCE("setting_more_than_one_type_related_stereotype_throws");

    dogen::dia_to_sml::validator v;
    dogen::dia_to_sml::object_profile op1;
    op1.is_uml_class(true);
    op1.is_enumeration(true);
    op1.is_exception(true);
    BOOST_LOG_SEV(lg, debug) << "input op1: " << op1;

    contains_checker<validation_error> cc(type_related_stereotype);
    BOOST_CHECK_EXCEPTION(v.validate(op1), validation_error, cc);

    dogen::dia_to_sml::object_profile op2;
    op2.is_uml_class(true);
    op2.is_entity(true);
    op2.is_service(true);

    BOOST_LOG_SEV(lg, debug) << "input op2: " << op2;
    BOOST_CHECK_EXCEPTION(v.validate(op2), validation_error, cc);

    dogen::dia_to_sml::object_profile op3;
    op3.is_uml_class(true);
    op3.is_entity(true);
    op3.is_service(true);
    op3.is_value(true);

    BOOST_LOG_SEV(lg, debug) << "input op3: " << op3;
    BOOST_CHECK_EXCEPTION(v.validate(op3), validation_error, cc);
}

BOOST_AUTO_TEST_CASE(setting_only_one_type_flag_does_not_throw) {
    SETUP_TEST_LOG_SOURCE("setting_only_one_type_flag_does_not_throw");
    dogen::dia_to_sml::validator v;
    dogen::dia_to_sml::object_profile op;
    op.is_uml_class(true);
    BOOST_LOG_SEV(lg, debug) << "input: " << op;
    v.validate(op);

    op.is_uml_large_package(true);
    op.is_uml_class(false);
    BOOST_LOG_SEV(lg, debug) << "input: " << op;
    v.validate(op);

    op.is_uml_large_package(false);
    op.is_uml_generalization(true);
    BOOST_LOG_SEV(lg, debug) << "input: " << op;
    v.validate(op);

    op.is_uml_association(true);
    op.is_uml_generalization(false);
    BOOST_LOG_SEV(lg, debug) << "input: " << op;
    v.validate(op);

    op.is_uml_note(true);
    op.is_uml_association(false);
    BOOST_LOG_SEV(lg, debug) << "input: " << op;
    v.validate(op);

    op.is_uml_note(false);
    op.is_uml_message(true);
    BOOST_LOG_SEV(lg, debug) << "input: " << op;
    v.validate(op);

    op.is_uml_realization(true);
    op.is_uml_message(false);
    BOOST_LOG_SEV(lg, debug) << "input: " << op;
    v.validate(op);
}

BOOST_AUTO_TEST_SUITE_END()
