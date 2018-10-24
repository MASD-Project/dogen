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
#include "masd.dogen.utility/test/macros.hpp"
#include "masd.dogen.utility/test/logging.hpp"
#include "masd.dogen.utility/test/asserter.hpp"
#include "masd.dogen.utility/test_data/external_dia.hpp"
#include "masd.dogen.utility/io/vector_io.hpp"
#include "masd.dogen.dia/types/all.hpp"
#include "masd.dogen.dia/io/all_io.hpp"
#include "masd.dogen.dia/serialization/all_ser.hpp"
#include "masd.dogen.dia/serialization/registrar_ser.hpp"
#include "masd.dogen.dia/types/hydrator.hpp"

template<typename Archive> void register_types(Archive& ar) {
    masd::dogen::dia::register_types<Archive>(ar);
}

namespace {

const std::string test_module("dia");
const std::string test_suite("hydrator_tests");



bool test_hydrator(
    boost::filesystem::path input_path,
    boost::filesystem::path expected_path,
    boost::filesystem::path actual_path) {

    masd::dogen::dia::hydrator h;
    masd::dogen::dia::diagram actual(h.hydrate(input_path));

    using masd::dogen::utility::test::asserter;
    /*
     * Set to true to rebase. Note that you still need to run the
     * appropriate rebase target afterwards to copy the files across.
     */
    const bool rm(false);
    return asserter::assert_object(rm, expected_path, actual_path, actual);
}

}

using masd::dogen::utility::test_data::external_dia;

BOOST_AUTO_TEST_SUITE(hydrator_tests)

BOOST_AUTO_TEST_CASE(cpp_model_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("cpp_model_results_in_expected_objects");
    const auto input(external_dia::input_cpp_model_dia());
    const auto actual(external_dia::actual_cpp_model_dia_xml());
    const auto expected(external_dia::expected_cpp_model_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_IGNORE_AUTO_TEST_CASE(compressed_diagram_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("compressed_diagram_results_in_expected_objects");
    const auto input(external_dia::input_compressed_dia());
    const auto actual(external_dia::actual_compressed_dia_xml());
    const auto expected(external_dia::expected_compressed_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_CASE(empty_diagram_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("empty_diagram_results_in_expected_objects");
    const auto input(external_dia::input_empty_dia());
    const auto actual(external_dia::actual_empty_dia_xml());
    const auto expected(external_dia::expected_empty_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_CASE(two_empty_layers_diagram_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("two_empty_layers_diagram_results_in_expected_objects");
    const auto input(external_dia::input_two_empty_layers_dia());
    const auto actual(external_dia::actual_two_empty_layers_dia_xml());
    const auto expected(external_dia::expected_two_empty_layers_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_CASE(class_without_name_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("class_without_name_results_in_expected_objects");
    const auto input(external_dia::input_class_without_name_dia());
    const auto actual(external_dia::actual_class_without_name_dia_xml());
    const auto expected(external_dia::expected_class_without_name_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_CASE(package_without_name_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("package_without_name_results_in_expected_objects");
    const auto input(external_dia::input_package_without_name_dia());
    const auto actual(external_dia::actual_package_without_name_dia_xml());
    const auto expected(external_dia::expected_package_without_name_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_CASE(two_layers_with_objects_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("two_layers_with_objects_results_in_expected_objects");
    const auto input(external_dia::input_two_layers_with_objects_dia());
    const auto actual(external_dia::actual_two_layers_with_objects_dia_xml());
    const auto expected(external_dia::expected_two_layers_with_objects_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_CASE(boost_model_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("boost_model_results_in_expected_objects");
    const auto input(external_dia::input_boost_model_dia());
    const auto actual(external_dia::actual_boost_model_dia_xml());
    const auto expected(external_dia::expected_boost_model_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_CASE(std_model_results_in_expected_objects) {
    SETUP_TEST_LOG_SOURCE("std_model_results_in_expected_objects");
    const auto input(external_dia::input_std_model_dia());
    const auto actual(external_dia::actual_std_model_dia_xml());
    const auto expected(external_dia::expected_std_model_dia_xml());
    BOOST_CHECK(test_hydrator(input, expected, actual));
}

BOOST_AUTO_TEST_SUITE_END()
