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
#include "dogen/utility/test_data/dia_sml.hpp"
#include "dogen/utility/test_data/codegen_tds.hpp"
#include "dogen/utility/test_data/empty_tds.hpp"
#include "dogen/utility/test_data/debug_dogen.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/dia/io/diagram_io.hpp"
#include "dogen/engine/types/generation_failure.hpp"
#include "dogen/config/test/mock_settings_factory.hpp"
#include "dogen/config/types/settings.hpp"
#include "dogen/engine/types/workflow.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/dia/serialization/diagram_ser.hpp"
#include "dogen/sml/serialization/model_ser.hpp"
#include "dogen/dia/test/dia_file_asserter.hpp"
#include "dogen/sml/test/sml_file_asserter.hpp"
#include "dogen/utility/test/exception_checkers.hpp"

using dogen::utility::test_data::dia_sml;

namespace  {

const std::string empty;
const std::string empty_module_path;
const std::string test_module("engine");
const std::string test_suite("workflow_spec");
const std::string module_path("dogen");
const std::string module_path_disabled_model_module("dogen::dmp");
const std::string extra_folder("dmp");
const std::string domain_facet_must_be_enabled("Domain facet must be enabled");
const std::string io_facet_and_integrated_io_error(
    "Integrated IO cannot be used with the IO facet");
const std::string dia_invalid_name("Dia object name is empty");

const bool enable_om(true);

std::vector<dogen::utility::test::file_asserter::shared_ptr>
file_asserters() {
    using dogen::utility::test::file_asserter;
    std::vector<file_asserter::shared_ptr> r;

    using dogen::dia::test::dia_file_asserter;
    r.push_back(file_asserter::shared_ptr(new dia_file_asserter()));

    using dogen::sml::test::sml_file_asserter;
    r.push_back(file_asserter::shared_ptr(new sml_file_asserter()));

    return r;
}

dogen::config::settings
default_mock_settings(dogen::utility::test_data::codegen_tds tds) {
    using dogen::config::test::mock_settings_factory;
    return mock_settings_factory::build_settings(
        tds.target(), tds.actual(), module_path);
}

dogen::config::settings debug_dogen_mock_settings() {
    typedef dogen::utility::test_data::debug_dogen tds;
    using dogen::config::test::mock_settings_factory;
    return mock_settings_factory::build_settings(
        tds::target(),
        tds::actual_src(),
        tds::actual_include(),
        empty_module_path);
}

dogen::config::settings empty_tds_mock_settings() {
    typedef dogen::utility::test_data::empty_tds tds;
    using dogen::config::test::mock_settings_factory;
    return mock_settings_factory::build_settings(
        tds::target(),
        tds::actual_src(),
        tds::actual_include(),
        empty_module_path);
}

template<typename SettingsFactoryFunction>
bool check_code_generation(boost::filesystem::path target,
    SettingsFactoryFunction sff, const bool enable_om = false) {
    using dogen::utility::test_data::codegen_tds;
    codegen_tds tds(target);

    dogen::engine::workflow w(sff(tds));
    w.enable_om(enable_om);
    w.execute();

    using dogen::utility::test::asserter;
    return asserter::assert_directory(tds.expected(), tds.actual());
}

bool check_code_generation(boost::filesystem::path target,
    const bool enable_om = false) {
    return check_code_generation(target, default_mock_settings, enable_om);
}

}

using dogen::utility::test::contains_checker;
using dogen::engine::generation_failure;

BOOST_AUTO_TEST_SUITE(workflow)

BOOST_IGNORE_AUTO_TEST_CASE(debug_options_generate_expected_debug_info) {
    SETUP_TEST_LOG("debug_options_generate_expected_debug_info");
    auto s(debug_dogen_mock_settings());
    auto ts(s.troubleshooting());
    typedef dogen::utility::test_data::debug_dogen tds;
    ts.debug_dir(tds::actual());

    using dogen::config::archive_types;
    ts.save_dia_model(archive_types::xml);
    ts.save_sml_model(archive_types::xml);
    ts.stop_after_formatting(true);
    s.troubleshooting(ts);

    dogen::engine::workflow w(s);
    w.execute();

    using dogen::utility::test::asserter;
    const auto f(file_asserters());
    BOOST_CHECK(asserter::assert_directory(tds::expected(), tds::actual(), f));
}

