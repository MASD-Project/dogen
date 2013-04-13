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
#include "dogen/utility/test/xml_serialization_helper.hpp"
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test_data/codegen_tds.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test_data/dia_sml.hpp"
#include "dogen/dia/io/diagram_io.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/dia/serialization/diagram_ser.hpp"
#include "dogen/sml/serialization/model_ser.hpp"
#include "dogen/utility/test/exception_checkers.hpp"
#include "dogen/dia_to_sml/types/workflow.hpp"

using namespace dogen::dia_to_sml;
using dogen::utility::test::asserter;

namespace  {

const std::string test_module("dia_to_sml");
const std::string test_suite("workflow_spec");

bool test_transformer(
    boost::filesystem::path input_path,
    boost::filesystem::path expected_path,
    boost::filesystem::path actual_path) {

    using dogen::utility::test::xml_deserialize;
    const auto i(xml_deserialize<dogen::dia::diagram>(input_path));

    const std::string epp;
    const bool is_target(true);
    const std::string model_name(input_path.stem().string());

    workflow w;
    dogen::sml::model actual(w.execute(i, model_name, epp, is_target));
    return asserter::assert_object(expected_path, actual_path, actual);
}

}

using dogen::utility::test_data::dia_sml;
using dogen::utility::test::contains_checker;

BOOST_AUTO_TEST_SUITE(workflow)

BOOST_AUTO_TEST_CASE(class_in_a_package_dia_transforms_into_expected_sml) {
    SETUP_TEST_LOG("class_in_a_package_dia_transforms_into_expected_sml");
    const auto input_path(dia_sml::expected_class_in_a_package_dia_xml());
    const auto actual_path(dia_sml::actual_class_in_a_package_sml_xml());
    const auto expected_path(dia_sml::expected_class_in_a_package_sml_xml());
    BOOST_CHECK(test_transformer(input_path, expected_path, actual_path));
}

BOOST_AUTO_TEST_SUITE_END()
