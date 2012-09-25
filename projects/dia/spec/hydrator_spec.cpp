/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Dogen
 *
 * This file is distributed under the Dogen Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test_data/dia_sml.hpp"
#include "dogen/utility/io/vector_io.hpp"
#include "dogen/dia/domain/dia_domain.hpp"
#include "dogen/dia/io/dia_io.hpp"
#include "dogen/dia/serialization/dia_ser.hpp"
#include "dogen/dia/xml/hydrator.hpp"

namespace {

const std::string test_module("sml");
const std::string test_suite("hydrator_spec");

bool test_hydrator(
    boost::filesystem::path input_path,
    boost::filesystem::path expected_path,
    boost::filesystem::path actual_path) {

    dogen::dia::xml::hydrator hydrator(input_path);
    dogen::dia::diagram actual(hydrator.hydrate());

    using dogen::utility::test::asserter;
    return asserter::assert_object(expected_path, actual_path, actual);
}

}

BOOST_AUTO_TEST_SUITE(hydrator)

BOOST_AUTO_TEST_CASE(class_in_a_package_diagram_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("class_in_a_package_diagram_results_in_expected_objects");
    using dogen::utility::test_data::dia_sml;
    const auto input(dia_sml::input_class_in_a_package_dia());
    const auto actual(dia_sml::actual_class_in_a_package_dia_xml());
    const auto expected(dia_sml::expected_class_in_a_package_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_CASE(compressed_diagram_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("compressed_diagram_results_in_expected_objects");
    using dogen::utility::test_data::dia_sml;
    const auto input(dia_sml::input_compressed_dia());
    const auto actual(dia_sml::actual_compressed_dia_xml());
    const auto expected(dia_sml::expected_compressed_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_CASE(empty_diagram_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("empty_diagram_results_in_expected_objects");
    using dogen::utility::test_data::dia_sml;
    const auto input(dia_sml::input_empty_dia());
    const auto actual(dia_sml::actual_empty_dia_xml());
    const auto expected(dia_sml::expected_empty_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_CASE(two_empty_layers_diagram_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("two_empty_layers_diagram_results_in_expected_objects");
    using dogen::utility::test_data::dia_sml;
    const auto input(dia_sml::input_two_empty_layers_dia());
    const auto actual(dia_sml::actual_two_empty_layers_dia_xml());
    const auto expected(dia_sml::expected_two_empty_layers_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_CASE(class_without_package_and_attributes_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("class_without_package_and_attributes_results_in_expected_objects");
    using dogen::utility::test_data::dia_sml;
    const auto input(dia_sml::input_class_without_package_and_attributes_dia());
    const auto actual(dia_sml::actual_class_without_package_and_attributes_dia_xml());
    const auto expected(dia_sml::expected_class_without_package_and_attributes_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_CASE(class_with_empty_package_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("class_with_empty_package_results_in_expected_objects");
    using dogen::utility::test_data::dia_sml;
    const auto input(dia_sml::input_empty_package_dia());
    const auto actual(dia_sml::actual_empty_package_dia_xml());
    const auto expected(dia_sml::expected_empty_package_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_CASE(class_without_name_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("class_without_name_results_in_expected_objects");
    using dogen::utility::test_data::dia_sml;
    const auto input(dia_sml::input_class_without_name_dia());
    const auto actual(dia_sml::actual_class_without_name_dia_xml());
    const auto expected(dia_sml::expected_class_without_name_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_CASE(class_in_a_package_class_without_package_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("class_in_a_package_class_without_package_results_in_expected_objects");
    using dogen::utility::test_data::dia_sml;
    const auto input(dia_sml::input_classes_inside_and_outside_package_dia());
    const auto actual(dia_sml::actual_classes_inside_and_outside_package_dia_xml());
    const auto expected(dia_sml::expected_classes_inside_and_outside_package_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_CASE(class_without_attributes_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("class_without_attributes_results_in_expected_objects");
    using dogen::utility::test_data::dia_sml;
    const auto input(dia_sml::input_class_without_attributes_dia());
    const auto actual(dia_sml::actual_class_without_attributes_dia_xml());
    const auto expected(dia_sml::expected_class_without_attributes_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_CASE(class_without_package_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("class_without_package_results_in_expected_objects");
    using dogen::utility::test_data::dia_sml;
    const auto input(dia_sml::input_class_without_package_dia());
    const auto actual(dia_sml::actual_class_without_package_dia_xml());
    const auto expected(dia_sml::expected_class_without_package_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_CASE(classes_in_a_package_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("classes_in_a_package_results_in_expected_objects");
    using dogen::utility::test_data::dia_sml;
    const auto input(dia_sml::input_classes_in_a_package_dia());
    const auto actual(dia_sml::actual_classes_in_a_package_dia_xml());
    const auto expected(dia_sml::expected_classes_in_a_package_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_CASE(classes_without_package_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("classes_without_package_results_in_expected_objects");
    using dogen::utility::test_data::dia_sml;
    const auto input(dia_sml::input_classes_without_package_dia());
    const auto actual(dia_sml::actual_classes_without_package_dia_xml());
    const auto expected(dia_sml::expected_classes_without_package_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_CASE(package_without_name_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("package_without_name_results_in_expected_objects");
    using dogen::utility::test_data::dia_sml;
    const auto input(dia_sml::input_package_without_name_dia());
    const auto actual(dia_sml::actual_package_without_name_dia_xml());
    const auto expected(dia_sml::expected_package_without_name_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_CASE(two_layers_with_objects_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("two_layers_with_objects_results_in_expected_objects");
    using dogen::utility::test_data::dia_sml;
    const auto input(dia_sml::input_two_layers_with_objects_dia());
    const auto actual(dia_sml::actual_two_layers_with_objects_dia_xml());
    const auto expected(dia_sml::expected_two_layers_with_objects_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_SUITE_END()