BOOST_AUTO_TEST_CASE(stdout_option_generates_expected_output) {
    SETUP_TEST_LOG("stdout_option_generates_expected_output");
    auto s(empty_tds_mock_settings());
    auto fs(s.output());
    fs.output_to_stdout(true);
    fs.output_to_file(false);

    s.output(fs);

    // use a pointer to avoid -Wreturn-stack-address on clang
    std::unique_ptr<std::ostringstream> stream(new std::ostringstream());
    auto lambda([&]() -> std::ostream& {return *stream;});

    dogen::engine::workflow w(s, lambda);
    w.execute();

    const auto expected(dia_sml::expected_class_in_a_package_stdout_txt());
    auto actual(dia_sml::actual_class_in_a_package_stdout_txt());

    std::string contents(stream->str());
    using dogen::utility::test_data::resolver;
    const auto top_dir(resolver::resolve(boost::filesystem::path()));
    boost::replace_all(contents, top_dir.generic_string(), empty);

    using dogen::utility::filesystem::write_file_content;
    write_file_content(actual, contents);

    using dogen::utility::test::asserter;
    BOOST_CHECK(asserter::assert_file(
            dia_sml::expected_class_in_a_package_stdout_txt(),
            dia_sml::actual_class_in_a_package_stdout_txt()));

    typedef dogen::utility::test_data::empty_tds tds;
    BOOST_CHECK(asserter::assert_directory(tds::expected(), tds::actual()));
}

BOOST_AUTO_TEST_CASE(disabling_cpp_backend_results_in_no_cpp_output) {
    SETUP_TEST_LOG("disabling_cpp_backend_results_in_no_cpp_output");
    auto s(empty_tds_mock_settings());
    auto cs(s.cpp());
    cs.disable_backend(true);
    s.cpp(cs);

    dogen::engine::workflow w(s);
    w.execute();

    using dogen::utility::test::asserter;
    typedef dogen::utility::test_data::empty_tds tds;
    BOOST_CHECK(asserter::assert_directory(tds::expected(), tds::actual()));
}

BOOST_AUTO_TEST_CASE(disable_full_ctor_generates_expected_code) {
    SETUP_TEST_LOG("disable_full_ctor_generates_expected_code");
    using dogen::config::settings;
    auto lambda([](dogen::utility::test_data::codegen_tds tds) -> settings {
            auto s(default_mock_settings(tds));
            auto cs(s.cpp());
            cs.split_project(false);
            cs.disable_complete_constructor(true);
            s.cpp(cs);
            return s;
        });

    const auto t(dia_sml::input_disable_full_ctor_dia());
    BOOST_CHECK(check_code_generation(t, lambda));
}

BOOST_AUTO_TEST_CASE(disable_facet_folders_generates_expected_code) {
    SETUP_TEST_LOG("disable_facet_folders_generates_expected_code");
    using dogen::config::settings;
    auto lambda([](dogen::utility::test_data::codegen_tds tds) -> settings {
            auto s(default_mock_settings(tds));
            auto cs(s.cpp());
            cs.disable_facet_folders(true);
            s.cpp(cs);
            return s;
        });

    const auto t(dia_sml::input_disable_facet_folders_dia());
    BOOST_CHECK(check_code_generation(t, lambda));
}

