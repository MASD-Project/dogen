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
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/dia_to_sml/types/processed_object.hpp"
#include "dogen/dia_to_sml/types/processor.hpp"
#include "dogen/dia_to_sml/types/processing_error.hpp"
#include "dogen/dia_to_sml/io/context_io.hpp"
#include "dogen/dia_to_sml/io/processed_object_io.hpp"
#include "dogen/dia/test/mock_object_factory.hpp"
#include "dogen/utility/test/exception_checkers.hpp"

using namespace dogen::dia_to_sml;
using dogen::utility::test::asserter;

namespace  {

const std::string test_module("dia_to_sml");
const std::string test_suite("processor_spec");
const std::string model_name("test");
const std::string missing_name("Could not find name");
const std::string empty_name("Dia object name is empty");
const std::string missing_package("Missing package for dia object");

const std::string enumeration_stereotype("#enumeration#");
const std::string value_stereotype("#value#");
const std::string entity_stereotype("#entity#");
const std::string service_stereotype("#service#");
const std::string exception_stereotype("#exception#");

}

using dogen::utility::test::contains_checker;
using dogen::dia::test::mock_object_factory;
using dogen::dia_to_sml::object_types;

BOOST_AUTO_TEST_SUITE(processor)

BOOST_AUTO_TEST_CASE(uml_class_with_no_stereotype_transforms_into_expected_processed_object) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_no_stereotype_transforms_into_expected_pod");
    dogen::dia_to_sml::processor p;
    const auto o(p.process(mock_object_factory::build_class(0)));
    BOOST_LOG_SEV(lg, debug) << "actual:" << o;
    BOOST_CHECK(o.id() == mock_object_factory::to_oject_id(0));
    BOOST_CHECK(!o.name().empty());
    BOOST_CHECK(o.object_type() == object_types::uml_class);
    BOOST_CHECK(o.stereotype() == stereotypes::no_stereotype);
}

BOOST_AUTO_TEST_CASE(uml_class_with_enumeration_stereotype_transforms_into_expected_processed_object) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_enumeration_stereotype_transforms_into_processed_object");
    dogen::dia_to_sml::processor p;
    const std::string st(enumeration_stereotype);
    const auto o(mock_object_factory::build_stereotyped_class(st, 0));
    const auto po(p.process(o));
    BOOST_LOG_SEV(lg, debug) << "actual:" << po;
    BOOST_CHECK(po.id() == mock_object_factory::to_oject_id(0));
    BOOST_CHECK(!po.name().empty());
    BOOST_CHECK(po.object_type() == object_types::uml_class);
    BOOST_CHECK(po.stereotype() == stereotypes::enumeration);
}

BOOST_AUTO_TEST_CASE(uml_class_with_exception_stereotype_transforms_into_expected_processed_object) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_exception_stereotype_transforms_into_processed_object");
    dogen::dia_to_sml::processor p;
    const std::string st(exception_stereotype);
    const auto o(mock_object_factory::build_stereotyped_class(st, 0));
    const auto po(p.process(o));
    BOOST_LOG_SEV(lg, debug) << "actual:" << po;
    BOOST_CHECK(po.id() == mock_object_factory::to_oject_id(0));
    BOOST_CHECK(!po.name().empty());
    BOOST_CHECK(po.object_type() == object_types::uml_class);
    BOOST_CHECK(po.stereotype() == stereotypes::exception);
}

BOOST_AUTO_TEST_CASE(uml_large_package_transforms_into_expected_package) {
    SETUP_TEST_LOG_SOURCE("uml_large_package_transforms_into_expected_package");

    dogen::dia_to_sml::processor p;
    const auto o(mock_object_factory::build_large_package(0));
    const auto po(p.process(o));
    BOOST_LOG_SEV(lg, debug) << "actual:" << po;
    BOOST_CHECK(po.id() == mock_object_factory::to_oject_id(0));
    BOOST_CHECK(!po.name().empty());
    BOOST_CHECK(po.object_type() == object_types::uml_large_package);
    BOOST_CHECK(po.stereotype() == stereotypes::no_stereotype);
}

BOOST_AUTO_TEST_CASE(uml_class_in_package_transforms_into_expected_processed_object) {
    SETUP_TEST_LOG_SOURCE("uml_class_in_package_transforms_into_expected_processed_object");

    dogen::dia_to_sml::processor p;
    const auto o(mock_object_factory::build_class_inside_large_package(0));
    const auto po(p.process(o[1]));
    BOOST_LOG_SEV(lg, debug) << "actual:" << po;
    BOOST_CHECK(po.id() == mock_object_factory::to_oject_id(1));
    BOOST_CHECK(!po.name().empty());
    BOOST_CHECK(po.object_type() == object_types::uml_class);
    BOOST_CHECK(po.stereotype() == stereotypes::no_stereotype);
    BOOST_CHECK(po.child_node_id() == o[0].id());
}

BOOST_AUTO_TEST_CASE(uml_generalization_transforms_into_expected_processed_object) {
    SETUP_TEST_LOG_SOURCE("uml_generalization_transforms_into_expected_processed_object");
    dogen::dia_to_sml::processor p;
    const auto o(mock_object_factory::build_generalization(0));
    const auto po(p.process(o[0]));
    BOOST_LOG_SEV(lg, debug) << "actual:" << po;
    BOOST_CHECK(po.id() == mock_object_factory::to_oject_id(0));
    BOOST_CHECK(po.name().empty());
    BOOST_CHECK(po.object_type() == object_types::uml_generalization);
    BOOST_CHECK(po.stereotype() == stereotypes::no_stereotype);
    BOOST_REQUIRE(po.connection());
    BOOST_REQUIRE(po.connection()->first == o[1].id());
    BOOST_REQUIRE(po.connection()->second == o[2].id());
}

BOOST_AUTO_TEST_CASE(uml_note_transforms_into_expected_processed_object) {
    SETUP_TEST_LOG_SOURCE("uml_note_transforms_into_expected_processed_object");
    dogen::dia_to_sml::processor p;
    const auto o(mock_object_factory::build_uml_note(0));
    const auto po(p.process(o));
    BOOST_LOG_SEV(lg, debug) << "actual:" << po;
    BOOST_CHECK(po.id() == mock_object_factory::to_oject_id(0));
    BOOST_CHECK(po.name().empty());
    BOOST_CHECK(po.object_type() == object_types::uml_note);
    BOOST_CHECK(po.stereotype() == stereotypes::no_stereotype);
    BOOST_CHECK(!po.text().empty());
}

BOOST_AUTO_TEST_SUITE_END()
