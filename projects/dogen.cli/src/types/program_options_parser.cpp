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
#include <string_view>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/program_options.hpp>
#include <boost/throw_exception.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "dogen/types/database_engine.hpp"
#include "dogen/config.hpp"
#include "dogen.utility/types/log/severity_level.hpp"
#include "dogen.utility/types/log/logging_configuration.hpp"
#include "dogen.cli/types/parser_exception.hpp"
#include "dogen.cli/types/program_options_parser.hpp"

namespace {

const std::string empty;
const std::string indent("   ");
const std::string run_identifier_prefix("cli.");

const std::string more_information("Try --help' for more information.");
const std::string product_version("MASD Dogen v" DOGEN_VERSION);
const std::string build_info(DOGEN_BUILD_INFO);
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
const std::string dumpspecs_command_name("dumpspecs");
const std::string dumpspecs_command_desc(
    "Dumps all specs for Dogen.");

const std::string help_arg("help");
const std::string version_arg("version");
const std::string command_arg("command");
const std::string reference_directory_arg("reference-directory");

const std::string logging_log_enabled_arg("log-enabled");
const std::string logging_log_to_console_arg("log-to-console");
const std::string logging_log_level_arg("log-level");
const std::string logging_log_level_trace("trace");
const std::string logging_log_level_debug("debug");
const std::string logging_log_level_info("info");
const std::string logging_log_level_warn("warn");
const std::string logging_log_level_error("error");

const std::string tracing_enabled_arg("tracing-enabled");
const std::string tracing_level_arg("tracing-level");
const std::string tracing_level_detail("detail");
const std::string tracing_level_summary("summary");
const std::string tracing_guids_enabled_arg("tracing-guids-enabled");
const std::string tracing_format_arg("tracing-format");
const std::string tracing_format_plain("plain");
const std::string tracing_format_org_mode("org-mode");
const std::string tracing_format_graphviz("graphviz");
const std::string tracing_default_directory("tracing");
const std::string tracing_backend_arg("tracing-backend");
const std::string tracing_backend_file("file");
const std::string tracing_backend_database("relational");
const std::string tracing_run_id_arg("tracing-run-id");
const std::string tracing_filter_regex_arg("tracing-filter-regex");

const std::string reporting_enabled_arg("reporting-enabled");
const std::string reporting_style_arg("reporting-style");
const std::string reporting_style_org_mode("org-mode");
const std::string reporting_style_plain("plain");

const std::string diffing_enabled_arg("diffing-enabled");
const std::string diffing_destination_arg("diffing-destination");
const std::string diffing_report_unchanged_arg("diffing-report-unchanged");
const std::string diffing_destination_file("file");
const std::string diffing_destination_console("console");

const std::string database_hostname_arg("database-host");
const std::string database_port_arg("database-port");
const std::string database_name_arg("database-name");
const std::string database_user_arg("database-user");
const std::string database_password_arg("database-password");
const std::string database_engine_arg("database-engine");
const std::string database_engine_postgres("postgres");
const std::string database_engine_sqlite("sqlite");
const std::string database_schema_gen_arg("database-generate-schema");

const std::string model_processing_compatibility_mode_arg(
    "compatibility-mode-enabled");
const std::string model_processing_dry_run_mode_enabled_arg(
    "dry-run-mode-enabled");
const std::string model_processing_variability_override_arg(
    "variability-override");
const std::string model_processing_activity_timestamp_arg("activity-timestamp");

const std::string output_byproduct_directory_arg(
    "byproduct-directory");
const std::string output_default_byproduct_directory("dogen.byproducts");

const std::string generate_target_arg("target");
const std::string generate_output_dir_arg("output-directory");
const std::string convert_source_arg("source");
const std::string convert_destination_arg("destination");

const std::string invalid_engine("Database engine is not valid: ");
const std::string invalid_backend("Tracing backend is not valid: ");
const std::string invalid_option("Option is not valid for command: ");
const std::string invalid_command("Command is invalid or unsupported: ");
const std::string missing_target("Mandatory parameter target is missing. ");
const std::string invalid_tracing_level("Tracing level is invalid: ");
const std::string invalid_log_level("Log level is invalid: ");
const std::string invalid_format("Tracing format is invalid: ");
const std::string invalid_diffing_destination(
    "Diffing destination is invalid or unsupported: ");
const std::string invalid_reporting_style(
    "Reporting style is invalid or unsupported: ");
const std::string invalid_activity_timestamp("Invalid activity timestamp: ");

const std::string logging_impact_none("none");
const std::string logging_impact_moderate("none");
const std::string logging_impact_severe("severe");

using boost::program_options::value;
using boost::program_options::variables_map;
using boost::program_options::options_description;
using boost::program_options::positional_options_description;
using dogen::cli::configuration;
using dogen::cli::parser_exception;
using dogen::cli::generation_configuration;
using dogen::cli::conversion_configuration;
using dogen::cli::dumpspecs_configuration;
using dogen::utility::log::logging_configuration;

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

