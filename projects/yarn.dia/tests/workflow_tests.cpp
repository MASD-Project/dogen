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
#include "dogen/yarn/types/meta_model/module.hpp"
#include "dogen/yarn/types/meta_model/concept.hpp"
#include "dogen/yarn/types/meta_model/builtin.hpp"
#include "dogen/yarn/types/meta_model/enumeration.hpp"
#include "dogen/yarn/types/meta_model/object.hpp"
#include "dogen/yarn/types/meta_model/exception.hpp"
#include "dogen/yarn/types/meta_model/exogenous_model.hpp"
#include "dogen/yarn/io/meta_model/exogenous_model_io.hpp"
#include "dogen/yarn/serialization/meta_model/exogenous_model_ser.hpp"
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

template<typename Element> bool
comparer(const std::pair<dogen::annotations::scribble_group,
    boost::shared_ptr<Element>>& lhs,
    const std::pair<dogen::annotations::scribble_group,
    boost::shared_ptr<Element>>& rhs) {
    return lhs.second->name().id() < rhs.second->name().id();
}

void sort_model(dogen::yarn::meta_model::exogenous_model& em) {
    em.modules().sort(comparer<dogen::yarn::meta_model::module>);
    em.concepts().sort(comparer<dogen::yarn::meta_model::concept>);
    em.builtins().sort(comparer<dogen::yarn::meta_model::builtin>);
    em.enumerations().sort(comparer<dogen::yarn::meta_model::enumeration>);
    em.primitives().sort(comparer<dogen::yarn::meta_model::primitive>);
    em.objects().sort(comparer<dogen::yarn::meta_model::object>);
    em.exceptions().sort(comparer<dogen::yarn::meta_model::exception>);
}

bool test_workflow(
    boost::filesystem::path input_path,
    boost::filesystem::path expected_path,
    boost::filesystem::path actual_path) {

    boost::filesystem::ifstream s(input_path);
    using dogen::dia::test::diagram_serialization_helper;
    const auto i(diagram_serialization_helper::from_xml(s));

    using namespace dogen::annotations::test;
    mock_type_repository_factory rf;
    const auto rp(rf.make());
    auto actual(workflow::execute(i));
    sort_model(actual);

    /*
     * Set to true to rebase. Note that you still need to run the
     * appropriate rebase target afterwards to copy the files across.
     */
    const bool rm(false);
    return asserter::assert_object(rm, expected_path, actual_path, actual);
}

}

using dogen::utility::test_data::yarn_dia;
using dogen::utility::test::contains_checker;

BOOST_AUTO_TEST_SUITE(workflow_tests)

BOOST_AUTO_TEST_CASE(empty_dia_transforms_into_expected_yarn) {
    SETUP_TEST_LOG("empty_dia_transforms_into_expected_yarn");
    const auto i(yarn_dia::expected_empty_dia_xml());
    const auto e(yarn_dia::expected_empty_yarn_xml());
    const auto a(yarn_dia::actual_empty_yarn_xml());
    BOOST_CHECK(test_workflow(i, e, a));
}

BOOST_AUTO_TEST_CASE(two_layers_with_objects_dia_transforms_into_expected_yarn) {
    SETUP_TEST_LOG("two_layers_with_objects_dia_transforms_into_expected_yarn");
    const auto i(yarn_dia::expected_two_layers_with_objects_dia_xml());
    const auto e(yarn_dia::expected_two_layers_with_objects_yarn_xml());
    const auto a(yarn_dia::actual_two_layers_with_objects_yarn_xml());
    BOOST_CHECK(test_workflow(i, e, a));
}

BOOST_AUTO_TEST_CASE(cpp_model_dia_transforms_into_expected_yarn) {
    SETUP_TEST_LOG("cpp_model_dia_transforms_into_expected_yarn");
    const auto i(yarn_dia::expected_cpp_model_dia_xml());
    const auto e(yarn_dia::expected_cpp_model_yarn_xml());
    const auto a(yarn_dia::actual_cpp_model_yarn_xml());
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

BOOST_AUTO_TEST_SUITE_END()
