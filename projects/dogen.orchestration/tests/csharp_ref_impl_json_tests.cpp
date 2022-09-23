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
#include <regex>
#include <sstream>
#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_monitor.hpp>
#include "dogen.utility/types/test/logging.hpp"
#include "dogen.utility/types/test_data/dogen_product.hpp"
#include "dogen.utility/types/test_data/cpp_ref_impl_product.hpp"
#include "dogen.utility/types/test_data/csharp_ref_impl_product.hpp"
#include "dogen.orchestration/tests/model_producer.hpp"

namespace  {

const std::string test_module("dogen.orchestration.tests");
const std::string test_suite("csharp_ref_impl_json_tests");

}

using dogen::orchestration::tests::model_producer;
using dogen::utility::test_data::csharp_ref_impl_product;

BOOST_AUTO_TEST_SUITE(csharp_ref_impl_json_tests)

#ifdef ENABLE_CSHARP_REF_IMPL_TESTS

BOOST_AUTO_TEST_CASE(csharprefimpl_csharpmodel_json_produces_expected_model) {
    SETUP_TEST_LOG("csharprefimpl_csharpmodel_json_produces_expected_model");
    const auto t(csharp_ref_impl_product::input_csharprefimpl_csharpmodel_json());
    const auto od(csharp_ref_impl_product::project_directory());
    model_producer mp(true/*read_environment_variables*/);
    const auto m(mp.apply_physical_model_production(t, od));
    BOOST_CHECK(mp.check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(csharprefimpl_directorysettings_json_produces_expected_model) {
    SETUP_TEST_LOG("csharprefimpl_directorysettings_json_produces_expected_model");
    const auto t(csharp_ref_impl_product::input_csharprefimpl_directory_settings_json());
    const auto od(csharp_ref_impl_product::project_directory());
    model_producer mp(true/*read_environment_variables*/);
    const auto m(mp.apply_physical_model_production(t, od));
    BOOST_CHECK(mp.check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(csharprefimpl_lammodel_json_produces_expected_model) {
    SETUP_TEST_LOG("csharprefimpl_lammodel_json_produces_expected_model");
    const auto t(csharp_ref_impl_product::input_csharprefimpl_lammodel_json());
    const auto od(csharp_ref_impl_product::project_directory());
    model_producer mp(true/*read_environment_variables*/);
    const auto m(mp.apply_physical_model_production(t, od));
    BOOST_CHECK(mp.check_for_differences(od, m));
}

#endif // ENABLE_CSHARP_REF_IMPL_TESTS

BOOST_AUTO_TEST_SUITE_END()
