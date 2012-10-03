/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#define BOOST_RESULT_OF_USE_DECLTYPE
#include <string>
#include <sstream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/range/combine.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm/set_algorithm.hpp>
#include "dogen/utility/test_data/dia_sml.hpp"
#include "dogen/utility/exception/invalid_enum_value.hpp"
#include "dogen/driver/parser_validation_error.hpp"
#include "dogen/driver/program_options_parser.hpp"

namespace {

const std::string empty;
const std::string help_arg("help");
const std::string version_arg("version");

const std::string verbose_arg("verbose");
const std::string debug_dir_arg("debug-dir");
const std::string save_dia_model_arg("save-dia-model");
const std::string save_sml_model_arg("save-sml-model");

const std::string invalid_facet_type("Invalid facet type");
const std::string domain_facet_type("domain");
const std::string io_facet_type("io");
const std::string hash_facet_type("hash");
const std::string serialization_facet_type("serialization");

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
const std::string cpp_database_facet_folder_arg("cpp-database-facet-folder");
const std::string cpp_disable_xml_serialization_arg(
    "cpp-disable-xml-serialization");
const std::string cpp_use_integrated_io_arg("cpp-use-integrated-io");
const std::string cpp_disable_versioning_arg("cpp-disable-versioning");

const std::string sql_disable_backend_arg("sql-disable-backend");
const std::string sql_create_schema_arg("sql-create-schema");
const std::string sql_schema_name_arg("sql-schema-name");

const std::string target_arg("target");
const std::string external_package_path_arg("external-package-path");
const std::string reference_arg("reference");
const std::string disable_model_package("disable-model-package");

const std::string output_to_stdout_arg("output-to-stdout");
const std::string output_to_file_arg("output-to-file");
const std::string delete_extra_files_arg("delete-extra-files");
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
        ("external-package-path,p",
            value<std::string>(),
            "External packages containing the target model, delimited by '::'.")
        ("target,t",
            value<std::string>(),
            "Dia diagram to generate code for.")
        ("reference,r",
            value<std::vector<std::string> >(),
            "Dia diagrams that our target diagram depends on.")
        ("disable-model-package",
            "Do not generate a top-level package with the model name.");

    return r;
}

boost::program_options::options_description
program_options_parser::output_options_factory() const {
    using boost::program_options::value;
    boost::program_options::options_description r("Output options");
    r.add_options()
        ("delete-extra-files,d", "Delete any additional files found in "
            "directories managed by Dogen. NOT IMPLEMENTED")
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
            "[io | hash | serialization | test_data].")
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
            value<std::string>()->default_value("domain"),
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
        ("cpp-database-facet-folder",
            value<std::string>()->default_value("database"),
            "Name for the database facet folder.")
        ("cpp-disable-xml-serialization", "Do not add NVP macros to boost"
            " serialization code. This is used to support boost XML archives.")
        ("cpp-use-integrated-io", "Add inserters directly to domain facet "
            "rather than using IO facet.")
        ("cpp-use-const-ref",
            "Use constant references for complex types. **NOT IMPLEMENTED**")
        ("cpp-disable-versioning",
            "Do not generate entity versioning code for domain types.");

    return r;
}

boost::program_options::options_description
program_options_parser::sql_options_factory() const {
    using boost::program_options::value;
    boost::program_options::options_description r("SQL backend options");
    r.add_options()
        ("sql-disable-backend", "Do not generate SQL code. "
            "Incompatible with disabling versioning in C++.")
        ("sql-create-schema", "Generate DDL for creating a schema")
        ("sql-schema-name",
            value<std::string>(),
            "Which SQL schema to place all SQL code in."
            " Defaults to the top-level package name if external package path "
            " is supplied; if not, it defaults to the model name.");
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
    r.add(sql_options_factory());
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
    } catch (const error& e) {
        throw parser_validation_error(e.what());
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
    throw parser_validation_error(stream.str());
}

