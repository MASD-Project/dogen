/* -*- Mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
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
#include <boost/algorithm/string.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/string.hpp>
#include "dogen/utility/serialization/path.hpp"
#include "dogen/sml/serialization/model_ser.hpp"
#include "dogen/utility/test/xml_serialization_helper.hpp"
#include "dogen/utility/test/exception_checkers.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test_data/dia_sml.hpp"
#include "dogen/utility/io/map_io.hpp"
#include "dogen/config/test/mock_settings_factory.hpp"
#include "dogen/cpp/io/file_info_io.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/dia_to_sml/types/workflow.hpp"
#include "dogen/cpp/types/workflow_failure.hpp"
#include "dogen/cpp/types/workflow.hpp"

using namespace dogen::cpp;
using dogen::utility::test::asserter;
using dogen::utility::test_data::dia_sml;

namespace {

const std::string empty;
const std::string test_module("cpp");
const std::string test_suite("workflow_spec");
const std::string package_path("dogen");

using boost::filesystem::path;
bool test_workflow(path t, path e, path a) {

    using dogen::config::test::mock_settings_factory;
    const auto s(mock_settings_factory::build_settings(t, e, package_path));
    using dogen::utility::test::xml_deserialize;
    const auto m(xml_deserialize<dogen::sml::model>(t));

    workflow w(m, s.cpp());
    auto actual_full_path(w.execute());
    std::map<std::string, std::string> actual;
    for (auto& pair : actual_full_path) {
        const auto base(dia_sml::actual());
        auto key(pair.first.string());
        using boost::replace_first;
        replace_first(key, base.string(), empty);
        actual.insert(std::make_pair(key, pair.second));
    }
    return asserter::assert_object(e, a, actual);
}

}

using dogen::utility::test::contains_checker;

BOOST_AUTO_TEST_SUITE(workflow)

BOOST_AUTO_TEST_CASE(class_in_a_package_model_generates_expected_code) {
    SETUP_TEST_LOG("class_in_a_package_model_generates_expected_code");

    const auto i(dia_sml::expected_class_in_a_package_sml_xml());
    const auto a(dia_sml::actual_class_in_a_package_cpp_xml());
    const auto e(dia_sml::expected_class_in_a_package_cpp_xml());

    BOOST_CHECK(test_workflow(i, e, a));
}

BOOST_AUTO_TEST_SUITE_END()
