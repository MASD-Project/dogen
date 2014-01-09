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
#include "dogen/engine/types/housekeeper.hpp"
#include "dogen/engine/types/generation_failure.hpp"
#include "dogen/sml_to_cpp/types/workflow_failure.hpp"
#include "dogen/cpp_formatters/types/formatting_error.hpp" // FIXME
#include "dogen/engine/types/outputters/factory.hpp"
#include "dogen/sml/serialization/model_ser.hpp"
#include "dogen/engine/types/backends/factory.hpp"
#include "dogen/sml/types/workflow.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/engine/types/provider.hpp"
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
    : verbose_(s.troubleshooting().verbose()), settings_(s), enable_om_(false),
      legacy_mode_(false) {

    if (settings_.output().output_to_stdout()) {
        BOOST_LOG_SEV(lg, error) << incorrect_stdout_config;
        BOOST_THROW_EXCEPTION(generation_failure(incorrect_stdout_config));
    }

    config::validator::validate(s);
}

workflow::
workflow(const config::settings& s, const output_fn& o)
    : verbose_(s.troubleshooting().verbose()), settings_(s), output_(o),
      enable_om_(false), legacy_mode_(false) {

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

void workflow::generate(const sml::model& m) const {
    try {
        backends::factory f(m, settings_, enable_om_, legacy_mode_);
        const auto backends(f.create());
        if (backends.empty())
            return;

        backends::backend::value_type r;
        std::vector<boost::filesystem::path> managed_directories;
        if (!enable_om_) {
            if (backends.size() != 1) {
                BOOST_LOG_SEV(lg, error) << "expected only one backend but got "
                                         << backends.size();

                BOOST_THROW_EXCEPTION(generation_failure(
                        "Unexpected number of backends"));
            }
            r = backends.front()->generate();
            managed_directories = backends.front()->managed_directories();
        } else {
            if (backends.size() != 2) {
                BOOST_LOG_SEV(lg, error) << "expected two backends but got "
                                         << backends.size();

                BOOST_THROW_EXCEPTION(generation_failure(
                        "Unexpected number of backends"));
            }

            auto legacy(backends.front()->generate());
            r = backends.back()->generate();
            r.insert(legacy.begin(), legacy.end());
            managed_directories = backends.back()->managed_directories();
        }

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
            managed_directories, expected_files, verbose_);
        hk.tidy_up();

    } catch(const dogen::cpp_formatters::formatting_error& e) {
        BOOST_THROW_EXCEPTION(dogen::engine::generation_failure(e.what()));
    } catch(const dogen::sml_to_cpp::workflow_failure& e) {
        BOOST_THROW_EXCEPTION(dogen::engine::generation_failure(e.what()));
    }
}

boost::optional<sml::model> workflow::make_generatable_model() const {
    bool is_target(false);
    provider pro(settings_);
    std::list<sml::model> references;
    for (const auto ref : settings_.modeling().references()) {
        const auto path(ref.path());
        const auto epp(ref.external_module_path());
        references.push_back(pro.provide(path, epp, is_target));
    }

    is_target = true;
    const auto path(settings_.modeling().target());
    const auto epp(settings_.modeling().external_module_path());
    const sml::model target(pro.provide(path, epp, is_target));

    const bool add_system_models(true);
    sml::workflow w(add_system_models, settings_);
    const auto pair(w.execute(target, references));
    const auto& m(pair.second);

    BOOST_LOG_SEV(lg, debug) << "Merged model: " << m;
    persister per(settings_);
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

void workflow::enable_om(const bool v) {
    enable_om_= v;
}

void workflow::legacy_mode(const bool v) {
    legacy_mode_= v;
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