BOOST_AUTO_TEST_CASE(disable_model_module_generates_expected_code) {
    SETUP_TEST_LOG("disable_model_module_generates_expected_code");
    using dogen::config::settings;
    auto lambda([](dogen::utility::test_data::codegen_tds tds) -> settings {
            auto s(default_mock_settings(tds));
            auto cs(s.cpp());
            cs.project_directory(cs.project_directory() /= extra_folder);
            s.cpp(cs);

            auto ms(s.modeling());
            ms.disable_model_module(true);
            ms.external_module_path(module_path_disabled_model_module);
            s.modeling(ms);
            return s;
        });

    const auto t(dia_sml::input_disable_model_package_dia());
    BOOST_CHECK(check_code_generation(t, lambda));
}

BOOST_AUTO_TEST_CASE(disable_cmakelists_generates_expected_code) {
    SETUP_TEST_LOG("disable_cmakelists_generates_expected_code");
    using dogen::config::settings;
    auto lambda([](dogen::utility::test_data::codegen_tds tds) -> settings {
            auto s(default_mock_settings(tds));
            auto cs(s.cpp());
            cs.disable_cmakelists(true);
            s.cpp(cs);
            return s;
        });

    const auto t(dia_sml::input_disable_cmakelists_dia());
    BOOST_CHECK(check_code_generation(t, lambda));
}

BOOST_AUTO_TEST_CASE(not_enabling_facet_domain_throws) {
    SETUP_TEST_LOG("not_enabling_facet_domain_throws");
    const auto t(dia_sml::input_enable_facet_hash_dia());

    using dogen::utility::test_data::codegen_tds;
    codegen_tds tds(t);

    auto s(default_mock_settings(tds));
    auto cs(s.cpp());
    using dogen::config::cpp_facet_types;
    std::set<cpp_facet_types> f = { cpp_facet_types::hash };
    cs.enabled_facets(f);
    s.cpp(cs);

    dogen::engine::workflow w(s);
    contains_checker<generation_failure> c(domain_facet_must_be_enabled);
    BOOST_CHECK_EXCEPTION(w.execute(), generation_failure, c);
}

BOOST_AUTO_TEST_CASE(enable_facet_domain_generates_expected_code) {
    SETUP_TEST_LOG("enable_facet_domain_generates_expected_code");
    using dogen::config::settings;
    auto lambda([](dogen::utility::test_data::codegen_tds tds) -> settings {
            auto s(default_mock_settings(tds));
            auto cs(s.cpp());
            using dogen::config::cpp_facet_types;
            std::set<cpp_facet_types> f = {
                cpp_facet_types::types
            };
            cs.enabled_facets(f);
            cs.use_integrated_io(true);
            s.cpp(cs);
            return s;
        });

    const auto t(dia_sml::input_enable_facet_domain_dia());
    BOOST_CHECK(check_code_generation(t, lambda));
}

BOOST_AUTO_TEST_CASE(enable_facet_hash_generates_expected_code) {
    SETUP_TEST_LOG("enable_facet_hash_generates_expected_code");
    using dogen::config::settings;
    auto lambda([](dogen::utility::test_data::codegen_tds tds) ->  settings {
            auto s(default_mock_settings(tds));
            auto cs(s.cpp());
            using dogen::config::cpp_facet_types;
            std::set<cpp_facet_types> f = {
                cpp_facet_types::types,
                cpp_facet_types::hash
            };
            cs.enabled_facets(f);
            s.cpp(cs);
            return s;
        });

    const auto t(dia_sml::input_enable_facet_hash_dia());
    BOOST_CHECK(check_code_generation(t, lambda));
}

BOOST_AUTO_TEST_CASE(enable_facet_serialization_generates_expected_code) {
    SETUP_TEST_LOG("enable_facet_serialization_generates_expected_code");
    using dogen::config::settings;
    auto lambda([](dogen::utility::test_data::codegen_tds tds) -> settings {
            auto s(default_mock_settings(tds));
            auto cs(s.cpp());
            using dogen::config::cpp_facet_types;
            std::set<cpp_facet_types> f = {
                cpp_facet_types::types,
                cpp_facet_types::serialization
            };
            cs.enabled_facets(f);
            cs.disable_xml_serialization(false);
            s.cpp(cs);
            return s;
        });

    const auto t(dia_sml::input_enable_facet_serialization_dia());
    BOOST_CHECK(check_code_generation(t, lambda));
}

