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
#include <memory>
#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_monitor.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/replace.hpp>
#include "dogen/utility/test_data/validating_resolver.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/utility/test/macros.hpp"
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test_data/yarn_dia.hpp"
#include "dogen/utility/test_data/yarn_json.hpp"
#include "dogen/utility/test_data/yarn_upsilon.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/dia/io/diagram_io.hpp"
#include "dogen/knit/types/workflow_error.hpp"
#include "dogen/options/test/mock_options_factory.hpp"
#include "dogen/options/types/knitting_options.hpp"
#include "dogen/knit/types/workflow.hpp"
#include "dogen/yarn/types/model.hpp"
#include "dogen/yarn/io/model_io.hpp"
#include "dogen/dia/serialization/diagram_ser.hpp"
#include "dogen/yarn/serialization/model_ser.hpp"
#include "dogen/dia/test/dia_file_asserter.hpp"
#include "dogen/yarn/test/yarn_file_asserter.hpp"
#include "dogen/utility/test/exception_checkers.hpp"

/*
 * Comment these out as required if testing only one frontend.
 */
#define ENABLE_DIA_TESTS
#define ENABLE_JSON_TESTS
#define ENABLE_CSHARP_TESTS
#define ENABLE_UPSILON_TESTS

using dogen::utility::test_data::yarn_dia;
using dogen::utility::test_data::yarn_json;
using dogen::utility::test_data::yarn_upsilon;

namespace  {

const std::string empty;
const std::string empty_module_path;
const std::string test_module("knit");
const std::string test_suite("workflow_tests");

const std::string expected("/expected");
const std::string actual_dia_dir("/actual.dia");
const std::string actual_json_dir("/actual.json");
const std::string actual_upsilon_dir("/actual.upsilon");

const std::string domain_facet_must_be_enabled("Domain facet must be enabled");
const std::string dia_invalid_name("Dia object name is empty");

bool generate_and_diff(const std::string& model_name,
    const boost::filesystem::path& target,
    const std::string& actual_dir) {
    using dogen::utility::test_data::validating_resolver;
    const auto expected(validating_resolver::resolve(model_name + ::expected));
    const auto actual(validating_resolver::resolve(model_name + actual_dir));

    /*
     * Ensure the actual directory is empty before we run the
     * tests. Note that the actual directory is guaranteed to exist as
     * it is created by the scripts. This is a very roundabout way of
     * doing things, but works for now.
     */
    boost::filesystem::remove_all(actual);
    boost::filesystem::create_directory(actual);

    using dogen::options::test::mock_options_factory;
    const auto ko(mock_options_factory::make_knitting_options(target, actual));

    dogen::knit::workflow w(ko);
    w.execute();

    using dogen::utility::test::asserter;
    return asserter::assert_directory(expected, actual);
}

bool generate_and_diff(const boost::filesystem::path& target,
    const std::string& actual_dir) {
    const auto name(target.stem().string());
    return generate_and_diff(name, target, actual_dir);
}

}

using dogen::utility::test::contains_checker;
using dogen::knit::workflow_error;

BOOST_AUTO_TEST_SUITE(workflow_tests)

#ifdef ENABLE_DIA_TESTS

BOOST_AUTO_TEST_CASE(cpp_model_generates_expected_code_dia) {
    SETUP_TEST_LOG("cpp_model_generates_expected_code_dia");
    const auto dia(yarn_dia::input_cpp_model_dia());
    BOOST_CHECK(generate_and_diff(dia, actual_dia_dir));
}

BOOST_AUTO_TEST_CASE(disable_facet_folders_generates_expected_code_dia) {
    SETUP_TEST_LOG("disable_facet_folders_generates_expected_code_dia");
    const auto dia(yarn_dia::input_disable_facet_folders_dia());
    BOOST_CHECK(generate_and_diff(dia, actual_dia_dir));
}

BOOST_AUTO_TEST_CASE(disable_cmakelists_generates_expected_code_dia) {
    SETUP_TEST_LOG("disable_cmakelists_generates_expected_code_dia");
    const auto dia(yarn_dia::input_disable_cmakelists_dia());
    BOOST_CHECK(generate_and_diff(dia, actual_dia_dir));
}

BOOST_AUTO_TEST_CASE(enable_facet_types_generates_expected_code_dia) {
    SETUP_TEST_LOG("enable_facet_types_generates_expected_code_dia");
    const auto dia(yarn_dia::input_enable_facet_types_dia());
    BOOST_CHECK(generate_and_diff(dia, actual_dia_dir));
}

BOOST_AUTO_TEST_CASE(enable_facet_hash_generates_expected_code_dia) {
    SETUP_TEST_LOG("enable_facet_hash_generates_expected_cod_diae");
    const auto dia(yarn_dia::input_enable_facet_hash_dia());
    BOOST_CHECK(generate_and_diff(dia, actual_dia_dir));
}

