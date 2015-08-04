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
#include <memory>
#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_monitor.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/replace.hpp>
#include "dogen/utility/test_data/resolver.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/utility/test/macros.hpp"
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test_data/tack_dia.hpp"
#include "dogen/utility/test_data/codegen_tds.hpp"
#include "dogen/utility/test_data/empty_tds.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/dia/io/diagram_io.hpp"
#include "dogen/knit/types/workflow_error.hpp"
#include "dogen/config/test/mock_options_factory.hpp"
#include "dogen/config/types/knitting_options.hpp"
#include "dogen/knit/types/workflow.hpp"
#include "dogen/tack/types/model.hpp"
#include "dogen/tack/io/model_io.hpp"
#include "dogen/dia/serialization/diagram_ser.hpp"
#include "dogen/tack/serialization/model_ser.hpp"
#include "dogen/dia/test/dia_file_asserter.hpp"
#include "dogen/tack/test/tack_file_asserter.hpp"
#include "dogen/utility/test/exception_checkers.hpp"

using dogen::utility::test_data::tack_dia;

namespace  {

const std::string empty;
const std::string empty_module_path;
const std::string test_module("knit");
const std::string test_suite("workflow_spec");
const std::string module_path("dogen::test_models");
const std::string domain_facet_must_be_enabled("Domain facet must be enabled");
const std::string io_facet_and_integrated_io_error(
    "Integrated IO cannot be used with the IO facet");
const std::string dia_invalid_name("Dia object name is empty");

dogen::config::knitting_options
default_mock_options(dogen::utility::test_data::codegen_tds tds) {
    using dogen::config::test::mock_options_factory;
    return mock_options_factory::make_knitting_options(
        tds.target(), tds.actual(), module_path);
}

dogen::config::knitting_options empty_tds_mock_options() {
    typedef dogen::utility::test_data::empty_tds tds;
    using dogen::config::test::mock_options_factory;
    return mock_options_factory::make_knitting_options(
        tds::target(),
        tds::actual_src(),
        tds::actual_include(),
        empty_module_path);
}

template<typename OptionsFactoryFunction>
bool check_code_generation(boost::filesystem::path target,
    OptionsFactoryFunction sff) {
    using dogen::utility::test_data::codegen_tds;
    codegen_tds tds(target);

    dogen::knit::workflow w(sff(tds));
    w.execute();

    using dogen::utility::test::asserter;
    return asserter::assert_directory(tds.expected(), tds.actual());
}

bool check_code_generation(boost::filesystem::path target) {
    return check_code_generation(target, default_mock_options);
}

}

using dogen::utility::test::contains_checker;
using dogen::knit::workflow_error;

BOOST_AUTO_TEST_SUITE(workflow)

BOOST_IGNORE_AUTO_TEST_CASE(disabling_cpp_backend_results_in_no_cpp_output) {
    SETUP_TEST_LOG("disabling_cpp_backend_results_in_no_cpp_output");
    auto s(empty_tds_mock_options());
    auto cs(s.cpp());
    s.cpp(cs);
    // FIXME implement in terms of meta-data.

    dogen::knit::workflow w(s);
    w.execute();

    using dogen::utility::test::asserter;
    typedef dogen::utility::test_data::empty_tds tds;
    BOOST_CHECK(asserter::assert_directory(tds::expected(), tds::actual()));
}

BOOST_AUTO_TEST_CASE(disable_full_ctor_generates_expected_code) {
    SETUP_TEST_LOG("disable_full_ctor_generates_expected_code");
    using dogen::config::knitting_options;
    using dogen::utility::test_data::codegen_tds;
    auto lambda([](codegen_tds tds) -> knitting_options {
            auto s(default_mock_options(tds));
            auto cs(s.cpp());
            cs.split_project(false);
            s.cpp(cs);
            return s;
        });

    const auto t(tack_dia::input_disable_full_ctor_dia());
    BOOST_CHECK(check_code_generation(t, lambda));
}

BOOST_AUTO_TEST_CASE(disable_facet_folders_generates_expected_code) {
    SETUP_TEST_LOG("disable_facet_folders_generates_expected_code");
    using dogen::config::knitting_options;
    using dogen::utility::test_data::codegen_tds;
    auto lambda([](codegen_tds tds) -> knitting_options {
            auto s(default_mock_options(tds));
            auto cs(s.cpp());
            s.cpp(cs);
            return s;
        });

    const auto t(tack_dia::input_disable_facet_folders_dia());
    BOOST_CHECK(check_code_generation(t, lambda));
}

BOOST_AUTO_TEST_CASE(disable_cmakelists_generates_expected_code) {
    SETUP_TEST_LOG("disable_cmakelists_generates_expected_code");
    using dogen::config::knitting_options;
    using dogen::utility::test_data::codegen_tds;
    auto lambda([](codegen_tds tds) -> knitting_options {
            auto s(default_mock_options(tds));
            auto cs(s.cpp());
            cs.disable_cmakelists(true);
            s.cpp(cs);
            return s;
        });

    const auto t(tack_dia::input_disable_cmakelists_dia());
    BOOST_CHECK(check_code_generation(t, lambda));
}

