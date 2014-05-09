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
#include "dogen/utility/exception/invalid_enum_value.hpp"
#include "dogen/utility/serialization/xml_helper.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/config/types/knitting_settings_validator.hpp"
#include "dogen/config/io/knitting_settings_io.hpp"
#include "dogen/knit/types/housekeeper.hpp"
#include "dogen/knit/types/generation_failure.hpp"
#include "dogen/sml_to_cpp/types/workflow_failure.hpp"
#include "dogen/cpp_formatters/types/formatting_error.hpp" // FIXME
#include "dogen/knit/types/outputters/factory.hpp"
#include "dogen/sml/serialization/model_ser.hpp"
#include "dogen/knit/types/backends/factory.hpp"
#include "dogen/sml/types/workflow.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/knit/types/provider.hpp"
#include "dogen/knit/types/persister.hpp"
#include "dogen/knit/types/workflow.hpp"

using namespace dogen::utility::log;

typedef boost::error_info<struct tag_workflow, std::string> errmsg_workflow;

namespace {

auto lg(logger_factory("knit.workflow"));

const std::string merged("merged_");
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

bool workflow::
is_generation_required(const boost::optional<sml::model>& m) const {
    if (knitting_settings_.troubleshooting().stop_after_merging()) {
        BOOST_LOG_SEV(lg, info) << "Stopping after merging.";
        return false;
    }

    if (!m)
        return false;

    return true;
}

boost::optional<sml::model> workflow::obtain_model_activity() const {
    const bool is_target(true);
    provider pro(knitting_settings_);
    std::list<sml::model> references;
    for (const auto ref : knitting_settings_.input().references()) {
        const auto path(ref.path());
        const auto epp(ref.external_module_path());
        references.push_back(pro.provide(path, epp, !is_target));
    }

    const auto path(knitting_settings_.input().target());
    const auto epp(knitting_settings_.input().external_module_path());
    const sml::model target(pro.provide(path, epp, is_target));

    const bool add_system_models(true);
    sml::workflow w(add_system_models, knitting_settings_);
    const auto pair(w.execute(target, references));
    const auto& m(pair.second);

    BOOST_LOG_SEV(lg, debug) << "Merged model: " << m;
    persister per(knitting_settings_);
    per.persist(m, merged);

    BOOST_LOG_SEV(lg, debug) << "Totals: objects: " << m.objects().size()
                             << " modules: " << m.modules().size()
                             << " enumerations: " << m.enumerations().size()
                             << " primitives: " << m.primitives().size();

    const auto has_generatable_types(pair.first);
    if ((has_generatable_types))
        return boost::optional<sml::model>(m);

    BOOST_LOG_SEV(lg, warn) << "No generatable types found.";
    return boost::optional<sml::model>();
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
        const auto m(obtain_model_activity());
        if (!is_generation_required(m))
            return;

        auto fs(extract_formatting_settings_activity(*m));
        generate_model_activity(*m, fs);
    } catch (boost::exception& e) {
        e << errmsg_workflow(code_generation_failure);
        throw;
    }
    BOOST_LOG_SEV(lg, info) << "Workflow finished.";
}

} }
