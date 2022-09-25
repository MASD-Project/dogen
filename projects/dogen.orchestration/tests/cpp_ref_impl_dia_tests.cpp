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
const std::string test_suite("cpp_ref_impl_dia_tests");

}

#ifdef ENABLE_CPP_REF_IMPL_TESTS

using dogen::orchestration::tests::model_producer;
using dogen::utility::test_data::cpp_ref_impl_product;

BOOST_AUTO_TEST_SUITE(cpp_ref_impl_dia_tests)

BOOST_AUTO_TEST_CASE(cpp_ref_impl_boost_model_dia_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_boost_model_dia_produces_expected_model");
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_boost_model_dia());
    const auto od(cpp_ref_impl_product::project_directory());
    model_producer mp;
    const auto m(mp.apply_physical_model_production(t, od));
    BOOST_CHECK(mp.check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_cpp_98_dia_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_cpp_98_dia_produces_expected_model");
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_cpp_98_dia());
    const auto od(cpp_ref_impl_product::project_directory());
    model_producer mp;
    const auto m(mp.apply_physical_model_production(t, od));
    BOOST_CHECK(mp.check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_cpp_model_dia_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_cpp_model_dia_produces_expected_model");
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_cpp_model_dia());
    const auto od(cpp_ref_impl_product::project_directory());
    model_producer mp;
    const auto m(mp.apply_physical_model_production(t, od));
    BOOST_CHECK(mp.check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_directory_settings_dia_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_directory_settings_dia_produces_expected_model");
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_directory_settings_dia());
    const auto od(cpp_ref_impl_product::project_directory());
    model_producer mp;
    const auto m(mp.apply_physical_model_production(t, od));
    BOOST_CHECK(mp.check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_disable_cmakelists_dia_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_disable_cmakelists_dia_produces_expected_model");
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_disable_cmakelists_dia());
    const auto od(cpp_ref_impl_product::project_directory());
    model_producer mp;
    const auto m(mp.apply_physical_model_production(t, od));
    BOOST_CHECK(mp.check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_disable_facet_folders_dia_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_disable_facet_folders_dia_produces_expected_model");
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_disable_facet_folders_dia());
    const auto od(cpp_ref_impl_product::project_directory());
    model_producer mp;
    const auto m(mp.apply_physical_model_production(t, od));
    BOOST_CHECK(mp.check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_enable_facet_hash_dia_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_enable_facet_hash_dia_produces_expected_model");
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_enable_facet_hash_dia());
    const auto od(cpp_ref_impl_product::project_directory());
    model_producer mp;
    const auto m(mp.apply_physical_model_production(t, od));
    BOOST_CHECK(mp.check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_enable_facet_io_dia_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_enable_facet_io_dia_produces_expected_model");
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_enable_facet_io_dia());
    const auto od(cpp_ref_impl_product::project_directory());
    model_producer mp;
    const auto m(mp.apply_physical_model_production(t, od));
    BOOST_CHECK(mp.check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_enable_facet_serialization_dia_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_enable_facet_serialization_dia_produces_expected_model");
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_enable_facet_serialization_dia());
    const auto od(cpp_ref_impl_product::project_directory());
    model_producer mp;
    const auto m(mp.apply_physical_model_production(t, od));
    BOOST_CHECK(mp.check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_enable_facet_types_dia_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_enable_facet_types_dia_produces_expected_model");
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_enable_facet_types_dia());
    const auto od(cpp_ref_impl_product::project_directory());
    model_producer mp;
    const auto m(mp.apply_physical_model_production(t, od));
    BOOST_CHECK(mp.check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_flat_directory_mode_dia_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_flat_directory_mode_dia_produces_expected_model");
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_flat_directory_mode_dia());
    const auto od(cpp_ref_impl_product::project_directory());
    model_producer mp;
    const auto m(mp.apply_physical_model_production(t, od));
    BOOST_CHECK(mp.check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_lam_model_dia_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_lam_model_dia_produces_expected_model");
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_lam_model_dia());
    const auto od(cpp_ref_impl_product::project_directory());
    model_producer mp;
    const auto m(mp.apply_physical_model_production(t, od));
    BOOST_CHECK(mp.check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_northwind_dia_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_northwind_dia_produces_expected_model");
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_northwind_dia());
    const auto od(cpp_ref_impl_product::project_directory());
    model_producer mp;
    const auto m(mp.apply_physical_model_production(t, od));
    BOOST_CHECK(mp.check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_split_project_dia_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_split_project_dia_produces_expected_model");
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_split_project_dia());
    const auto od(cpp_ref_impl_product::project_directory());
    model_producer mp;
    const auto m(mp.apply_physical_model_production(t, od));
    BOOST_CHECK(mp.check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_std_model_dia_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_std_model_dia_produces_expected_model");
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_std_model_dia());
    const auto od(cpp_ref_impl_product::project_directory());
    model_producer mp;
    const auto m(mp.apply_physical_model_production(t, od));
    BOOST_CHECK(mp.check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_two_layers_with_objects_dia_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_two_layers_with_objects_dia_produces_expected_model");
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_two_layers_with_objects_dia());
    const auto od(cpp_ref_impl_product::project_directory());
     model_producer mp;
    const auto m(mp.apply_physical_model_production(t, od));
    BOOST_CHECK(mp.check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_delete_extra_dia_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_delete_extra_dia_produces_expected_model");
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_delete_extra_dia());
    const auto od(cpp_ref_impl_product::project_directory());
    model_producer mp;
    const auto m(mp.apply_physical_model_production(t, od));
    BOOST_CHECK(mp.check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_force_write_dia_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_two_layers_with_objects_dia_produces_expected_model");
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_force_write_dia());
    const auto od(cpp_ref_impl_product::project_directory());
    model_producer mp;
    const auto m(mp.apply_physical_model_production(t, od));
    BOOST_CHECK(mp.check_for_force_write(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_ignore_extra_dia_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_ignore_extra_dia_produces_expected_model");
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_ignore_extra_dia());
    const auto od(cpp_ref_impl_product::project_directory());
    model_producer mp;
    const auto m(mp.apply_physical_model_production(t, od));
    BOOST_CHECK(mp.check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_out_of_sync_dia_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_out_of_sync_dia_produces_expected_model");
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_out_of_sync_dia());
    const auto od(cpp_ref_impl_product::project_directory());
    model_producer mp;
    const auto m(mp.apply_physical_model_production(t, od));
    BOOST_CHECK(mp.check_out_of_sync(od, m));
}

BOOST_AUTO_TEST_SUITE_END()

#endif // ENABLE_CPP_REF_IMPL_TESTS
