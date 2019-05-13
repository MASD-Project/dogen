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
/*
#include <fstream>
#include <sstream>
#include <boost/filesystem/fstream.hpp>
#include <boost/test/unit_test.hpp>
#include "dogen.utility/types/test/xml_serialization_helper.hpp"
#include "dogen.utility/types/test/asserter.hpp"
#include "dogen.utility/types/test/logging.hpp"
#include "dogen.utility/types/test_data/injection_dia.hpp"
#include "dogen.dia/io/diagram_io.hpp"
#include "dogen.coding/types/meta_model/model.hpp"
#include "dogen.coding/io/meta_model/model_io.hpp"
#include "dogen.coding/serialization/meta_model/model_ser.hpp"
#include "dogen.coding/test/mock_context_factory.hpp"
#include "dogen.utility/types/test/exception_checkers.hpp"
#include "dogen.dia/test/diagram_serialization_helper.hpp"
#include "dogen.coding/serialization/registrar_ser.hpp"
#include "dogen.variability/test/mock_type_repository_factory.hpp"
#include "dogen.injection.dia/types/workflow.hpp"

template<typename Archive> void register_types(Archive& ar) {
    dogen::coding::register_types<Archive>(ar);
}

using namespace dogen::injection::dia;
using dogen::utility::test::asserter;
using dogen::coding::test::mock_context_factory;

namespace  {

const std::string test_module("masd.injection.dia.tests");
const std::string test_suite("workflow_tests");

bool test_workflow(
    boost::filesystem::path input_path,
    boost::filesystem::path expected_path,
    boost::filesystem::path actual_path) {

    boost::filesystem::ifstream s(input_path);
    using dogen::dia::test::diagram_serialization_helper;
    const auto i(diagram_serialization_helper::from_xml(s));

    using namespace dogen::variability::test;
    mock_type_repository_factory rf;
    const auto rp(rf.make());
    const auto actual(workflow::execute(i));
    const dogen::coding::transforms::context ctx(mock_context_factory::make());

    *
     * Set to true to rebase. Note that you still need to run the
     * appropriate rebase target afterwards to copy the files across.
     *
    const bool rm(false);
    return asserter::assert_object(rm, expected_path, actual_path, actual);
}

}

using dogen::utility::test_data::injection_dia;
using dogen::utility::test::contains_checker;

BOOST_AUTO_TEST_SUITE(workflow_tests)

BOOST_IGNORE_AUTO_TEST_CASE(empty_dia_transforms_into_expected_model) {
    SETUP_TEST_LOG("empty_dia_transforms_into_expected_model");
    const auto i(injection_dia::expected_empty_dia_xml());
    const auto e(injection_dia::expected_empty_injection_xml());
    const auto a(injection_dia::actual_empty_injection_xml());
    BOOST_CHECK(test_workflow(i, e, a));
}

BOOST_IGNORE_AUTO_TEST_CASE(two_layers_with_objects_dia_transforms_into_expected_model) {
    SETUP_TEST_LOG("two_layers_with_objects_dia_transforms_into_expected_model");
    const auto i(injection_dia::expected_two_layers_with_objects_dia_xml());
    const auto e(injection_dia::expected_two_layers_with_objects_injection_xml());
    const auto a(injection_dia::actual_two_layers_with_objects_injection_xml());
    BOOST_CHECK(test_workflow(i, e, a));
}

BOOST_IGNORE_AUTO_TEST_CASE(cpp_model_dia_transforms_into_expected_model) {
    SETUP_TEST_LOG("cpp_model_dia_transforms_into_expected_model");
    const auto i(injection_dia::expected_cpp_model_dia_xml());
    const auto e(injection_dia::expected_cpp_model_injection_xml());
    const auto a(injection_dia::actual_cpp_model_injection_xml());
    BOOST_CHECK(test_workflow(i, e, a));
}


BOOST_IGNORE_AUTO_TEST_CASE(std_model_dia_transforms_into_expected_model) {
    SETUP_TEST_LOG("std_model_dia_transforms_into_expected_model");
    const auto i(injection_dia::expected_std_model_dia_xml());
    const auto e(injection_dia::expected_std_model_injection_xml());
    const auto a(injection_dia::actual_std_model_injection_xml());
    BOOST_CHECK(test_workflow(i, e, a));
}

BOOST_IGNORE_AUTO_TEST_CASE(boost_model_dia_transforms_into_expected_model) {
    SETUP_TEST_LOG("boost_model_dia_transforms_into_expected_model");
    const auto i(injection_dia::expected_boost_model_dia_xml());
    const auto e(injection_dia::expected_boost_model_injection_xml());
    const auto a(injection_dia::actual_boost_model_injection_xml());
    BOOST_CHECK(test_workflow(i, e, a));
}

BOOST_AUTO_TEST_SUITE_END()
*/
