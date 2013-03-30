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
#include "dogen/config/types/validator.hpp"
#include "dogen/config/io/settings_io.hpp"
#include "dogen/cpp/types/generation_failure.hpp"
#include "dogen/engine/types/housekeeper.hpp"
#include "dogen/engine/types/generation_failure.hpp"
#include "dogen/engine/types/outputters/factory.hpp"
#include "dogen/sml/serialization/model_ser.hpp"
#include "dogen/engine/types/backends/factory.hpp"
#include "dogen/sml/types/workflow.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/engine/types/model_source.hpp"
#include "dogen/engine/types/persister.hpp"
#include "dogen/engine/types/workflow.hpp"

using namespace dogen::utility::log;

typedef boost::error_info<struct tag_workflow, std::string> errmsg_workflow;

namespace {

auto lg(logger_factory("engine.workflow"));

const std::string merged("merged_");
const std::string codegen_error("Error occurred during code generation: ");
const std::string incorrect_stdout_config(
    "Configuration for output to stdout is incorrect");
const std::string code_generation_failure("Code generation failure.");

}

namespace dogen {
namespace engine {

workflow::workflow(const config::settings& s)
    : verbose_(s.troubleshooting().verbose()), settings_(s) {

    if (settings_.output().output_to_stdout()) {
        BOOST_LOG_SEV(lg, error) << incorrect_stdout_config;
        BOOST_THROW_EXCEPTION(generation_failure(incorrect_stdout_config));
    }

    config::validator::validate(s);
}

workflow::
workflow(const config::settings& s, const output_fn& o)
    : verbose_(s.troubleshooting().verbose()), settings_(s), output_(o) {

    if (!settings_.output().output_to_stdout() || !output_) {
        BOOST_LOG_SEV(lg, error) << incorrect_stdout_config;
        BOOST_THROW_EXCEPTION(generation_failure(incorrect_stdout_config));
    }

    config::validator::validate(s);
}

bool workflow::housekeeping_required() const {
    return
        !settings_.troubleshooting().stop_after_merging() &&
        !settings_.troubleshooting().stop_after_formatting() &&
        settings_.output().delete_extra_files() &&
        settings_.output().output_to_file();
}

void workflow::output(const outputters::outputter::value_type& o) const {
    if (settings_.troubleshooting().stop_after_formatting()) {
        BOOST_LOG_SEV(lg, warn) << "Stopping after formatting so not outputting";
        return;
    }

    if (o.empty()) {
        BOOST_LOG_SEV(lg, warn) << "No files were generated, nothing to output.";

        return;
    }

    const auto lambda([&](outputters::outputter::ptr p) { p->output(o); });
    outputters::factory f(settings_.output(), output_);
    boost::for_each(f.create(), lambda);
}

void workflow::generate(backends::backend& b) const {
    const auto r(b.generate());
    output(r);

    if (!housekeeping_required())
        return;

    using boost::adaptors::transformed;
    using boost::filesystem::path;
    std::set<path> expected_files;
    boost::copy(r | transformed([&](std::pair<path, std::string> p) {
                return p.first;
            }),
        std::inserter(expected_files, expected_files.end()));

    housekeeper hk(settings_.output().ignore_patterns(),
        b.managed_directories(), expected_files, verbose_);
    hk.tidy_up();
}

void workflow::generate(const sml::model& m) const {
    try {
        const auto lambda([&](backends::backend::ptr p) { generate(*p); });
        backends::factory f(m, settings_);
        boost::for_each(f.create(), lambda);
    } catch(const dogen::cpp::generation_failure& e) {
        BOOST_THROW_EXCEPTION(dogen::engine::generation_failure(e.what()));
    }
}

boost::optional<sml::model> workflow::make_generatable_model() const {
    const bool add_system_models(true);
    const bool add_versioning_types(!settings_.cpp().disable_versioning());
    sml::workflow w(add_system_models, add_versioning_types);

    model_source source(settings_);
    const auto pair(w.execute(source));
    const auto& m(pair.second);

    BOOST_LOG_SEV(lg, debug) << "Merged model: " << m;
    persister p(settings_);
    p.persist(m, merged);

    BOOST_LOG_SEV(lg, debug) << "Totals: pods: " << m.pods().size()
                             << " enumerations: " << m.enumerations().size()
                             << " exceptions: " << m.exceptions().size()
                             << " primitives: " << m.primitives().size();

    const auto has_generatable_types(pair.first);
    if ((has_generatable_types))
        return boost::optional<sml::model>(m);

    BOOST_LOG_SEV(lg, warn) << "No generatable types found.";
    return boost::optional<sml::model>();
}

void workflow::execute() const {
    BOOST_LOG_SEV(lg, info) << "Workflow started.";
    BOOST_LOG_SEV(lg, debug) << "Settings: " << settings_;

    try {
        const auto o(make_generatable_model());
        if (settings_.troubleshooting().stop_after_merging()) {
            BOOST_LOG_SEV(lg, info) << "Stopping after merging.";
            return;
        }

        if (o)
            generate(*o);
    } catch (boost::exception& e) {
        e << errmsg_workflow(code_generation_failure);
        throw;
    }
    BOOST_LOG_SEV(lg, info) << "Workflow finished.";
}

} }
