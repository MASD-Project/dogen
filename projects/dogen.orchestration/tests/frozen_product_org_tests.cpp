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
#include "dogen.utility/types/test_data/frozen_product.hpp"
#include "dogen.utility/types/test_data/cpp_ref_impl_product.hpp"
#include "dogen.utility/types/test_data/csharp_ref_impl_product.hpp"
#include "dogen.orchestration/tests/model_producer.hpp"

namespace  {

const std::string test_module("dogen.orchestration.tests");
const std::string test_suite("frozen_product_org_tests");

}

#ifdef ENABLE_FROZEN_TESTS

using mg = dogen::orchestration::tests::model_producer;
using dogen::utility::test_data::frozen_product;

BOOST_AUTO_TEST_SUITE(frozen_product_org_tests)

BOOST_AUTO_TEST_CASE(dogen_org_produces_expected_model) {
    SETUP_TEST_LOG("dogen_org_produces_expected_model");
    const auto t(frozen_product::input_frozen_org());
    const auto od(frozen_product::project_directory());
    const auto m(mg::apply_physical_model_production(t, od));
    BOOST_CHECK(mg::check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(dogen_physical_org_produces_expected_model) {
    SETUP_TEST_LOG("dogen_physical_org_produces_expected_model");
    const auto t(frozen_product::input_frozen_physical_org());
    const auto od(frozen_product::project_directory());
    const auto m(mg::apply_physical_model_production(t, od));
    BOOST_CHECK(mg::check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(dogen_cli_org_produces_expected_model) {
    SETUP_TEST_LOG("dogen_cli_org_produces_expected_model");
    const auto t(frozen_product::input_frozen_cli_org());
    const auto od(frozen_product::project_directory());
    const auto m(mg::apply_physical_model_production(t, od));
    BOOST_CHECK(mg::check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(dogen_dia_org_produces_expected_model) {
    SETUP_TEST_LOG("dogen_dia_org_produces_expected_model");
    const auto t(frozen_product::input_frozen_dia_org());
    const auto od(frozen_product::project_directory());
    const auto m(mg::apply_physical_model_production(t, od));
    BOOST_CHECK(mg::check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(dogen_org_org_produces_expected_model) {
    SETUP_TEST_LOG("dogen_org_org_produces_expected_model");
    const auto t(frozen_product::input_frozen_org_org());
    const auto od(frozen_product::project_directory());
    const auto m(mg::apply_physical_model_production(t, od));
    BOOST_CHECK(mg::check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(dogen_tracing_org_produces_expected_model) {
    SETUP_TEST_LOG("dogen_tracing_org_produces_expected_model");
    const auto t(frozen_product::input_frozen_tracing_org());
    const auto od(frozen_product::project_directory());
    const auto m(mg::apply_physical_model_production(t, od));
    BOOST_CHECK(mg::check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(dogen_codec_org_produces_expected_model) {
    SETUP_TEST_LOG("frozen_product_org_produces_expected_model");
    const auto t(frozen_product::input_frozen_codec_org());
    const auto od(frozen_product::project_directory());
    const auto m(mg::apply_physical_model_production(t, od));
    BOOST_CHECK(mg::check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(dogen_codec_dia_org_produces_expected_model) {
    SETUP_TEST_LOG("dogen_codec_dia_org_produces_expected_model");
    const auto t(frozen_product::input_frozen_codec_dia_org());
    const auto od(frozen_product::project_directory());
    const auto m(mg::apply_physical_model_production(t, od));
    BOOST_CHECK(mg::check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(dogen_text_org_produces_expected_model) {
    SETUP_TEST_LOG("dogen_text_org_produces_expected_model");
    const auto t(frozen_product::input_frozen_text_org());
    const auto od(frozen_product::project_directory());
    const auto m(mg::apply_physical_model_production(t, od));
    BOOST_CHECK(mg::check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(dogen_logical_org_produces_expected_model) {
    SETUP_TEST_LOG("dogen_logical_org_produces_expected_model");
    const auto t(frozen_product::input_frozen_logical_org());
    const auto od(frozen_product::project_directory());
    const auto m(mg::apply_physical_model_production(t, od));
    BOOST_CHECK(mg::check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(dogen_templating_org_produces_expected_model) {
    SETUP_TEST_LOG("dogen_templating_org_produces_expected_model");
    const auto t(frozen_product::input_frozen_templating_org());
    const auto od(frozen_product::project_directory());
    const auto m(mg::apply_physical_model_production(t, od));
    BOOST_CHECK(mg::check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(dogen_orchestration_org_produces_expected_model) {
    SETUP_TEST_LOG("dogen_orchestration_org_produces_expected_model");
    const auto t(frozen_product::input_frozen_orchestration_org());
    const auto od(frozen_product::project_directory());
    const auto m(mg::apply_physical_model_production(t, od));
    BOOST_CHECK(mg::check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(dogen_utility_org_produces_expected_model) {
    SETUP_TEST_LOG("dogen_utility_org_produces_expected_model");
    const auto t(frozen_product::input_frozen_utility_org());
    const auto od(frozen_product::project_directory());
    const auto m(mg::apply_physical_model_production(t, od));
    BOOST_CHECK(mg::check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(dogen_variability_org_produces_expected_model) {
    SETUP_TEST_LOG("dogen_variability_org_produces_expected_model");
    const auto t(frozen_product::input_frozen_variability_org());
    const auto od(frozen_product::project_directory());
    const auto m(mg::apply_physical_model_production(t, od));
    BOOST_CHECK(mg::check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(dogen_relational_org_produces_expected_model) {
    SETUP_TEST_LOG("dogen_relational_org_produces_expected_model");
    const auto t(frozen_product::input_frozen_relational_org());
    const auto od(frozen_product::project_directory());
    const auto m(mg::apply_physical_model_production(t, od));
    BOOST_CHECK(mg::check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(dogen_identification_org_produces_expected_model) {
    SETUP_TEST_LOG("dogen_identification_org_produces_expected_model");
    const auto t(frozen_product::input_frozen_identification_org());
    const auto od(frozen_product::project_directory());
    const auto m(mg::apply_physical_model_production(t, od));
    BOOST_CHECK(mg::check_for_differences(od, m));
}

BOOST_AUTO_TEST_SUITE_END()

#endif // ENABLE_FROZEN_TESTS
