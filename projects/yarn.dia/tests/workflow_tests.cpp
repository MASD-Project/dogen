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
#include <fstream>
#include <sstream>
#include <boost/filesystem/fstream.hpp>
#include <boost/test/unit_test.hpp>
#include "dogen/utility/test/xml_serialization_helper.hpp"
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test_data/yarn_dia.hpp"
#include "dogen/dia/io/diagram_io.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"
#include "dogen/yarn/io/intermediate_model_io.hpp"
#include "dogen/yarn/serialization/intermediate_model_ser.hpp"
#include "dogen/utility/test/exception_checkers.hpp"
#include "dogen/dia/test/diagram_serialization_helper.hpp"
#include "dogen/yarn/serialization/registrar_ser.hpp"
#include "dogen/annotations/test/mock_type_repository_factory.hpp"
#include "dogen/yarn.dia/types/workflow.hpp"

template<typename Archive> void register_types(Archive& ar) {
    dogen::yarn::register_types<Archive>(ar);
}

using namespace dogen::yarn::dia;
using dogen::utility::test::asserter;

namespace  {

const std::string test_module("yarn.dia");
const std::string test_suite("workflow_tests");

bool test_workflow(
    boost::filesystem::path input_path,
    boost::filesystem::path expected_path,
    boost::filesystem::path actual_path) {

    boost::filesystem::ifstream s(input_path);
    using dogen::dia::test::diagram_serialization_helper;
    const auto i(diagram_serialization_helper::from_xml(s));

    const std::string epp;
    const bool is_target(true);
    const std::string model_name(input_path.stem().string());

    using namespace dogen::annotations::test;
    mock_type_repository_factory rf;
    const auto rp(rf.make());
    workflow w;
    dogen::yarn::intermediate_model
        actual(w.execute(i, model_name, epp, is_target));
    return asserter::assert_object(expected_path, actual_path, actual);
}

}

using dogen::utility::test_data::yarn_dia;
using dogen::utility::test::contains_checker;

BOOST_AUTO_TEST_SUITE(workflow_tests)

BOOST_AUTO_TEST_CASE(class_in_a_package_dia_transforms_into_expected_yarn) {
    SETUP_TEST_LOG("class_in_a_package_dia_transforms_into_expected_yarn");
    const auto i(yarn_dia::expected_class_in_a_package_dia_xml());
    const auto e(yarn_dia::expected_class_in_a_package_yarn_xml());
    const auto a(yarn_dia::actual_class_in_a_package_yarn_xml());
    BOOST_CHECK(test_workflow(i, e, a));
}

BOOST_AUTO_TEST_CASE(empty_dia_transforms_into_expected_yarn) {
    SETUP_TEST_LOG("empty_dia_transforms_into_expected_yarn");
    const auto i(yarn_dia::expected_empty_dia_xml());
    const auto e(yarn_dia::expected_empty_yarn_xml());
    const auto a(yarn_dia::actual_empty_yarn_xml());
    BOOST_CHECK(test_workflow(i, e, a));
}

BOOST_AUTO_TEST_CASE(empty_package_dia_transforms_into_expected_yarn) {
    SETUP_TEST_LOG("empty_package_dia_transforms_into_expected_yarn");
    const auto i(yarn_dia::expected_empty_package_dia_xml());
    const auto e(yarn_dia::expected_empty_package_yarn_xml());
    const auto a(yarn_dia::actual_empty_package_yarn_xml());
    BOOST_CHECK(test_workflow(i, e, a));
}

BOOST_AUTO_TEST_CASE(classes_inout_package_dia_transforms_into_expected_yarn) {
    SETUP_TEST_LOG("classes_inout_package_dia_transforms_into_expected_yarn");
    const auto i(yarn_dia::expected_classes_inout_package_dia_xml());
    const auto e(yarn_dia::expected_classes_inout_package_yarn_xml());
    const auto a(yarn_dia::actual_classes_inout_package_yarn_xml());
    BOOST_CHECK(test_workflow(i, e, a));
}

BOOST_AUTO_TEST_CASE(class_without_attributes_dia_transforms_into_expected_yarn) {
    SETUP_TEST_LOG("class_without_attributes_dia_transforms_into_expected_yarn");
    const auto i(yarn_dia::expected_class_without_attributes_dia_xml());
    const auto e(yarn_dia::expected_class_without_attributes_yarn_xml());
    const auto a(yarn_dia::actual_class_without_attributes_yarn_xml());
    BOOST_CHECK(test_workflow(i, e, a));
}

