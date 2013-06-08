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
#include "dogen/driver/parser_validation_error.hpp"
#include "dogen/driver/program_options_parser.hpp"
#include "dogen/utility/log/logger.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("driver.program_options_parser"));

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
const std::string cpp_disable_backend_arg("cpp-disable-backend");
const std::string cpp_disable_cmakelists_arg("cpp-disable-cmakelists");
const std::string cpp_enable_facet_arg("cpp-enable-facet");
const std::string cpp_header_extension_arg("cpp-header-extension");
const std::string cpp_source_extension_arg("cpp-source-extension");
const std::string cpp_disable_complete_constructor_arg(
    "cpp-disable-complete-constructor");
const std::string cpp_disable_facet_includers("cpp-disable-facet-includers");
const std::string cpp_disable_facet_folders_arg("cpp-disable-facet-folders");
const std::string cpp_disable_unique_file_names_arg(
    "cpp-disable-unique-file-names");
const std::string cpp_domain_facet_folder_arg("cpp-domain-facet-folder");
const std::string cpp_hash_facet_folder_arg("cpp-hash-facet-folder");
const std::string cpp_io_facet_folder_arg("cpp-io-facet-folder");
const std::string cpp_serialization_facet_folder_arg(
    "cpp-serialization-facet-folder");
const std::string cpp_test_data_facet_folder_arg("cpp-test-data-facet-folder");
const std::string cpp_odb_facet_folder_arg("cpp-odb-facet-folder");
const std::string cpp_disable_xml_serialization_arg(
    "cpp-disable-xml-serialization");
const std::string cpp_use_integrated_io_arg("cpp-use-integrated-io");

const std::string target_arg("target");
const std::string external_module_path_arg("external-module-path");
const std::string reference_arg("reference");
const std::string disable_model_module("disable-model-module");

const std::string output_to_stdout_arg("output-to-stdout");
const std::string output_to_file_arg("output-to-file");
const std::string delete_extra_files_arg("delete-extra-files");
const std::string ignore_files_matching_regex_arg(
    "ignore-files-matching-regex");
const std::string force_write_arg("force-write");

const std::string integrated_io_incompatible_with_io_facet(
    "Integrated IO cannot be used with the IO facet.");

}

namespace dogen {
namespace driver {

program_options_parser::
program_options_parser(std::vector<std::string> arguments)
    : verbose_(false), arguments_(arguments),
      current_path_(boost::filesystem::current_path()) { }

program_options_parser::
program_options_parser(int argc, char** argv)
    : verbose_(false), arguments_(argv + 1, argv + argc),
      current_path_(boost::filesystem::current_path()) { }

boost::program_options::options_description
program_options_parser::general_options_factory() const {
    boost::program_options::options_description r("General options");
    r.add_options()
        ("help,h", "Display this help and exit.")
        ("version", "Output version information and exit.")
        ("info", "Lists available backends.");
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
            "If required you can add the module path: file,PP.")
        ("disable-model-module",
            "Do not generate a top-level module with the model name.");

    return r;
}

boost::program_options::options_description
program_options_parser::output_options_factory() const {
    using boost::program_options::value;
    boost::program_options::options_description r("Output options");
    r.add_options()
        ("delete-extra-files,d", "Delete any additional files found in "
            "directories managed by Dogen.")
        ("ignore-files-matching-regex",
            value<std::vector<std::string> >(),
            "Ignore files matching regex, if they are on the deletion list")
        ("force-write", "Always write to file even when there are no differences")
        ("output-to-file", "Create files. Disabled by default if "
            "output-to-stdout is chosen.")
        ("output-to-stdout", " Output generated code to standard output. "
            "Disables output-to-file by default.");

    return r;
}

boost::program_options::options_description
program_options_parser::cpp_options_factory() const {
    using boost::program_options::value;
    boost::program_options::options_description r("C++ backend options");
    r.add_options()
        ("cpp-disable-backend", "Do not generate C++ code.")
        ("cpp-disable-complete-constructor",
            "Do not generate a constructor taking as arguments all member "
            "variables")
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
            "If supplied, source directory must be supplied too.")
        ("cpp-enable-facet",
            value<std::vector<std::string> >(),
            "If set, only domain and enabled facets are generated. "
            "By default all facets are generated. Valid values: "
            "[io | hash | serialization | test_data | odb].")
        ("cpp-header-extension",
            value<std::string>()->default_value(".hpp"),
            "Extension for C++ header files, including leading '.'.")
        ("cpp-source-extension",
            value<std::string>()->default_value(".cpp"),
            "Extension for C++ source files, including leading '.'.")
        ("cpp-disable-facet-includers", "Do not create a global header file "
            "that includes all header files in that facet.")
        ("cpp-disable-facet-folders", "Do not create sub-folders for facets.")
        ("cpp-disable-unique-file-names", "Do not make file names unique. "
            "Defaults to true. Must be true if not generating facet folders.")
        ("cpp-domain-facet-folder",
            value<std::string>()->default_value("types"),
            "Name for the domain facet folder.")
        ("cpp-hash-facet-folder",
            value<std::string>()->default_value("hash"),
            "Name for the hash facet folder.")
        ("cpp-io-facet-folder",
            value<std::string>()->default_value("io"),
            "Name for the io facet folder.")
        ("cpp-serialization-facet-folder",
            value<std::string>()->default_value("serialization"),
            "Name for the serialization facet folder.")
        ("cpp-test-data-facet-folder",
            value<std::string>()->default_value("test_data"),
            "Name for the test data facet folder.")
        ("cpp-odb-facet-folder",
            value<std::string>()->default_value("odb"),
            "Name for the ODB facet folder.")
        ("cpp-disable-xml-serialization", "Do not add NVP macros to boost"
            " serialization code. This is used to support boost XML archives.")
        ("cpp-use-integrated-io", "Add inserters directly to domain facet "
            "rather than using IO facet.")
        ("cpp-disable-versioning",
            "Do not generate entity versioning code for domain types.");

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
        BOOST_LOG_SEV(lg, dogen::utility::log::error) << e.what();
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
           << " Try `dogen --help' for more information.";
    BOOST_LOG_SEV(lg, error) << stream.str();
    BOOST_THROW_EXCEPTION(parser_validation_error(stream.str()));
}