    options_description bod("Output");
    bod.add_options()
        ("byproduct-directory", "Directory in which to place all of the "
            "byproducts of the run such as log files, traces, etc.");
    r.add(bod);

    options_description lod("Logging");
    lod.add_options()
        ("log-enabled,e", "Generate a log file.")
        ("log-level,l", value<std::string>(),
            "What level to use for logging. Valid values: trace, debug, info, "
            "warn, error. Defaults to info.")
        ("log-to-console",
            "Output logging to the console, as well as to file.");
    r.add(lod);

    options_description tod("Tracing");
    tod.add_options()
        ("tracing-enabled", "Generate metrics about executed transforms.")
        ("tracing-level",  value<std::string>(), "Level at which to trace."
            "Valid values: detail, summary. Defaults to summary.")
        ("tracing-guids-enabled", "Use guids in tracing metrics, Not"
            "  recommended when making comparisons between runs.")
        ("tracing-format", value<std::string>(), "Format to use for tracing"
            " metrics. Valid values: plain, org-mode, graphviz. "
            "Defaults to org-mode.")
        ("tracing-backend", value<std::string>(),
            "Backend to use for tracing. Valid values: file, relational.")
        ("tracing-run-id", value<std::string>(),
            "Run ID to use to identify the tracing session.")
        ("tracing-filter-regex", value<std::vector<std::string>>(),
            "One or more regular expressions for the transform ID, used "
            "to filter the tracing output.");
    r.add(tod);

    options_description orod("Reporting");
    orod.add_options()
        ("reporting-enabled", "Generate a report detailing operations.")
        ("reporting-style",  value<std::string>(),
            "Style to use in the operational report. "
            "Valid values: plain, org-mode. Defaults to org-mode.");
    r.add(orod);

    options_description dod("Diffing");
    dod.add_options()
        ("diffing-enabled", "Generate diffs against files in the filesystem.")
        ("diffing-destination",  value<std::string>(), "Where to write the "
            " diff output. Valid values: file, console. Defaults to file.");
    r.add(dod);

    options_description ehod("Processing");
    ehod.add_options()
        ("compatibility-mode-enabled",
            "Try to process models even if there are errors.")
        ("dry-run-mode-enabled",
            "Executes all transforms but does not emit generated code.")
        ("variability-override", value<std::vector<std::string>>(),
            "CSV string with a variability override. Must have the form of "
            "[MODEL_NAME,][ELEMENT_NAME,][ATTRIBUTE_NAME,]KEY,VALUE")
        ("activity-timestamp", value<std::string>(),
            "Override the NOW value used for the activity timestamp. "
            "Format: %Y-%m-%dT%H:%M:%S");
    r.add(ehod);

    options_description db("Database");
    db.add_options()
        ("database-host", value<std::string>(),
            "Name of the machine hosting the database.")
        ("database-port", value<unsigned int>(),
            "Port to connect to access the database.")
        ("database-name", value<std::string>(),
            "Name of the database.")
        ("database-user", value<std::string>(),
            "User to connect as in the database.")
        ("database-password", value<std::string>(),
            "Password for the user.")
        ("database-engine", value<std::string>(),
            "Database engine. Valid values: postgresql, sqlite.")
        ("database-generate-schema",
            "If true, deletes all tables and regenerates them. Otherwise, "
            "assumes their presence.");