BOOST_AUTO_TEST_CASE(enable_facet_serialization_generates_expected_code_dia) {
    SETUP_TEST_LOG("enable_facet_serialization_generates_expected_code_dia");
    const auto dia(yarn_dia::input_enable_facet_serialization_dia());
    BOOST_CHECK(generate_and_diff(dia, actual_dia_dir));
}

BOOST_AUTO_TEST_CASE(enable_facet_io_generates_expected_code_dia) {
    SETUP_TEST_LOG("enable_facet_io_generates_expected_code_dia");
    const auto dia(yarn_dia::input_enable_facet_io_dia());
    BOOST_CHECK(generate_and_diff(dia, actual_dia_dir));
}

BOOST_AUTO_TEST_CASE(two_empty_layers_model_does_not_generate_code_dia) {
    SETUP_TEST_LOG("two_empty_layers_model_does_not_generate_code_dia");
    const auto dia(yarn_dia::input_two_empty_layers_dia());
    BOOST_CHECK(generate_and_diff(dia, actual_dia_dir));
}

BOOST_AUTO_TEST_CASE(class_without_name_model_throws) {
    SETUP_TEST_LOG("class_without_name_model_throws");
    const auto target(yarn_dia::input_class_without_name_dia());
    contains_checker<std::exception> c(dia_invalid_name);
    BOOST_CHECK_EXCEPTION(generate_and_diff(target, actual_dia_dir),
        std::exception, c);
}

BOOST_AUTO_TEST_CASE(empty_model_generates_expected_code_dia) {
    SETUP_TEST_LOG("empty_model_generates_expected_code_dia");
    const auto dia(yarn_dia::input_empty_dia());
    BOOST_CHECK(generate_and_diff(dia, actual_dia_dir));
}

BOOST_AUTO_TEST_CASE(compressed_model_generates_expected_code_dia) {
    SETUP_TEST_LOG("compressed_model_generates_expected_code_dia");
    const auto dia(yarn_dia::input_compressed_dia());
    BOOST_CHECK(generate_and_diff(dia, actual_dia_dir));
}

BOOST_AUTO_TEST_CASE(two_layers_with_objects_model_generates_expected_code_dia) {
    SETUP_TEST_LOG("two_layers_with_objects_model_generates_expected_code_dia");
    const auto dia(yarn_dia::input_two_layers_with_objects_dia());
    BOOST_CHECK(generate_and_diff(dia, actual_dia_dir));
}

BOOST_AUTO_TEST_CASE(std_model_generates_expected_code_dia) {
    SETUP_TEST_LOG("std_model_generates_expected_code_dia");
    const auto dia(yarn_dia::input_std_model_dia());
    BOOST_CHECK(generate_and_diff(dia, actual_dia_dir));
}

BOOST_AUTO_TEST_CASE(boost_model_generates_expected_code_dia) {
    SETUP_TEST_LOG("boost_model_generates_expected_code_dia");
    const auto dia(yarn_dia::input_boost_model_dia());
    BOOST_CHECK(generate_and_diff(dia, actual_dia_dir));
}

BOOST_AUTO_TEST_CASE(package_without_name_model_throws) {
    SETUP_TEST_LOG("package_without_name_model_throws");
    const auto dia(yarn_dia::input_package_without_name_dia());
    contains_checker<std::exception> c(dia_invalid_name);
    BOOST_CHECK_EXCEPTION(generate_and_diff(dia, actual_dia_dir),
        std::exception, c);
}

BOOST_AUTO_TEST_CASE(all_path_and_directory_settings_generates_expected_code_dia) {
    SETUP_TEST_LOG("all_path_and_directory_settings_generates_expected_code_dia");
    const auto dia(yarn_dia::input_all_path_and_directory_settings_dia());
    BOOST_CHECK(generate_and_diff(dia, actual_dia_dir));
}

#ifdef ENABLE_CSHARP_TESTS

BOOST_AUTO_TEST_CASE(csharp_model_generates_expected_code_dia) {
    SETUP_TEST_LOG("csharp_model_generates_expected_code_dia");
    const auto dia(yarn_dia::input_csharp_model_dia());
    BOOST_CHECK(generate_and_diff(dia, actual_dia_dir));
}

#endif // ENABLE_CSHARP_TESTS

#endif // ENABLE_DIA_TESTS

#ifdef ENABLE_JSON_TESTS

BOOST_AUTO_TEST_CASE(cpp_model_generates_expected_code_json) {
    SETUP_TEST_LOG("cpp_model_generates_expected_code_json");
    const auto json(yarn_json::input_cpp_model_json());
    BOOST_CHECK(generate_and_diff(json, actual_json_dir));
}