void program_options_parser::throw_include_source_without_split() const {
    std::ostringstream stream;
    stream << "Arguments source-dir and include-dir"
           << " require project splitting. "
           << " Try `dogen --help' for more information.";
    throw parser_validation_error(stream.str());
}

void program_options_parser::throw_missing_include_source() const {
    std::ostringstream stream;
    stream << "You must supply both source-dir and include-dir"
           << " or not supply either. "
           << " Try `dogen --help' for more information.";
    throw parser_validation_error(stream.str());
}

void program_options_parser::throw_missing_target() const {
    std::ostringstream stream;
    stream << "Mandatory parameter target is missing. "
           << "Try `dogen --help' for more information.";
    throw parser_validation_error(stream.str());
}

void program_options_parser::version_function(std::function<void()> value) {
    version_function_ = value;
}

dogen::utility::serialization::archive_types
program_options_parser::parse_archive_type(std::string s) const {
    if (s == xml_archive_type)
        return archive_types::xml;
    if (s == text_archive_type)
        return archive_types::text;
    if (s == binary_archive_type)
        return archive_types::binary;

    using utility::exception::invalid_enum_value;
    throw invalid_enum_value(invalid_archive_type);
}

dogen::generator::backends::cpp::cpp_facet_types
program_options_parser::parse_facet_types(std::string s) {
    if (s == domain_facet_type)
        return cpp_facet_types::domain;
    if (s == hash_facet_type)
        return cpp_facet_types::hash;
    if (s == serialization_facet_type)
        return cpp_facet_types::serialization;
    if (s == io_facet_type)
        return cpp_facet_types::io;

    using utility::exception::invalid_enum_value;
    throw invalid_enum_value(invalid_facet_type);
}

generator::config::cpp_settings program_options_parser::
transform_cpp_settings(boost::program_options::variables_map vm) const {
    generator::config::cpp_settings r;

    r.verbose(verbose_);

    if (vm.count(cpp_split_project_arg)) {
        if (vm.count(cpp_project_dir_arg))
            throw_project_dir_with_split();

        if (vm.count(cpp_source_dir_arg) != vm.count(cpp_include_dir_arg))
            throw_missing_include_source();

    } else {
        if (vm.count(cpp_source_dir_arg) || vm.count(cpp_include_dir_arg))
            throw_include_source_without_split();
    }

    using boost::filesystem::path;
    if (!vm.count(cpp_source_dir_arg) && !vm.count(cpp_include_dir_arg)) {
        r.source_directory(current_path_);
        r.include_directory(current_path_);
    } else {
        r.source_directory(vm[cpp_source_dir_arg].as<std::string>());
        r.include_directory(vm[cpp_include_dir_arg].as<std::string>());
    }

    r.disable_backend(vm.count(cpp_disable_backend_arg));
    r.disable_cmakelists(vm.count(cpp_disable_cmakelists_arg));
    r.disable_facet_includers(vm.count(cpp_disable_facet_includers));
    r.disable_facet_folders(vm.count(cpp_disable_facet_folders_arg));
    r.disable_xml_serialization(vm.count(cpp_disable_xml_serialization_arg));
    r.disable_unique_file_names(vm.count(cpp_disable_unique_file_names_arg));
    r.use_integrated_io(vm.count(cpp_use_integrated_io_arg));
    r.disable_versioning(vm.count(cpp_disable_versioning_arg));
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
    r.database_facet_folder(
        vm[cpp_database_facet_folder_arg].as<std::string>());

    std::set<cpp_facet_types> set;
    if (vm.count(cpp_enable_facet_arg)) {
        try {
            set.insert(cpp_facet_types::domain);
            typedef std::vector<std::string> vector;
            const auto v(vm[cpp_enable_facet_arg].as<vector>());
            boost::copy(v |
                boost::adaptors::transformed(
                    &program_options_parser::parse_facet_types),
                std::inserter(set, set.end()));
        } catch (const utility::exception::invalid_enum_value& e) {
            throw parser_validation_error(e.what());
        }

        if (r.use_integrated_io()) {
            const auto f(r.enabled_facets());
            const bool has_io_facet(f.find(cpp_facet_types::io) != f.end());
            if (has_io_facet) {
                throw parser_validation_error(
                    integrated_io_incompatible_with_io_facet);
            }
        }
    } else {
        set.insert(cpp_facet_types::domain);
        set.insert(cpp_facet_types::hash);
        set.insert(cpp_facet_types::serialization);
        set.insert(cpp_facet_types::test_data);
        set.insert(cpp_facet_types::database);
        if (!r.use_integrated_io())
            set.insert(cpp_facet_types::io);
    }
    r.enabled_facets(set);

    return r;
}

