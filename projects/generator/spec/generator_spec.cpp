/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <sstream>
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE generator_spec
#include <boost/test/included/unit_test.hpp>
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
#include "dogen/generator/generation_failure.hpp"
#include "dogen/generator/test/mock_settings_factory.hpp"
#include "dogen/generator/modeling/dia_to_sml.hpp"
#include "dogen/generator/config/settings.hpp"
#include "dogen/generator/generator.hpp"
#include "dogen/sml/domain/model.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/dia/serialization/diagram_ser.hpp"
#include "dogen/sml/serialization/model_ser.hpp"
#include "dogen/dia/test/dia_file_asserter.hpp"
#include "dogen/sml/test/sml_file_asserter.hpp"

namespace  {

const std::string empty;
const std::string empty_package_path;
const std::string test_module("generator");
const std::string test_suite("generator_spec");
const std::string package_path("dogen");
const std::string package_path_disabled_model_package("dogen::dmp");
const std::string extra_folder("dmp");
const std::string domain_facet_must_be_enabled("Domain facet must be enabled");
const std::string io_facet_and_integrated_io_error(
    "Integrated IO cannot be used with the IO facet");
const std::string dia_invalid_name("Dia object name is invalid");

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

dogen::generator::config::settings
default_mock_settings(dogen::utility::test_data::codegen_tds tds) {
    using dogen::generator::test::mock_settings_factory;
    return mock_settings_factory::build_settings(
        tds.target(), tds.actual(), package_path);
}

dogen::generator::config::settings debug_dogen_mock_settings() {
    typedef dogen::utility::test_data::debug_dogen tds;
    using dogen::generator::test::mock_settings_factory;
    return mock_settings_factory::build_settings(
        tds::target(),
        tds::actual_src(),
        tds::actual_include(),
        empty_package_path);
}

dogen::generator::config::settings empty_tds_mock_settings() {
    typedef dogen::utility::test_data::empty_tds tds;
    using dogen::generator::test::mock_settings_factory;
    return mock_settings_factory::build_settings(
        tds::target(),
        tds::actual_src(),
        tds::actual_include(),
        empty_package_path);
}

template<typename SettingsFactoryFunction>
bool check_code_generation(boost::filesystem::path target,
    SettingsFactoryFunction sff) {
    using dogen::utility::test_data::codegen_tds;
    codegen_tds tds(target);

    dogen::generator::generator cg(sff(tds));
    cg.generate();

    using dogen::utility::test::asserter;
    return asserter::assert_directory(tds.expected(), tds.actual());
}

bool check_code_generation(boost::filesystem::path target) {
    return check_code_generation(target, default_mock_settings);
}

}

BOOST_AUTO_TEST_SUITE(generator)

BOOST_AUTO_TEST_CASE(debug_options_generate_expected_debug_info) {
    SETUP_TEST_LOG("debug_options_generate_expected_debug_info");
    auto s(debug_dogen_mock_settings());
    auto ts(s.troubleshooting());
    typedef dogen::utility::test_data::debug_dogen tds;
    ts.debug_dir(tds::actual());

    using dogen::utility::serialization::archive_types;
    ts.save_dia_model(archive_types::xml);
    ts.save_sml_model(archive_types::xml);
    ts.stop_after_formatting(true);
    s.troubleshooting(ts);

    dogen::generator::generator cg(s);
    cg.generate();

    using dogen::utility::test::asserter;
    const auto f(file_asserters());
    BOOST_CHECK(asserter::assert_directory(tds::expected(), tds::actual(), f));
}

BOOST_IGNORE_AUTO_TEST_CASE(stdout_option_generates_expected_output) {
    SETUP_TEST_LOG("stdout_option_generates_expected_output");
    auto s(empty_tds_mock_settings());
    auto fs(s.output());
    fs.output_to_stdout(true);
    fs.output_to_file(false);

    s.output(fs);

    std::ostringstream stream;
    auto lambda([&]() -> std::ostream& {return stream;});

    dogen::generator::generator cg(s, lambda);
    cg.generate();

    using dogen::utility::test_data::dia_sml;
    const auto expected(dia_sml::expected_class_in_a_package_stdout_txt());
    auto actual(dia_sml::actual_class_in_a_package_stdout_txt());

    std::string contents(stream.str());
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

    dogen::generator::generator cg(s);
    cg.generate();

    using dogen::utility::test::asserter;
    typedef dogen::utility::test_data::empty_tds tds;
    BOOST_CHECK(asserter::assert_directory(tds::expected(), tds::actual()));
}