    r.add(db);

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
            "Available commands: generate, convert, dumpspecs.")
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
            "Defaults to the current working directory.")
        ("reference-directory,r",
            value<std::vector<std::string>>(), "One or more directories to"
            " check for referenced models.");

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
 * @brief Creates the options related to dumping specs.
 */
options_description make_dumpspecs_options_description() {
    options_description r("Dumping specs");
    r.add_options()
        ("reporting-style", value<std::string>(), "Format to use for dumping"
            " specs. Valid values: plain, org-mode. Defaults to org-mode.");

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
        command_name == dumpspecs_command_name);

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
    s << "dogen.cli uses a command-based interface: <command> <options>. "
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
    lambda(dumpspecs_command_name, dumpspecs_command_desc);

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
    s << product_version << std::endl
      << "Copyright (C) 2015-2017 Domain Driven Consulting Plc."
      << std::endl
      << "Copyright (C) 2012-2015 Marco Craveiro." << std::endl
      << "License GPLv3: GNU GPL version 3 or later "
      << "<http://gnu.org/licenses/gpl.html>." << std::endl
      << "This is free software: you are free to change and redistribute it."
      << std::endl << "There is NO WARRANTY, to the extent permitted by law."
      << std::endl;


    if (!build_info.empty()) {
        s << build_info << std::endl;
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
     * The only valid options are help or version, so if those are not
     * present we can safely throw.
     */
    if (!has_version && !has_help)
        BOOST_THROW_EXCEPTION(parser_exception(no_command_msg));

    /*
     * Note that we do not mind if the user has supplied both help and
     * version - help takes priority.
     */
    if (has_help)
        print_help(od, info);
    else if (has_version)
        version(info);

    return boost::optional<configuration>();
}

std::string
compute_logging_impact(const boost::optional<logging_configuration> cfg) {

    if (!cfg)
        return logging_impact_none;

    if (cfg->severity() == logging_log_level_info)
        return logging_impact_moderate;

    return logging_impact_severe;
}

/**
 * @brief Reads the tracing configuration from the variables map.
 */
boost::optional<dogen::tracing_configuration>
read_tracing_configuration(const variables_map& vm,
    const std::string& logging_impact,
    const boost::filesystem::path& byproduct_dir) {

    const bool enabled(vm.count(tracing_enabled_arg) != 0);
    if (!enabled)
        return boost::optional<dogen::tracing_configuration>();

    dogen::tracing_configuration r;
    r.guids_enabled(vm.count(tracing_guids_enabled_arg) != 0);
    r.logging_impact(logging_impact);

    using dogen::tracing_level;
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

    using dogen::tracing_format;
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

    using dogen::tracing_backend;
    if (vm.count(tracing_backend_arg)) {
        const auto s(vm[tracing_backend_arg].as<std::string>());
        if (s == tracing_backend_file)
            r.backend(tracing_backend::file);
        else if (s == tracing_backend_database)
            r.backend(tracing_backend::relational_database);
        else
            BOOST_THROW_EXCEPTION(parser_exception(invalid_backend + s));
    }

    if (!vm.count(tracing_run_id_arg)) {
        const auto uuid = boost::uuids::random_generator()();
        r.run_id(boost::uuids::to_string(uuid));
    } else
        r.run_id(vm[tracing_run_id_arg].as<std::string>());

    const auto tracing_dir(byproduct_dir / tracing_default_directory);
    r.output_directory(tracing_dir);

    if (vm.count(tracing_filter_regex_arg)) {
        r.filter_regexes(vm[tracing_filter_regex_arg]
            .as<std::vector<std::string>>());
    }

    return r;
}

