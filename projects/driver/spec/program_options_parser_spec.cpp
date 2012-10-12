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
#include <vector>
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE driver_spec
#include <boost/test/included/unit_test.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/io/vector_io.hpp"
#include "dogen/driver/program_options_parser.hpp"
#include "dogen/driver/parser_validation_error.hpp"

namespace {

const std::string empty;
const std::string test_module("driver");
const std::string test_suite("program_options_parser_spec");
const std::string help_sanity_line("General options");
const std::string missing_target("Mandatory parameter target is missing");
const std::string invalid_facet_type("Invalid facet type");
const std::string invalid_archive_type("Invalid archive type");
const std::string unknown_option("unknown option invalid-argument");
const std::string source_include_error(
    "You must supply both source-dir and include-dir");
const std::string split_project_dir_error(
    "Argument project-dir cannot be used in conjunction with project splitting");
const std::string source_include_without_split(
    "Arguments source-dir and include-dir require project splitting");

const std::string help_arg("--help");
const std::string version_arg("--version");
const std::string invalid_arg("--invalid-argument");
const std::string invalid_value_arg("invalid-value");

const std::string verbose_arg("--verbose");
const std::string debug_dir_arg("--debug-dir");
const std::string debug_dir_value_arg("some_dir");
const std::string save_dia_model_arg("--save-dia-model");
const std::string save_dia_model_value_arg("xml");
const std::string save_sml_model_arg("--save-sml-model");
const std::string save_sml_model_value_arg("text");
const std::string stop_after_merging_arg("--stop-after-merging");
const std::string stop_after_formatting_arg("--stop-after-formatting");

const std::string target_arg("--target");
const std::string target_value_arg("some_target");
const std::string external_package_path_arg("--external-package-path");
const std::string external_package_path_value_arg("a package");
const std::string reference_arg("--reference");
const std::string reference_value_1_arg("some reference");
const std::string reference_value_2_arg("another reference");
const std::string disable_model_package_arg("--disable-model-package");

const std::string cpp_split_project_arg("--cpp-split-project");
const std::string cpp_project_dir_arg("--cpp-project-dir");
const std::string cpp_project_dir_value_arg("a project dir");
const std::string cpp_source_arg("--cpp-source-dir");
const std::string cpp_source_value_arg("some_source");
const std::string cpp_include_arg("--cpp-include-dir");
const std::string cpp_include_value_arg("some_include");
const std::string cpp_disable_backend_arg("--cpp-disable-backend");
const std::string cpp_disable_cmakelists_arg("--cpp-disable-cmakelists");
const std::string cpp_enable_facet_arg("--cpp-enable-facet");
const std::string cpp_enable_facet_value_1_arg("hash");
const std::string cpp_enable_facet_value_2_arg("io");
const std::string cpp_header_extension_arg("--cpp-header-extension");
const std::string cpp_header_extension_value_arg("header extension");
const std::string cpp_source_extension_arg("--cpp-source-extension");
const std::string cpp_source_extension_value_arg("source extension");
const std::string cpp_disable_complete_constructor_arg(
    "--cpp-disable-complete-constructor");
const std::string cpp_disable_facet_includers_arg(
    "--cpp-disable-facet-includers");
const std::string cpp_disable_facet_folders_arg("--cpp-disable-facet-folders");
const std::string cpp_disable_unique_file_names_arg(
    "--cpp-disable-unique-file-names");
const std::string cpp_domain_facet_folder_arg("--cpp-domain-facet-folder");
const std::string cpp_domain_facet_folder_value_arg("some domain folder");
const std::string cpp_hash_facet_folder_arg("--cpp-hash-facet-folder");
const std::string cpp_hash_facet_folder_value_arg("some hash facet folder");
const std::string cpp_io_facet_folder_arg("--cpp-io-facet-folder");
const std::string cpp_io_facet_folder_value_arg("io facet folder");
const std::string cpp_serialization_facet_folder_arg(
    "--cpp-serialization-facet-folder");
const std::string cpp_serialization_facet_folder_value_arg("ser facet folder");
const std::string cpp_test_data_facet_folder_arg(
    "--cpp-test-data-facet-folder");
const std::string cpp_test_data_facet_folder_value_arg(
    "test data facet folder");
const std::string cpp_disable_xml_serialization_arg(
    "--cpp-disable-xml-serialization");
const std::string cpp_use_integrated_io_arg(
    "--cpp-use-integrated-io");
const std::string cpp_disable_versioning_arg("--cpp-disable-versioning");

const std::string sql_disable_backend_arg("--sql-disable-backend");
const std::string sql_create_schema_arg("--sql-create-schema");
const std::string sql_schema_name_arg("--sql-schema-name");
const std::string sql_schema_name_value_arg("some_schema");

const std::string output_to_stdout_arg("--output-to-stdout");
const std::string output_to_file_arg("--output-to-file");
const std::string delete_extra_files_arg("--delete-extra-files");
const std::string force_write_arg("--force-write");

class help_mock {
public:
    explicit help_mock(bool& called) : called_(called) { }