BOOST_AUTO_TEST_CASE(disable_complete_constructor_generates_expected_code) {
    SETUP_TEST_LOG("disable_complete_constructor_generates_expected_code");
    auto lambda([](dogen::utility::test_data::codegen_tds tds) {
            auto s(default_mock_settings(tds));
            auto cs(s.cpp());
            cs.split_project(false);
            cs.disable_complete_constructor(true);
            s.cpp(cs);
            return s;
        });

    using dogen::utility::test_data::dia_sml;
    const auto t(dia_sml::input_disable_complete_constructor_dia());
    BOOST_CHECK(check_code_generation(t, lambda));
}

BOOST_IGNORE_AUTO_TEST_CASE(disable_facet_folders_generates_expected_code) {
    SETUP_TEST_LOG("disable_facet_folders_generates_expected_code");
    auto lambda([](dogen::utility::test_data::codegen_tds tds) {
            auto s(default_mock_settings(tds));
            auto cs(s.cpp());
            cs.disable_facet_folders(true);
            s.cpp(cs);
            return s;
        });

    using dogen::utility::test_data::dia_sml;
    const auto t(dia_sml::input_disable_facet_folders_dia());
    BOOST_CHECK(check_code_generation(t, lambda));
}

BOOST_IGNORE_AUTO_TEST_CASE(disable_model_package_generates_expected_code) {
    SETUP_TEST_LOG("disable_model_package_generates_expected_code");
    auto lambda([](dogen::utility::test_data::codegen_tds tds) {
            auto s(default_mock_settings(tds));
            auto cs(s.cpp());
            cs.source_directory(cs.source_directory() /= extra_folder);
            cs.include_directory(cs.include_directory() /= extra_folder);
            s.cpp(cs);

            auto ms(s.modeling());
            ms.disable_model_package(true);
            ms.external_package_path(package_path_disabled_model_package);
            s.modeling(ms);
            return s;
        });

    using dogen::utility::test_data::dia_sml;
    const auto t(dia_sml::input_disable_model_package_dia());
    BOOST_CHECK(check_code_generation(t, lambda));
}

BOOST_AUTO_TEST_CASE(disable_cmakelists_generates_expected_code) {
    SETUP_TEST_LOG("disable_cmakelists_generates_expected_code");
    auto lambda([](dogen::utility::test_data::codegen_tds tds) {
            auto s(default_mock_settings(tds));
            auto cs(s.cpp());
            cs.disable_cmakelists(true);
            s.cpp(cs);
            return s;
        });

    using dogen::utility::test_data::dia_sml;
    const auto t(dia_sml::input_disable_cmakelists_dia());
    BOOST_CHECK(check_code_generation(t, lambda));
}

BOOST_AUTO_TEST_CASE(not_enabling_facet_domain_throws) {
    SETUP_TEST_LOG("not_enabling_facet_domain_throws");
    using dogen::utility::test_data::dia_sml;
    const auto t(dia_sml::input_enable_facet_hash_dia());

    using dogen::utility::test_data::codegen_tds;
    codegen_tds tds(t);

    auto s(default_mock_settings(tds));
    auto cs(s.cpp());
    using dogen::generator::backends::cpp::cpp_facet_types;
    std::set<cpp_facet_types> f = { cpp_facet_types::hash };
    cs.enabled_facets(f);
    s.cpp(cs);

    dogen::generator::generator cg(s);
    using dogen::generator::generation_failure;
    auto lambda([](const generation_failure& e) {
            const std::string msg(e.what());
            return boost::contains(msg, domain_facet_must_be_enabled);
        });
    BOOST_CHECK_EXCEPTION(cg.generate(), generation_failure, lambda);
}

BOOST_AUTO_TEST_CASE(enable_facet_domain_generates_expected_code) {
    SETUP_TEST_LOG("enable_facet_domain_generates_expected_code");
    auto lambda([](dogen::utility::test_data::codegen_tds tds) {
            auto s(default_mock_settings(tds));
            auto cs(s.cpp());
            using dogen::generator::backends::cpp::cpp_facet_types;
            std::set<cpp_facet_types> f = {
                cpp_facet_types::domain
            };
            cs.enabled_facets(f);
            cs.use_integrated_io(true);
            s.cpp(cs);
            return s;
        });

    using dogen::utility::test_data::dia_sml;
    const auto t(dia_sml::input_enable_facet_domain_dia());
    BOOST_CHECK(check_code_generation(t, lambda));
}

BOOST_AUTO_TEST_CASE(enable_facet_hash_generates_expected_code) {
    SETUP_TEST_LOG("enable_facet_hash_generates_expected_code");
    auto lambda([](dogen::utility::test_data::codegen_tds tds) {
            auto s(default_mock_settings(tds));
            auto cs(s.cpp());
            using dogen::generator::backends::cpp::cpp_facet_types;
            std::set<cpp_facet_types> f = {
                cpp_facet_types::domain,
                cpp_facet_types::hash
            };
            cs.enabled_facets(f);
            s.cpp(cs);
            return s;
        });

    using dogen::utility::test_data::dia_sml;
    const auto t(dia_sml::input_enable_facet_hash_dia());
    BOOST_CHECK(check_code_generation(t, lambda));
}

