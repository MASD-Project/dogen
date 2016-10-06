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
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/dia/io/object_io.hpp"
#include "dogen/yarn.dia/types/processed_object.hpp"
#include "dogen/yarn.dia/types/object_processor.hpp"
#include "dogen/yarn.dia/types/processing_error.hpp"
#include "dogen/yarn.dia/io/repository_io.hpp"
#include "dogen/yarn.dia/io/processed_object_io.hpp"
#include "dogen/dia/test/mock_object_factory.hpp"
#include "dogen/utility/test/exception_checkers.hpp"

using namespace dogen::yarn::dia;
using dogen::utility::test::asserter;

namespace  {

const std::string test_module("yarn.dia");
const std::string test_suite("object_processor_tests");
const std::string model_name("test");
const std::string missing_name("Could not find name");
const std::string empty_name("Dia object name is empty");

const std::string enumeration_stereotype("enumeration");
const std::string exception_stereotype("exception");

}

using dogen::utility::test::contains_checker;
using dogen::dia::test::mock_object_factory;
using dogen::yarn::dia::object_types;

BOOST_AUTO_TEST_SUITE(object_processor_tests)

BOOST_AUTO_TEST_CASE(uml_class_with_no_stereotype_transforms_into_expected_processed_object) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_no_stereotype_transforms_into_expected_object");
    const auto o(mock_object_factory::make_class(0));
    BOOST_LOG_SEV(lg, debug) << "dia object:" << o;

    dogen::yarn::dia::object_processor op;
    const auto po(op.process(o));
    BOOST_LOG_SEV(lg, debug) << "actual:" << po;
    BOOST_CHECK(po.id() == mock_object_factory::to_oject_id(0));
    BOOST_CHECK(!po.name().empty());
    BOOST_CHECK(po.object_type() == object_types::uml_class);
    BOOST_CHECK(po.stereotype().empty());
    BOOST_CHECK(!po.comment().original_content().empty());
    BOOST_CHECK(!po.comment().documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_enumeration_stereotype_transforms_into_expected_processed_object) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_enumeration_stereotype_transforms_into_processed_object");
    dogen::yarn::dia::object_processor op;
    const std::string st(enumeration_stereotype);
    const auto o(mock_object_factory::make_stereotyped_class(st, 0));
    const auto po(op.process(o));
    BOOST_LOG_SEV(lg, debug) << "actual:" << po;
    BOOST_CHECK(po.id() == mock_object_factory::to_oject_id(0));
    BOOST_CHECK(!po.name().empty());
    BOOST_CHECK(po.object_type() == object_types::uml_class);
    BOOST_CHECK(po.stereotype() == enumeration_stereotype);
    BOOST_CHECK(!po.comment().original_content().empty());
    BOOST_CHECK(!po.comment().documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_exception_stereotype_transforms_into_expected_processed_object) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_exception_stereotype_transforms_into_processed_object");
    dogen::yarn::dia::object_processor op;
    const std::string st(exception_stereotype);
    const auto o(mock_object_factory::make_stereotyped_class(st, 0));
    const auto po(op.process(o));
    BOOST_LOG_SEV(lg, debug) << "actual:" << po;
    BOOST_CHECK(po.id() == mock_object_factory::to_oject_id(0));
    BOOST_CHECK(!po.name().empty());
    BOOST_CHECK(po.object_type() == object_types::uml_class);
    BOOST_CHECK(po.stereotype() == exception_stereotype);
    BOOST_CHECK(!po.comment().original_content().empty());
    BOOST_CHECK(!po.comment().documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_large_package_transforms_into_expected_processed_object) {
    SETUP_TEST_LOG_SOURCE("uml_large_package_transforms_into_expected_processed_object");

    dogen::yarn::dia::object_processor op;
    const auto o(mock_object_factory::make_large_package(0));
    const auto po(op.process(o));
    BOOST_LOG_SEV(lg, debug) << "actual:" << po;
    BOOST_CHECK(po.id() == mock_object_factory::to_oject_id(0));
    BOOST_CHECK(!po.name().empty());
    BOOST_CHECK(po.object_type() == object_types::uml_large_package);
    BOOST_CHECK(po.stereotype().empty());
    BOOST_CHECK(po.comment().original_content().empty());
    BOOST_CHECK(po.comment().documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_in_package_transforms_into_expected_processed_object) {
    SETUP_TEST_LOG_SOURCE("uml_class_in_package_transforms_into_expected_processed_object");

    dogen::yarn::dia::object_processor op;
    const auto o(mock_object_factory::make_class_inside_large_package(0));
    const auto po(op.process(o[1]));
    BOOST_LOG_SEV(lg, debug) << "actual:" << po;
    BOOST_CHECK(po.id() == mock_object_factory::to_oject_id(1));
    BOOST_CHECK(!po.name().empty());
    BOOST_CHECK(po.object_type() == object_types::uml_class);
    BOOST_CHECK(po.stereotype().empty());
    BOOST_CHECK(po.child_node_id() == o[0].id());
    BOOST_CHECK(!po.comment().original_content().empty());
    BOOST_CHECK(!po.comment().documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_generalization_transforms_into_expected_processed_object) {
    SETUP_TEST_LOG_SOURCE("uml_generalization_transforms_into_expected_processed_object");
    dogen::yarn::dia::object_processor op;
    const auto o(mock_object_factory::make_generalization(0));
    const auto po(op.process(o[0]));
    BOOST_LOG_SEV(lg, debug) << "actual:" << po;
    BOOST_CHECK(po.id() == mock_object_factory::to_oject_id(0));
    BOOST_CHECK(po.name().empty());
    BOOST_CHECK(po.object_type() == object_types::uml_generalization);
    BOOST_CHECK(po.stereotype().empty());
    BOOST_REQUIRE(po.connection());
    BOOST_REQUIRE(po.connection()->first == o[1].id());
    BOOST_REQUIRE(po.connection()->second == o[2].id());
}

BOOST_AUTO_TEST_CASE(uml_note_transforms_into_expected_processed_object) {
    SETUP_TEST_LOG_SOURCE("uml_note_transforms_into_expected_processed_object");
    dogen::yarn::dia::object_processor op;
    const auto o(mock_object_factory::make_uml_note(0));
    const auto po(op.process(o));
    BOOST_LOG_SEV(lg, debug) << "actual:" << po;
    BOOST_CHECK(po.id() == mock_object_factory::to_oject_id(0));
    BOOST_CHECK(po.name().empty());
    BOOST_CHECK(po.object_type() == object_types::uml_note);
    BOOST_CHECK(po.stereotype().empty());
    BOOST_CHECK(!po.comment().original_content().empty());
    BOOST_CHECK(!po.comment().documentation().empty());
}

BOOST_AUTO_TEST_SUITE_END()