    void operator()(std::string description) {
        using namespace dogen::utility::log;
        logger lg(logger_factory(test_suite));
        BOOST_LOG_SEV(lg, debug) << "description: " << description;
        BOOST_CHECK(!description.empty());
        BOOST_CHECK(boost::contains(description, help_sanity_line));
        called_ = true;
    }

    bool& called_;
};

help_mock help_mock_factory(bool& called) {
    return help_mock(called);
}

class version_mock {
public:
    explicit version_mock(bool& called) : called_(called) { }
    void operator()() { called_ = true; }
    bool& called_;
};

version_mock version_mock_factory(bool& called) {
    return version_mock(called);
}

dogen::driver::program_options_parser setup_parser(
    std::vector<std::string> options,
    bool& help_called,
    bool& version_called) {

    using namespace dogen::utility::log;
    logger lg(logger_factory(test_suite));
    BOOST_LOG_SEV(lg, debug) << "options: " << options;
    dogen::driver::program_options_parser r(options);
    r.help_function(help_mock_factory(help_called));
    r.version_function(version_mock_factory(version_called));
    return r;
}

void check_exception(std::vector<std::string> options, std::string expected) {
    bool help(false);
    bool version(false);
    auto parser(setup_parser(options, help, version));

    using dogen::driver::parser_validation_error;
    auto lambda([&](const parser_validation_error& e) -> bool {
            const std::string msg(e.what());

            if (!boost::starts_with(msg, expected)) {
                using namespace dogen::utility::log;
                logger lg(logger_factory(test_suite));
                BOOST_LOG_SEV(lg, error)
                    << "Unexpected exception text. Expected: '" << expected
                    << "'. Actual: '" << msg << "'.";
                return false;
            }
            return true;
        });

    BOOST_CHECK_EXCEPTION(parser.parse(), parser_validation_error, lambda);
    BOOST_CHECK(!help);
    BOOST_CHECK(!version);
}

dogen::generator::config::settings
check_valid_arguments(std::vector<std::string> options) {
    bool help(false);
    bool version(false);
    auto parser(setup_parser(options, help, version));

    const auto r(parser.parse());

    BOOST_CHECK(r);
    BOOST_CHECK(!help);
    BOOST_CHECK(!version);
    return r.get();
}

void check_help(std::vector<std::string> options) {
    bool help(false);
    bool version(false);
    auto parser(setup_parser(options, help, version));

    const auto r(parser.parse());

    BOOST_CHECK(!r);
    BOOST_CHECK(help);
    BOOST_CHECK(!version);
}

void check_version(std::vector<std::string> options) {
    bool help(false);
    bool version(false);
    auto parser(setup_parser(options, help, version));

    const auto r(parser.parse());

    BOOST_CHECK(!r);
    BOOST_CHECK(!help);
    BOOST_CHECK(version);
}

}

BOOST_AUTO_TEST_SUITE(program_options_parser)

BOOST_AUTO_TEST_CASE(supplying_help_argument_results_in_help) {
    SETUP_TEST_LOG("supplying_help_argument_results_in_help");
    check_help(std::vector<std::string> { help_arg });
}