BOOST_IGNORE_AUTO_TEST_CASE(not_enabling_facet_domain_throws) {
    SETUP_TEST_LOG("not_enabling_facet_domain_throws");
    const auto t(tack_dia::input_enable_facet_hash_dia());

    using dogen::utility::test_data::codegen_tds;
    codegen_tds tds(t);

    dogen::knit::workflow w(default_mock_options(tds));
    contains_checker<workflow_error> c(domain_facet_must_be_enabled);
    BOOST_CHECK_EXCEPTION(w.execute(), workflow_error, c);
}

BOOST_AUTO_TEST_CASE(enable_facet_domain_generates_expected_code) {
    SETUP_TEST_LOG("enable_facet_domain_generates_expected_code");
    using dogen::config::knitting_options;
    using dogen::utility::test_data::codegen_tds;
    auto lambda([](codegen_tds tds) -> knitting_options {
            return default_mock_options(tds);
        });

    const auto t(tack_dia::input_enable_facet_domain_dia());
    BOOST_CHECK(check_code_generation(t, lambda));
}

BOOST_AUTO_TEST_CASE(enable_facet_hash_generates_expected_code) {
    SETUP_TEST_LOG("enable_facet_hash_generates_expected_code");
    using dogen::config::knitting_options;
    using dogen::utility::test_data::codegen_tds;
    auto lambda([](codegen_tds tds) -> knitting_options {
            return default_mock_options(tds);
        });

    const auto t(tack_dia::input_enable_facet_hash_dia());
    BOOST_CHECK(check_code_generation(t, lambda));
}

BOOST_AUTO_TEST_CASE(enable_facet_serialization_generates_expected_code) {
    SETUP_TEST_LOG("enable_facet_serialization_generates_expected_code");
    using dogen::config::knitting_options;
    using dogen::utility::test_data::codegen_tds;
    auto lambda([](codegen_tds tds) -> knitting_options {
            return default_mock_options(tds);
        });

    const auto t(tack_dia::input_enable_facet_serialization_dia());
    BOOST_CHECK(check_code_generation(t, lambda));
}

BOOST_AUTO_TEST_CASE(enable_facet_io_generates_expected_code) {
    SETUP_TEST_LOG("enable_facet_io_generates_expected_code");
    using dogen::config::knitting_options;
    using dogen::utility::test_data::codegen_tds;
    auto lambda([](codegen_tds tds) -> knitting_options {
            return default_mock_options(tds);
        });

    const auto t(tack_dia::input_enable_facet_io_dia());
    BOOST_CHECK(check_code_generation(t, lambda));
}

BOOST_IGNORE_AUTO_TEST_CASE(enabling_facet_io_and_using_integrated_io_throws) {
    SETUP_TEST_LOG("enabling_facet_io_and_using_integrated_io_throws");
    const auto t(tack_dia::input_enable_facet_io_dia());

    using dogen::utility::test_data::codegen_tds;
    codegen_tds tds(t);

    // FIXME: reimplement using meta-data.
    dogen::knit::workflow w(default_mock_options(tds));
    contains_checker<workflow_error> c(io_facet_and_integrated_io_error);
    BOOST_CHECK_EXCEPTION(w.execute(), workflow_error, c);
}

BOOST_AUTO_TEST_CASE(class_in_a_package_model_generates_expected_code) {
    SETUP_TEST_LOG("class_in_a_package_model_generates_expected_code");
    BOOST_CHECK(check_code_generation(tack_dia::input_class_in_a_package_dia()));
}

