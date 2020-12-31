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
#include "dogen.utility/types/test/logging.hpp"
#include "dogen.utility/types/test/asserter.hpp"
#include "dogen.codec.dia/types/validator.hpp"
#include "dogen.codec/io/entities/object_io.hpp"
#include "dogen.codec.dia/types/validation_error.hpp"
#include "dogen.utility/types/test/exception_checkers.hpp"

using dogen::utility::test::asserter;

namespace  {

const std::string empty;
const std::string test_module("masd.codec.dia.tests");
const std::string test_suite("validator_tests");

const std::string no_uml_type("No UML type");
const std::string invalid_stereotypes("Stereotypes can only be used with yarn");

const std::string uml_large_package("UML - LargePackage");
const std::string uml_class("UML - Class");
const std::string uml_generalization("UML - Generalization");
const std::string uml_association("UML - Association");
const std::string uml_note("UML - Note");
const std::string uml_message("UML - Message");
const std::string uml_realization("UML - Realizes");

}

using dogen::utility::test::contains_checker;
using dogen::codec::dia::validation_error;

BOOST_AUTO_TEST_SUITE(validator_tests)

BOOST_AUTO_TEST_CASE(default_processed_object_throws) {
    SETUP_TEST_LOG_SOURCE("default_processed_object_throws");
    dogen::codec::dia::validator v;
    dogen::codec::entities::object po;
    BOOST_LOG_SEV(lg, debug) << "input: " << po;
    BOOST_CHECK_THROW(v.validate(po), validation_error);
}

BOOST_AUTO_TEST_CASE(setting_only_one_uml_type_validates) {
    SETUP_TEST_LOG_SOURCE("setting_only_one_uml_type_validates");

    dogen::codec::dia::validator v;
    dogen::codec::entities::object po;
    po.object_type(uml_class);
    BOOST_LOG_SEV(lg, debug) << "input: " << po;
    v.validate(po);
    BOOST_TEST_CHECKPOINT("po is valid.");

    po.object_type(uml_large_package);
    BOOST_LOG_SEV(lg, debug) << "input: " << po;
    v.validate(po);
    BOOST_TEST_CHECKPOINT("po is valid.");

    po.object_type(uml_generalization);
    BOOST_LOG_SEV(lg, debug) << "input: " << po;
    v.validate(po);
    BOOST_TEST_CHECKPOINT("po is valid.");

    po.object_type(uml_association);
    BOOST_LOG_SEV(lg, debug) << "input: " << po;
    v.validate(po);
    BOOST_TEST_CHECKPOINT("po is valid.");

    po.object_type(uml_note);
    BOOST_LOG_SEV(lg, debug) << "input: " << po;
    v.validate(po);
    BOOST_TEST_CHECKPOINT("po is valid.");

    po.object_type(uml_message);
    BOOST_LOG_SEV(lg, debug) << "input: " << po;
    v.validate(po);
    BOOST_TEST_CHECKPOINT("po is valid.");

    po.object_type(uml_realization);
    BOOST_LOG_SEV(lg, debug) << "input: " << po;
    v.validate(po);
    BOOST_TEST_CHECKPOINT("po is valid.");
}

BOOST_AUTO_TEST_SUITE_END()
