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
#include <sstream>
#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen.utility/types/test/logging.hpp"
#include "dogen.utility/types/io/optional_io.hpp"
#include "dogen.utility/types/io/vector_io.hpp"
#include "dogen.cli/io/configuration_io.hpp"
#include "dogen.cli/types/configuration.hpp"
#include "dogen.cli/types/command_line_parser.hpp"
#include "dogen.cli/types/program_options_parser.hpp"
#include "dogen.cli/types/program_options_parser.hpp"
#include "dogen.cli/types/parser_exception.hpp"

using namespace dogen::utility::log;
using dogen::cli::generation_configuration;
using dogen::cli::program_options_parser;

namespace {

const std::string test_module("dogen.cli.tests");
const std::string test_suite("program_options_parser_tests");

const std::string empty;
const std::string help_general_msg("Global options:");
const std::string help_command_msg("Displaying options specific");
const std::string version_msg("MASD Dogen v");
const std::string usage_msg("Usage error: ");
const std::string missing_command_msg("No command supplied.");
const std::string missing_target_msg("Mandatory parameter target is missing");
const std::string invalid_command_msg("Command is invalid or unsupported:");
const std::string invalid_argument_msg("unrecognised option");
const std::string invalid_option_msg("Option is not valid");
const std::string invalid_log_level_msg("Log level is invalid");

const std::string invalid_command_arg("invalid-command");
const std::string generate_command_arg("generate");
const std::string convert_command_arg("convert");
const std::string help_arg("--help");
const std::string version_arg("--version");
const std::string invalid_arg("--invalid-argument");
const std::string invalid_value_arg("invalid-value");

const std::string log_enabled_arg("--log-enabled");
const std::string log_level_arg("--log-level");
const std::string log_level_value_arg("info");
const std::string log_level_invalid_value_arg("invalid");

const std::string target_arg("--target");
const std::string target_value_arg("some_target");

const std::string output_dir_arg("--output-directory");
const std::string output_dir_value_arg("an output dir");


void check_exception(std::vector<std::string> args, std::string expected) {
    std::ostringstream info, err;
    logger lg(logger_factory(test_suite));

    program_options_parser p;
    BOOST_LOG_SEV(lg, debug) << "Arguments: " << args;

    using dogen::cli::parser_exception;
    auto lambda([&](const parser_exception& e) -> bool {
            const std::string msg(e.what());
            logger lg(logger_factory(test_suite));

            BOOST_LOG_SEV(lg, debug) << "Caught an exception: '" << msg;
            if (!boost::contains(msg, expected)) {
                BOOST_LOG_SEV(lg, error)
                    << "Unexpected exception text. Expected: '" << expected;
                return false;
            }
            BOOST_LOG_SEV(lg, debug) << "Text is the expected message.";
            return true;
        });

    BOOST_CHECK_EXCEPTION(p.parse(args, info, err), parser_exception, lambda);

    const auto info_str(info.str());
    BOOST_LOG_SEV(lg, debug) << "Info stream: '" << info_str << "'";
    BOOST_CHECK(info_str.empty());

    const auto err_str(err.str());
    BOOST_LOG_SEV(lg, debug) << "Error stream: '" << err_str << "'";
    BOOST_CHECK(!err_str.empty());
    BOOST_CHECK(boost::contains(err_str, usage_msg));
}

dogen::cli::configuration
check_valid_arguments(std::vector<std::string> args) {
    std::ostringstream info, err;
    logger lg(logger_factory(test_suite));
    BOOST_LOG_SEV(lg, debug) << "Arguments: " << args;

    program_options_parser p;
    const auto r(p.parse(args, info, err));
    BOOST_LOG_SEV(lg, debug) << "Options: " << r;
    BOOST_CHECK(r);

    const auto info_str(info.str());
    BOOST_LOG_SEV(lg, debug) << "Info stream: '" << info_str << "'";
    BOOST_CHECK(info_str.empty());

    const auto err_str(err.str());
    BOOST_LOG_SEV(lg, debug) << "Error stream: '" << err_str << "'";
    BOOST_CHECK(err_str.empty());

    return *r;
}

void check_help(const std::vector<std::string>& args) {
    std::ostringstream info, err;
    logger lg(logger_factory(test_suite));
    BOOST_LOG_SEV(lg, debug) << "Arguments: " << args;

    program_options_parser p;
    const auto r(p.parse(args, info, err));
    BOOST_LOG_SEV(lg, debug) << "Options: " << r;
    BOOST_CHECK(!r);

    const auto info_str(info.str());
    BOOST_LOG_SEV(lg, debug) << "Info stream: '" << info_str << "'";
    BOOST_CHECK(!info_str.empty());
    BOOST_CHECK(boost::contains(info_str, help_general_msg) ||
        boost::contains(info_str, help_command_msg));

    const auto err_str(err.str());
    BOOST_LOG_SEV(lg, debug) << "Error stream: '" << err_str << "'";
    BOOST_CHECK(err_str.empty());
}

void check_version(std::vector<std::string> args) {
    std::ostringstream info, err;
    logger lg(logger_factory(test_suite));
    BOOST_LOG_SEV(lg, debug) << "Arguments: " << args;

    program_options_parser p;
    const auto r(p.parse(args, info, err));
    BOOST_LOG_SEV(lg, debug) << "Options: " << r;
    BOOST_CHECK(!r);

    const auto info_str(info.str());
    BOOST_LOG_SEV(lg, debug) << "Info stream: '" << info_str << "'";
    BOOST_CHECK(!info_str.empty());
    BOOST_CHECK(boost::contains(info_str, version_msg));

    const auto err_str(err.str());
    BOOST_LOG_SEV(lg, debug) << "Error stream: '" << err_str << "'";
    BOOST_CHECK(err_str.empty());
}

}