dogen::model_processing_configuration
read_model_processing_configuration(const variables_map& vm) {
    const bool compatibility_mode(
        vm.count(model_processing_compatibility_mode_arg) != 0);

    dogen::model_processing_configuration r;
    r.compatibility_mode_enabled(compatibility_mode);

    const bool dry_run(
        vm.count(model_processing_dry_run_mode_enabled_arg) != 0);
    r.dry_run_mode_enabled(dry_run);

    if (vm.count(model_processing_variability_override_arg)) {
        const auto vo(vm[model_processing_variability_override_arg]
            .as<std::vector<std::string>>());
        r.variability_overrides(vo);
    }

    if (vm.count(model_processing_activity_timestamp_arg)) {
        const auto at(vm[model_processing_activity_timestamp_arg]
            .as<std::string>());

        const std::string fmt("%Y-%m-%dT%H:%M:%S");
        const std::locale l(std::locale::classic(),
            new boost::posix_time::time_input_facet(fmt));

        std::istringstream is(at);
        is.imbue(l);
        boost::posix_time::ptime pt;
        is >> pt;
        if(pt == boost::posix_time::ptime()) {
            BOOST_THROW_EXCEPTION(
                parser_exception(invalid_activity_timestamp + at));
        }
        r.activity_timestamp(pt);
    } else
        r.activity_timestamp(boost::posix_time::second_clock::local_time());

    return r;
}

boost::optional<dogen::diffing_configuration>
read_diffing_configuration(const variables_map& vm,
    const boost::filesystem::path& byproduct_dir) {
    const bool enabled(vm.count(diffing_enabled_arg) != 0);
    if (!enabled)
        return boost::optional<dogen::diffing_configuration>();

    dogen::diffing_configuration r;
    using dogen::diffing_destination;
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

    r.output_directory(byproduct_dir);

    return r;
}

boost::optional<dogen::reporting_configuration>
read_reporting_configuration(const variables_map& vm,
    const boost::filesystem::path& byproduct_dir) {
    using dogen::reporting_configuration;
    const bool enabled(vm.count(reporting_enabled_arg) != 0);
    if (!enabled)
        return boost::optional<reporting_configuration>();

    reporting_configuration r;
    using dogen::reporting_style;
    if (vm.count(reporting_style_arg)) {
        const auto s(vm[reporting_style_arg].as<std::string>());

        if (s == reporting_style_org_mode)
            r.style(reporting_style::org_mode);
        else if (s == reporting_style_plain)
            r.style(reporting_style::plain);
        else
            BOOST_THROW_EXCEPTION(parser_exception(
                    invalid_reporting_style + s));
    } else if (enabled)
        r.style(reporting_style::org_mode);

    r.output_directory(byproduct_dir);

    return r;
}