void program_options_parser::throw_include_source_without_split() const {
    std::ostringstream stream;
    stream << "Arguments source-dir and include-dir"
           << " require project splitting. "
           << " Try `dogen --help' for more information.";
    BOOST_LOG_SEV(lg, error) << stream.str();
    BOOST_THROW_EXCEPTION(parser_validation_error(stream.str()));
}

void program_options_parser::throw_missing_include_source() const {
    std::ostringstream stream;
    stream << "You must supply both source-dir and include-dir"
           << " or not supply either. "
           << " Try `dogen --help' for more information.";
    BOOST_LOG_SEV(lg, error) << stream.str();
    BOOST_THROW_EXCEPTION(parser_validation_error(stream.str()));
}

void program_options_parser::throw_missing_target() const {
    std::ostringstream stream;
    stream << "Mandatory parameter target is missing. "
           << "Try `dogen --help' for more information.";
    BOOST_LOG_SEV(lg, error) << stream.str();
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
    BOOST_LOG_SEV(lg, error) << invalid_archive_type;
    BOOST_THROW_EXCEPTION(invalid_enum_value(invalid_archive_type));
}

config::cpp_facet_types
program_options_parser::parse_facet_types(const std::string& s) {
    using config::cpp_facet_types;
    if (s == domain_facet_type) return cpp_facet_types::types;
    if (s == hash_facet_type) return cpp_facet_types::hash;
    if (s == serialization_facet_type) return cpp_facet_types::serialization;
    if (s == io_facet_type) return cpp_facet_types::io;
    if (s == test_data_facet_type) return cpp_facet_types::test_data;
    if (s == odb_facet_type) return cpp_facet_types::odb;

    using utility::exception::invalid_enum_value;
    BOOST_LOG_SEV(lg, error) << invalid_facet_type << s;
    BOOST_THROW_EXCEPTION(invalid_enum_value(invalid_facet_type + s));
}

