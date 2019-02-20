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
#include "masd.dogen.utility/types/test/logging.hpp"
#include "masd.dogen.utility/types/io/optional_io.hpp"
#include "masd.dogen.utility/types/io/vector_io.hpp"
#include "masd.dogen.cli/io/configuration_io.hpp"
#include "masd.dogen.cli/types/configuration.hpp"
#include "masd.dogen.cli/types/injector_factory.hpp"
#include "masd.dogen.cli/types/command_line_parser.hpp"
#include "masd.dogen.cli/types/program_options_parser.hpp"
#include "masd.dogen.cli/types/program_options_parser.hpp"
#include "masd.dogen.cli/types/parser_exception.hpp"

using namespace masd::dogen::utility::log;
using masd::dogen::cli::injector_factory;
using masd::dogen::cli::command_line_parser;
using masd::dogen::cli::weaving_configuration;
using masd::dogen::cli::conversion_configuration;
using masd::dogen::cli::generation_configuration;
using masd::dogen::cli::program_options_parser;

namespace {

const std::string test_module("masd.dogen.cli.tests");
const std::string test_suite("program_options_parser_tests");

const std::string empty;
const std::string help_msg("Global options:");
const std::string version_msg("MASD Dogen v");
const std::string usage_msg("Usage error: ");
const std::string missing_command_msg("No command supplied.");
const std::string missing_target_msg("Mandatory parameter target is missing");
const std::string unknown_command_msg("Command is invalid or unsupported:");

const std::string unknown_argumemnt("--unknown-argument");
const std::string unknown_command("unknown-command");
const std::string generate_command_arg("generate");
const std::string weave_command_arg("weave");
const std::string convert_command_arg("convert");
const std::string help_arg("--help");
const std::string version_arg("--version");
const std::string invalid_arg("--invalid-argument");
const std::string invalid_value_arg("invalid-value");

const std::string log_level_arg("--log-level");
const std::string log_level_value_arg("info");
const std::string log_directory_arg("--log-directory");
const std::string log_directory_value_arg("some_dir");

const std::string target_arg("--target");
const std::string target_value_arg("some_target");

const std::string output_dir_arg("--output-directory");
const std::string output_dir_value_arg("an output dir");


void check_exception(std::vector<std::string> args, std::string expected) {
    std::ostringstream info, err;
    logger lg(logger_factory(test_suite));

    auto inj(injector_factory::make_injector());
    const auto p(inj.create<std::unique_ptr<command_line_parser>>());

    BOOST_LOG_SEV(lg, debug) << "Arguments: " << args;

    using masd::dogen::cli::parser_exception;
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

    BOOST_CHECK_EXCEPTION(p->parse(args, info, err), parser_exception, lambda);

    const auto info_str(info.str());
    BOOST_LOG_SEV(lg, debug) << "Info stream: '" << info_str << "'";
    BOOST_CHECK(info_str.empty());

    const auto err_str(err.str());
    BOOST_LOG_SEV(lg, debug) << "Error stream: '" << err_str << "'";
    BOOST_CHECK(!err_str.empty());
    BOOST_CHECK(boost::contains(err_str, usage_msg));
}

masd::dogen::cli::configuration
check_valid_arguments(std::vector<std::string> args) {
    std::ostringstream info, err;
    logger lg(logger_factory(test_suite));
    BOOST_LOG_SEV(lg, debug) << "Arguments: " << args;

    auto inj(injector_factory::make_injector());
    const auto p(inj.create<std::unique_ptr<command_line_parser>>());
    const auto r(p->parse(args, info, err));
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

    auto inj(injector_factory::make_injector());
    const auto p(inj.create<std::unique_ptr<command_line_parser>>());
    const auto r(p->parse(args, info, err));
    BOOST_LOG_SEV(lg, debug) << "Options: " << r;
    BOOST_CHECK(!r);

    const auto info_str(info.str());
    BOOST_LOG_SEV(lg, debug) << "Info stream: '" << info_str << "'";
    BOOST_CHECK(!info_str.empty());
    BOOST_CHECK(boost::contains(info_str, help_msg));

    const auto err_str(err.str());
    BOOST_LOG_SEV(lg, debug) << "Error stream: '" << err_str << "'";
    BOOST_CHECK(err_str.empty());
}

void check_version(std::vector<std::string> args) {
    std::ostringstream info, err;
    logger lg(logger_factory(test_suite));
    BOOST_LOG_SEV(lg, debug) << "Arguments: " << args;

    auto inj(injector_factory::make_injector());
    const auto p(inj.create<std::unique_ptr<command_line_parser>>());
    const auto r(p->parse(args, info, err));
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

BOOST_AUTO_TEST_CASE(supplying_unknown_command_throws) {
    SETUP_TEST_LOG("supplying_unknown_command_throws");
    check_exception(std::vector<std::string> { unknown_command },
        unknown_command_msg);
}

BOOST_AUTO_TEST_CASE(supplying_valid_generation_invocation_results_in_expected_options) {
    SETUP_TEST_LOG_SOURCE("supplying_valid_generation_invocation_results_in_expected_options");

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

/*
BOOST_AUTO_TEST_CASE_IGNORE(not_supplying_coding_options_other_than_target_results_in_expected_options) {
    SETUP_TEST_LOG_SOURCE("not_supplying_coding_options_other_than_target_results_in_expected_options");

    const std::vector<std::string> o = {
        target_arg, target_value_arg,
    };

    const auto ko(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "options: " << ko;

    using boost::algorithm::ends_with;
    const auto gs(ko.target().generic_string());
    BOOST_CHECK(ends_with(gs, target_value_arg));
}

BOOST_AUTO_TEST_CASE_IGNORE(supplying_arguments_without_target_throws) {
    SETUP_TEST_LOG("supplying_arguments_without_target_throws");
    const std::vector<std::string> o = {
        output_dir_arg, output_dir_value_arg
    };
    check_exception(o, missing_target_msg);
}

BOOST_AUTO_TEST_CASE_IGNORE(supplying_output_dir_results_in_expected_options) {
    SETUP_TEST_LOG_SOURCE("supplying_output_dir_results_in_expected_options");
    const std::vector<std::string> o = {
        target_arg, target_value_arg,
        output_dir_arg, output_dir_value_arg
    };

    const auto ko(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "options: " << ko;

    using boost::algorithm::ends_with;
    const auto gs(ko.output_directory_path().generic_string());
    BOOST_CHECK(ends_with(gs, output_dir_value_arg));
}

BOOST_AUTO_TEST_CASE_IGNORE(not_supplying_output_dir_results_in_expected_options) {
    SETUP_TEST_LOG_SOURCE("not_supplying_output_dir_results_in_expected_options");
    const std::vector<std::string> o = { target_arg, target_value_arg };

    const auto ko(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "options: " << ko;
    BOOST_CHECK(!ko.output_directory_path().empty());
}

BOOST_AUTO_TEST_CASE_IGNORE(supplying_an_invalid_argument_throws) {
    SETUP_TEST_LOG("supplying_an_invalid_argument_throws");
    typedef std::vector<std::string> vector;
    check_exception(vector { invalid_arg }, unknown_option);
    check_exception(vector { invalid_arg, help_arg }, unknown_option);
    check_exception(vector { help_arg, invalid_arg }, unknown_option);
    check_exception(vector { invalid_arg, version_arg }, unknown_option);
    check_exception(vector { version_arg, invalid_arg }, unknown_option);
}

BOOST_AUTO_TEST_CASE_IGNORE(supplying_valid_arguments_with_help_results_in_help) {
    SETUP_TEST_LOG("supplying_valid_arguments_with_help_results_in_help");
    const std::vector<std::string> o = {
        target_arg, target_value_arg,
        output_dir_arg, output_dir_value_arg,
        help_arg
    };
    check_help(o);
}

BOOST_AUTO_TEST_CASE_IGNORE(supplying_valid_arguments_with_version_results_in_version) {
    SETUP_TEST_LOG("supplying_valid_arguments_with_version_results_in_version");
    const std::vector<std::string> o = {
        target_arg, target_value_arg,
        output_dir_arg, output_dir_value_arg,
        version_arg
    };
    check_version(o);
}

BOOST_AUTO_TEST_CASE_IGNORE(supplying_output_directory_results_in_expected_options) {
    SETUP_TEST_LOG_SOURCE("supplying_output_directory_results_in_expected_options");
    const std::vector<std::string> o = {
        target_arg, target_value_arg,
        output_dir_arg, output_dir_value_arg
    };

    const auto ko(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "options: " << ko;

    using boost::algorithm::ends_with;
    const auto gs(ko.output_directory_path().generic_string());
    BOOST_CHECK(ends_with(gs, output_dir_value_arg));
}

BOOST_AUTO_TEST_CASE_IGNORE(not_supplying_output_options_results_in_expected_options) {
    SETUP_TEST_LOG_SOURCE("not_supplying_output_options_results_in_expected_options");
    const std::vector<std::string> o = { target_arg, target_value_arg };
    const auto ko(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "options: " << ko;
}

BOOST_AUTO_TEST_CASE_IGNORE(supplying_output_options_results_in_expected_options) {
    SETUP_TEST_LOG_SOURCE("supplying_output_options_results_in_expected_options");
    const std::vector<std::string> o = {
        target_arg, target_value_arg
    };
    const auto ko(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "options: " << ko;
}

BOOST_AUTO_TEST_CASE_IGNORE(supplying_log_options_results_in_options_with_expected_log_options) {
    SETUP_TEST_LOG_SOURCE("supplying_log_options_results_in_options_with_expected_log_options");

    const std::vector<std::string> o = {
        target_arg, target_value_arg,
        log_level_arg, log_level_value_arg,
        log_directory_arg, log_directory_value_arg
    };
    const auto ko(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "options: " << ko;
    BOOST_CHECK(ko.log_level() == log_level_value_arg);

    using boost::algorithm::ends_with;
    const auto gs(ko.log_file().generic_string());
    const auto log_filename(log_directory_value_arg +
        "/dogen.knitter." + target_value_arg + ".log");
    BOOST_LOG_SEV(lg, debug) << "expected to end with: " << log_filename;
    BOOST_CHECK(ends_with(gs, log_filename));
}

BOOST_AUTO_TEST_CASE_IGNORE(not_supplying_log_level_results_in_a_default_log_level_set) {
    SETUP_TEST_LOG_SOURCE("not_supplying_log_level_results_in_a_default_log_level_set");

    const std::vector<std::string> o = { target_arg, target_value_arg };
    const auto ko(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "options: " << ko;
    BOOST_CHECK(!ko.log_level().empty());
    BOOST_CHECK(!ko.log_file().empty());
}
*/
BOOST_AUTO_TEST_SUITE_END()