BOOST_AUTO_TEST_SUITE(program_options_parser_tests)

BOOST_AUTO_TEST_CASE(supplying_help_argument_with_no_command_results_in_help) {
    SETUP_TEST_LOG("supplying_help_argument_with_no_command_results_in_help");
    check_help(std::vector<std::string> { help_arg });
}

BOOST_AUTO_TEST_CASE(supplying_version_argument_results_in_just_printing_version) {
    SETUP_TEST_LOG("supplying_version_argument_results_in_just_printing_version");
    check_version(std::vector<std::string> { version_arg });
}

BOOST_AUTO_TEST_CASE(supplying_no_arguments_throws) {
    SETUP_TEST_LOG("supplying_no_arguments_throws");
    check_exception(std::vector<std::string> {}, missing_command_msg);
}

BOOST_AUTO_TEST_CASE(supplying_invalid_command_throws) {
    SETUP_TEST_LOG("supplying_invalid_command_throws");
    check_exception(std::vector<std::string> { invalid_command_arg },
        invalid_command_msg);
}

BOOST_AUTO_TEST_CASE(supplying_valid_generation_invocation_results_in_expected_options) {
    SETUP_TEST_LOG("supplying_valid_generation_invocation_results_in_expected_options");

    const std::vector<std::string> args = {
        generate_command_arg,
        target_arg, target_value_arg
    };

    const auto o(check_valid_arguments(args));
    BOOST_CHECK(o.cli().activity().type() == typeid(generation_configuration));
    const auto gc(boost::get<generation_configuration>(o.cli().activity()));

    using boost::algorithm::ends_with;
    const auto gs(gc.target().generic_string());
    BOOST_CHECK(ends_with(gs, target_value_arg));
}

BOOST_AUTO_TEST_CASE(supplying_arguments_without_target_throws) {
    SETUP_TEST_LOG("supplying_arguments_without_target_throws");
    const std::vector<std::string> args = {
        generate_command_arg,
        output_dir_arg, output_dir_value_arg
    };
    check_exception(args, missing_target_msg);
}

BOOST_AUTO_TEST_CASE(supplying_output_dir_results_in_expected_options) {
    SETUP_TEST_LOG_SOURCE("supplying_output_dir_results_in_expected_options");
    const std::vector<std::string> args = {
        generate_command_arg,
        target_arg, target_value_arg,
        output_dir_arg, output_dir_value_arg
    };

    const auto o(check_valid_arguments(args));
    BOOST_CHECK(o.cli().activity().type() == typeid(generation_configuration));
    const auto gc(boost::get<generation_configuration>(o.cli().activity()));

    using boost::algorithm::ends_with;
    const auto gs(gc.output_directory().generic_string());
    BOOST_CHECK(ends_with(gs, output_dir_value_arg));
}

