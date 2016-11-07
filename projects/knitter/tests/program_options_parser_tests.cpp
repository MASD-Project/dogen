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
#include <vector>
#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/io/vector_io.hpp"
#include "dogen/options/io/knitting_options_io.hpp"
#include "dogen/knitter/program_options_parser.hpp"
#include "dogen/knitter/parser_validation_error.hpp"

using namespace dogen::utility::log;

namespace {

const std::string empty;
const std::string test_module("knitter");
const std::string test_suite("program_options_parser_tests");
const std::string help_sanity_line("General options");
const std::string missing_target("Mandatory parameter target is missing");
const std::string invalid_facet_type("Invalid facet type");
const std::string unknown_option("invalid-argument");

const std::string help_arg("--help");
const std::string version_arg("--version");
const std::string invalid_arg("--invalid-argument");
const std::string invalid_value_arg("invalid-value");

const std::string verbose_arg("--verbose");
const std::string target_arg("--target");
const std::string target_value_arg("some_target");
const std::string target_value_external_path_arg("some_target,a module");
const std::string external_modules_value_arg("a module");

const std::string cpp_project_dir_arg("--cpp-project-dir");
const std::string cpp_project_dir_value_arg("a project dir");

const std::string delete_extra_files_arg("--delete-extra-files");
const std::string force_write_arg("--force-write");

class help_mock {
public:
    explicit help_mock(bool& called) : called_(called) { }

