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
#include <iostream>
#include <boost/program_options.hpp>
#include <boost/throw_exception.hpp>
#include <boost/filesystem/operations.hpp>
#include "masd.dogen/version.hpp"
#include "masd.dogen.utility/types/log/logging_configuration.hpp"
#include "masd.dogen.cli/types/parser_exception.hpp"
#include "masd.dogen.cli/types/program_options_parser.hpp"

namespace {

const std::string indent("   ");
const std::string run_identifier_prefix("masd.dogen.cli.");

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
const std::string logging_log_enabled_arg("log-enabled");
const std::string logging_log_directory_arg("log-directory");
const std::string logging_log_to_console_arg("log-to-console");
const std::string logging_log_level_arg("log-level");
const std::string logging_log_level_trace("trace");
const std::string logging_log_level_debug("debug");
const std::string logging_log_level_info("info");
const std::string logging_log_level_warn("warn");
const std::string logging_log_level_error("error");
const std::string logging_default_log_directory("log");

const std::string tracing_enabled_arg("tracing-enabled");
const std::string tracing_level_arg("tracing-level");
const std::string tracing_level_detail("detail");
const std::string tracing_level_summary("summary");
const std::string tracing_guids_enabled_arg("tracing-guids-enabled");
const std::string tracing_format_arg("tracing-format");
const std::string tracing_format_plain("plain");
const std::string tracing_format_org_mode("org-mode");
const std::string tracing_format_graphviz("graphviz");
const std::string tracing_output_directory_arg("tracing-output-directory");
const std::string tracing_default_directory("tracing");

const std::string diffing_enabled_arg("diffing-enabled");
const std::string diffing_style_arg("diffing-style");
const std::string diffing_destination_arg("diffing-destination");
const std::string diffing_report_unchanged_arg("diffing-report-unchanged");
const std::string diffing_output_directory_arg("diffing-output-directory");
const std::string diffing_style_brief("brief");
const std::string diffing_style_unified("unified");
const std::string diffing_destination_file("file");
const std::string diffing_destination_console("console");
const std::string diffing_default_directory("diffing");

const std::string error_handling_compatibility_mode_arg(
    "compatibility-mode-enabled");

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
const std::string invalid_diffing_style(
    "Diffing style is invalid or unsupported: ");
const std::string invalid_diffing_destination(
    "Diffing destination is invalid or unsupported: ");

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
 * @brief Creates the the top-level option descriptions that are
 * visible to the end users.
 */
options_description make_top_level_visible_options_description() {
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
            "warn, error. Defaults to 'info'.")
        ("log-to-console", value<std::string>(),
            "Output logging to the console, as well as to file.");
    r.add(lod);

    options_description tod("Tracing");
    tod.add_options()
        ("tracing-enabled", "Generate metrics about executed transforms.")
        ("tracing-level",  value<std::string>(), "Level at which to trace."
            "Valid values: detail, summary.")
        ("tracing-guids-enabled", "Use guids in tracing metrics, Not"
            "  recommended when making comparisons between runs.")
        ("tracing-format", value<std::string>(), "Format to use for tracing"
            " metrics. Valid values: org-mode, text")
        ("tracing-output-directory", value<std::string>(), "Directory in which "
            "to dump probe data. Only used if transforms tracing is enabled.");
    r.add(tod);

    options_description dod("Diffing");
    dod.add_options()
        ("diffing-enabled", "Generate diffs against files in the filesystem. "
            "When enabled, dogen is in dry-run mode.")
        ("diffing-style",  value<std::string>(), "Style to use in the diff. "
            "Valid values: brief, unified.")
        ("diffing-destination",  value<std::string>(), "Where to write the "
            " diff output. Valid values: file, console.")
        ("diffing-output-directory", value<std::string>(), "Directory in which "
            "to dump the diff file. Only used when outputting to file.");
    r.add(dod);

    options_description ehod("Error Handling");
    ehod.add_options()
        ("compatibility-mode-enabled",
            "Try to process models even if there are errors.");
    r.add(ehod);

    return r;
}

/**
 * @brief Creates the the top-level option descriptions that are
 * hidden to end users.
 */