BOOST_AUTO_TEST_CASE(enable_facet_io_generates_expected_code) {
    SETUP_TEST_LOG("enable_facet_io_generates_expected_code");
    using dogen::config::settings;
    auto lambda([](dogen::utility::test_data::codegen_tds tds) -> settings {
            auto s(default_mock_settings(tds));
            auto cs(s.cpp());
            using dogen::config::cpp_facet_types;
            std::set<cpp_facet_types> f = {
                cpp_facet_types::types,
                cpp_facet_types::io
            };
            cs.enabled_facets(f);
            s.cpp(cs);
            return s;
        });

    const auto t(dia_sml::input_enable_facet_io_dia());
    BOOST_CHECK(check_code_generation(t, lambda));
}

BOOST_AUTO_TEST_CASE(enabling_facet_io_and_using_integrated_io_throws) {
    SETUP_TEST_LOG("enabling_facet_io_and_using_integrated_io_throws");
    const auto t(dia_sml::input_enable_facet_io_dia());

    using dogen::utility::test_data::codegen_tds;
    codegen_tds tds(t);

    auto s(default_mock_settings(tds));
    auto cs(s.cpp());
    using dogen::config::cpp_facet_types;
    std::set<cpp_facet_types> f = {
        cpp_facet_types::hash,
        cpp_facet_types::io
    };
    cs.enabled_facets(f);
    cs.use_integrated_io(true);
    s.cpp(cs);

    dogen::engine::workflow w(s);
    contains_checker<generation_failure> c(io_facet_and_integrated_io_error);
    BOOST_CHECK_EXCEPTION(w.execute(), generation_failure, c);
}

BOOST_AUTO_TEST_CASE(class_in_a_package_model_generates_expected_code) {
    SETUP_TEST_LOG("class_in_a_package_model_generates_expected_code");
    const auto t(dia_sml::input_class_in_a_package_dia());
    BOOST_CHECK(check_code_generation(t, enable_om));
}

BOOST_AUTO_TEST_CASE(two_empty_layers_model_does_not_generate_code) {
    SETUP_TEST_LOG("two_empty_layers_model_does_not_generate_code");
    const auto t(dia_sml::input_two_empty_layers_dia());
    BOOST_CHECK(check_code_generation(t, enable_om));
}

BOOST_AUTO_TEST_CASE(class_without_name_model_throws) {
    SETUP_TEST_LOG("class_without_name_model_throws");
    const auto t(dia_sml::input_class_without_name_dia());

    using dogen::utility::test_data::codegen_tds;
    codegen_tds tds(t);

    auto s(default_mock_settings(tds));
    dogen::engine::workflow w(s);
    w.enable_om(enable_om);
    contains_checker<std::exception> c(dia_invalid_name);
    BOOST_CHECK_EXCEPTION(w.execute(), std::exception, c);
}

BOOST_AUTO_TEST_CASE(empty_model_generates_expected_code) {
    SETUP_TEST_LOG("empty_model_generates_expected_code");
    const auto t(dia_sml::input_empty_dia());
    BOOST_CHECK(check_code_generation(t, enable_om));
}

BOOST_AUTO_TEST_CASE(empty_package_model_does_not_generate_code) {
    SETUP_TEST_LOG("empty_package_model_does_not_generate_code");
    const auto t(dia_sml::input_empty_package_dia());
    BOOST_CHECK(check_code_generation(t, enable_om));
}

BOOST_AUTO_TEST_CASE(classes_inout_package_model_generates_expected_code) {
    SETUP_TEST_LOG("classes_inout_package_model_generates_expected_code");
    const auto t(dia_sml::input_classes_inout_package_dia());
    BOOST_CHECK(check_code_generation(t, enable_om));
}

