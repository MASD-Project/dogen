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
#define BOOST_RESULT_OF_USE_DECLTYPE
#include <string>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <boost/throw_exception.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/range/combine.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm/set_algorithm.hpp>
#include "dogen/utility/io/vector_io.hpp"
#include "dogen/utility/exception/invalid_enum_value.hpp"
#include "dogen/knitter/parser_validation_error.hpp"
#include "dogen/knitter/program_options_parser.hpp"

/*
 * Note on logging: we are NOT logging any of the exceptions to the
 * log in this file. This is by design. The logger is only initialised
 * after the options have been parsed; were we to log prior to this,
 * we would dump all the messages into the console. The output is very
 * confusing users that are accustomed to normal console applications.
 */
namespace {

const std::string empty;
const std::string missing_target("Mandatory parameter target is missing. ");

const std::string help_arg("help");
const std::string version_arg("version");
const std::string log_level_arg("log-level");
const std::string log_directory_arg("log-directory");
const std::string compatibility_mode_arg("compatibility-mode");
const std::string target_arg("target");
const std::string output_dir_arg("output-directory");
const std::string cpp_headers_output_directory_arg(
    "cpp-headers-output-directory");
const std::string delete_extra_files_arg("delete-extra-files");
const std::string ignore_files_matching_regex_arg(
    "ignore-files-matching-regex");
const std::string force_write_arg("force-write");
const std::string info_level("info");
const std::string default_log_directory("log");

const std::string probe_stats_arg("probe-stats");
const std::string probe_stats_graph_arg("probe-stats-graph");
const std::string probe_all_arg("probe-all");
const std::string probe_directory_arg("probe-directory");
const std::string default_probe_directory("probe");

}