BOOST_AUTO_TEST_CASE(two_empty_layers_model_does_not_generate_code) {
    SETUP_TEST_LOG("two_empty_layers_model_does_not_generate_code");
    const auto t(tack_dia::input_two_empty_layers_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_AUTO_TEST_CASE(class_without_name_model_throws) {
    SETUP_TEST_LOG("class_without_name_model_throws");
    const auto t(tack_dia::input_class_without_name_dia());

    using dogen::utility::test_data::codegen_tds;
    codegen_tds tds(t);

    auto s(default_mock_options(tds));
    dogen::knit::workflow w(s);
    contains_checker<std::exception> c(dia_invalid_name);
    BOOST_CHECK_EXCEPTION(w.execute(), std::exception, c);
}

BOOST_AUTO_TEST_CASE(empty_model_generates_expected_code) {
    SETUP_TEST_LOG("empty_model_generates_expected_code");
    const auto t(tack_dia::input_empty_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_AUTO_TEST_CASE(empty_package_model_does_not_generate_code) {
    SETUP_TEST_LOG("empty_package_model_does_not_generate_code");
    const auto t(tack_dia::input_empty_package_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_AUTO_TEST_CASE(classes_inout_package_model_generates_expected_code) {
    SETUP_TEST_LOG("classes_inout_package_model_generates_expected_code");
    const auto t(tack_dia::input_classes_inout_package_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_AUTO_TEST_CASE(class_without_attributes_model_generates_expected_code) {
    SETUP_TEST_LOG("class_without_attributes_model_generates_expected_code");
    const auto t(tack_dia::input_class_without_attributes_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_AUTO_TEST_CASE(class_without_package_model_generates_expected_code) {
    SETUP_TEST_LOG("class_without_package_model_generates_expected_code");
    const auto t(tack_dia::input_class_without_package_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_AUTO_TEST_CASE(stand_alone_class_model_generates_expected_code) {
    SETUP_TEST_LOG("stand_alone_class_model_generates_expected_code");
    const auto t(tack_dia::input_stand_alone_class_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_AUTO_TEST_CASE(classes_in_a_package_model_generates_expected_code) {
    SETUP_TEST_LOG("classes_in_a_package_model_generates_expected_code");
    const auto t(tack_dia::input_classes_in_a_package_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_AUTO_TEST_CASE(classes_without_package_model_generates_expected_code) {
    SETUP_TEST_LOG("classes_without_package_model_generates_expected_code");
    const auto t(tack_dia::input_classes_without_package_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_AUTO_TEST_CASE(compressed_model_generates_expected_code) {
    SETUP_TEST_LOG("compressed_model_generates_expected_code");
    const auto t(tack_dia::input_compressed_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_AUTO_TEST_CASE(two_layers_with_objects_model_generates_expected_code) {
    SETUP_TEST_LOG("two_layers_with_objects_model_generates_expected_code");
    const auto t(tack_dia::input_two_layers_with_objects_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_AUTO_TEST_CASE(trivial_inheritance_model_generates_expected_code) {
    SETUP_TEST_LOG("trivial_inheritance_model_generates_expected_code");
    const auto t(tack_dia::input_trivial_inheritance_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_AUTO_TEST_CASE(trivial_association_model_generates_expected_code) {
    SETUP_TEST_LOG("trivial_association_model_generates_expected_code");
    const auto t(tack_dia::input_trivial_association_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_AUTO_TEST_CASE(comments_model_generates_expected_code) {
    SETUP_TEST_LOG("comments_model_generates_expected_code");
    const auto t(tack_dia::input_comments_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_AUTO_TEST_CASE(enumeration_model_generates_expected_code) {
    SETUP_TEST_LOG("enumeration_model_generates_expected_code");
    const auto t(tack_dia::input_enumeration_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_AUTO_TEST_CASE(exception_model_generates_expected_code) {
    SETUP_TEST_LOG("exception_model_generates_expected_code");
    const auto t(tack_dia::input_exception_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_AUTO_TEST_CASE(std_model_generates_expected_code) {
    SETUP_TEST_LOG("std_model_generates_expected_code");
    const auto t(tack_dia::input_std_model_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_AUTO_TEST_CASE(boost_model_generates_expected_code) {
    SETUP_TEST_LOG("boost_model_generates_expected_code");
    const auto t(tack_dia::input_boost_model_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_AUTO_TEST_CASE(stereotypes_model_generates_expected_code) {
    SETUP_TEST_LOG("stereotypes_model_generates_expected_code");
    const auto t(tack_dia::input_stereotypes_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_AUTO_TEST_CASE(eos_serialization_model_generates_expected_code) {
    SETUP_TEST_LOG("eos_serialisation_model_generates_expected_code");
    const auto t(tack_dia::input_enable_eos_serialization_dia());

    using dogen::config::knitting_options;
    using dogen::utility::test_data::codegen_tds;
    auto lambda([](codegen_tds tds) -> knitting_options {
            return default_mock_options(tds);
        });
    BOOST_CHECK(check_code_generation(t, lambda));
}

BOOST_AUTO_TEST_CASE(package_without_name_model_throws) {
    SETUP_TEST_LOG("package_without_name_model_throws");
    const auto t(tack_dia::input_package_without_name_dia());

    using dogen::utility::test_data::codegen_tds;
    codegen_tds tds(t);

    auto s(default_mock_options(tds));
    dogen::knit::workflow w(s);
    contains_checker<std::exception> c(dia_invalid_name);
    BOOST_CHECK_EXCEPTION(w.execute(), std::exception, c);
}

BOOST_AUTO_TEST_CASE(all_primitives_model_generates_expected_code) {
    SETUP_TEST_LOG("all_primitives_model_generates_expected_code");
    const auto t(tack_dia::input_all_primitives_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_IGNORE_AUTO_TEST_CASE(split_project_model_generates_expected_code) {
    SETUP_TEST_LOG("split_project_model_generates_expected_code");

    // note that we keep the project name just to make the life easier
    // for the rebaselining scripts.
    using dogen::config::knitting_options;
    using dogen::utility::test_data::codegen_tds;
    auto lambda([](codegen_tds tds) -> knitting_options {
            using dogen::config::test::mock_options_factory;
            return mock_options_factory::make_knitting_options(
                tds.target(),
                tds.actual() / "split_project/source",
                tds.actual() / "split_project/dir/inc/dogen",
                module_path);
        });

    const auto t(tack_dia::input_split_project_dia());
    BOOST_CHECK(check_code_generation(t, lambda));
}

BOOST_AUTO_TEST_SUITE_END()
