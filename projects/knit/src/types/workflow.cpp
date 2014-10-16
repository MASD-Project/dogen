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
#include <boost/filesystem.hpp>
#include <boost/range/combine.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm/set_algorithm.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/utility/exception/invalid_enum_value.hpp"
#include "dogen/frontend/types/workflow.hpp"
#include "dogen/config/types/knitting_settings_validator.hpp"
#include "dogen/config/io/knitting_settings_io.hpp"
#include "dogen/knit/types/housekeeper.hpp"
#include "dogen/knit/types/generation_failure.hpp"
#include "dogen/sml_to_cpp/types/workflow_failure.hpp"
#include "dogen/cpp_formatters/types/formatting_error.hpp" // FIXME
#include "dogen/knit/types/outputters/factory.hpp"
#include "dogen/sml/serialization/model_ser.hpp"
#include "dogen/knit/types/backends/factory.hpp"
#include "dogen/sml/types/persister.hpp"
#include "dogen/sml/types/workflow.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/knit/types/workflow.hpp"

using namespace dogen::utility::log;

typedef boost::error_info<struct tag_workflow, std::string> errmsg_workflow;

namespace {

auto lg(logger_factory("knit.workflow"));

const std::string xml_extension(".xml");
const std::string text_extension(".txt");
const std::string binary_extension(".bin");
const std::string target_postfix("_target");
const std::string library_dir("library");
const std::string merged("merged_");
const std::string invalid_archive_type("Invalid or unexpected archive type");
const std::string codegen_error("Error occurred during code generation: ");
const std::string incorrect_stdout_config(
    "Configuration for output to stdout is incorrect");
const std::string code_generation_failure("Code generation failure.");

}

