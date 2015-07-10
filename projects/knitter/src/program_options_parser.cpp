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
#include "dogen/utility/test_data/dia_sml.hpp"
#include "dogen/utility/exception/invalid_enum_value.hpp"
#include "dogen/knitter/parser_validation_error.hpp"
#include "dogen/knitter/program_options_parser.hpp"

// Note on logging: we are NOT logging any of the exceptions to the
// log in this file. This is by design. The logger is only initialised
// after the options have been parsed; were we to log prior to this,
// we would dump all the messages into the console. The output is very
// confusing users that are accustomed to normal console applications.

namespace {

const std::string more_information(
    "Try `dogen_knitter --help' for more information.");
const std::string at_least_one_argument(
    "Expected at least one argument for reference");
const std::string at_most_two_arguments(
    "Expected only at most two arguments for reference");
const std::string empty;
const std::string help_arg("help");
const std::string version_arg("version");

const std::string verbose_arg("verbose");
const std::string debug_dir_arg("debug-dir");
const std::string save_dia_model_arg("save-dia-model");
const std::string save_sml_model_arg("save-sml-model");

const std::string invalid_facet_type("Invalid facet type: ");
const std::string domain_facet_type("domain");
const std::string io_facet_type("io");
const std::string hash_facet_type("hash");
const std::string serialization_facet_type("serialization");
const std::string test_data_facet_type("test_data");
const std::string odb_facet_type("odb");

const std::string invalid_archive_type("Invalid archive type");
const std::string xml_archive_type("xml");
const std::string text_archive_type("text");
const std::string binary_archive_type("binary");

const std::string stop_after_merging_arg("stop-after-merging");
const std::string stop_after_formatting_arg("stop-after-formatting");

const std::string cpp_split_project_arg("cpp-split-project");
const std::string cpp_project_dir_arg("cpp-project-dir");
const std::string cpp_source_dir_arg("cpp-source-dir");
const std::string cpp_include_dir_arg("cpp-include-dir");
const std::string cpp_disable_cmakelists_arg("cpp-disable-cmakelists");

const std::string target_arg("target");
const std::string external_module_path_arg("external-module-path");
const std::string reference_arg("reference");

const std::string delete_extra_files_arg("delete-extra-files");
const std::string ignore_files_matching_regex_arg(
    "ignore-files-matching-regex");
const std::string force_write_arg("force-write");

const std::string integrated_io_incompatible_with_io_facet(
    "Integrated IO cannot be used with the IO facet.");

}