BOOST_AUTO_TEST_CASE(enable_facet_serialization_generates_expected_code) {
    SETUP_TEST_LOG("enable_facet_serialization_generates_expected_code");
    auto lambda([](dogen::utility::test_data::codegen_tds tds) {
            auto s(default_mock_settings(tds));
            auto cs(s.cpp());
            using dogen::generator::backends::cpp::cpp_facet_types;
            std::set<cpp_facet_types> f = {
                cpp_facet_types::domain,
                cpp_facet_types::serialization
            };
            cs.enabled_facets(f);
            cs.disable_xml_serialization(true);
            s.cpp(cs);
            return s;
        });

    using dogen::utility::test_data::dia_sml;
    const auto t(dia_sml::input_enable_facet_serialization_dia());
    BOOST_CHECK(check_code_generation(t, lambda));
}

BOOST_IGNORE_AUTO_TEST_CASE(enable_facet_io_generates_expected_code) {
    SETUP_TEST_LOG("enable_facet_io_generates_expected_code");
    auto lambda([](dogen::utility::test_data::codegen_tds tds) {
            auto s(default_mock_settings(tds));
            auto cs(s.cpp());
            using dogen::generator::backends::cpp::cpp_facet_types;
            std::set<cpp_facet_types> f = {
                cpp_facet_types::domain,
                cpp_facet_types::io
            };
            cs.enabled_facets(f);
            s.cpp(cs);
            return s;
        });

    using dogen::utility::test_data::dia_sml;
    const auto t(dia_sml::input_enable_facet_io_dia());
    BOOST_CHECK(check_code_generation(t, lambda));
}

BOOST_AUTO_TEST_CASE(enabling_facet_io_and_using_integrated_io_throws) {
    SETUP_TEST_LOG("enabling_facet_io_and_using_integrated_io_throws");
    using dogen::utility::test_data::dia_sml;
    const auto t(dia_sml::input_enable_facet_io_dia());

    using dogen::utility::test_data::codegen_tds;
    codegen_tds tds(t);

    auto s(default_mock_settings(tds));
    auto cs(s.cpp());
    using dogen::generator::backends::cpp::cpp_facet_types;
    std::set<cpp_facet_types> f = {
        cpp_facet_types::hash,
        cpp_facet_types::io
    };
    cs.enabled_facets(f);
    cs.use_integrated_io(true);
    s.cpp(cs);

    dogen::generator::generator cg(s);
    using dogen::generator::generation_failure;
    auto lambda([](const generation_failure& e) {
            const std::string msg(e.what());
            return boost::contains(msg, io_facet_and_integrated_io_error);
        });
    BOOST_CHECK_EXCEPTION(cg.generate(), generation_failure, lambda);
}

BOOST_IGNORE_AUTO_TEST_CASE(class_in_a_package_model_generates_expected_code) {
    SETUP_TEST_LOG("class_in_a_package_model_generates_expected_code");
    using dogen::utility::test_data::dia_sml;
    BOOST_CHECK(check_code_generation(dia_sml::input_class_in_a_package_dia()));
}