BOOST_AUTO_TEST_CASE(not_supplying_output_dir_results_in_expected_options) {
    SETUP_TEST_LOG_SOURCE("not_supplying_output_dir_results_in_expected_options");
    const std::vector<std::string> args = {
        generate_command_arg,
        target_arg, target_value_arg
    };

    const auto o(check_valid_arguments(args));
    BOOST_CHECK(o.cli().activity().type() == typeid(generation_configuration));
    const auto gc(boost::get<generation_configuration>(o.cli().activity()));

    const auto gs(gc.output_directory().generic_string());
    BOOST_CHECK(!gs.empty());
}

BOOST_AUTO_TEST_CASE(supplying_an_invalid_command_or_argument_throws) {
    SETUP_TEST_LOG("supplying_an_invalid_command_or_argument_throws");
    using vector = std::vector<std::string>;
    check_exception(vector { invalid_arg }, missing_command_msg);
    check_exception(vector { generate_command_arg, invalid_arg },
        invalid_argument_msg);
    check_exception(vector { convert_command_arg, invalid_arg },
        invalid_argument_msg);
    check_exception(vector { invalid_command_arg, help_arg },
        invalid_command_msg);
}

BOOST_AUTO_TEST_CASE(supplying_help_argument_with_invalid_command_results_in_help) {
    SETUP_TEST_LOG("supplying_help_argument_with_invalid_command_results_in_help");
    check_help(std::vector<std::string> { invalid_arg, help_arg });
}

BOOST_AUTO_TEST_CASE(supplying_valid_arguments_with_help_results_in_help) {
    SETUP_TEST_LOG("supplying_valid_arguments_with_help_results_in_help");
    const std::vector<std::string> args = {
        generate_command_arg,
        target_arg, target_value_arg,
        output_dir_arg, output_dir_value_arg,
        help_arg
    };
    check_help(args);
}

BOOST_AUTO_TEST_CASE(supplying_valid_arguments_with_version_throws) {
    SETUP_TEST_LOG("supplying_valid_arguments_with_version_throws");
    const std::vector<std::string> args = {
        generate_command_arg,
        target_arg, target_value_arg,
        output_dir_arg, output_dir_value_arg,
        version_arg
    };
    check_exception(args, invalid_option_msg);
}


BOOST_AUTO_TEST_CASE(supplying_log_options_results_in_options_with_expected_log_options) {
    SETUP_TEST_LOG_SOURCE("supplying_log_options_results_in_options_with_expected_log_options");

    const std::vector<std::string> args = {
        generate_command_arg,
        target_arg, target_value_arg,
        log_enabled_arg,
        log_level_arg, log_level_value_arg
    };
    const auto o(check_valid_arguments(args));
    BOOST_LOG_SEV(lg, debug) << "options: " << o;
    BOOST_REQUIRE(o.logging());
    const auto& l(*o.logging());
    BOOST_CHECK(l.severity() == log_level_value_arg);

    using boost::algorithm::ends_with;
    const auto fn("cli.generate." + target_value_arg);

    BOOST_LOG_SEV(lg, debug) << "expected to end with: " << fn;
    BOOST_CHECK(ends_with(l.filename(), fn));
}

BOOST_AUTO_TEST_CASE(supplying_invalid_log_options_throws) {
    SETUP_TEST_LOG_SOURCE("supplying_invalid_log_options_throws");

    const std::vector<std::string> args = {
        generate_command_arg,
        target_arg, target_value_arg,
        log_enabled_arg,
        log_level_arg, log_level_invalid_value_arg
    };

    check_exception(args, invalid_log_level_msg);
}

BOOST_AUTO_TEST_CASE(not_supplying_log_level_results_in_disabling_logging) {
    SETUP_TEST_LOG_SOURCE("not_supplying_log_level_results_in_disabling_logging");

    const std::vector<std::string> args = {
        generate_command_arg,
        target_arg, target_value_arg
    };
    const auto o(check_valid_arguments(args));
    BOOST_LOG_SEV(lg, debug) << "options: " << o;
    BOOST_CHECK(!o.logging());
}

BOOST_AUTO_TEST_SUITE_END()