options_description make_top_level_hidden_options_description() {
    options_description r("Commands");
    r.add_options()
        ("command", value<std::string>(), "Command to execute. "
            "Available commands: generate, convert, weave.")
        ("args", value<std::vector<std::string> >(),
            "Arguments for command");
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
void validate_command_name(const std::string& command_name) {
    const bool is_valid_command_name(
        command_name == generate_command_name ||
        command_name == convert_command_name ||
        command_name == weave_command_name);

    if (is_valid_command_name)
        return;

    BOOST_THROW_EXCEPTION(parser_exception(invalid_command + command_name));
}

/**
 * @brief Prints the header of the help text, applicable to all cases.
 */
void print_help_header(std::ostream& s) {
    s << "Dogen is a Model Driven Engineering tool that processes models"
      << " encoded in supported codecs." << std::endl
      << "Dogen is created by the MASD project. " << std::endl;
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
      << std::endl << "See below for a list of valid commands. " << std::endl
      << std::endl << "Global options: " << std::endl << od << std::endl
      <<  "Commands: "<< std::endl << std::endl;

    auto lambda([&](const std::string& name, const std::string& desc) {
                    const unsigned int command_width(15);
                    s << indent << std::setfill(' ') << std::left
                      << std::setw(command_width)
                      << name << desc << std::endl;
                });
    lambda(generate_command_name, generate_command_desc);
    lambda(convert_command_name, convert_command_desc);
    lambda(weave_command_name, weave_command_desc);

    s << std::endl << "For command specific options, type <command> --help."
      << std::endl;
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
    const options_description& od, std::ostream& info) {
    /*
     * The only valid options are help or version, so if those are
     * not present we can safely throw.
     */
    if (!has_version && !has_help) {
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
boost::optional<masd::dogen::tracing_configuration>
read_tracing_configuration(const variables_map& vm) {

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
        else if (s == tracing_level_summary)
            r.level(tracing_level::summary);
        else
            BOOST_THROW_EXCEPTION(parser_exception(invalid_tracing_level + s));
    } else if (enabled)
        r.level(tracing_level::summary);

    using masd::dogen::tracing_format;
    if (vm.count(tracing_format_arg)) {
        const auto s(vm[tracing_format_arg].as<std::string>());
        if (s == tracing_format_plain)
            r.format(tracing_format::plain);
        else if (s == tracing_format_org_mode)
            r.format(tracing_format::org_mode);
        else if (s == tracing_format_graphviz)
            r.format(tracing_format::graphviz);
        else
            BOOST_THROW_EXCEPTION(parser_exception(invalid_format + s));
    } else if (enabled)
        r.format(tracing_format::org_mode);

    return r;
}

boost::optional<masd::dogen::error_handling_configuration>
read_error_handling_configuration(const variables_map& vm) {
    const bool compatibility_mode(
        vm.count(error_handling_compatibility_mode_arg) != 0);
    if (!compatibility_mode)
        return boost::optional<masd::dogen::error_handling_configuration>();

    masd::dogen::error_handling_configuration r;
    r.compatibility_mode_enabled(compatibility_mode);
    return r;
}

boost::optional<masd::dogen::diffing_configuration>
read_diffing_configuration(const variables_map& vm) {
    const bool enabled(vm.count(diffing_enabled_arg) != 0);
    if (!enabled)
        return boost::optional<masd::dogen::diffing_configuration>();

    using masd::dogen::diffing_style;
    masd::dogen::diffing_configuration r;
    r.report_unchanged_files(vm.count(diffing_report_unchanged_arg) != 0);

    if (vm.count(diffing_style_arg)) {
        const auto s(vm[diffing_style_arg].as<std::string>());

        if (s == diffing_style_brief)
            r.style(diffing_style::brief);
        else if (s == diffing_style_unified)
            r.style(diffing_style::unified);
        else
            BOOST_THROW_EXCEPTION(parser_exception(invalid_diffing_style + s));
    } else if (enabled)
        r.style(diffing_style::unified);

    using masd::dogen::diffing_destination;
    if (vm.count(diffing_destination_arg)) {
        const auto s(vm[diffing_destination_arg].as<std::string>());

        if (s == diffing_destination_file)
            r.destination(diffing_destination::file);
        else if (s == diffing_destination_console)
            r.destination(diffing_destination::console);
        else
            BOOST_THROW_EXCEPTION(
                parser_exception(invalid_diffing_destination + s));
    } else if (enabled)
        r.destination(diffing_destination::file);

    return r;
}

/**
 * @brief Constructs an identifier sufficiently unique for this
 * run. It can be used for log file names, directories, etc.
 */
std::string compute_run_identifier(const std::string& command,
    const boost::filesystem::path& target) {

    std::ostringstream s;
    s << run_identifier_prefix << command;

    const auto fn(target.filename().string());
    if (!fn.empty())
        s << "." << fn;

    return s.str();
}

/**
 * @brief Reads the tracing configuration from the variables map.
 */
boost::optional<logging_configuration> read_logging_configuration(
    const std::string& run_identifier, const variables_map& vm) {
    const auto enabled(vm.count(logging_log_enabled_arg) != 0);
    if (!enabled)
        return boost::optional<logging_configuration>();

    logging_configuration r;
    r.filename(run_identifier);
    r.output_to_console(vm.count(logging_log_to_console_arg) != 0);

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
    } else if (enabled)
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
    if (vm.count(generate_target_arg) == 0)
        BOOST_THROW_EXCEPTION(parser_exception(missing_target));

    const auto target_str(vm[generate_target_arg].as<std::string>());
    r.target(absolute(target_str));

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
        r.destination(s);
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
    configuration r;
    boost::filesystem::path target;
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
        target = gc.target();
        r.cli().activity(gc);
    } else if (command_name == convert_command_name) {
        const auto cod(make_convert_options_description());
        if (has_help) {
            print_help_command(convert_command_name, cod, info);
            return empty_config();
        }

        store(command_line_parser(options).options(cod).run(), vm);
        const auto cc(read_conversion_configuration(vm));
        target = cc.source();
        r.cli().activity(cc);
    } else if (command_name == weave_command_name) {
        const auto cod(make_weave_options_description());
        if (has_help) {
            print_help_command(weave_command_name, cod, info);
            return empty_config();
        }

        store(command_line_parser(options).options(cod).run(), vm);
        const auto wc(read_weaving_configuration(vm));
        target = wc.target();
        r.cli().activity(wc);
    }

    /*
     * Now process the common options. We must do this at the end
     * because we require the model name.
     */
    r.api().tracing(read_tracing_configuration(vm));
    r.api().diffing(read_diffing_configuration(vm));
    r.api().error_handling(read_error_handling_configuration(vm));

    const auto run_identifier(compute_run_identifier(command_name, target));
    const auto tracing_out_dir =
        [&]() {
            using boost::filesystem::absolute;
            if (vm.count(tracing_output_directory_arg) == 0) {
                if (!r.api().tracing())
                    return boost::filesystem::path();
                return absolute(tracing_default_directory) / run_identifier;
            }

            const auto s(vm[tracing_output_directory_arg].as<std::string>());
            return absolute(s) / run_identifier;
        }();
    r.cli().tracing_output_directory(tracing_out_dir);

    if (r.api().tracing())
        r.api().tracing()->output_directory(tracing_out_dir);

    const auto diffing_out_dir =
        [&]() {
            using boost::filesystem::absolute;
            if (vm.count(diffing_output_directory_arg) == 0) {
                if (!r.api().diffing())
                    return boost::filesystem::path();
                return absolute(diffing_default_directory) / run_identifier;
            }

            const auto s(vm[diffing_output_directory_arg].as<std::string>());
            return absolute(s) / run_identifier;
        }();
    r.cli().diffing_output_directory(diffing_out_dir);

    if (r.api().diffing())
        r.api().diffing()->output_directory(diffing_out_dir);

    r.logging(read_logging_configuration(run_identifier, vm));
    return r;
}

