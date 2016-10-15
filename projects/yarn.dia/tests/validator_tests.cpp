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
#include <boost/test/unit_test.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/asserter.hpp"
#include "dogen/yarn.dia/types/validator.hpp"
#include "dogen/yarn.dia/io/profile_io.hpp"
#include "dogen/yarn.dia/types/validation_error.hpp"
#include "dogen/utility/test/exception_checkers.hpp"

using dogen::utility::test::asserter;

namespace  {

const std::string empty;
const std::string test_module("yarn.dia");
const std::string test_suite("validator_tests");

const std::string no_uml_type("No UML type");
const std::string too_many_uml_types("Too many UML");
const std::string too_many_yarn_types("Can only have one yarn");
const std::string stereotypes_require_uml_class("Only UML classes can");

const std::string object_options_on_non_object(
    "Only yarn objects can have object options");
const std::string concepts_require_yarn_object(
    "Only yarn objects can have concepts");

}

using dogen::utility::test::contains_checker;
using dogen::yarn::dia::validation_error;

BOOST_AUTO_TEST_SUITE(validator_tests)

BOOST_AUTO_TEST_CASE(default_profile_throws) {
    SETUP_TEST_LOG_SOURCE("default_profile_throws");
    dogen::yarn::dia::validator v;
    dogen::yarn::dia::profile p;
    BOOST_LOG_SEV(lg, debug) << "input: " << p;
    BOOST_CHECK_THROW(v.validate(p), validation_error);
}

BOOST_AUTO_TEST_CASE(setting_more_than_one_uml_type_throws) {
    SETUP_TEST_LOG_SOURCE("setting_more_than_one_uml_type_throws");
    dogen::yarn::dia::validator v;
    dogen::yarn::dia::profile p1;
    p1.is_uml_large_package(true);
    p1.is_uml_class(true);
    BOOST_LOG_SEV(lg, debug) << "input p1: " << p1;

    contains_checker<validation_error> cc(too_many_uml_types);
    BOOST_CHECK_EXCEPTION(v.validate(p1), validation_error, cc);

    dogen::yarn::dia::profile p2;
    p2.is_uml_note(true);
    p2.is_uml_message(true);
    p2.is_uml_realization(true);

    BOOST_LOG_SEV(lg, debug) << "input p2: " << p2;
    BOOST_CHECK_EXCEPTION(v.validate(p2), validation_error, cc);

    dogen::yarn::dia::profile p3;
    p3.is_uml_generalization(true);
    p3.is_uml_association(true);

    BOOST_LOG_SEV(lg, debug) << "input p3: " << p3;
    BOOST_CHECK_EXCEPTION(v.validate(p3), validation_error, cc);
}

BOOST_AUTO_TEST_CASE(setting_only_one_uml_type_validates) {
    SETUP_TEST_LOG_SOURCE("setting_only_one_uml_type_validates");

    dogen::yarn::dia::validator v;
    dogen::yarn::dia::profile p;
    p.is_uml_class(true);
    BOOST_LOG_SEV(lg, debug) << "input: " << p;
    v.validate(p);
    BOOST_TEST_CHECKPOINT("p is valid.");

    p.is_uml_large_package(true);
    p.is_uml_class(false);
    BOOST_LOG_SEV(lg, debug) << "input: " << p;
    v.validate(p);
    BOOST_TEST_CHECKPOINT("p is valid.");

    p.is_uml_large_package(false);
    p.is_uml_generalization(true);
    BOOST_LOG_SEV(lg, debug) << "input: " << p;
    v.validate(p);
    BOOST_TEST_CHECKPOINT("p is valid.");

    p.is_uml_association(true);
    p.is_uml_generalization(false);
    BOOST_LOG_SEV(lg, debug) << "input: " << p;
    v.validate(p);
    BOOST_TEST_CHECKPOINT("p is valid.");

    p.is_uml_note(true);
    p.is_uml_association(false);
    BOOST_LOG_SEV(lg, debug) << "input: " << p;
    v.validate(p);
    BOOST_TEST_CHECKPOINT("p is valid.");

    p.is_uml_note(false);
    p.is_uml_message(true);
    BOOST_LOG_SEV(lg, debug) << "input: " << p;
    v.validate(p);
    BOOST_TEST_CHECKPOINT("p is valid.");

    p.is_uml_realization(true);
    p.is_uml_message(false);
    BOOST_LOG_SEV(lg, debug) << "input: " << p;
    v.validate(p);
    BOOST_TEST_CHECKPOINT("p is valid.");
}

BOOST_AUTO_TEST_CASE(setting_stereotypes_for_non_uml_classes_throws) {
    SETUP_TEST_LOG_SOURCE("setting_stereotypes_for_non_uml_classes_throws");

    dogen::yarn::dia::validator v;
    dogen::yarn::dia::profile p1;
    p1.is_uml_large_package(true);
    p1.is_enumeration(true);
    BOOST_LOG_SEV(lg, debug) << "input p1: " << p1;

    contains_checker<validation_error> cc(stereotypes_require_uml_class);
    BOOST_CHECK_EXCEPTION(v.validate(p1), validation_error, cc);

    dogen::yarn::dia::profile p2;
    p2.is_uml_generalization(true);
    p2.is_exception(true);
    p2.is_object(true);

    BOOST_LOG_SEV(lg, debug) << "input p2: " << p2;
    BOOST_CHECK_EXCEPTION(v.validate(p2), validation_error, cc);

    dogen::yarn::dia::profile p3;
    p3.is_uml_generalization(true);
    p3.unknown_stereotypes().push_back("test");

    BOOST_LOG_SEV(lg, debug) << "input p3: " << p3;
    BOOST_CHECK_EXCEPTION(v.validate(p3), validation_error, cc);
}

BOOST_AUTO_TEST_CASE(setting_more_than_one_yarn_type_throws) {
    SETUP_TEST_LOG_SOURCE("setting_more_than_one_yarn_type_throws");

    dogen::yarn::dia::validator v;
    dogen::yarn::dia::profile p1;
    p1.is_uml_class(true);
    p1.is_enumeration(true);
    p1.is_exception(true);
    BOOST_LOG_SEV(lg, debug) << "input p1: " << p1;

    contains_checker<validation_error> cc(too_many_yarn_types);
    BOOST_CHECK_EXCEPTION(v.validate(p1), validation_error, cc);

    dogen::yarn::dia::profile p2;
    p2.is_uml_class(true);
    p2.is_enumeration(true);
    p2.is_object(true);

    BOOST_LOG_SEV(lg, debug) << "input p2: " << p2;
    BOOST_CHECK_EXCEPTION(v.validate(p2), validation_error, cc);
}

BOOST_AUTO_TEST_CASE(setting_one_yarn_type_validates) {
    SETUP_TEST_LOG_SOURCE("setting_one_yarn_type_validates");

    dogen::yarn::dia::validator v;
    dogen::yarn::dia::profile p1;
    p1.is_uml_class(true);
    p1.is_enumeration(true);
    BOOST_LOG_SEV(lg, debug) << "input p1: " << p1;
    v.validate(p1);
    BOOST_TEST_CHECKPOINT("p1 is valid.");

    dogen::yarn::dia::profile p2;
    p2.is_uml_class(true);
    p2.is_object(true);
    v.validate(p2);
    BOOST_TEST_CHECKPOINT("p2 is valid.");
}

BOOST_AUTO_TEST_SUITE_END()