BOOST_AUTO_TEST_CASE(supplying_help_argument_with_no_help_function_results_in_no_op) {
    SETUP_TEST_LOG_SOURCE("supplying_help_argument_with_no_help_function_results_in_no_op");
    bool version(false);
    const std::vector<std::string> o = { help_arg };
    BOOST_LOG_SEV(lg, debug) << "options: " << o;

    dogen::driver::program_options_parser parser(o);
    parser.version_function(version_mock_factory(version));
    const auto r(parser.parse());

    BOOST_CHECK(!r);
    BOOST_CHECK(!version);
}

BOOST_AUTO_TEST_CASE(supplying_version_argument_results_in_just_printing_version) {
    SETUP_TEST_LOG("supplying_version_argument_results_in_just_printing_version");
    check_version(std::vector<std::string> { version_arg });
}

BOOST_AUTO_TEST_CASE(supplying_version_argument_with_no_version_function_results_in_no_op) {
    SETUP_TEST_LOG_SOURCE("supplying_version_argument_with_no_version_function_results_in_no_op");
    bool help(false);
    const std::vector<std::string> o = { version_arg };
    BOOST_LOG_SEV(lg, debug) << "options: " << o;

    dogen::driver::program_options_parser parser(o);
    parser.help_function(help_mock_factory(help));
    const auto r(parser.parse());

    BOOST_CHECK(!r);
    BOOST_CHECK(!help);
}

BOOST_AUTO_TEST_CASE(supplying_no_arguments_throws) {
    SETUP_TEST_LOG("supplying_no_arguments_throws");
    check_exception(std::vector<std::string> {}, missing_target);
}

