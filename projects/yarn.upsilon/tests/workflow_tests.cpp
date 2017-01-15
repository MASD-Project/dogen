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
#include <istream>
#include <fstream>
#include <sstream>
#include <boost/test/unit_test.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test_data/yarn_upsilon.hpp"
#include "dogen/utility/test/xml_serialization_helper.hpp"
#include "dogen/annotations/test/mock_type_repository_factory.hpp"
#include "dogen/upsilon/serialization/registrar_ser.hpp"
#include "dogen/yarn/serialization/registrar_ser.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"
#include "dogen/yarn/io/intermediate_model_io.hpp"
#include "dogen/yarn/serialization/intermediate_model_ser.hpp"
#include "dogen/yarn.upsilon/types/workflow.hpp"
#include "dogen/upsilon/serialization/model_ser.hpp"

template<typename Archive> void register_types(Archive& ar) {
    dogen::yarn::register_types<Archive>(ar);
}

using dogen::utility::test::asserter;

namespace {

const std::string empty;
const std::string test_module("yarn.upsilon");
const std::string test_suite("workflow_tests");

dogen::upsilon::model from_xml(std::istream& s) {
    boost::archive::xml_iarchive a(s);
    dogen::upsilon::register_types(a);
    dogen::upsilon::model r;
    a & boost::serialization::make_nvp("model", r);
    return r;
}

}

BOOST_AUTO_TEST_SUITE(workflow_tests)

BOOST_AUTO_TEST_CASE(test_data_mode_transforms_into_expected_yarn) {
    SETUP_TEST_LOG("test_data_mode_transforms_into_expected_yarn");

    using dogen::utility::test_data::yarn_upsilon;
    const auto input_path(yarn_upsilon::expected_test_model_upsilon_xml());

    boost::filesystem::ifstream s(input_path);
    const auto input(from_xml(s));

    const std::string model_name(input_path.stem().string());

    using namespace dogen::annotations::test;
    mock_type_repository_factory rf;
    const auto rp(rf.make());
    dogen::yarn::upsilon::workflow w;
    dogen::yarn::intermediate_model actual(w.execute(input));

    const auto expected_path(yarn_upsilon::expected_test_model_yarn_xml());
    const auto actual_path(yarn_upsilon::actual_test_model_yarn_xml());

    BOOST_CHECK(asserter::assert_object(expected_path, actual_path, actual));
}

BOOST_AUTO_TEST_SUITE_END()