BOOST_AUTO_TEST_CASE(disable_facet_folders_generates_expected_code_json) {
    SETUP_TEST_LOG("disable_facet_folders_generates_expected_code_json");
    const auto json(yarn_json::input_disable_facet_folders_json());
    BOOST_CHECK(generate_and_diff(json, actual_json_dir));
}

BOOST_AUTO_TEST_CASE(disable_cmakelists_generates_expected_code_json) {
    SETUP_TEST_LOG("disable_cmakelists_generates_expected_code_json");
    const auto json(yarn_json::input_disable_cmakelists_json());
    BOOST_CHECK(generate_and_diff(json, actual_json_dir));
}

BOOST_AUTO_TEST_CASE(enable_facet_types_generates_expected_code_json) {
    SETUP_TEST_LOG("enable_facet_types_generates_expected_code_json");
    const auto json(yarn_json::input_enable_facet_types_json());
    BOOST_CHECK(generate_and_diff(json, actual_json_dir));
}

BOOST_AUTO_TEST_CASE(enable_facet_hash_generates_expected_code_json) {
    SETUP_TEST_LOG("enable_facet_hash_generates_expected_code_json");
    const auto json(yarn_json::input_enable_facet_hash_json());
    BOOST_CHECK(generate_and_diff(json, actual_json_dir));
}

BOOST_AUTO_TEST_CASE(enable_facet_serialization_generates_expected_code_json) {
    SETUP_TEST_LOG("enable_facet_serialization_generates_expected_code_json");
    const auto json(yarn_json::input_enable_facet_serialization_json());
    BOOST_CHECK(generate_and_diff(json, actual_json_dir));
}

BOOST_AUTO_TEST_CASE(enable_facet_io_generates_expected_code_json) {
    SETUP_TEST_LOG("enable_facet_io_generates_expected_code_json");
    const auto json(yarn_json::input_enable_facet_io_json());
    BOOST_CHECK(generate_and_diff(json, actual_json_dir));
}

BOOST_AUTO_TEST_CASE(empty_model_generates_expected_code_json) {
    SETUP_TEST_LOG("empty_model_generates_expected_code_json");
    const auto json(yarn_json::input_empty_json());
    BOOST_CHECK(generate_and_diff(json, actual_json_dir));
}

BOOST_AUTO_TEST_CASE(compressed_model_generates_expected_code_json) {
    SETUP_TEST_LOG("compressed_model_generates_expected_code_json");
    const auto json(yarn_json::input_compressed_json());
    BOOST_CHECK(generate_and_diff(json, actual_json_dir));
}

BOOST_AUTO_TEST_CASE(two_layers_with_objects_model_generates_expected_code_json) {
    SETUP_TEST_LOG("two_layers_with_objects_model_generates_expected_code_json");
    const auto json(yarn_json::input_two_layers_with_objects_json());
    BOOST_CHECK(generate_and_diff(json, actual_json_dir));
}

BOOST_AUTO_TEST_CASE(std_model_generates_expected_code_json) {
    SETUP_TEST_LOG("std_model_generates_expected_code_json");
    const auto json(yarn_json::input_std_model_json());
    BOOST_CHECK(generate_and_diff(json, actual_json_dir));
}

BOOST_AUTO_TEST_CASE(boost_model_generates_expected_code_json) {
    SETUP_TEST_LOG("boost_model_generates_expected_code_json");
    const auto json(yarn_json::input_boost_model_json());
    BOOST_CHECK(generate_and_diff(json, actual_json_dir));
}

BOOST_AUTO_TEST_CASE(all_path_and_directory_settings_generates_expected_code_json) {
    SETUP_TEST_LOG("all_path_and_directory_settings_generates_expected_code_json");
    const auto dia(yarn_json::input_all_path_and_directory_settings_json());
    BOOST_CHECK(generate_and_diff(dia, actual_dia_dir));
}

#ifdef ENABLE_CSHARP_TESTS

BOOST_AUTO_TEST_CASE(csharp_model_generates_expected_code_json) {
    SETUP_TEST_LOG("csharp_model_generates_expected_code_json");
    const auto dia(yarn_json::input_csharp_model_json());
    BOOST_CHECK(generate_and_diff(dia, actual_json_dir));
}

#endif // ENABLE_CSHARP_TESTS

#endif // ENABLE_JSON_TESTS

BOOST_AUTO_TEST_CASE(upsilon_model_generates_expected_code) {
    SETUP_TEST_LOG("upsilon_model_generates_expected_code");
    const auto upsilon(yarn_upsilon::input_zeta_model_configuration_xml());
    BOOST_CHECK(generate_and_diff("Zeta", upsilon, actual_upsilon_dir));
}

BOOST_AUTO_TEST_SUITE_END()