BOOST_AUTO_TEST_CASE(supplying_modeling_options_results_in_expected_settings) {
    SETUP_TEST_LOG_SOURCE("supplying_modeling_options_results_in_expected_settings");
    const std::vector<std::string> o = {
        target_arg, target_value_arg,
        external_package_path_arg,
        external_package_path_value_arg,
        reference_arg,
        reference_value_1_arg,
        reference_arg,
        reference_value_2_arg,
        disable_model_package_arg
    };

    const auto s(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "settings: " << s;

    const auto ms(s.modeling());
    BOOST_CHECK(ms.target().string() == target_value_arg);
    BOOST_CHECK(ms.external_package_path() == external_package_path_value_arg);
    BOOST_CHECK(ms.disable_model_package());

    const auto refs(ms.references());
    BOOST_REQUIRE(refs.size() == 2);
    BOOST_CHECK(refs[0].string() == reference_value_1_arg);
    BOOST_CHECK(refs[1].string() == reference_value_2_arg);
}

BOOST_AUTO_TEST_CASE(not_supplying_modeling_options_other_than_target_results_in_expected_settings) {
    SETUP_TEST_LOG_SOURCE("not_supplying_modeling_options_other_than_target_results_in_expected_settings");

    const std::vector<std::string> o = {
        target_arg, target_value_arg,
    };

    const auto s(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "settings: " << s;

    const auto ms(s.modeling());
    BOOST_CHECK(ms.target().string() == target_value_arg);
    BOOST_CHECK(ms.external_package_path().empty());
    BOOST_REQUIRE(ms.references().empty());
}

BOOST_AUTO_TEST_CASE(supplying_arguments_without_target_throws) {
    SETUP_TEST_LOG("supplying_arguments_without_target_throws");
    const std::vector<std::string> o = {
        cpp_split_project_arg,
        cpp_source_arg, cpp_source_value_arg,
        cpp_include_arg, cpp_include_value_arg
    };
    check_exception(o, missing_target);
}

BOOST_AUTO_TEST_CASE(supplying_cpp_arguments_results_in_expected_settings) {
    SETUP_TEST_LOG_SOURCE("supplying_cpp_arguments_results_in_expected_settings");
    const std::vector<std::string> o = {
        target_arg, target_value_arg,
        cpp_split_project_arg,
        cpp_source_arg, cpp_source_value_arg,
        cpp_include_arg, cpp_include_value_arg,
        cpp_disable_backend_arg,
        cpp_disable_cmakelists_arg,
        cpp_enable_facet_arg, cpp_enable_facet_value_1_arg,
        cpp_enable_facet_arg, cpp_enable_facet_value_2_arg,
        cpp_header_extension_arg, cpp_header_extension_value_arg,
        cpp_source_extension_arg, cpp_source_extension_value_arg,
        cpp_disable_complete_constructor_arg,
        cpp_disable_facet_includers_arg,
        cpp_disable_facet_folders_arg,
        cpp_disable_unique_file_names_arg,
        cpp_domain_facet_folder_arg, cpp_domain_facet_folder_value_arg,
        cpp_hash_facet_folder_arg, cpp_hash_facet_folder_value_arg,
        cpp_io_facet_folder_arg, cpp_io_facet_folder_value_arg,
        cpp_serialization_facet_folder_arg,
        cpp_serialization_facet_folder_value_arg,
        cpp_test_data_facet_folder_arg,
        cpp_test_data_facet_folder_value_arg,
        cpp_disable_xml_serialization_arg,
        cpp_use_integrated_io_arg,
        cpp_disable_versioning_arg
    };

    const auto s(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "settings: " << s;

    const auto cs(s.cpp());
    BOOST_CHECK(cs.source_directory().string() == cpp_source_value_arg);
    BOOST_CHECK(cs.include_directory().string() == cpp_include_value_arg);

    BOOST_CHECK(cs.disable_backend());
    BOOST_CHECK(cs.disable_cmakelists());
    BOOST_CHECK(cs.disable_complete_constructor());
    BOOST_CHECK(cs.disable_facet_includers());
    BOOST_CHECK(cs.disable_facet_folders());
    BOOST_CHECK(cs.disable_unique_file_names());
    BOOST_CHECK(cs.disable_xml_serialization());
    BOOST_CHECK(cs.use_integrated_io());
    BOOST_CHECK(cs.disable_versioning());

    BOOST_CHECK(cs.header_extension() == cpp_header_extension_value_arg);
    BOOST_CHECK(cs.source_extension() == cpp_source_extension_value_arg);

    BOOST_CHECK(cs.domain_facet_folder() == cpp_domain_facet_folder_value_arg);
    BOOST_CHECK(cs.hash_facet_folder() == cpp_hash_facet_folder_value_arg);
    BOOST_CHECK(cs.hash_facet_folder() == cpp_hash_facet_folder_value_arg);
    BOOST_CHECK(cs.io_facet_folder() == cpp_io_facet_folder_value_arg);
    BOOST_CHECK(cs.serialization_facet_folder() ==
        cpp_serialization_facet_folder_value_arg);
    BOOST_CHECK(cs.test_data_facet_folder() ==
        cpp_test_data_facet_folder_value_arg);

    const auto facets(cs.enabled_facets());
    BOOST_REQUIRE(facets.size() == 3);

    using dogen::generator::backends::cpp::cpp_facet_types;
    BOOST_CHECK(facets.find(cpp_facet_types::domain) != facets.end());
    BOOST_CHECK(facets.find(cpp_facet_types::hash) != facets.end());
    BOOST_CHECK(facets.find(cpp_facet_types::io) != facets.end());
}

BOOST_AUTO_TEST_CASE(supplying_invalid_facet_throws) {
    SETUP_TEST_LOG_SOURCE("supplying_invalid_facet_throws");
    const std::vector<std::string> o = {
        target_arg, target_value_arg,
        cpp_enable_facet_arg, invalid_value_arg,
    };
    check_exception(o, invalid_facet_type);
}

BOOST_AUTO_TEST_CASE(supplying_invalid_archive_type_throws) {
    SETUP_TEST_LOG_SOURCE("supplying_invalid_archive_type_throws");
    const std::vector<std::string> o1 = {
        target_arg, target_value_arg,
        save_dia_model_arg, invalid_value_arg,
    };
    check_exception(o1, invalid_archive_type);

    const std::vector<std::string> o2 = {
        target_arg, target_value_arg,
        save_sml_model_arg, invalid_value_arg,
    };
    check_exception(o2, invalid_archive_type);
}

BOOST_AUTO_TEST_CASE(not_supplying_cpp_arguments_results_in_expected_settings) {
    SETUP_TEST_LOG_SOURCE("not_supplying_cpp_arguments_results_in_expected_settings");
    const std::vector<std::string> o = { target_arg, target_value_arg };

    const auto s(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "settings: " << s;

    const auto cs(s.cpp());
    BOOST_CHECK(!cs.split_project());
    BOOST_CHECK(!cs.project_directory().empty());
    BOOST_CHECK(cs.source_directory().empty());
    BOOST_CHECK(cs.include_directory().empty());

    BOOST_CHECK(!cs.disable_backend());
    BOOST_CHECK(!cs.disable_cmakelists());
    BOOST_CHECK(!cs.disable_complete_constructor());
    BOOST_CHECK(!cs.disable_facet_folders());
    BOOST_CHECK(!cs.disable_unique_file_names());
    BOOST_CHECK(!cs.disable_xml_serialization());
    BOOST_CHECK(!cs.use_integrated_io());
    BOOST_CHECK(!cs.disable_versioning());

    BOOST_CHECK(!cs.header_extension().empty());
    BOOST_CHECK(!cs.source_extension().empty());

    BOOST_CHECK(!cs.domain_facet_folder().empty());
    BOOST_CHECK(!cs.hash_facet_folder().empty());
    BOOST_CHECK(!cs.hash_facet_folder().empty());
    BOOST_CHECK(!cs.io_facet_folder().empty());
    BOOST_CHECK(!cs.serialization_facet_folder().empty());

    const auto facets(cs.enabled_facets());
    BOOST_REQUIRE(facets.size() == 6);

    using dogen::generator::backends::cpp::cpp_facet_types;
    BOOST_CHECK(facets.find(cpp_facet_types::domain) != facets.end());
    BOOST_CHECK(facets.find(cpp_facet_types::hash) != facets.end());
    BOOST_CHECK(facets.find(cpp_facet_types::io) != facets.end());
    BOOST_CHECK(facets.find(cpp_facet_types::serialization) != facets.end());
    BOOST_CHECK(facets.find(cpp_facet_types::test_data) != facets.end());
    BOOST_CHECK(facets.find(cpp_facet_types::database) != facets.end());
}

BOOST_AUTO_TEST_CASE(supplying_an_invalid_argument_throws) {
    SETUP_TEST_LOG("supplying_an_invalid_argument_throws");
    typedef std::vector<std::string> vector;
    check_exception(vector { invalid_arg }, unknown_option);
    check_exception(vector { invalid_arg, help_arg }, unknown_option);
    check_exception(vector { help_arg, invalid_arg }, unknown_option);
    check_exception(vector { invalid_arg, version_arg }, unknown_option);
    check_exception(vector { version_arg, invalid_arg }, unknown_option);
}

BOOST_AUTO_TEST_CASE(supplying_valid_arguments_with_help_results_in_help) {
    SETUP_TEST_LOG("supplying_valid_arguments_with_help_results_in_help");
    const std::vector<std::string> o = {
        target_arg, target_value_arg,
        cpp_include_arg, cpp_include_value_arg,
        help_arg
    };
    check_help(o);
}

BOOST_AUTO_TEST_CASE(supplying_valid_arguments_with_version_results_in_version) {
    SETUP_TEST_LOG("supplying_valid_arguments_with_version_results_in_version");
    const std::vector<std::string> o = {
        target_arg, target_value_arg,
        cpp_include_arg, cpp_include_value_arg,
        version_arg
    };
    check_version(o);
}

BOOST_AUTO_TEST_CASE(supplying_project_directory_results_in_expected_settings) {
    SETUP_TEST_LOG_SOURCE("supplying_project_directory_results_in_expected_settings");
    const std::vector<std::string> o = {
        target_arg, target_value_arg,
        cpp_project_dir_arg, cpp_project_dir_value_arg
    };

    const auto s(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "settings: " << s;

    const auto cs(s.cpp());
    BOOST_CHECK(cs.project_directory() == cpp_project_dir_value_arg);
}

BOOST_AUTO_TEST_CASE(supplying_split_without_source_and_include_defaults_them) {
    SETUP_TEST_LOG_SOURCE("supplying_split_without_source_and_include_defaults_them");
    const std::vector<std::string> o = {
        target_arg, target_value_arg,
        cpp_split_project_arg
    };

    const auto s(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "settings: " << s;

    const auto cs(s.cpp());
    BOOST_CHECK(!cs.source_directory().empty());
    BOOST_CHECK(!cs.include_directory().empty());
}

BOOST_AUTO_TEST_CASE(supplying_source_or_include_without_split_throws) {
    SETUP_TEST_LOG("supplying_source_or_include_without_split_throws");
    const std::vector<std::string> o0 = {
        target_arg, target_value_arg,
        cpp_source_arg, cpp_source_value_arg
    };
    check_exception(o0, source_include_without_split);

    const std::vector<std::string> o1 = {
        target_arg, target_value_arg,
        cpp_include_arg, cpp_include_value_arg
    };
    check_exception(o1, source_include_without_split);

    const std::vector<std::string> o2 = {
        target_arg, target_value_arg,
        cpp_source_arg, cpp_source_value_arg,
        cpp_include_arg, cpp_include_value_arg
    };
    check_exception(o2, source_include_without_split);
}

BOOST_AUTO_TEST_CASE(supplying_project_dir_with_split_throws) {
    SETUP_TEST_LOG("supplying_project_dir_with_split_throws");
    const std::vector<std::string> o = {
        target_arg, target_value_arg,
        cpp_split_project_arg,
        cpp_project_dir_arg, cpp_project_dir_value_arg
    };
    check_exception(o, split_project_dir_error);
}

BOOST_AUTO_TEST_CASE(supplying_source_and_no_include_throws) {
    SETUP_TEST_LOG("supplying_source_and_no_include_throws");
    const std::vector<std::string> o = {
        target_arg, target_value_arg,
        cpp_split_project_arg,
        cpp_source_arg, cpp_source_value_arg
    };
    check_exception(o, source_include_error);
}

BOOST_AUTO_TEST_CASE(supplying_include_and_no_source_throws) {
    SETUP_TEST_LOG("supplying_include_and_no_source_throws");
    const std::vector<std::string> o = {
        target_arg, target_value_arg,
        cpp_split_project_arg,
        cpp_include_arg, cpp_include_value_arg
    };
    check_exception(o, source_include_error);
}

BOOST_AUTO_TEST_CASE(supplying_sql_arguments_results_in_expected_settings) {
    SETUP_TEST_LOG_SOURCE("supplying_sql_arguments_results_in_expected_settings");
    const std::vector<std::string> o = {
        target_arg, target_value_arg,
        sql_disable_backend_arg,
        sql_create_schema_arg,
        sql_schema_name_arg, sql_schema_name_value_arg
    };

    const auto s(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "settings: " << s;

    const auto ss(s.sql());
    BOOST_CHECK(ss.disable_backend());
    BOOST_CHECK(ss.create_schema());
    BOOST_CHECK(ss.schema_name() == sql_schema_name_value_arg);
}

BOOST_AUTO_TEST_CASE(not_supplying_sql_arguments_results_in_expected_settings) {
    SETUP_TEST_LOG_SOURCE("not_supplying_sql_arguments_results_in_expected_settings");
    const std::vector<std::string> o = {
        target_arg, target_value_arg
    };

    const auto s(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "settings: " << s;

    const auto ss(s.sql());
    BOOST_CHECK(!ss.disable_backend());
    BOOST_CHECK(!ss.create_schema());
    BOOST_CHECK(ss.schema_name().empty());
}

BOOST_AUTO_TEST_CASE(not_supplying_troubleshooting_options_results_in_expected_settings) {
    SETUP_TEST_LOG_SOURCE("not_supplying_troubleshooting_options_results_in_expected_settings");
    const std::vector<std::string> o = {
        target_arg, target_value_arg
    };
    const auto s(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "settings: " << s;

    const auto ts(s.troubleshooting());
    BOOST_CHECK(!ts.verbose());
    BOOST_CHECK(ts.debug_dir().empty());

    using dogen::utility::serialization::archive_types;
    BOOST_CHECK(ts.save_dia_model() == archive_types::invalid);
    BOOST_CHECK(ts.save_dia_model() == archive_types::invalid);

    BOOST_CHECK(!ts.stop_after_merging());
    BOOST_CHECK(!ts.stop_after_merging());
}

BOOST_AUTO_TEST_CASE(supplying_troubleshooting_options_results_in_expected_settings) {
    SETUP_TEST_LOG_SOURCE("supplying_troubleshooting_options_results_in_expected_settings");
    const std::vector<std::string> o = {
        target_arg, target_value_arg,
        verbose_arg,
        debug_dir_arg, debug_dir_value_arg,
        save_dia_model_arg, save_dia_model_value_arg,
        save_sml_model_arg, save_sml_model_value_arg,
        stop_after_merging_arg, stop_after_formatting_arg
    };
    const auto s(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "settings: " << s;

    const auto ts(s.troubleshooting());
    BOOST_CHECK(ts.verbose());
    BOOST_CHECK(ts.debug_dir().string() == debug_dir_value_arg);

    using dogen::utility::serialization::archive_types;
    BOOST_CHECK(ts.save_dia_model() == archive_types::xml);
    BOOST_CHECK(ts.save_sml_model() == archive_types::text);

    BOOST_CHECK(ts.stop_after_merging());
    BOOST_CHECK(ts.stop_after_formatting());
}

BOOST_AUTO_TEST_CASE(supplying_save_sml_or_dia_results_in_settings_with_debug_dir) {
    SETUP_TEST_LOG_SOURCE("supplying_save_sml_or_dia_results_in_settings_with_debug_dir");
    typedef std::vector<std::string> vector;
    auto lambda([&](vector o) {
            const auto s(check_valid_arguments(o));
            BOOST_LOG_SEV(lg, debug) << "settings: " << s;

            const auto ts(s.troubleshooting());
            BOOST_CHECK(!ts.debug_dir().empty());
        });

    const vector o1 = {
        target_arg, target_value_arg,
        save_dia_model_arg, save_dia_model_value_arg
    };
    lambda(o1);

    const vector o2 = {
        target_arg, target_value_arg,
        save_sml_model_arg, save_sml_model_value_arg
    };
    lambda(o2);
}

BOOST_AUTO_TEST_CASE(not_supplying_output_options_results_in_expected_settings) {
    SETUP_TEST_LOG_SOURCE("not_supplying_output_options_results_in_expected_settings");
    const std::vector<std::string> o = { target_arg, target_value_arg };
    const auto s(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "settings: " << s;

    const auto fs(s.output());
    BOOST_CHECK(fs.output_to_file());
    BOOST_CHECK(!fs.output_to_stdout());
    BOOST_CHECK(!fs.delete_extra_files());
    BOOST_CHECK(!fs.force_write());
}

BOOST_AUTO_TEST_CASE(supplying_output_options_results_in_expected_settings) {
    SETUP_TEST_LOG_SOURCE("supplying_output_options_results_in_expected_settings");
    const std::vector<std::string> o = {
        target_arg, target_value_arg,
        output_to_stdout_arg,
        output_to_file_arg,
        delete_extra_files_arg,
        force_write_arg
    };
    const auto s(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "settings: " << s;

    const auto fs(s.output());
    BOOST_CHECK(fs.output_to_file());
    BOOST_CHECK(fs.output_to_stdout());
    BOOST_CHECK(fs.delete_extra_files());
    BOOST_CHECK(fs.force_write());
}

BOOST_AUTO_TEST_CASE(supplying_output_to_std_out_disables_output_to_file) {
    SETUP_TEST_LOG_SOURCE("supplying_output_to_std_out_disables_output_to_file");
    const std::vector<std::string> o = {
        target_arg, target_value_arg,
        output_to_stdout_arg,
    };
    const auto s(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "settings: " << s;

    const auto fs(s.output());
    BOOST_CHECK(!fs.output_to_file());
    BOOST_CHECK(fs.output_to_stdout());
}

BOOST_AUTO_TEST_SUITE_END()