config::cpp_settings program_options_parser::
transform_cpp_settings(const boost::program_options::variables_map& vm) const {
    config::cpp_settings r;

    r.verbose(verbose_);
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
            r.source_directory(current_path_);
            r.include_directory(current_path_);
        } else {
            r.source_directory(vm[cpp_source_dir_arg].as<std::string>());
            r.include_directory(vm[cpp_include_dir_arg].as<std::string>());
        }
    } else {
        if (!vm.count(cpp_project_dir_arg))
            r.project_directory(current_path_);
        else
            r.project_directory(vm[cpp_project_dir_arg].as<std::string>());
    }

    r.disable_backend(vm.count(cpp_disable_backend_arg));
    r.disable_cmakelists(vm.count(cpp_disable_cmakelists_arg));
    r.disable_facet_includers(vm.count(cpp_disable_facet_includers));
    r.disable_facet_folders(vm.count(cpp_disable_facet_folders_arg));
    r.disable_xml_serialization(vm.count(cpp_disable_xml_serialization_arg));
    r.disable_unique_file_names(vm.count(cpp_disable_unique_file_names_arg));
    r.use_integrated_io(vm.count(cpp_use_integrated_io_arg));
    r.disable_complete_constructor(
        vm.count(cpp_disable_complete_constructor_arg));

    r.header_extension(vm[cpp_header_extension_arg].as<std::string>());
    r.source_extension(vm[cpp_source_extension_arg].as<std::string>());

    r.domain_facet_folder(vm[cpp_domain_facet_folder_arg].as<std::string>());
    r.hash_facet_folder(vm[cpp_hash_facet_folder_arg].as<std::string>());
    r.io_facet_folder(vm[cpp_io_facet_folder_arg].as<std::string>());
    r.serialization_facet_folder(
        vm[cpp_serialization_facet_folder_arg].as<std::string>());
    r.test_data_facet_folder(
        vm[cpp_test_data_facet_folder_arg].as<std::string>());
    r.odb_facet_folder(vm[cpp_odb_facet_folder_arg].as<std::string>());

    using config::cpp_facet_types;
    std::set<cpp_facet_types> set;
    if (vm.count(cpp_enable_facet_arg)) {
        try {
            set.insert(cpp_facet_types::types);
            typedef std::vector<std::string> vector;
            const auto v(vm[cpp_enable_facet_arg].as<vector>());
            boost::copy(v |
                boost::adaptors::transformed(
                    &program_options_parser::parse_facet_types),
                std::inserter(set, set.end()));
        } catch (const utility::exception::invalid_enum_value& e) {
            BOOST_LOG_SEV(lg, error) << e.what();
            BOOST_THROW_EXCEPTION(parser_validation_error(e.what()));
        }

        if (r.use_integrated_io()) {
            const auto f(r.enabled_facets());
            const bool has_io_facet(f.find(cpp_facet_types::io) != f.end());
            if (has_io_facet) {
                BOOST_LOG_SEV(lg, error)
                    << integrated_io_incompatible_with_io_facet;
                BOOST_THROW_EXCEPTION(parser_validation_error(
                        integrated_io_incompatible_with_io_facet));
            }
        }
    } else {
        set.insert(cpp_facet_types::types);
        set.insert(cpp_facet_types::hash);
        set.insert(cpp_facet_types::serialization);
        set.insert(cpp_facet_types::test_data);
        set.insert(cpp_facet_types::odb);
        if (!r.use_integrated_io())
            set.insert(cpp_facet_types::io);
    }
    r.enabled_facets(set);

    return r;
}

config::modeling_settings
program_options_parser::transform_modeling_settings(
    const boost::program_options::variables_map& vm) const {
    config::modeling_settings r;

    r.verbose(verbose_);
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

            if (tokens.empty()) {
                BOOST_LOG_SEV(lg, error) << at_least_one_argument;
                BOOST_THROW_EXCEPTION(parser_validation_error(
                        at_least_one_argument));
            }
            if (tokens.size() > 2) {
                BOOST_LOG_SEV(lg, error) << at_most_two_arguments;
                BOOST_THROW_EXCEPTION(parser_validation_error(
                        at_most_two_arguments));
            }
            dogen::config::reference ref;
            ref.path(tokens[0]);
            if (tokens.size() > 1)
                ref.external_module_path(tokens[1]);
            references.push_back(ref);
        }
        r.references(references);
    }
    r.disable_model_module(vm.count(disable_model_module));

    return r;
}

config::troubleshooting_settings program_options_parser::
transform_troubleshooting_settings(const variables_map& vm) const {
    config::troubleshooting_settings r;

    r.verbose(verbose_);
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
                    BOOST_LOG_SEV(lg, error) << e.what();
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

config::output_settings program_options_parser::
transform_output_settings(const variables_map& vm) const {
    config::output_settings r;
    r.verbose(verbose_);
    r.output_to_stdout(vm.count(output_to_stdout_arg));
    r.output_to_file(vm.count(output_to_file_arg) || !r.output_to_stdout());
    r.delete_extra_files(vm.count(delete_extra_files_arg));
    if (vm.count(ignore_files_matching_regex_arg)) {
        r.ignore_patterns(
            vm[ignore_files_matching_regex_arg].as<std::vector<std::string> >());
    }
    r.force_write(vm.count(force_write_arg));
    return r;
}

boost::optional<config::settings> program_options_parser::parse() {
    auto optional_vm(variables_map_factory());

    if (!optional_vm)
        return boost::optional<config::settings>();

    const boost::program_options::variables_map vm(*optional_vm);
    verbose_ = vm.count(verbose_arg);

    settings_.modeling(transform_modeling_settings(vm));
    settings_.cpp(transform_cpp_settings(vm));
    settings_.troubleshooting(transform_troubleshooting_settings(vm));
    settings_.output(transform_output_settings(vm));

    return boost::optional<config::settings>(settings_);
}

} }
