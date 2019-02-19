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
#include <iomanip>
#include <boost/program_options.hpp>
#include <boost/throw_exception.hpp>
#include <boost/filesystem/operations.hpp>
#include "masd.dogen/version.hpp"
#include "masd.dogen.utility/types/log/logging_configuration.hpp"
#include "masd.dogen.cli/types/parser_exception.hpp"
#include "masd.dogen.cli/types/program_options_parser.hpp"

namespace {

const std::string indent("   ");
const std::string log_file_prefix("dogen.cli.");

const std::string more_information("Try --help' for more information.");
const std::string knitter_product("MASD Dogen v" DOGEN_VERSION);
const std::string knitter_build_info(DOGEN_BUILD_INFO);
const std::string usage_error_msg("Usage error: ");
const std::string fatal_error_msg("Fatal Error: " );
const std::string no_command_msg("No command supplied. ");
const std::string code_generation_failure("Code generation failure.");
const std::string log_file_msg("See the log file for details: ");
const std::string errors_msg(" finished with errors.");

const std::string generate_command_name("generate");
const std::string generate_command_desc(
    "Generates source code from input models.");
const std::string convert_command_name("convert");
const std::string convert_command_desc(
    "Converts a model from one codec to another. ");
const std::string weave_command_name("weave");
const std::string weave_command_desc(
    "Weaves one or more template files into its final output. ");

const std::string help_arg("help");
const std::string version_arg("version");
const std::string command_arg("command");
const std::string tracing_enabled_arg("tracing-enabled");
const std::string tracing_level_arg("tracing-level");
const std::string tracing_level_detail("detail");
const std::string tracing_level_summary("summary");
const std::string tracing_guids_enabled_arg("tracing-guids-enabled");
const std::string tracing_format_arg("tracing-format");
const std::string tracing_format_org_mode("org-mode");
const std::string tracing_format_markdown("markdown");
const std::string tracing_output_directory_arg("tracing-output-directory");
const std::string tracing_default_directory("tracing");

const std::string logging_log_enabled_arg("log-enabled");
const std::string logging_log_directory_arg("log-directory");
const std::string logging_log_level_arg("log-level");
const std::string logging_log_level_trace("trace");
const std::string logging_log_level_debug("debug");
const std::string logging_log_level_info("info");
const std::string logging_log_level_warn("warn");
const std::string logging_log_level_error("error");
const std::string logging_default_log_directory("log");
const std::string generate_target_arg("target");
const std::string generate_output_dir_arg("output-directory");
const std::string convert_source_arg("source");
const std::string convert_destination_arg("destination");
const std::string weaving_target_arg("target");

const std::string invalid_option("Option is not valid for command: ");
const std::string invalid_command("Command is invalid or unsupported: ");
const std::string missing_target("Mandatory parameter target is missing. ");
const std::string invalid_tracing_level("Tracing level is invalid: ");
const std::string invalid_log_level("Tracing level is invalid: ");
const std::string invalid_format("Tracing format is invalid: ");

using boost::program_options::value;
using boost::program_options::variables_map;
using boost::program_options::options_description;
using boost::program_options::positional_options_description;
using masd::dogen::cli::configuration;
using masd::dogen::cli::parser_exception;
using masd::dogen::cli::weaving_configuration;
using masd::dogen::cli::generation_configuration;
using masd::dogen::cli::conversion_configuration;
using masd::dogen::utility::log::logging_configuration;
using masd::dogen::utility::log::severity_level;

/**
 * @brief Creates the the top-level option descriptions.
 */
options_description make_top_level_options_description() {
    options_description god("General");
    god.add_options()
        ("help,h", "Display usage and exit.")
        ("version,v", "Output version information and exit.");

    options_description r;
    r.add(god);

    options_description lod("Logging");
    lod.add_options()
        ("log-enabled,e", "Generate a log file.")
        ("log-directory,g", value<std::string>(),
            "Directory to place the log file in. Defaults to 'log'.")
        ("log-level,l", value<std::string>(),
            "What level to use for logging. Valid values: trace, debug, info, "
            "warn, error. Defaults to 'info'.");
    r.add(lod);

    options_description tod("Tracing");
    tod.add_options()
        ("tracing-enabled", "Generate metrics about executed transforms.")
        ("tracing-level", "Level at which to trace. "
            "Valid values: detail, summary.")
        ("tracing-guids-enabled", "Use guids in tracing metrics, Not"
            "  recommended when making comparisons between runs.")
        ("tracing-format", "Format to use for tracing metrics. "
            "Valid values: org-mode, markdown")
        ("tracing-output-directory", "Directory in which to dump probe data. "
            "Only used if transforms tracing is enabled.");
    r.add(tod);

    options_description cod("Commands");
    cod.add_options()
        ("command", value<std::string>(), "Command to execute. "
            "Available commands: generate, convert, weave.")
        ("args", value<std::vector<std::string> >(),
            "Arguments for command");
    r.add(cod);
    return r;
}

/**
 * @brief Creates the positional options.
 */
positional_options_description make_positional_options() {
    positional_options_description r;
    r.add("command", 1).add("args", -1);
    return r;
}

/**
 * @brief Creates the options related to code generation.
 */
options_description make_generate_options_description() {
    options_description r("Generation");
    r.add_options()
        ("target,t",
            value<std::string>(),
            "Model to generate code for, in any of the supported formats.")
        ("output-directory,o",
            value<std::string>(), "Output directory for the generated code. "
            "Defaults to the current working directory.");

    return r;
}

/**
 * @brief Creates the options related to conversion.
 */
options_description make_convert_options_description() {
    options_description r("Convert");
    r.add_options()
        ("source,s",
            value<std::string>(),
            "Input model to read, in any of the supported formats.")
        ("destination,d",
            value<std::string>(),
            "Output model to convert to, in any of the supported formats.");

    return r;
}

/**
 * @brief Creates the options related to weaving.
 */
options_description make_weave_options_description() {
    options_description r("Weave");
    r.add_options()
        ("target,t",
            value<std::string>(),
            "File or directory containing supported templates.");

    return r;
}

/**
 * @brief ensures the supplied command is a valid command. If not,
 * reports the erros into stream and throws.
 */
void validate_command_name(const std::string& command_name,
    std::ostream& err) {
    const bool is_valid_command_name(
        command_name == generate_command_name ||
        command_name == convert_command_name ||
        command_name == weave_command_name);

    if (is_valid_command_name)
        return;

    err << "Error: '" << command_name << "' is not a valid command. "
        << more_information  << std::endl;

    BOOST_THROW_EXCEPTION(parser_exception(invalid_command + command_name));
}

/**
 * @brief Prints the header of the help text, applicable to all cases.
 */
void print_help_header(std::ostream& s) {
    s << "Dogen is a Model Driven Engineering tool that processes models"
      << " encoded in supported codecs." << std::endl
      << "Dogen is created by the MASD project. "
      << "For details, type --version."
      << std::endl;
}

/**
 * @brief Prints the top-level help text when no command is supplied.
 *
 * @param od top-level options.
 * @param s info stream.
 */
void print_help(const boost::program_options::options_description& od,
    std::ostream& s) {
    print_help_header(s);
    s << "Dogen uses a command-based interface: <command> <options>. "
      << std::endl << "See below for a list of valid commands. "
      << "For command specific options, type <command> --help." << std::endl
      << std::endl << "Global options: " << std::endl << od << std::endl
      <<  "Command information: "<< std::endl << std::endl;

    auto lambda([&](const std::string& name, const std::string& desc) {
                    const unsigned int command_width(15);
                    s << indent << std::setfill(' ') << std::left
                      << std::setw(command_width)
                      << name << desc << std::endl;
                });
    lambda(generate_command_name, generate_command_desc);
    lambda(convert_command_name, convert_command_desc);
    lambda(weave_command_name, weave_command_desc);
}

/**
 * @brief Prints help text at the command level.
 *
 * @param command_name name of the command to print help for.
 * @param od command options.
 * @param s info stream.
 */
void print_help_command(const std::string& command_name,
    const boost::program_options::options_description& od, std::ostream& s) {
    print_help_header(s);
    s << "Displaying options specific to the " << command_name << " command. "
      << std::endl
      << "For global options, type --help." << std::endl << std::endl
      << od;
}

/**
 * @brief Print the program's version details.
 *
 * @param s info stream.
 */
void version(std::ostream& s) {
    s << knitter_product << std::endl
      << "Copyright (C) 2015-2017 Domain Driven Consulting Plc."
      << std::endl
      << "Copyright (C) 2012-2015 Marco Craveiro." << std::endl
      << "License GPLv3: GNU GPL version 3 or later "
      << "<http://gnu.org/licenses/gpl.html>." << std::endl
      << "This is free software: you are free to change and redistribute it."
      << std::endl << "There is NO WARRANTY, to the extent permitted by law."
      << std::endl;


    if (!knitter_build_info.empty()) {
        s << knitter_build_info << std::endl;
        s << "IMPORTANT: build details are NOT for security purposes."
          << std::endl;
    }
}

/**
 * @brief Contains the processing logic for when the user did not
 * supply a command in the command line.
 */
boost::optional<configuration>
handle_no_command(const bool has_version, const bool has_help,
    const options_description& od, std::ostream& info, std::ostream& err) {
    /*
     * The only valid options are help or version, so if those are
     * not present we can safely throw.
     */
    if (!has_version && !has_help) {
        err << usage_error_msg << no_command_msg
            << more_information << std::endl;
        BOOST_THROW_EXCEPTION(parser_exception(no_command_msg));
    }

    /*
     * Note that we do not mind if the user has supplied both help
     * and version - help takes priority.
     */
    if (has_help)
        print_help(od, info);
    else if (has_version)
        version(info);

    return boost::optional<configuration>();
}

/**
 * @brief Reads the tracing configuration from the variables map.
 */
boost::optional<masd::dogen::tracing_configuration> read_tracing_configuration(
    const std::string& model_name, const variables_map& vm) {

    const bool enabled(vm.count(tracing_enabled_arg) != 0);
    if (!enabled)
        return boost::optional<masd::dogen::tracing_configuration>();

    masd::dogen::tracing_configuration r;
    r.guids_enabled(vm.count(tracing_guids_enabled_arg) != 0);

    using masd::dogen::tracing_level;
    if (vm.count(tracing_level_arg)) {
        const auto s(vm[tracing_level_arg].as<std::string>());
        if (s == tracing_level_detail)
            r.level(tracing_level::detail);
        if (s == tracing_level_summary)
            r.level(tracing_level::summary);
        else
            BOOST_THROW_EXCEPTION(parser_exception(invalid_tracing_level + s));
    } else if (enabled)
        r.level(tracing_level::summary);

    using masd::dogen::tracing_format;
    if (vm.count(tracing_format_arg)) {
        const auto s(vm[tracing_format_arg].as<std::string>());
        if (s == tracing_format_org_mode)
            r.format(tracing_format::org_mode);
        else if (s == tracing_format_markdown)
            r.format(tracing_format::markdown);
        else
            BOOST_THROW_EXCEPTION(parser_exception(invalid_format + s));
    } else if (enabled)
        r.format(tracing_format::org_mode);

    const auto out_dir =
        [&]() {
            using boost::filesystem::absolute;
            if (vm.count(tracing_output_directory_arg) == 0) {
                if (!enabled)
                    return boost::filesystem::path();
                return absolute(tracing_default_directory) / model_name;
            }

            const auto s(vm[tracing_output_directory_arg].as<std::string>());
            return absolute(s) / model_name;
        }();
    return r;
}

boost::optional<masd::dogen::diffing_configuration> read_diffing_configuration(
    const std::string& /*model_name*/, const variables_map& vm) {

    const bool enabled(vm.count(tracing_enabled_arg) != 0);
    if (!enabled)
        return boost::optional<masd::dogen::diffing_configuration>();

    masd::dogen::diffing_configuration r;
    return r;
}

/**
 * @brief Reads the tracing configuration from the variables map.
 */
boost::optional<logging_configuration> read_logging_configuration(
    const std::string& model_name, const variables_map& vm) {
    const auto enabled(vm.count(logging_log_enabled_arg) != 0);
    if (!enabled)
        return boost::optional<logging_configuration>();

    logging_configuration r;
    r.filename(log_file_prefix + model_name);

    if (vm.count(logging_log_level_arg)) {
        const auto s(vm[logging_log_level_arg].as<std::string>());
        if (s == logging_log_level_trace)
            r.severity(severity_level::trace);
        else if (s == logging_log_level_debug)
            r.severity(severity_level::debug);
        else if (s == logging_log_level_info)
            r.severity(severity_level::info);
        else if (s == logging_log_level_warn)
            r.severity(severity_level::warn);
        else if (s == logging_log_level_error)
            r.severity(severity_level::error);
        else
            BOOST_THROW_EXCEPTION(parser_exception(invalid_log_level + s));
    } else  if (enabled)
        r.severity(severity_level::info);

    const boost::filesystem::path out_dir =
        [&]() {
            using boost::filesystem::absolute;
            if (vm.count(logging_log_directory_arg) == 0) {
                if (!enabled)
                    return boost::filesystem::path();
                return absolute(logging_default_log_directory);
            }

            const auto s(vm[logging_log_directory_arg].as<std::string>());
            return absolute(s);
        }();
    r.output_directory(out_dir);

    return r;
}

/**
 * @brief Reads the generation configuration from the variables map.
 */
generation_configuration
read_generation_configuration(const variables_map& vm) {
    generation_configuration r;

    using boost::filesystem::absolute;
    if (vm.count(generate_target_arg)) {
        const auto target_str(vm[generate_target_arg].as<std::string>());
        r.target(absolute(target_str));
    }

    if (!vm.count(generate_output_dir_arg))
        r.output_directory(boost::filesystem::current_path());
    else {
        const auto s(vm[generate_output_dir_arg].as<std::string>());
        r.output_directory(absolute(s));
    }

    return r;
}

/**
 * @brief Reads the conversion configuration from the variables map.
 */
conversion_configuration
read_conversion_configuration(const variables_map& vm) {
    conversion_configuration r;

    using boost::filesystem::absolute;
    if (vm.count(convert_source_arg)) {
        const auto s(vm[convert_source_arg].as<std::string>());
        r.source(absolute(s));
    }

    if (vm.count(convert_destination_arg)) {
        const auto s(vm[convert_destination_arg].as<std::string>());
        r.destination_file_name(s);
    }

    return r;
}

/**
 * @brief Reads the weaving configuration from the variables map.
 */
weaving_configuration read_weaving_configuration(const variables_map& vm) {
    weaving_configuration r;

    using boost::filesystem::absolute;
    if (vm.count(weaving_target_arg)) {
        const auto s(vm[weaving_target_arg].as<std::string>());
        r.target(absolute(s));
    }

    return r;
}

/**
 * @brief Contains the processing logic for when the user supplies a
 * command in the command line.
 */
boost::optional<configuration>
handle_command(const std::string& command_name, const bool has_help,
    const boost::program_options::parsed_options& po, std::ostream& info,
    variables_map& vm) {

    /*
     * Collect all the unrecognized options from the first pass. It
     * includes the positional command name, so we need to erase it.
     */
    using boost::program_options::include_positional;
    using boost::program_options::collect_unrecognized;
    auto options(collect_unrecognized(po.options, include_positional));
    options.erase(options.begin());

    /*
     * For each command we need to setup their set of options, parse
     * them and then generate the appropriate options.
     */
    std::string model_name;
    configuration r;
    using boost::program_options::command_line_parser;
    typedef boost::optional<configuration> empty_config;
    if (command_name == generate_command_name) {
        const auto god(make_generate_options_description());
        if (has_help) {
            print_help_command(generate_command_name, god, info);
            return empty_config();
        }

        store(command_line_parser(options).options(god).run(), vm);
        const auto gc(read_generation_configuration(vm));
        model_name = gc.target().stem().filename().string();
        r.cli().activity(gc);
    } else if (command_name == convert_command_name) {
        const auto cod(make_convert_options_description());
        if (has_help) {
            print_help_command(convert_command_name, cod, info);
            return empty_config();
        }

        store(command_line_parser(options).options(cod).run(), vm);
        const auto cc(read_conversion_configuration(vm));
        model_name = cc.source().stem().filename().string();
        r.cli().activity(cc);
    } else if (command_name == weave_command_name) {
        const auto cod(make_weave_options_description());
        if (has_help) {
            print_help_command(weave_command_name, cod, info);
            return empty_config();
        }

        store(command_line_parser(options).options(cod).run(), vm);
        const auto wc(read_weaving_configuration(vm));
        model_name = wc.target().stem().filename().string();
        r.cli().activity(wc);
    }

    /*
     * Now process the common options. We must do this at the end
     * because we require the model name.
     */
    r.api().tracing(read_tracing_configuration(model_name, vm));
    r.api().diffing(read_diffing_configuration(model_name, vm));
    r.logging(read_logging_configuration(model_name, vm));
    return r;
}

boost::optional<configuration> parse(const std::vector<std::string>& arguments,
    std::ostream& info, std::ostream& err) {
    /*
     * Create the top-level command line options, parse them and
     * retrieve the results of the parsing.
     */
    const options_description tlod(make_top_level_options_description());
    const auto po = boost::program_options::command_line_parser(arguments).
        options(tlod).
        positional(make_positional_options()).
        allow_unregistered().
        run();

    variables_map vm;
    boost::program_options::store(po, vm);
    const bool has_command(vm.count(command_arg));
    const bool has_version(vm.count(version_arg));
    const bool has_help(vm.count(help_arg));

    /*
     * First, handle the simpler case where no command is supplied.
     */
    if (!has_command)
        return handle_no_command(has_version, has_help, tlod, info, err);

    /*
     * If the user supplied a command, we need to retrieve it and
     * ensure it is valid.
     */
    const auto command_name(vm[command_arg].as<std::string>());
    validate_command_name(command_name, err);

    /*
     * Copying the same approach as git, we also consider version to
     * be invalid at the command level. We don't bother to handle this
     * at program options level, but instead check for the presence of
     * the (supposedly valid, according to program options) version
     * command and throw.
     */
    if (has_version) {
        err << "Error: unrecognised option for command '" << command_name
            << "'. " << more_information  << std::endl;

        BOOST_THROW_EXCEPTION(parser_exception(invalid_option + "version"));
    }

    /*
     * We can now process the command. Notice that we are suppliying
     * the variables map into the handler by reference. This is
     * because we need access to the global options that may have
     * already been setup.
     */
    return handle_command(command_name, has_help, po, info, vm);
}

}

namespace masd::dogen::cli {

boost::optional<configuration>
program_options_parser::parse(const std::vector<std::string>& arguments,
    std::ostream& info, std::ostream& err) const {

    try {
        return ::parse(arguments, info, err);
    } catch (const boost::program_options::error& e) {
        err << usage_error_msg << e.what() << std::endl
            << more_information << std::endl;
        BOOST_THROW_EXCEPTION(parser_exception(e.what()));
    }
}

}