BOOST_IGNORE_AUTO_TEST_CASE(two_empty_layers_model_generates_expected_code) {
    SETUP_TEST_LOG("two_empty_layers_model_generates_expected_code");
    using dogen::utility::test_data::dia_sml;
    const auto t(dia_sml::input_two_empty_layers_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_IGNORE_AUTO_TEST_CASE(class_without_name_model_generates_expected_code) {
    SETUP_TEST_LOG("class_without_name_model_generates_expected_code");
    using dogen::utility::test_data::dia_sml;
    const auto t(dia_sml::input_class_without_name_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_IGNORE_AUTO_TEST_CASE(empty_model_generates_expected_code) {
    SETUP_TEST_LOG("empty_model_generates_expected_code");
    using dogen::utility::test_data::dia_sml;
    const auto t(dia_sml::input_empty_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_IGNORE_AUTO_TEST_CASE(empty_package_model_generates_expected_code) {
    SETUP_TEST_LOG("empty_package_model_generates_expected_code");
    using dogen::utility::test_data::dia_sml;
    const auto t(dia_sml::input_empty_package_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_IGNORE_AUTO_TEST_CASE(classes_inout_package_model_generates_expected_code) {
    SETUP_TEST_LOG("classes_inout_package_model_generates_expected_code");
    using dogen::utility::test_data::dia_sml;
    const auto t(dia_sml::input_classes_inout_package_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_IGNORE_AUTO_TEST_CASE(class_without_attributes_model_generates_expected_code) {
    SETUP_TEST_LOG("class_without_attributes_model_generates_expected_code");
    using dogen::utility::test_data::dia_sml;
    const auto t(dia_sml::input_class_without_attributes_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_IGNORE_AUTO_TEST_CASE(class_without_package_model_generates_expected_code) {
    SETUP_TEST_LOG("class_without_package_model_generates_expected_code");
    using dogen::utility::test_data::dia_sml;
    const auto t(dia_sml::input_class_without_package_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_IGNORE_AUTO_TEST_CASE(stand_alone_class_model_generates_expected_code) {
    SETUP_TEST_LOG("stand_alone_class_model_generates_expected_code");
    using dogen::utility::test_data::dia_sml;
    const auto t(dia_sml::input_stand_alone_class_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_IGNORE_AUTO_TEST_CASE(classes_in_a_package_model_generates_expected_code) {
    SETUP_TEST_LOG("classes_in_a_package_model_generates_expected_code");
    using dogen::utility::test_data::dia_sml;
    const auto t(dia_sml::input_classes_in_a_package_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_IGNORE_AUTO_TEST_CASE(classes_without_package_model_generates_expected_code) {
    SETUP_TEST_LOG("classes_without_package_model_generates_expected_code");
    using dogen::utility::test_data::dia_sml;
    const auto t(dia_sml::input_classes_without_package_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_IGNORE_AUTO_TEST_CASE(compressed_model_generates_expected_code) {
    SETUP_TEST_LOG("compressed_model_generates_expected_code");
    using dogen::utility::test_data::dia_sml;
    const auto t(dia_sml::input_compressed_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_IGNORE_AUTO_TEST_CASE(two_layers_with_objects_model_generates_expected_code) {
    SETUP_TEST_LOG("two_layers_with_objects_model_generates_expected_code");
    using dogen::utility::test_data::dia_sml;
    const auto t(dia_sml::input_two_layers_with_objects_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_IGNORE_AUTO_TEST_CASE(package_without_name_model_generates_expected_code) {
    SETUP_TEST_LOG("package_without_name_model_generates_expected_code");
    using dogen::utility::test_data::dia_sml;
    const auto t(dia_sml::input_package_without_name_dia());

    using dogen::utility::test_data::dia_sml;
    using dogen::utility::test_data::codegen_tds;
    codegen_tds tds(t);

    auto s(default_mock_settings(tds));
    dogen::generator::generator cg(s);

    using dogen::generator::generation_failure;
    auto lambda([](const generation_failure& e) {
            const std::string msg(e.what());
            return boost::contains(msg, dia_invalid_name);
        });
    BOOST_CHECK_EXCEPTION(cg.generate(), generation_failure, lambda);
}

BOOST_IGNORE_AUTO_TEST_CASE(all_primitives_model_generates_expected_code) {
    SETUP_TEST_LOG("all_primitives_model_generates_expected_code");
    using dogen::utility::test_data::dia_sml;
    const auto t(dia_sml::input_all_primitives_dia());
    BOOST_CHECK(check_code_generation(t));
}

BOOST_AUTO_TEST_CASE(housekeeping_is_not_triggered_when_we_are_not_generating_files) {
    SETUP_TEST_LOG("housekeeping_is_not_triggered_when_we_are_not_generating_files");
    auto s(empty_tds_mock_settings());
    auto ts(s.troubleshooting());
    ts.stop_after_merging(true);
    s.troubleshooting(ts);

    dogen::generator::generator cg1(s);
    BOOST_CHECK(!cg1.housekeeping_required());

    s = empty_tds_mock_settings();
    ts = s.troubleshooting();
    ts.stop_after_formatting(true);
    s.troubleshooting(ts);
    dogen::generator::generator cg2(s);
    BOOST_CHECK(!cg2.housekeeping_required());

    s = empty_tds_mock_settings();
    auto os = s.output();
    os.output_to_stdout(true);
    os.output_to_file(false);
    s.output(os);
    std::ostringstream stream;
    auto lambda([&]() -> std::ostream& {return stream;});
    dogen::generator::generator cg3(s, lambda);
    BOOST_CHECK(!cg3.housekeeping_required());

    s = empty_tds_mock_settings();
    os = s.output();
    os.delete_extra_files(false);
    s.output(os);
    dogen::generator::generator cg4(s);
    BOOST_CHECK(!cg4.housekeeping_required());
}

BOOST_AUTO_TEST_CASE(housekeeping_is_not_triggered_when_delete_extra_files_is_requested) {
    SETUP_TEST_LOG("housekeeping_is_not_triggered_when_delete_extra_files_is_requested");
    auto s = empty_tds_mock_settings();
    auto os = s.output();
    os.delete_extra_files(true);
    s.output(os);
    dogen::generator::generator cg(s);
    BOOST_CHECK(cg.housekeeping_required());
}

BOOST_AUTO_TEST_SUITE_END()