BOOST_AUTO_TEST_CASE(class_without_attributes_model_generates_expected_code) {
    SETUP_TEST_LOG("class_without_attributes_model_generates_expected_code");
    const auto t(dia_sml::input_class_without_attributes_dia());
    BOOST_CHECK(check_code_generation(t, enable_om));
}

BOOST_AUTO_TEST_CASE(class_without_package_model_generates_expected_code) {
    SETUP_TEST_LOG("class_without_package_model_generates_expected_code");
    const auto t(dia_sml::input_class_without_package_dia());
    BOOST_CHECK(check_code_generation(t, enable_om));
}

BOOST_AUTO_TEST_CASE(stand_alone_class_model_generates_expected_code) {
    SETUP_TEST_LOG("stand_alone_class_model_generates_expected_code");
    const auto t(dia_sml::input_stand_alone_class_dia());
    BOOST_CHECK(check_code_generation(t, enable_om));
}

BOOST_AUTO_TEST_CASE(classes_in_a_package_model_generates_expected_code) {
    SETUP_TEST_LOG("classes_in_a_package_model_generates_expected_code");
    const auto t(dia_sml::input_classes_in_a_package_dia());
    BOOST_CHECK(check_code_generation(t, enable_om));
}

BOOST_AUTO_TEST_CASE(classes_without_package_model_generates_expected_code) {
    SETUP_TEST_LOG("classes_without_package_model_generates_expected_code");
    const auto t(dia_sml::input_classes_without_package_dia());
    BOOST_CHECK(check_code_generation(t, enable_om));
}

BOOST_AUTO_TEST_CASE(compressed_model_generates_expected_code) {
    SETUP_TEST_LOG("compressed_model_generates_expected_code");
    const auto t(dia_sml::input_compressed_dia());
    BOOST_CHECK(check_code_generation(t, enable_om));
}

BOOST_AUTO_TEST_CASE(two_layers_with_objects_model_generates_expected_code) {
    SETUP_TEST_LOG("two_layers_with_objects_model_generates_expected_code");
    const auto t(dia_sml::input_two_layers_with_objects_dia());
    BOOST_CHECK(check_code_generation(t, enable_om));
}

