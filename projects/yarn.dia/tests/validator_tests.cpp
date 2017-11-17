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
#include "dogen/yarn.dia/io/processed_object_io.hpp"
#include "dogen/yarn.dia/types/validation_error.hpp"
#include "dogen/utility/test/exception_checkers.hpp"

using dogen::utility::test::asserter;

namespace  {

const std::string empty;
const std::string test_module("yarn.dia");
const std::string test_suite("validator_tests");

const std::string no_uml_type("No UML type");
const std::string invalid_stereotypes("Stereotypes can only be used with yarn");

}

using dogen::utility::test::contains_checker;
using dogen::yarn::dia::validation_error;
using dogen::yarn::dia::dia_object_types;
using dogen::yarn::dia::yarn_element_types;

BOOST_AUTO_TEST_SUITE(validator_tests)

BOOST_AUTO_TEST_CASE(default_processed_object_throws) {
    SETUP_TEST_LOG_SOURCE("default_processed_object_throws");
    dogen::yarn::dia::validator v;
    dogen::yarn::dia::processed_object po;
    BOOST_LOG_SEV(lg, debug) << "input: " << po;
    BOOST_CHECK_THROW(v.validate(po), validation_error);
}

BOOST_AUTO_TEST_CASE(setting_only_one_uml_type_validates) {
    SETUP_TEST_LOG_SOURCE("setting_only_one_uml_type_validates");

    dogen::yarn::dia::validator v;
    dogen::yarn::dia::processed_object po;
    po.dia_object_type(dia_object_types::uml_class);
    BOOST_LOG_SEV(lg, debug) << "input: " << po;
    v.validate(po);
    BOOST_TEST_CHECKPOINT("po is valid.");

    po.dia_object_type(dia_object_types::uml_large_package);
    BOOST_LOG_SEV(lg, debug) << "input: " << po;
    v.validate(po);
    BOOST_TEST_CHECKPOINT("po is valid.");

    po.dia_object_type(dia_object_types::uml_generalization);
    BOOST_LOG_SEV(lg, debug) << "input: " << po;
    v.validate(po);
    BOOST_TEST_CHECKPOINT("po is valid.");

    po.dia_object_type(dia_object_types::uml_association);
    BOOST_LOG_SEV(lg, debug) << "input: " << po;
    v.validate(po);
    BOOST_TEST_CHECKPOINT("po is valid.");

    po.dia_object_type(dia_object_types::uml_note);
    BOOST_LOG_SEV(lg, debug) << "input: " << po;
    v.validate(po);
    BOOST_TEST_CHECKPOINT("po is valid.");

    po.dia_object_type(dia_object_types::uml_message);
    BOOST_LOG_SEV(lg, debug) << "input: " << po;
    v.validate(po);
    BOOST_TEST_CHECKPOINT("po is valid.");

    po.dia_object_type(dia_object_types::uml_realization);
    BOOST_LOG_SEV(lg, debug) << "input: " << po;
    v.validate(po);
    BOOST_TEST_CHECKPOINT("po is valid.");
}

BOOST_AUTO_TEST_CASE(setting_stereotypes_for_non_uml_classes_throws) {
    SETUP_TEST_LOG_SOURCE("setting_stereotypes_for_non_uml_classes_throws");

    dogen::yarn::dia::validator v;
    dogen::yarn::dia::processed_object po;
    po.dia_object_type(dia_object_types::uml_large_package);
    po.unknown_stereotypes().push_back("test");

    contains_checker<validation_error> cc(invalid_stereotypes);
    BOOST_LOG_SEV(lg, debug) << "input po: " << po;
    BOOST_CHECK_EXCEPTION(v.validate(po), validation_error, cc);
}

BOOST_AUTO_TEST_CASE(setting_one_yarn_type_validates) {
    SETUP_TEST_LOG_SOURCE("setting_one_yarn_type_validates");

    dogen::yarn::dia::validator v;
    dogen::yarn::dia::processed_object po0;
    po0.dia_object_type(dia_object_types::uml_class);
    po0.yarn_element_type(yarn_element_types::object);
    BOOST_LOG_SEV(lg, debug) << "input po0: " << po0;

    v.validate(po0);
    BOOST_TEST_CHECKPOINT("po0 is valid.");

    dogen::yarn::dia::processed_object po1;
    po1.dia_object_type(dia_object_types::uml_class);
    po1.yarn_element_type(yarn_element_types::enumeration);
    BOOST_LOG_SEV(lg, debug) << "input po1: " << po1;

    v.validate(po1);
    BOOST_TEST_CHECKPOINT("po1 is valid.");

    dogen::yarn::dia::processed_object po2;
    po2.dia_object_type(dia_object_types::uml_class);
    po2.yarn_element_type(yarn_element_types::exception);
    BOOST_LOG_SEV(lg, debug) << "input po2: " << po2;

    v.validate(po2);
    BOOST_TEST_CHECKPOINT("po2 is valid.");
}

BOOST_AUTO_TEST_SUITE_END()