BOOST_AUTO_TEST_CASE(class_without_package_dia_transforms_into_expected_yarn) {
    SETUP_TEST_LOG("class_without_package_dia_transforms_into_expected_yarn");
    const auto i(yarn_dia::expected_class_without_package_dia_xml());
    const auto e(yarn_dia::expected_class_without_package_yarn_xml());
    const auto a(yarn_dia::actual_class_without_package_yarn_xml());
    BOOST_CHECK(test_workflow(i, e, a));
}

BOOST_AUTO_TEST_CASE(classes_without_package_dia_transforms_into_expected_yarn) {
    SETUP_TEST_LOG("classes_without_package_dia_transforms_into_expected_yarn");
    const auto i(yarn_dia::expected_classes_without_package_dia_xml());
    const auto e(yarn_dia::expected_classes_without_package_yarn_xml());
    const auto a(yarn_dia::actual_classes_without_package_yarn_xml());
    BOOST_CHECK(test_workflow(i, e, a));
}

BOOST_AUTO_TEST_CASE(two_layers_with_objects_dia_transforms_into_expected_yarn) {
    SETUP_TEST_LOG("two_layers_with_objects_dia_transforms_into_expected_yarn");
    const auto i(yarn_dia::expected_two_layers_with_objects_dia_xml());
    const auto e(yarn_dia::expected_two_layers_with_objects_yarn_xml());
    const auto a(yarn_dia::actual_two_layers_with_objects_yarn_xml());
    BOOST_CHECK(test_workflow(i, e, a));
}

BOOST_AUTO_TEST_CASE(all_primitives_dia_transforms_into_expected_yarn) {
    SETUP_TEST_LOG("all_primitives_dia_transforms_into_expected_yarn");
    const auto i(yarn_dia::expected_all_primitives_dia_xml());
    const auto e(yarn_dia::expected_all_primitives_yarn_xml());
    const auto a(yarn_dia::actual_all_primitives_yarn_xml());
    BOOST_CHECK(test_workflow(i, e, a));
}

BOOST_AUTO_TEST_CASE(trivial_inheritance_dia_transforms_into_expected_yarn) {
    SETUP_TEST_LOG("trivial_inheritance_dia_transforms_into_expected_yarn");
    const auto i(yarn_dia::expected_trivial_inheritance_dia_xml());
    const auto e(yarn_dia::expected_trivial_inheritance_yarn_xml());
    const auto a(yarn_dia::actual_trivial_inheritance_yarn_xml());
    BOOST_CHECK(test_workflow(i, e, a));
}

BOOST_AUTO_TEST_CASE(std_model_dia_transforms_into_expected_yarn) {
    SETUP_TEST_LOG("std_model_dia_transforms_into_expected_yarn");
    const auto i(yarn_dia::expected_std_model_dia_xml());
    const auto e(yarn_dia::expected_std_model_yarn_xml());
    const auto a(yarn_dia::actual_std_model_yarn_xml());
    BOOST_CHECK(test_workflow(i, e, a));
}

BOOST_AUTO_TEST_CASE(boost_model_dia_transforms_into_expected_yarn) {
    SETUP_TEST_LOG("boost_model_dia_transforms_into_expected_yarn");
    const auto i(yarn_dia::expected_boost_model_dia_xml());
    const auto e(yarn_dia::expected_boost_model_yarn_xml());
    const auto a(yarn_dia::actual_boost_model_yarn_xml());
    BOOST_CHECK(test_workflow(i, e, a));
}

BOOST_AUTO_TEST_CASE(comments_dia_transforms_into_expected_yarn) {
    SETUP_TEST_LOG("comments_dia_transforms_into_expected_yarn");
    const auto i(yarn_dia::expected_comments_dia_xml());
    const auto e(yarn_dia::expected_comments_yarn_xml());
    const auto a(yarn_dia::actual_comments_yarn_xml());
    BOOST_CHECK(test_workflow(i, e, a));
}

BOOST_AUTO_TEST_CASE(enumeration_dia_transforms_into_expected_yarn) {
    SETUP_TEST_LOG("enumeration_dia_transforms_into_expected_yarn");
    const auto i(yarn_dia::expected_enumeration_dia_xml());
    const auto e(yarn_dia::expected_enumeration_yarn_xml());
    const auto a(yarn_dia::actual_enumeration_yarn_xml());
    BOOST_CHECK(test_workflow(i, e, a));
}

BOOST_AUTO_TEST_CASE(exception_dia_transforms_into_expected_yarn) {
    SETUP_TEST_LOG("exception_dia_transforms_into_expected_yarn");
    const auto i(yarn_dia::expected_exception_dia_xml());
    const auto e(yarn_dia::expected_exception_yarn_xml());
    const auto a(yarn_dia::actual_exception_yarn_xml());
    BOOST_CHECK(test_workflow(i, e, a));
}

BOOST_AUTO_TEST_SUITE_END()
