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
const std::string verbose_arg("verbose");

const std::string target_arg("target");
const std::string cpp_project_dir_arg("cpp-project-dir");
const std::string delete_extra_files_arg("delete-extra-files");
const std::string ignore_files_matching_regex_arg(
    "ignore-files-matching-regex");
const std::string force_write_arg("force-write");

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
program_options_parser::general_options_factory() const {
    boost::program_options::options_description r("General options");
    r.add_options()
        ("help,h", "Display this help and exit.")
        ("version", "Output version information and exit.")
        ("verbose,v", "Output additional diagnostic information.");
    return r;
}

boost::program_options::options_description
program_options_parser::modeling_options_factory() const {
    using boost::program_options::value;
    boost::program_options::options_description r("Modeling options");
    r.add_options()
        ("target,t",
            value<std::string>(),
            "Model to generate code for, in any of the supported formats."
            "If required, you can add the module path: FILE,MODULES.");

    return r;
}

boost::program_options::options_description
program_options_parser::output_options_factory() const {
    using boost::program_options::value;
    boost::program_options::options_description r("Output options");
    r.add_options()
        ("delete-extra-files,d", "Delete any additional files found in "
            "directories managed by Knitter.")
        ("ignore-files-matching-regex",
            value<std::vector<std::string> >(),
            "Ignore files matching regex, if they are on the deletion list")
        ("force-write", "Always write files, even when there are "
            "no differences");

    return r;
}

boost::program_options::options_description
program_options_parser::cpp_options_factory() const {
    using boost::program_options::value;
    boost::program_options::options_description r("C++ backend options");
    r.add_options()
        ("cpp-project-dir,x",
            value<std::string>(),
            "Output directory for all project files. "
            "Defaults to the current working directory.");

    return r;
}

boost::program_options::options_description
program_options_parser::options_factory() const {
    boost::program_options::options_description r;
    r.add(general_options_factory());
    r.add(modeling_options_factory());
    r.add(output_options_factory());
    r.add(cpp_options_factory());
    return r;
}

boost::optional<boost::program_options::variables_map>
program_options_parser::variables_map_factory() const {
    const auto options(options_factory());

    using namespace boost::program_options;
    variables_map r;
    try {
        basic_command_line_parser<char> parser(arguments_);
        store(parser.options(options).run(), r);
        notify(r);
    } catch (const boost::program_options::error& e) {
        BOOST_THROW_EXCEPTION(parser_validation_error(e.what()));
    }

    if (r.count(help_arg)) {
        if (help_function_) {
            std::ostringstream stream;
            stream << options;
            help_function_(stream.str());
        }
        return boost::optional<boost::program_options::variables_map>();
    }

    if (r.count(version_arg)) {
        if (version_function_)
            version_function_();
        return boost::optional<boost::program_options::variables_map>();
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

options::cpp_options program_options_parser::
transform_cpp_options(const boost::program_options::variables_map& vm) const {
    options::cpp_options r;
    if (!vm.count(cpp_project_dir_arg))
        r.project_directory_path(boost::filesystem::current_path());
    else
        r.project_directory_path(vm[cpp_project_dir_arg].as<std::string>());

    return r;
}

options::input_options program_options_parser::transform_input_options(
    const boost::program_options::variables_map& vm) const {
    options::input_options r;

    if (!vm.count(target_arg))
        BOOST_THROW_EXCEPTION(parser_validation_error(missing_target));

    r.target(vm[target_arg].as<std::string>());

    return r;
}

options::output_options program_options_parser::
transform_output_options(const variables_map& vm) const {
    options::output_options r;
    r.delete_extra_files(vm.count(delete_extra_files_arg));
    r.force_write(vm.count(force_write_arg));

    if (!vm.count(ignore_files_matching_regex_arg))
        return r;

    typedef std::vector<std::string> argument_type;
    const auto p(vm[ignore_files_matching_regex_arg].as<argument_type>());
    r.ignore_patterns(p);

    return r;
}

boost::optional<options::knitting_options> program_options_parser::parse() {
    auto optional_vm(variables_map_factory());

    if (!optional_vm)
        return boost::optional<options::knitting_options>();

    options::knitting_options r;
    const auto& vm(*optional_vm);
    r.verbose(vm.count(verbose_arg));
    r.input(transform_input_options(vm));
    r.cpp(transform_cpp_options(vm));
    r.output(transform_output_options(vm));

    return r;
}

} }