namespace dogen {
namespace knitter {

program_options_parser::
program_options_parser(std::vector<std::string> arguments)
    : arguments_(arguments) { }

program_options_parser::
program_options_parser(const int argc, const char* argv[])
    : arguments_(argv + 1, argv + argc) { }

program_options_parser::program_options_parser(program_options_parser&& rhs)
    : arguments_(std::move(rhs.arguments_)),
      help_function_(std::move(rhs.help_function_)),
      version_function_(std::move(rhs.version_function_)) { }

boost::program_options::options_description
program_options_parser::make_general_options_description() const {
    using boost::program_options::value;
    boost::program_options::options_description r("General options");
    r.add_options()
        ("help,h", "Display usage and exit.")
        ("version,v", "Output version information and exit.");

    return r;
}

boost::program_options::options_description
program_options_parser::make_logging_options_description() const {
    using boost::program_options::value;
    boost::program_options::options_description r("Logging options");
    r.add_options()
        ("log-level,l", value<std::string>(),
            "What level to use for logging. Options: trace, debug, info, "
            "warn, error. Defaults to 'info'.")
        ("log-directory,g", value<std::string>(),
            "Directory to place the log file in. Defaults to 'log'.");

    return r;
}

boost::program_options::options_description
program_options_parser::make_input_options_description() const {
    using boost::program_options::value;
    boost::program_options::options_description r("Input options");
    r.add_options()
        ("target,t",
            value<std::string>(),
            "Model to generate code for, in any of the supported formats."
            "If required, you can add the module path: FILE,MODULES.");

    return r;
}

boost::program_options::options_description
program_options_parser::make_output_options_description() const {
    using boost::program_options::value;
    boost::program_options::options_description r("Output options");
    r.add_options()
        ("delete-extra-files,d", "Delete any additional files found in "
            "directories managed by Knitter.")
        ("ignore-files-matching-regex,i",
            value<std::vector<std::string> >(),
            "Ignore files matching regex, if they are on the deletion list")
        ("force-write,f", "Always write files, even when there are "
            "no differences.")
        ("output-directory,o",
            value<std::string>(),
            "Output directory for the generated code. "
            "Defaults to the current working directory.")
        ("cpp-headers-output-directory,c",
            value<std::string>(),
            "If set, the c++ header files will be placed at this location."
            "If not set, they are placed inside of output-directory.");

    return r;
}

boost::program_options::options_description
program_options_parser::make_transforms_options_description() const {
    using boost::program_options::value;
    boost::program_options::options_description r("Transforms options");
    r.add_options()
        ("compatibility-mode,m", "Attempt to process inputs, "
            "ignoring certain types of errors.")
        ("probe-stats", "Generate stats about executed transforms.")
        ("probe-stats-graph", "Generate a graph with stats about "
            "executed transforms.")
        ("probe-all", "Dump all available probing information "
            "about transforms.")
        ("probe-directory", "Directory in which to dump probe data. "
            "Only used if transforms probing is enabled.");

    return r;
}

boost::program_options::options_description
program_options_parser::make_options_description() const {
    boost::program_options::options_description r;
    r.add(make_general_options_description());
    r.add(make_logging_options_description());
    r.add(make_input_options_description());
    r.add(make_output_options_description());
    r.add(make_transforms_options_description());
    return r;
}

void program_options_parser::
generate_help(const options_description& od) const {
    if (!help_function_)
        return;

    std::ostringstream stream;
    stream << od;
    help_function_(stream.str());
}

void program_options_parser::generate_version() const {
    if (!version_function_)
        return;

    version_function_();
}

boost::optional<boost::program_options::variables_map> program_options_parser::
make_variables_map(const options_description& od) const {
    using namespace boost::program_options;
    variables_map r;
    try {
        basic_command_line_parser<char> parser(arguments_);
        store(parser.options(od).run(), r);
        notify(r);
    } catch (const boost::program_options::error& e) {
        BOOST_THROW_EXCEPTION(parser_validation_error(e.what()));
    }

    return r;
}

void program_options_parser::
help_function(std::function<void(std::string)> value) {
    help_function_ = value;
}

void program_options_parser::version_function(std::function<void()> value) {
    version_function_ = value;
}

options::knitting_options program_options_parser::
make_knitting_options(const variables_map& vm) const {
    options::knitting_options r;

    if (vm.count(target_arg) == 0)
        BOOST_THROW_EXCEPTION(parser_validation_error(missing_target));

    using boost::filesystem::absolute;
    const auto target_str(vm[target_arg].as<std::string>());
    r.target(absolute(target_str));

    if (vm.count(log_level_arg) == 0)
        r.log_level(info_level);
    else
        r.log_level(vm[log_level_arg].as<std::string>());

    if (vm.count(log_directory_arg) == 0)
        r.log_directory(absolute(default_log_directory));
    else {
        const auto s(vm[log_directory_arg].as<std::string>());
        r.log_directory(absolute(s));
    }

    r.delete_extra_files(vm.count(delete_extra_files_arg) != 0);
    r.force_write(vm.count(force_write_arg) != 0);

    if (vm.count(ignore_files_matching_regex_arg)) {
        typedef std::vector<std::string> argument_type;
        const auto p(vm[ignore_files_matching_regex_arg].as<argument_type>());
        r.ignore_patterns(p);
    }

    if (!vm.count(output_dir_arg))
        r.output_directory_path(boost::filesystem::current_path());
    else {
        const auto s(vm[output_dir_arg].as<std::string>());
        r.output_directory_path(absolute(s));
    }

    if (vm.count(cpp_headers_output_directory_arg)) {
        const auto s(vm[cpp_headers_output_directory_arg].as<std::string>());
        r.cpp_headers_output_directory_path(absolute(s));
    }

    r.compatibility_mode(vm.count(compatibility_mode_arg) != 0);
    r.probe_stats(vm.count(probe_stats_arg) != 0);
    r.probe_stats_graph(vm.count(probe_stats_graph_arg)  != 0);
    r.probe_all(vm.count(probe_all_arg) != 0);

    if (vm.count(probe_directory_arg) == 0)
        r.probe_directory(absolute(default_probe_directory));
    else {
        const auto s(vm[probe_directory_arg].as<std::string>());
        r.probe_directory(absolute(s));
    }

    return r;
}

boost::optional<options::knitting_options> program_options_parser::parse() {
    const boost::optional<options::knitting_options> r;
    const auto od(make_options_description());
    const auto ovm(make_variables_map(od));

    /*
     * This shouldn't really happen as we should throw if the user did
     * not supply mandatory options.
     */
    if (!ovm)
        return r;

    const auto& vm(*ovm);
    if (vm.count(help_arg)) {
        generate_help(od);
        return r;
    }

    if (vm.count(version_arg)) {
        generate_version();
        return r;
    }

    return make_knitting_options(vm);
}

} }