namespace dogen {
namespace knit {

workflow::workflow(workflow&& rhs)
    : knitting_settings_(std::move(rhs.knitting_settings_)) { }

workflow::
workflow(const config::knitting_settings& s) : knitting_settings_(s) {

    if (knitting_settings_.output().output_to_stdout()) {
        BOOST_LOG_SEV(lg, error) << incorrect_stdout_config;
        BOOST_THROW_EXCEPTION(generation_failure(incorrect_stdout_config));
    }
    config::knitting_settings_validator::validate(knitting_settings_);
}

workflow::workflow(const config::knitting_settings& s, const output_fn& o)
    : knitting_settings_(s), output_(o) {

    if (!knitting_settings_.output().output_to_stdout() || !output_) {
        BOOST_LOG_SEV(lg, error) << incorrect_stdout_config;
        BOOST_THROW_EXCEPTION(generation_failure(incorrect_stdout_config));
    }
    config::knitting_settings_validator::validate(knitting_settings_);
}

bool workflow::housekeeping_required() const {
    return
        !knitting_settings_.troubleshooting().stop_after_merging() &&
        !knitting_settings_.troubleshooting().stop_after_formatting() &&
        knitting_settings_.output().delete_extra_files() &&
        knitting_settings_.output().output_to_file();
}

void workflow::
housekeep(const std::map<boost::filesystem::path, std::string>& files,
    const std::vector<boost::filesystem::path>& dirs) const {
    using boost::adaptors::transformed;
    using boost::filesystem::path;
    std::set<path> expected_files;
    boost::copy(files | transformed([&](std::pair<path, std::string> p) {
                return p.first;
            }),
        std::inserter(expected_files, expected_files.end()));

    const auto& ip(knitting_settings_.output().ignore_patterns());
    housekeeper hk(ip, dirs, expected_files);
    hk.tidy_up();
}

void workflow::output_files(const outputters::outputter::value_type& o) const {
    if (knitting_settings_.troubleshooting().stop_after_formatting()) {
        BOOST_LOG_SEV(lg, warn) << "Stopping after formatting, so no output.";
        return;
    }

    if (o.empty()) {
        BOOST_LOG_SEV(lg, warn) << "No files were generated, so no output.";
        return;
    }

    const auto lambda([&](outputters::outputter::ptr p) { p->output(o); });
    outputters::factory f(knitting_settings_.output(), output_);
    boost::for_each(f.create(), lambda);
}

void workflow::create_files_for_backend(backends::backend& b) const {
    const auto files(b.generate());
    output_files(files);

    if (!housekeeping_required())
        return;

    housekeep(files, b.managed_directories());
}

std::string workflow::extension(config::archive_types at) const {
    using config::archive_types;
    switch (at) {
    case archive_types::xml: return xml_extension;
    case archive_types::text: return text_extension;
    case archive_types::binary: return binary_extension;
    default:
        break;
    }

    using dogen::utility::exception::invalid_enum_value;
    BOOST_LOG_SEV(lg, error) << invalid_archive_type;
    BOOST_THROW_EXCEPTION(invalid_enum_value(invalid_archive_type));
}

boost::filesystem::path workflow::
create_debug_file_path(const config::archive_types at,
    const boost::filesystem::path& original_path) const {

    const auto& ts(knitting_settings_.troubleshooting());
    boost::filesystem::path r(ts.debug_dir());
    r /= original_path.stem().string() + target_postfix;
    r.replace_extension(extension(at));
    return r;
}

std::list<frontend::input_descriptor>
workflow::obtain_input_descriptors_activity() const {
    std::list<frontend::input_descriptor> r;
    using namespace dogen::utility::filesystem;
    const auto dir(data_files_directory() / library_dir);

    const auto files(find_files(dir));
    BOOST_LOG_SEV(lg, debug) << "Found " << files.size()
                             << " paths to library models.";

    for (const auto& f : files) {
        BOOST_LOG_SEV(lg, debug) << "Library model: " << f.filename();
        frontend::input_descriptor id;
        id.path(f);
        id.is_target(false);
        r.push_back(id);
    }
    BOOST_LOG_SEV(lg, debug) << "Done creating paths to library models.";

    const auto input_settings(knitting_settings_.input());
    BOOST_LOG_SEV(lg, debug) << "Found " << input_settings.references().size()
                             << " paths to reference models.";

    for (const auto ref : input_settings.references()) {
        BOOST_LOG_SEV(lg, debug) << "Reference model: "
                                 << ref.path().filename();
        frontend::input_descriptor id;
        id.path(ref.path());
        id.external_module_path(ref.external_module_path());
        id.is_target(false);
        r.push_back(id);
    }
    BOOST_LOG_SEV(lg, debug) << "Done creating paths to reference models.";

    BOOST_LOG_SEV(lg, debug) << "Added target model: "
                             << input_settings.target().filename();
    frontend::input_descriptor target;
    target.path(input_settings.target());
    target.is_target(true);
    target.external_module_path(input_settings.external_module_path());
    r.push_back(target);
    return r;
}

std::list<sml::model> workflow::obtain_partial_sml_models_activity(
    const std::list<frontend::input_descriptor>& descriptors) const {
    frontend::workflow w(knitting_settings_);
    return w.execute(descriptors);
}

boost::filesystem::path workflow::obtain_target_path_activity(
    const std::list<frontend::input_descriptor>& descriptors) const {
    frontend::input_descriptor target_descriptor;
    for (const auto& d : descriptors) {
        if (!d.is_target())
            continue;

        return d.path();
    }
    return boost::filesystem::path();
}

std::pair<bool, sml::model> workflow::
merge_models_activity(const std::list<sml::model>& models) const {
    sml::workflow w(knitting_settings_);
    const auto pair(w.execute(models));
    const auto& m(pair.second);

    BOOST_LOG_SEV(lg, debug) << "Merged model: " << m;
    BOOST_LOG_SEV(lg, debug) << "Totals: objects: " << m.objects().size()
                             << " modules: " << m.modules().size()
                             << " concepts: " << m.concepts().size()
                             << " enumerations: " << m.enumerations().size()
                             << " primitives: " << m.primitives().size();

    return pair;
}

void workflow::persist_model_activity(const boost::filesystem::path p,
    const sml::model& m) const {

    const auto& ts(knitting_settings_.troubleshooting());
    using config::archive_types;
    archive_types at(ts.save_sml_model());
    if (at == archive_types::invalid)
        return;

    const auto& dp(create_debug_file_path(at, p));
    sml::persister persister;
    persister.persist(m, dp);
}

config::formatting_settings workflow::
extract_formatting_settings_activity(const sml::model&) const {
    config::formatting_settings r;
    r.cpp(knitting_settings_.cpp());
    return r;
}

void workflow::generate_model_activity(
    const sml::model& m, const config::formatting_settings& fs) const {
    try {
        backends::factory f(m, fs);
        boost::for_each(f.create(), [&](backends::backend::ptr p) {
                create_files_for_backend(*p);
            });
    } catch(const dogen::cpp_formatters::formatting_error& e) {
        BOOST_THROW_EXCEPTION(dogen::knit::generation_failure(e.what()));
    } catch(const dogen::sml_to_cpp::workflow_failure& e) {
        BOOST_THROW_EXCEPTION(dogen::knit::generation_failure(e.what()));
    }
}

void workflow::execute() const {
    BOOST_LOG_SEV(lg, info) << "Workflow started.";
    BOOST_LOG_SEV(lg, debug) << "Knitting settings: " << knitting_settings_;

    try {
        const auto d(obtain_input_descriptors_activity());
        const auto tp(obtain_target_path_activity(d));
        const auto pm(obtain_partial_sml_models_activity(d));
        const auto pair(merge_models_activity(pm));
        const auto& m(pair.second);
        const auto has_generatable_types(pair.first);
        persist_model_activity(tp, m);

        if (knitting_settings_.troubleshooting().stop_after_merging()) {
            BOOST_LOG_SEV(lg, info) << "Stopping after merging.";
            return;
        }

        if (!has_generatable_types) {
            BOOST_LOG_SEV(lg, warn) << "No generatable types found.";
            return;
        }

        auto fs(extract_formatting_settings_activity(m));
        generate_model_activity(m, fs);
    } catch (boost::exception& e) {
        e << errmsg_workflow(code_generation_failure);
        throw;
    }
    BOOST_LOG_SEV(lg, info) << "Workflow finished.";
}

} }