boost::optional<dogen::database_configuration>
read_database_configuration(const variables_map& vm) {
    using dogen::database_configuration;
    bool found(false);

    database_configuration r;
    if (vm.count(database_hostname_arg)) {
        found = true;
        r.host(vm[database_hostname_arg].as<std::string>());
    }

    if (vm.count(database_port_arg) != 0) {
        found = true;
        r.port(vm[database_port_arg].as<unsigned int>());
    }

    if (vm.count(database_name_arg) != 0) {
        found = true;
        r.name(vm[database_name_arg].as<std::string>());
    }

    if (vm.count(database_user_arg) != 0) {
        found = true;
        r.user(vm[database_user_arg].as<std::string>());
    }

    if (vm.count(database_password_arg) != 0) {
        found = true;
        r.password(vm[database_password_arg].as<std::string>());
    }

    if (vm.count(database_engine_arg) != 0) {
        found = true;
         const auto s(vm[database_engine_arg].as<std::string>());
         using dogen::database_engine;
         if (s == database_engine_postgres)
             r.engine(database_engine::postgres);
         else if (s == database_engine_sqlite)
             r.engine(database_engine::sqlite);
         else
             BOOST_THROW_EXCEPTION(parser_exception(invalid_engine + s));
    }

    if (vm.count(database_schema_gen_arg) != 0) {
        found = true;
        r.generate_schema(true);
    }

    if (!found)
        return boost::optional<database_configuration>();
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
    const std::string& run_identifier, const variables_map& vm,
    const boost::filesystem::path& byproduct_dir) {
    const auto enabled(vm.count(logging_log_enabled_arg) != 0);
    if (!enabled)
        return boost::optional<logging_configuration>();

    logging_configuration r;
    r.filename(run_identifier);
    r.output_to_console(vm.count(logging_log_to_console_arg) != 0);
    r.output_directory(byproduct_dir);

    const bool log_level_set(vm.count(logging_log_level_arg) != 0);
    if (!log_level_set) {
        r.severity(logging_log_level_info);
        return r;
    }

    const auto s(vm[logging_log_level_arg].as<std::string>());
    try {
        using dogen::utility::log::to_severity_level;
        to_severity_level(s);
        r.severity(s);
    } catch(const std::exception&) {
        BOOST_THROW_EXCEPTION(parser_exception(invalid_log_level + s));
    }
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

    if (vm.count(reference_directory_arg)) {
        const auto rds(vm[reference_directory_arg].
            as<std::vector<std::string>>());
        for (const auto& rd : rds) {
            const boost::filesystem::path p(rd);
            r.reference_model_directories().push_back(p);
        }
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

dumpspecs_configuration
read_dumpspecs_configuration(const variables_map& vm) {
    dumpspecs_configuration r;

    using dogen::reporting_style;
    if (vm.count(reporting_style_arg)) {
        const auto s(vm[reporting_style_arg].as<std::string>());

        if (s == reporting_style_org_mode)
            r.style(reporting_style::org_mode);
        else if (s == reporting_style_plain)
            r.style(reporting_style::plain);
        else
            BOOST_THROW_EXCEPTION(parser_exception(
                    invalid_reporting_style + s));
    } else
        r.style(reporting_style::org_mode);

    return r;
}

boost::filesystem::path read_byproduct_directory(
    const variables_map& vm, const std::string& run_identifier) {

    using boost::filesystem::absolute;
    if (vm.count(output_byproduct_directory_arg) != 0) {
        /*
         * First the simplest case: if the user has supplied a
         * byproduct output directory, we just honour it. The only
         * thing we need to do is to convert it to absolute. Note that
         * we do not partition this directory by run id - we assume
         * the user knows what it is doing.
         */
        const auto s(vm[output_byproduct_directory_arg].as<std::string>());
        return absolute(s);
    }

    /*
     * If the user as asked us to use the default directory, we need
     * to partition it by run id. This is so that we can have multiple
     * runs on the same directory.
     */
    auto p(absolute(output_default_byproduct_directory));
    p /= run_identifier;
    return p;
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
        const auto d(make_generate_options_description());
        if (has_help) {
            print_help_command(generate_command_name, d, info);
            return empty_config();
        }

        store(command_line_parser(options).options(d).run(), vm);
        const auto c(read_generation_configuration(vm));
        target = c.target();
        r.cli().activity(c);
    } else if (command_name == convert_command_name) {
        const auto d(make_convert_options_description());
        if (has_help) {
            print_help_command(convert_command_name, d, info);
            return empty_config();
        }

        store(command_line_parser(options).options(d).run(), vm);
        const auto c(read_conversion_configuration(vm));
        target = c.source();
        r.cli().activity(c);
    } else if (command_name == dumpspecs_command_name) {
        const auto d(make_dumpspecs_options_description());
        if (has_help) {
            print_help_command(dumpspecs_command_name, d, info);
            return empty_config();
        }
        store(command_line_parser(options).options(d).run(), vm);
        const auto c(read_dumpspecs_configuration(vm));
        r.cli().activity(c);
    }

    /*
     * Compute the byproduct directory, where all non-generated code
     * related stuff will be placed.
     */
    const auto run_id(compute_run_identifier(command_name, target));
    const auto bd(read_byproduct_directory(vm, run_id));
    r.api().byproduct_directory(bd);

    /*
     * Now process the common options. We must do this at the end
     * because we require the model name.
     */
    r.logging(read_logging_configuration(run_id, vm, bd));
    const auto li(compute_logging_impact(r.logging()));
    auto& a(r.api());
    a.tracing(read_tracing_configuration(vm, li, bd));
    a.reporting(read_reporting_configuration(vm, bd));
    a.diffing(read_diffing_configuration(vm, bd));
    a.model_processing(read_model_processing_configuration(vm));
    a.database(read_database_configuration(vm));

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

namespace dogen::cli {

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