namespace dogen {
namespace knitter {

program_options_parser::
program_options_parser(std::vector<std::string> arguments)
    : arguments_(arguments),
      current_path_(boost::filesystem::current_path()) { }

program_options_parser::
program_options_parser(const int argc, const char* argv[])
    : arguments_(argv + 1, argv + argc),
      current_path_(boost::filesystem::current_path()) { }

boost::program_options::options_description
program_options_parser::general_options_factory() const {
    boost::program_options::options_description r("General options");
    r.add_options()
        ("help,h", "Display this help and exit.")
        ("version", "Output version information and exit.");
    return r;
}

boost::program_options::options_description
program_options_parser::troubleshooting_options_factory() const {
    using boost::program_options::value;
    boost::program_options::options_description r("Troubleshooting options");
    r.add_options()
        ("verbose,v", "Output additional diagnostic information.")
        ("debug-dir",
            value<std::string>(),
            "Directory in which to dump debug files. "
            "Defaults to current directory.")
        ("save-dia-model",
            value<std::string>(),
            "If set, saves a Dia model representation of each diagram in the "
            "directory given by debug-dir. "
            "Valid values: [xml | text | binary].")
        ("save-sml-model",
            value<std::string>(),
            "If set, saves a SML model representation of each model in the "
            "directory given by debug-dir. "
            "Valid values: [xml | text | binary].")
        ("stop-after-merging",
            "Build combined model and validate all dependencies "
            "but don't code generate.")
        ("stop-after-formatting", "Do everything except writing files.");

    return r;
}

boost::program_options::options_description
program_options_parser::modeling_options_factory() const {
    using boost::program_options::value;
    boost::program_options::options_description r("Modeling options");
    r.add_options()
        ("external-module-path,p",
            value<std::string>(),
            "External modules containing the target model, delimited by '::'.")
        ("target,t",
            value<std::string>(),
            "Dia diagram to generate code for.")
        ("reference,r",
            value<std::vector<std::string> >(),
            "Dia diagrams that our target diagram depends on."
            "If required you can add the module path: file,PP.");

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
        ("force-write", "Always write to file even when there are"
            " no differences")
        ("output-to-file", "Create files. Disabled by default if "
            "output-to-stdout is chosen.")
        ("output-to-stdout", "Output generated code to standard output. "
            "Disables output-to-file by default.");

    return r;
}

boost::program_options::options_description
program_options_parser::cpp_options_factory() const {
    using boost::program_options::value;
    boost::program_options::options_description r("C++ backend options");
    r.add_options()
        ("cpp-disable-cmakelists", "Do not generate 'CMakeLists.txt' for C++.")
        ("cpp-split-project,y",
            "Split the model project into a source and include directory, "
            "with individually configurable locations.")
        ("cpp-project-dir,x",
            value<std::string>(),
            "Output directory for all project files. Defaults to '.'"
            "Cannot be used with --cpp-split-project")
        ("cpp-source-dir,s",
            value<std::string>(),
            "Output directory for C++ source files. Defaults to '.'"
            "Can only be used with --cpp-split-project."
            "If supplied, include directory must be supplied too.")
        ("cpp-include-dir,i",
            value<std::string>(),
            "Output directory for C++ include files. Defaults to '.'"
            "Can only be used with --cpp-split-project."
            "If supplied, source directory must be supplied too.");

    return r;
}

boost::program_options::options_description
program_options_parser::options_factory() const {
    boost::program_options::options_description r;
    r.add(general_options_factory());
    r.add(troubleshooting_options_factory());
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
    return boost::optional<boost::program_options::variables_map>(r);
}

void program_options_parser::
help_function(std::function<void(std::string)> value) {
    help_function_ = value;
}

void program_options_parser::throw_project_dir_with_split() const {
    std::ostringstream stream;
    stream << "Argument project-dir cannot be used in"
           << " conjunction with project splitting. "
           << more_information;
    BOOST_THROW_EXCEPTION(parser_validation_error(stream.str()));
}

void program_options_parser::throw_include_source_without_split() const {
    std::ostringstream stream;
    stream << "Arguments source-dir and include-dir"
           << " require project splitting. "
           << more_information;
    BOOST_THROW_EXCEPTION(parser_validation_error(stream.str()));
}

void program_options_parser::throw_missing_include_source() const {
    std::ostringstream stream;
    stream << "You must supply both source-dir and include-dir"
           << " or not supply either. "
           << more_information;
    BOOST_THROW_EXCEPTION(parser_validation_error(stream.str()));
}

void program_options_parser::throw_missing_target() const {
    std::ostringstream stream;
    stream << "Mandatory parameter target is missing. " << more_information;
    BOOST_THROW_EXCEPTION(parser_validation_error(stream.str()));
}

void program_options_parser::version_function(std::function<void()> value) {
    version_function_ = value;
}

dogen::config::archive_types
program_options_parser::parse_archive_type(const std::string& s) {
    using dogen::config::archive_types;
    if (s == xml_archive_type)
        return archive_types::xml;
    if (s == text_archive_type)
        return archive_types::text;
    if (s == binary_archive_type)
        return archive_types::binary;

    using utility::exception::invalid_enum_value;
    BOOST_THROW_EXCEPTION(invalid_enum_value(invalid_archive_type));
}

config::cpp_options program_options_parser::
transform_cpp_options(const boost::program_options::variables_map& vm) const {
    config::cpp_options r;

    r.split_project(vm.count(cpp_split_project_arg));

    if (r.split_project()) {
        if (vm.count(cpp_project_dir_arg))
            throw_project_dir_with_split();

        if (vm.count(cpp_source_dir_arg) != vm.count(cpp_include_dir_arg))
            throw_missing_include_source();

    } else {
        if (vm.count(cpp_source_dir_arg) || vm.count(cpp_include_dir_arg))
            throw_include_source_without_split();
    }

    using boost::filesystem::path;
    if (r.split_project()) {
        if (!vm.count(cpp_source_dir_arg) && !vm.count(cpp_include_dir_arg)) {
            r.source_directory_path(current_path_);
            r.include_directory_path(current_path_);
        } else {
            r.source_directory_path(vm[cpp_source_dir_arg].as<std::string>());
            r.include_directory_path(vm[cpp_include_dir_arg].as<std::string>());
        }
    } else {
        if (!vm.count(cpp_project_dir_arg))
            r.project_directory_path(current_path_);
        else
            r.project_directory_path(vm[cpp_project_dir_arg].as<std::string>());
    }

    r.disable_cmakelists(vm.count(cpp_disable_cmakelists_arg));

    return r;
}

config::input_options program_options_parser::transform_input_options(
    const boost::program_options::variables_map& vm) const {
    config::input_options r;

    if (!vm.count(target_arg))
        throw_missing_target();
    r.target(vm[target_arg].as<std::string>());

    if (vm.count(external_module_path_arg)) {
        r.external_module_path(
            vm[external_module_path_arg].as<std::string>());
    }

    if (vm.count(reference_arg)) {
        std::vector<config::reference> references;
        typedef std::vector<std::string> strings_type;
        const auto ra(vm[reference_arg].as<strings_type>());
        for (const auto i : ra) {
            strings_type tokens;
            boost::split(tokens, i, boost::is_any_of(","));

            if (tokens.empty())
                BOOST_THROW_EXCEPTION(parser_validation_error(
                        at_least_one_argument));

            if (tokens.size() > 2)
                BOOST_THROW_EXCEPTION(parser_validation_error(
                        at_most_two_arguments));

            dogen::config::reference ref;
            ref.path(tokens[0]);
            if (tokens.size() > 1)
                ref.external_module_path(tokens[1]);
            references.push_back(ref);
        }
        r.references(references);
    }

    return r;
}

config::troubleshooting_options program_options_parser::
transform_troubleshooting_options(const variables_map& vm) const {
    config::troubleshooting_options r;

    r.stop_after_merging(vm.count(stop_after_merging_arg));
    r.stop_after_formatting(vm.count(stop_after_formatting_arg));

    bool need_debug_dir(false);
    using config::archive_types;
    auto lambda([&](std::string arg) -> archive_types {
            if (vm.count(arg)) {
                need_debug_dir = true;
                using utility::exception::invalid_enum_value;
                try {
                    return parse_archive_type(vm[arg].as<std::string>());
                } catch (const invalid_enum_value& e) {
                    BOOST_THROW_EXCEPTION(parser_validation_error(e.what()));
                }
            }
            return archive_types::invalid;
        });

    r.save_dia_model(lambda(save_dia_model_arg));
    r.save_sml_model(lambda(save_sml_model_arg));

    if (vm.count(debug_dir_arg))
        r.debug_dir(vm[debug_dir_arg].as<std::string>());
    else if (need_debug_dir)
        r.debug_dir(current_path_);

    return r;
}

config::output_options program_options_parser::
transform_output_options(const variables_map& vm) const {
    config::output_options r;
    r.delete_extra_files(vm.count(delete_extra_files_arg));
    if (vm.count(ignore_files_matching_regex_arg)) {
        r.ignore_patterns(
            vm[ignore_files_matching_regex_arg].as<std::vector<std::string> >());
    }
    r.force_write(vm.count(force_write_arg));
    return r;
}

boost::optional<config::knitting_options> program_options_parser::parse() {
    auto optional_vm(variables_map_factory());

    if (!optional_vm)
        return boost::optional<config::knitting_options>();

    const boost::program_options::variables_map vm(*optional_vm);
    config::knitting_options r;
    r.verbose(vm.count(verbose_arg));
    r.input(transform_input_options(vm));
    r.cpp(transform_cpp_options(vm));
    r.troubleshooting(transform_troubleshooting_options(vm));
    r.output(transform_output_options(vm));

    return boost::optional<config::knitting_options>(r);
}

} }
