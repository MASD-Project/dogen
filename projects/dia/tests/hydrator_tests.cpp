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
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include "dogen/utility/test/macros.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test_data/yarn_dia.hpp"
#include "dogen/utility/io/vector_io.hpp"
#include "dogen/dia/types/all.hpp"
#include "dogen/dia/io/all_io.hpp"
#include "dogen/dia/serialization/all_ser.hpp"
#include "dogen/dia/serialization/registrar_ser.hpp"
#include "dogen/dia/types/hydrator.hpp"

template<typename Archive> void register_types(Archive& ar) {
    dogen::dia::register_types<Archive>(ar);
}

namespace {

const std::string test_module("dia");
const std::string test_suite("hydrator_tests");

bool test_hydrator(
    boost::filesystem::path input_path,
    boost::filesystem::path expected_path,
    boost::filesystem::path actual_path) {

    dogen::dia::hydrator hydrator(input_path);
    dogen::dia::diagram actual(hydrator.hydrate());

    using dogen::utility::test::asserter;
    return asserter::assert_object(expected_path, actual_path, actual);
}

}

BOOST_AUTO_TEST_SUITE(hydrator_tests)

BOOST_AUTO_TEST_CASE(class_in_a_package_diagram_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("class_in_a_package_diagram_results_in_expected_objects");
    using dogen::utility::test_data::yarn_dia;
    const auto input(yarn_dia::input_class_in_a_package_dia());
    const auto actual(yarn_dia::actual_class_in_a_package_dia_xml());
    const auto expected(yarn_dia::expected_class_in_a_package_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_IGNORE_AUTO_TEST_CASE(compressed_diagram_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("compressed_diagram_results_in_expected_objects");
    using dogen::utility::test_data::yarn_dia;
    const auto input(yarn_dia::input_compressed_dia());
    const auto actual(yarn_dia::actual_compressed_dia_xml());
    const auto expected(yarn_dia::expected_compressed_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_CASE(empty_diagram_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("empty_diagram_results_in_expected_objects");
    using dogen::utility::test_data::yarn_dia;
    const auto input(yarn_dia::input_empty_dia());
    const auto actual(yarn_dia::actual_empty_dia_xml());
    const auto expected(yarn_dia::expected_empty_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_CASE(two_empty_layers_diagram_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("two_empty_layers_diagram_results_in_expected_objects");
    using dogen::utility::test_data::yarn_dia;
    const auto input(yarn_dia::input_two_empty_layers_dia());
    const auto actual(yarn_dia::actual_two_empty_layers_dia_xml());
    const auto expected(yarn_dia::expected_two_empty_layers_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_CASE(stand_alone_class_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("stand_alone_class_results_in_expected_objects");
    using dogen::utility::test_data::yarn_dia;
    const auto input(yarn_dia::input_stand_alone_class_dia());
    const auto actual(yarn_dia::actual_stand_alone_class_dia_xml());
    const auto expected(yarn_dia::expected_stand_alone_class_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_CASE(class_with_empty_package_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("class_with_empty_package_results_in_expected_objects");
    using dogen::utility::test_data::yarn_dia;
    const auto input(yarn_dia::input_empty_package_dia());
    const auto actual(yarn_dia::actual_empty_package_dia_xml());
    const auto expected(yarn_dia::expected_empty_package_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_CASE(class_without_name_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("class_without_name_results_in_expected_objects");
    using dogen::utility::test_data::yarn_dia;
    const auto input(yarn_dia::input_class_without_name_dia());
    const auto actual(yarn_dia::actual_class_without_name_dia_xml());
    const auto expected(yarn_dia::expected_class_without_name_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_CASE(class_in_a_package_class_without_package_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("class_in_a_package_class_without_package_results_in_expected_objects");
    using dogen::utility::test_data::yarn_dia;
    const auto input(yarn_dia::input_classes_inout_package_dia());
    const auto actual(yarn_dia::actual_classes_inout_package_dia_xml());
    const auto expected(yarn_dia::expected_classes_inout_package_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_CASE(class_without_attributes_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("class_without_attributes_results_in_expected_objects");
    using dogen::utility::test_data::yarn_dia;
    const auto input(yarn_dia::input_class_without_attributes_dia());
    const auto actual(yarn_dia::actual_class_without_attributes_dia_xml());
    const auto expected(yarn_dia::expected_class_without_attributes_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_CASE(class_without_package_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("class_without_package_results_in_expected_objects");
    using dogen::utility::test_data::yarn_dia;
    const auto input(yarn_dia::input_class_without_package_dia());
    const auto actual(yarn_dia::actual_class_without_package_dia_xml());
    const auto expected(yarn_dia::expected_class_without_package_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_CASE(classes_in_a_package_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("classes_in_a_package_results_in_expected_objects");
    using dogen::utility::test_data::yarn_dia;
    const auto input(yarn_dia::input_classes_in_a_package_dia());
    const auto actual(yarn_dia::actual_classes_in_a_package_dia_xml());
    const auto expected(yarn_dia::expected_classes_in_a_package_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_CASE(classes_without_package_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("classes_without_package_results_in_expected_objects");
    using dogen::utility::test_data::yarn_dia;
    const auto input(yarn_dia::input_classes_without_package_dia());
    const auto actual(yarn_dia::actual_classes_without_package_dia_xml());
    const auto expected(yarn_dia::expected_classes_without_package_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_CASE(package_without_name_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("package_without_name_results_in_expected_objects");
    using dogen::utility::test_data::yarn_dia;
    const auto input(yarn_dia::input_package_without_name_dia());
    const auto actual(yarn_dia::actual_package_without_name_dia_xml());
    const auto expected(yarn_dia::expected_package_without_name_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_CASE(two_layers_with_objects_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("two_layers_with_objects_results_in_expected_objects");
    using dogen::utility::test_data::yarn_dia;
    const auto input(yarn_dia::input_two_layers_with_objects_dia());
    const auto actual(yarn_dia::actual_two_layers_with_objects_dia_xml());
    const auto expected(yarn_dia::expected_two_layers_with_objects_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_CASE(all_primitives_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("all_primitives_results_in_expected_objects");
    using dogen::utility::test_data::yarn_dia;
    const auto input(yarn_dia::input_all_primitives_dia());
    const auto actual(yarn_dia::actual_all_primitives_dia_xml());
    const auto expected(yarn_dia::expected_all_primitives_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_CASE(trivial_inheritance_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("trivial_inheritance_results_in_expected_objects");
    using dogen::utility::test_data::yarn_dia;
    const auto input(yarn_dia::input_trivial_inheritance_dia());
    const auto actual(yarn_dia::actual_trivial_inheritance_dia_xml());
    const auto expected(yarn_dia::expected_trivial_inheritance_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_CASE(boost_model_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("boost_model_results_in_expected_objects");
    using dogen::utility::test_data::yarn_dia;
    const auto input(yarn_dia::input_boost_model_dia());
    const auto actual(yarn_dia::actual_boost_model_dia_xml());
    const auto expected(yarn_dia::expected_boost_model_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_CASE(std_model_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("std_model_results_in_expected_objects");
    using dogen::utility::test_data::yarn_dia;
    const auto input(yarn_dia::input_std_model_dia());
    const auto actual(yarn_dia::actual_std_model_dia_xml());
    const auto expected(yarn_dia::expected_std_model_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_CASE(comments_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("comments_results_in_expected_objects");
    using dogen::utility::test_data::yarn_dia;
    const auto input(yarn_dia::input_comments_dia());
    const auto actual(yarn_dia::actual_comments_dia_xml());
    const auto expected(yarn_dia::expected_comments_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_CASE(enumeration_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("enumeration_results_in_expected_objects");
    using dogen::utility::test_data::yarn_dia;
    const auto input(yarn_dia::input_enumeration_dia());
    const auto actual(yarn_dia::actual_enumeration_dia_xml());
    const auto expected(yarn_dia::expected_enumeration_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_CASE(exception_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("exception_results_in_expected_objects");
    using dogen::utility::test_data::yarn_dia;
    const auto input(yarn_dia::input_exception_dia());
    const auto actual(yarn_dia::actual_exception_dia_xml());
    const auto expected(yarn_dia::expected_exception_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_SUITE_END()