boost::optional<configuration>
parse(const std::vector<std::string>& arguments, std::ostream& info) {
    /*
     * Create the top-level command line options, parse them and
     * retrieve the results of the parsing. Note that we split then
     * into visible and hidden to avoid showing the hidden options to
     * the user in the help description.
     */
    const auto visible(make_top_level_visible_options_description());
    const auto hidden(make_top_level_hidden_options_description());
    const auto all(
        [&](){
            options_description r;
            r.add(visible).add(hidden);
            return r;
        }());

    const auto po = boost::program_options::command_line_parser(arguments).
        options(all).
        positional(make_positional_options()).
        allow_unregistered().
        run();

    variables_map vm;
    boost::program_options::store(po, vm);
    const bool has_command(vm.count(command_arg));
    const bool has_version(vm.count(version_arg));
    const bool has_help(vm.count(help_arg));

    /*
     * First, handle the simpler case where no command is
     * supplied. Note that we only supply the visible options here.
     */
    if (!has_command)
        return handle_no_command(has_version, has_help, visible, info);

    /*
     * If the user supplied a command, we need to retrieve it and
     * ensure it is valid.
     */
    const auto command_name(vm[command_arg].as<std::string>());
    validate_command_name(command_name);

    /*
     * Copying the same approach as git, we also consider version to
     * be invalid at the command level. We don't bother to handle this
     * at program options level, but instead check for the presence of
     * the (supposedly valid, according to program options) version
     * command and throw.
     */
    if (has_version)
        BOOST_THROW_EXCEPTION(parser_exception(invalid_option + "version"));

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
        return ::parse(arguments, info);
    } catch(const parser_exception& e) {
        err << usage_error_msg << e.what() << std::endl
            << more_information << std::endl;
        BOOST_THROW_EXCEPTION(e);
    } catch (const boost::program_options::error& e) {
        err << usage_error_msg << e.what() << std::endl
            << more_information << std::endl;
        BOOST_THROW_EXCEPTION(parser_exception(e.what()));
    }
}

}
