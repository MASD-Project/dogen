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
#include "masd.dogen.cli/types/program_options_parser.hpp"

namespace {

const std::string generate_command("generate");
const std::string transform_command("transform");

using boost::program_options::value;
using boost::program_options::variables_map;
using boost::program_options::options_description;
using boost::program_options::positional_options_description;

options_description make_general_options_description() {
    options_description r("General");
    r.add_options()
        ("help,h", "Display usage and exit.")
        ("version,v", "Output version information and exit.")
        ("command", value<std::string>(), "Command to execute. "
            "Available commands: generate, transform.")
        ("args", value<std::vector<std::string> >(),
            "Arguments for command");

    return r;
}

positional_options_description make_positional_options() {
    positional_options_description r;
    r.add("command", 1).add("args", -1);
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
        ("tracing-enabled", "Generate stats about executed transforms.")
        ("tracing-disable-guids", "Disable guids in probe stats, "
            "to make comparisons easier.")
        ("tracing-org-mode-format", "Use org-mode format for stats."
            " Requires enabling stats.")
        ("tracing-all", "Dump all available probing information "
            "about transforms.")
        ("tracing-output-directory", "Directory in which to dump probe data. "
            "Only used if transforms probing is enabled.")
        ("tracing-use-short-names", "Use short names for directories and "
            "files. Useful for Windows where long paths are not supported.");

    return r;
}

/*
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

options_description make_transform_options_description() {
    options_description r("Generation");
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
*/
variables_map
create_first_stage_variables_map(std::vector<std::string> arguments) {
    options_description od;
    od.add(make_general_options_description());
    od.add(make_logging_options_description());
    od.add(make_tracing_options_description());
    const auto po = boost::program_options::command_line_parser(arguments).
        options(od).
        positional(make_positional_options()).
        allow_unregistered().
        run();

    variables_map r;
    boost::program_options::store(po, r);
    return r;
}

bool is_command_valid(const std::string& command) {
    return command == generate_command || command == transform_command;
}

}

namespace masd::dogen::cli {

boost::optional<coding::transforms::options>
program_options_parser::parse(std::vector<std::string> arguments,
    std::ostream& /*out*/, std::ostream& /*err*/) const {

    /*
     * Create the first stage command line options, parse them and
     * retrieve the results of the parsing.
     */
    const auto first_vm(create_first_stage_variables_map(arguments));

    /*
     *
     */
    const auto cmd(first_vm["command"].as<std::string>());
    if (!is_command_valid(cmd)) {
    }

    coding::transforms::options r;
    return r;
}

}