generator::config::sql_settings program_options_parser::
transform_sql_settings(boost::program_options::variables_map vm) const {
    generator::config::sql_settings r;

    r.verbose(verbose_);
    r.disable_backend(vm.count(sql_disable_backend_arg));

    if (vm.count(sql_schema_name_arg))
        r.schema_name(vm[sql_schema_name_arg].as<std::string>());
    r.create_schema(vm.count(sql_create_schema_arg));

    return r;
}

generator::config::modeling_settings program_options_parser::
transform_modeling_settings(boost::program_options::variables_map vm) const {
    generator::config::modeling_settings r;

    r.verbose(verbose_);
    if (!vm.count(target_arg))
        throw_missing_target();
    r.target(vm[target_arg].as<std::string>());

    if (vm.count(external_package_path_arg)) {
        r.external_package_path(
            vm[external_package_path_arg].as<std::string>());
    }

    if (vm.count(reference_arg)) {
        std::vector<boost::filesystem::path> o;
        const auto i(vm[reference_arg].as<std::vector<std::string> >());
        boost::copy(i | boost::adaptors::transformed([](std::string s) {
                    return boost::filesystem::path(s);
                }), std::back_inserter(o));
        r.references(o);
    }
    r.disable_model_package(vm.count(disable_model_package));

    return r;
}

generator::config::troubleshooting_settings program_options_parser::
transform_troubleshooting_settings(variables_map vm) const {
    generator::config::troubleshooting_settings r;

    r.verbose(verbose_);
    r.stop_after_merging(vm.count(stop_after_merging_arg));
    r.stop_after_formatting(vm.count(stop_after_formatting_arg));

    bool need_debug_dir(false);
    auto lambda([&](std::string arg) {
            if (vm.count(arg)) {
                need_debug_dir = true;
                using utility::exception::invalid_enum_value;
                try {
                    return parse_archive_type(vm[arg].as<std::string>());
                } catch (const invalid_enum_value& e) {
                    throw parser_validation_error(e.what());
                }
            }
            using utility::serialization::archive_types;
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

generator::config::output_settings
program_options_parser::transform_output_settings(variables_map vm) const {
    generator::config::output_settings r;
    r.verbose(verbose_);
    r.output_to_stdout(vm.count(output_to_stdout_arg));
    r.output_to_file(vm.count(output_to_file_arg) || !r.output_to_stdout());
    r.delete_extra_files(vm.count(delete_extra_files_arg));
    r.force_write(vm.count(force_write_arg));
    return r;
}

boost::optional<generator::config::settings> program_options_parser::parse() {
    auto optional_vm(variables_map_factory());

    if (!optional_vm)
        return boost::optional<generator::config::settings>();

    const boost::program_options::variables_map vm(*optional_vm);
    verbose_ = vm.count(verbose_arg);

    settings_.modeling(transform_modeling_settings(vm));
    settings_.cpp(transform_cpp_settings(vm));
    settings_.sql(transform_sql_settings(vm));
    settings_.troubleshooting(transform_troubleshooting_settings(vm));
    settings_.output(transform_output_settings(vm));

    return boost::optional<generator::config::settings>(settings_);
}

} }