    void operator()(const std::string& description) {
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

dogen::knitter::program_options_parser setup_parser(
    std::vector<std::string> options,
    bool& help_called,
    bool& version_called) {

    logger lg(logger_factory(test_suite));
    BOOST_LOG_SEV(lg, debug) << "options: " << options;
    dogen::knitter::program_options_parser r(options);
    r.help_function(help_mock_factory(help_called));
    r.version_function(version_mock_factory(version_called));
    return r;
}

void check_exception(std::vector<std::string> options, std::string expected) {
    bool help(false);
    bool version(false);
    auto parser(setup_parser(options, help, version));

    using dogen::knitter::parser_validation_error;
    auto lambda([&](const parser_validation_error& e) -> bool {
            const std::string msg(e.what());
            logger lg(logger_factory(test_suite));

            BOOST_LOG_SEV(lg, debug) << "Caught an exception: '" << msg;
            if (!boost::contains(msg, expected)) {
                BOOST_LOG_SEV(lg, error)
                    << "Unexpected exception text. Expected: '" << expected;
                return false;
            }
            BOOST_LOG_SEV(lg, debug) << "Text is the expected message";
            return true;
        });

    BOOST_CHECK_EXCEPTION(parser.parse(), parser_validation_error, lambda);
    BOOST_CHECK(!help);
    BOOST_CHECK(!version);
}

dogen::options::knitting_options
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

BOOST_AUTO_TEST_SUITE(program_options_parser_tests)

BOOST_AUTO_TEST_CASE(supplying_help_argument_results_in_help) {
    SETUP_TEST_LOG("supplying_help_argument_results_in_help");
    check_help(std::vector<std::string> { help_arg });
}

BOOST_AUTO_TEST_CASE(supplying_help_argument_with_no_help_function_results_in_no_op) {
    SETUP_TEST_LOG_SOURCE("supplying_help_argument_with_no_help_function_results_in_no_op");
    bool version(false);
    const std::vector<std::string> o = { help_arg };
    BOOST_LOG_SEV(lg, debug) << "options: " << o;

    dogen::knitter::program_options_parser parser(o);
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

    dogen::knitter::program_options_parser parser(o);
    parser.help_function(help_mock_factory(help));
    const auto r(parser.parse());

    BOOST_CHECK(!r);
    BOOST_CHECK(!help);
}

BOOST_AUTO_TEST_CASE(supplying_no_arguments_throws) {
    SETUP_TEST_LOG("supplying_no_arguments_throws");
    check_exception(std::vector<std::string> {}, missing_target);
}

BOOST_AUTO_TEST_CASE(supplying_modeling_options_results_in_expected_options) {
    SETUP_TEST_LOG_SOURCE("supplying_modeling_options_results_in_expected_options");

    const std::vector<std::string> o = {
        target_arg, target_value_external_path_arg
    };

    const auto ko(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "options: " << ko;

    const auto io(ko.input());
    BOOST_CHECK(io.target().path().string() == target_value_arg);
    BOOST_CHECK(io.target().external_modules() == external_modules_value_arg);
}

BOOST_AUTO_TEST_CASE(not_supplying_modeling_options_other_than_target_results_in_expected_options) {
    SETUP_TEST_LOG_SOURCE("not_supplying_modeling_options_other_than_target_results_in_expected_options");

    const std::vector<std::string> o = {
        target_arg, target_value_arg,
    };

    const auto ko(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "options: " << ko;

    const auto is(ko.input());
    BOOST_CHECK(is.target().path().string() == target_value_arg);
    BOOST_CHECK(is.target().external_modules().empty());
}

BOOST_AUTO_TEST_CASE(supplying_arguments_without_target_throws) {
    SETUP_TEST_LOG("supplying_arguments_without_target_throws");
    const std::vector<std::string> o = {
        cpp_project_dir_arg, cpp_project_dir_value_arg
    };
    check_exception(o, missing_target);
}

BOOST_AUTO_TEST_CASE(supplying_cpp_arguments_results_in_expected_options) {
    SETUP_TEST_LOG_SOURCE("supplying_cpp_arguments_results_in_expected_options");
    const std::vector<std::string> o = {
        target_arg, target_value_arg,
        cpp_project_dir_arg, cpp_project_dir_value_arg
    };

    const auto ko(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "options: " << ko;

    const auto co(ko.cpp());
    BOOST_CHECK(co.project_directory_path() == cpp_project_dir_value_arg);
}

BOOST_AUTO_TEST_CASE(not_supplying_cpp_arguments_results_in_expected_options) {
    SETUP_TEST_LOG_SOURCE("not_supplying_cpp_arguments_results_in_expected_options");
    const std::vector<std::string> o = { target_arg, target_value_arg };

    const auto ko(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "options: " << ko;

    const auto co(ko.cpp());
    BOOST_CHECK(!co.project_directory_path().empty());
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
        cpp_project_dir_arg, cpp_project_dir_value_arg,
        help_arg
    };
    check_help(o);
}

BOOST_AUTO_TEST_CASE(supplying_valid_arguments_with_version_results_in_version) {
    SETUP_TEST_LOG("supplying_valid_arguments_with_version_results_in_version");
    const std::vector<std::string> o = {
        target_arg, target_value_arg,
        cpp_project_dir_arg, cpp_project_dir_value_arg,
        version_arg
    };
    check_version(o);
}

BOOST_AUTO_TEST_CASE(supplying_project_directory_results_in_expected_options) {
    SETUP_TEST_LOG_SOURCE("supplying_project_directory_results_in_expected_options");
    const std::vector<std::string> o = {
        target_arg, target_value_arg,
        cpp_project_dir_arg, cpp_project_dir_value_arg
    };

    const auto ko(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "options: " << ko;

    const auto co(ko.cpp());
    BOOST_CHECK(co.project_directory_path() == cpp_project_dir_value_arg);
}

BOOST_AUTO_TEST_CASE(not_supplying_output_options_results_in_expected_options) {
    SETUP_TEST_LOG_SOURCE("not_supplying_output_options_results_in_expected_options");
    const std::vector<std::string> o = { target_arg, target_value_arg };
    const auto ko(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "options: " << ko;

    const auto oo(ko.output());
    BOOST_CHECK(!oo.delete_extra_files());
    BOOST_CHECK(!oo.force_write());
}

BOOST_AUTO_TEST_CASE(supplying_output_options_results_in_expected_options) {
    SETUP_TEST_LOG_SOURCE("supplying_output_options_results_in_expected_options");
    const std::vector<std::string> o = {
        target_arg, target_value_arg,
        delete_extra_files_arg,
        force_write_arg
    };
    const auto ko(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "options: " << ko;

    const auto oo(ko.output());
    BOOST_CHECK(oo.delete_extra_files());
    BOOST_CHECK(oo.force_write());
}

BOOST_AUTO_TEST_CASE(supplying_verobose_flag_results_in_options_with_verbose_on) {
    SETUP_TEST_LOG_SOURCE("supplying_verobose_flag_results_in_options_with_verbose_on");

    const std::vector<std::string> o = {
        target_arg, target_value_arg,
        verbose_arg
    };
    const auto ko(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "options: " << ko;
    BOOST_CHECK(ko.verbose());
}

BOOST_AUTO_TEST_CASE(not_supplying_verobose_flag_results_in_options_with_verbose_off) {
    SETUP_TEST_LOG_SOURCE("not_supplying_verobose_flag_results_in_options_with_verbose_off");

    const std::vector<std::string> o = { target_arg, target_value_arg };
    const auto ko(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "options: " << ko;
    BOOST_CHECK(!ko.verbose());
}

BOOST_AUTO_TEST_SUITE_END()