BOOST_AUTO_TEST_CASE(trivial_inheritance_model_generates_expected_code) {
    SETUP_TEST_LOG("trivial_inheritance_model_generates_expected_code");
    const auto t(dia_sml::input_trivial_inheritance_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_AUTO_TEST_CASE(trivial_association_model_generates_expected_code) {
    SETUP_TEST_LOG("trivial_association_model_generates_expected_code");
    const auto t(dia_sml::input_trivial_association_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_AUTO_TEST_CASE(comments_model_generates_expected_code) {
    SETUP_TEST_LOG("comments_model_generates_expected_code");
    const auto t(dia_sml::input_comments_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_AUTO_TEST_CASE(enumeration_model_generates_expected_code) {
    SETUP_TEST_LOG("enumeration_model_generates_expected_code");
    const auto t(dia_sml::input_enumeration_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_AUTO_TEST_CASE(exception_model_generates_expected_code) {
    SETUP_TEST_LOG("exception_model_generates_expected_code");
    const auto t(dia_sml::input_exception_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_AUTO_TEST_CASE(std_model_generates_expected_code) {
    SETUP_TEST_LOG("std_model_generates_expected_code");
    const auto t(dia_sml::input_std_model_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_AUTO_TEST_CASE(boost_model_generates_expected_code) {
    SETUP_TEST_LOG("boost_model_generates_expected_code");
    const auto t(dia_sml::input_boost_model_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_AUTO_TEST_CASE(stereotypes_model_generates_expected_code) {
    SETUP_TEST_LOG("stereotypes_model_generates_expected_code");
    const auto t(dia_sml::input_stereotypes_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_AUTO_TEST_CASE(eos_serialization_model_generates_expected_code) {
    SETUP_TEST_LOG("eos_serialisation_model_generates_expected_code");
    const auto t(dia_sml::input_enable_eos_serialization_dia());

    using dogen::config::settings;
    auto lambda([](dogen::utility::test_data::codegen_tds tds) -> settings {
            auto s(default_mock_settings(tds));
            auto cs(s.cpp());
            using dogen::config::cpp_facet_types;
            std::set<cpp_facet_types> f = {
                cpp_facet_types::types,
                cpp_facet_types::serialization
            };
            cs.enabled_facets(f);
            cs.disable_eos_serialization(false);
            s.cpp(cs);
            return s;
        });

    BOOST_CHECK(check_code_generation(t, lambda));
}

BOOST_AUTO_TEST_CASE(package_without_name_model_throws) {
    SETUP_TEST_LOG("package_without_name_model_throws");
    const auto t(dia_sml::input_package_without_name_dia());

    using dogen::utility::test_data::codegen_tds;
    codegen_tds tds(t);

    auto s(default_mock_settings(tds));
    dogen::engine::workflow w(s);
    contains_checker<std::exception> c(dia_invalid_name);
    BOOST_CHECK_EXCEPTION(w.execute(), std::exception, c);
}

BOOST_AUTO_TEST_CASE(all_primitives_model_generates_expected_code) {
    SETUP_TEST_LOG("all_primitives_model_generates_expected_code");
    const auto t(dia_sml::input_all_primitives_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_AUTO_TEST_CASE(split_project_model_generates_expected_code) {
    SETUP_TEST_LOG("split_project_model_generates_expected_code");

    // note that we keep the project name just to make the life easier
    // for the rebaselining scripts.
    using dogen::config::settings;
    auto lambda([](dogen::utility::test_data::codegen_tds tds) -> settings {
            using dogen::config::test::mock_settings_factory;
            return mock_settings_factory::build_settings(
                tds.target(),
                tds.actual() / "split_project/source",
                tds.actual() / "split_project/dir/inc/dogen",
                module_path);
        });

    const auto t(dia_sml::input_split_project_dia());
    BOOST_CHECK(check_code_generation(t, lambda));
}

BOOST_AUTO_TEST_CASE(housekeeping_is_not_triggered_when_we_are_not_generating_files) {
    SETUP_TEST_LOG("housekeeping_is_not_triggered_when_we_are_not_generating_files");
    auto s(empty_tds_mock_settings());
    auto ts(s.troubleshooting());
    ts.stop_after_merging(true);
    s.troubleshooting(ts);

    dogen::engine::workflow w1(s);
    BOOST_CHECK(!w1.housekeeping_required());

    s = empty_tds_mock_settings();
    ts = s.troubleshooting();
    ts.stop_after_formatting(true);
    s.troubleshooting(ts);
    dogen::engine::workflow w2(s);
    BOOST_CHECK(!w2.housekeeping_required());

    s = empty_tds_mock_settings();
    auto os = s.output();
    os.output_to_stdout(true);
    os.output_to_file(false);
    s.output(os);
    std::unique_ptr<std::ostringstream> stream(new std::ostringstream());
    auto lambda([&]() -> std::ostream& {return *stream;});
    dogen::engine::workflow w3(s, lambda);
    BOOST_CHECK(!w3.housekeeping_required());

    s = empty_tds_mock_settings();
    os = s.output();
    os.delete_extra_files(false);
    s.output(os);
    dogen::engine::workflow w4(s);
    BOOST_CHECK(!w4.housekeeping_required());
}

BOOST_AUTO_TEST_CASE(housekeeping_is_not_triggered_when_delete_extra_files_is_requested) {
    SETUP_TEST_LOG("housekeeping_is_not_triggered_when_delete_extra_files_is_requested");
    auto s = empty_tds_mock_settings();
    auto os = s.output();
    os.delete_extra_files(true);
    s.output(os);
    dogen::engine::workflow w(s);
    BOOST_CHECK(w.housekeeping_required());
}

BOOST_AUTO_TEST_SUITE_END()
