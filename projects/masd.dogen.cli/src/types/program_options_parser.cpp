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
#include <boost/throw_exception.hpp>
#include "masd.dogen/version.hpp"
#include "masd.dogen.cli/types/parser_exception.hpp"
#include "masd.dogen.cli/types/program_options_parser.hpp"

namespace {

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
    "Converts an input model from one format to another. ");
const std::string weave_command_name("weave");
const std::string weave_command_desc(
    "Weaves a template file into its final output. ");

const std::string help_arg("help");
const std::string version_arg("version");
const std::string command_arg("command");

const std::string indent("   ");

const std::string invalid_command("Command is invalid or unsupported: ");
const std::string missing_target("Mandatory parameter target is missing. ");

using boost::program_options::value;
using boost::program_options::variables_map;
using boost::program_options::include_positional;
using boost::program_options::options_description;
using boost::program_options::collect_unrecognized;
using boost::program_options::positional_options_description;

options_description make_general_options_description() {
    options_description r("General");
    r.add_options()
        ("help,h", "Display usage and exit.")
        ("version,v", "Output version information and exit.");

    return r;
}

options_description make_logging_options_description() {
    options_description r("Logging");
    r.add_options()
        ("log-level,l", value<std::string>(),
            "What level to use for logging. Options: trace, debug, info, "
            "warn, error. Defaults to 'info'.")
        ("log-directory,g", value<std::string>(),
            "Directory to place the log file in. Defaults to 'log'.");

    return r;
}

options_description make_tracing_options_description()  {
    options_description r("Tracing");
    r.add_options()
        ("tracing-enabled", "Generate metrics about executed transforms.")
        ("tracing-level", "Level at which to trace. "
            "Valid levels: detail, summary.")
        ("tracing-guids-enabled", "Use guids in tracing metrics, "
            "to make comparisons easier.")
        ("tracing-format", "Format to use for tracing metrics. "
            "Valid formts: org-mode, markdown")
        ("tracing-output-directory", "Directory in which to dump probe data. "
            "Only used if transforms tracing is enabled.");

    return r;
}

options_description make_command_options_description() {
    options_description r("Commands");
    r.add_options()
        ("command", value<std::string>(), "Command to execute. "
            "Available commands: generate, convert, weave.")
        ("args", value<std::vector<std::string> >(),
            "Arguments for command");

    return r;
}

positional_options_description make_positional_options() {
    positional_options_description r;
    r.add("command", 1).add("args", -1);
    return r;
}


options_description make_generation_options_description() {
    options_description r("Generation");
    r.add_options()
        ("compatibility-mode,m", "Attempt to process inputs, "
            "ignoring certain types of errors.")
        ("delete-extra-files,d", "Delete any additional files found in "
            "directories managed by Knitter.")
        ("ignore-files-matching-regex,i",
            value<std::vector<std::string> >(),
            "Ignore files matching regex, if they are on the deletion list")
        ("force-write,f", "Always write files, even when there are "
            "no differences.")
        ("output-directory,o",
            value<std::string>(), "Output directory for the generated code. "
            "Defaults to the current working directory.")
        ("cpp-headers-output-directory,c",
            value<std::string>(),
            "If set, the C++ header files will be placed at this location."
            "If not set, they are placed inside of output-directory.")
        ("target,t",
            value<std::string>(),
            "Model to generate code for, in any of the supported formats.");

    return r;
}

options_description make_convert_options_description() {
    options_description r("Convert");
    r.add_options()
        ("force-write,f", "Always write files, even when there are "
            "no differences.")
        ("destination,d",
            value<std::string>(), "Output directory for the generated code. "
            "Defaults to the current working directory.")
        ("target,t",
            value<std::string>(),
            "Model to generate code for, in any of the supported formats.");

    return r;
}

bool is_command_valid(const std::string& command) {
    return
        command == generate_command_name ||
        command == convert_command_name;
}

/**
 * @brief Prints the top-level help text.
 */
void help(const boost::program_options::options_description& od,
    std::ostream& s) {
    s << "Dogen is a Model Driven Engineering tool to process input models."
      << std::endl
      << "Dogen is created by the MASD project. For details type --version."
      << std::endl
      << "Dogen has a command-based interface: <command> <options>" << std::endl
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
 * @brief Print the program's version details.
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

}

namespace masd::dogen::cli {

program_options_parser::program_options_parser() {}

boost::optional<masd::dogen::configuration>
program_options_parser::parse(const std::vector<std::string>& arguments,
    std::ostream& info, std::ostream& err) const {

    /*
     * Create the first stage command line options, parse them and
     * retrieve the results of the parsing.
     */
    options_description od;
    od.add(make_general_options_description());
    od.add(make_logging_options_description());
    od.add(make_tracing_options_description());
    od.add(make_command_options_description());
    const auto po = boost::program_options::command_line_parser(arguments).
        options(od).
        positional(make_positional_options()).
        allow_unregistered().
        run();

    variables_map vm;
    boost::program_options::store(po, vm);

    const bool has_command(vm.count(command_arg));
    const bool has_version(vm.count(version_arg));
    const bool has_help(vm.count(help_arg));

    /*
     * First, handle the case of no command supplied.
     */
    if (!has_command) {
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
            help(od, info);
        else if (vm.count(version_arg))
            version(info);
        return boost::optional<masd::dogen::configuration>();
    }

    /*
     * The user supplied a command. Retrieve it, and ensure it is
     * valid.
     */
    const auto cmd(vm["command"].as<std::string>());
    if (!is_command_valid(cmd)) {
        err << "Error: '" << cmd << "' is not a valid command. "
            << more_information  << std::endl;

        BOOST_THROW_EXCEPTION(parser_exception(invalid_command + cmd));
    }

    /*
     * To make our life easier, we allow users to ask for version info
     * at the command level. We'd have to faff around a fair bit with
     * the original options in order to make version invalid, and it
     * does not seem worth the effort. Note that help is command
     * sensitive and thus it is handled below.
     */
    if (vm.count(version_arg)) {
        version(info);
        return boost::optional<masd::dogen::configuration>();
    }

    /*
     * Now lets process the actual, valid commands. For each we need
     * to setup their set of options and then parse them.
     */
    if (cmd == generate_command_name) {
        const auto god(make_generation_options_description());
        auto opts(collect_unrecognized(po.options, include_positional));
        opts.erase(opts.begin());
        store(boost::program_options::command_line_parser(opts)
            .options(god).run(), vm);

        if (has_help) {
            info << "Dogen is a Model Driven Engineering tool to process input models."
                 << std::endl
                 << "Dogen is created by the MASD project. "
                 << "For details type --version."
                 << std::endl
                 << "Displaying options specific to the generate command. "
                 << std::endl
                 << "For global options, type --help." << std::endl << std::endl
                 << god;
        }
    } else if (cmd == convert_command_name) {
        const auto cod(make_convert_options_description());
        auto opts(collect_unrecognized(po.options, include_positional));
        opts.erase(opts.begin());
        store(boost::program_options::command_line_parser(opts)
            .options(cod).run(), vm);

        if (has_help) {
            info << "Dogen is a Model Driven Engineering tool to process input models."
                 << std::endl
                 << "Dogen is created by the MASD project. "
                 << "For details type --version."
                 << std::endl
                 << "Displaying options specific to the generate command. "
                 << std::endl
                 << "For global options, type --help." << std::endl << std::endl
                 << cod;
        }
    }
    return boost::optional<masd::dogen::configuration>();
}

}
