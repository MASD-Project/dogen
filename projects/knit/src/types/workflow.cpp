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
#include "dogen/dynamic/schema/types/repository_workflow.hpp"
#include "dogen/config/types/knitting_options_validator.hpp"
#include "dogen/config/io/knitting_options_io.hpp"
#include "dogen/knit/types/housekeeper.hpp"
#include "dogen/knit/types/generation_failure.hpp"
#include "dogen/knit/types/outputters/factory.hpp"
#include "dogen/knit/types/backends/factory.hpp"
#include "dogen/sml_to_cpp/types/workflow_failure.hpp"
#include "dogen/cpp_formatters/types/formatting_error.hpp" // FIXME
#include "dogen/knit/types/frontend_to_middle_end_workflow.hpp"
#include "dogen/backend/types/workflow.hpp"
#include "dogen/knit/types/workflow.hpp"

using namespace dogen::utility::log;

typedef boost::error_info<struct tag_workflow, std::string> errmsg_workflow;

namespace {

auto lg(logger_factory("knit.workflow"));

const std::string fields_dir("fields");
const std::string codegen_error("Error occurred during code generation: ");
const std::string incorrect_stdout_config(
    "Configuration for output to stdout is incorrect");
const std::string code_generation_failure("Code generation failure.");

}

namespace dogen {
namespace knit {

workflow::workflow(workflow&& rhs)
    : knitting_options_(std::move(rhs.knitting_options_)) { }

workflow::
workflow(const config::knitting_options& o) : knitting_options_(o) {

    if (knitting_options_.output().output_to_stdout()) {
        BOOST_LOG_SEV(lg, error) << incorrect_stdout_config;
        BOOST_THROW_EXCEPTION(generation_failure(incorrect_stdout_config));
    }
    config::knitting_options_validator::validate(knitting_options_);
}

workflow::workflow(const config::knitting_options& o, const output_fn& fn)
    : knitting_options_(o), output_(fn) {

    if (!knitting_options_.output().output_to_stdout() || !output_) {
        BOOST_LOG_SEV(lg, error) << incorrect_stdout_config;
        BOOST_THROW_EXCEPTION(generation_failure(incorrect_stdout_config));
    }
    config::knitting_options_validator::validate(knitting_options_);
}

bool workflow::housekeeping_required() const {
    return
        !knitting_options_.troubleshooting().stop_after_merging() &&
        !knitting_options_.troubleshooting().stop_after_formatting() &&
        knitting_options_.output().delete_extra_files() &&
        knitting_options_.output().output_to_file();
}

void workflow::
housekeep(const std::map<boost::filesystem::path, std::string>& files,
    const std::forward_list<boost::filesystem::path>& dirs) const {
    using boost::adaptors::transformed;
    using boost::filesystem::path;
    std::set<path> expected_files;
    boost::copy(files | transformed([&](std::pair<path, std::string> p) {
                return p.first;
            }),
        std::inserter(expected_files, expected_files.end()));

    const auto& ip(knitting_options_.output().ignore_patterns());
    std::forward_list<std::string> ignore_patterns(ip.begin(), ip.end());
    housekeeper hk(ignore_patterns, dirs, expected_files);
    hk.tidy_up();
}

void workflow::output_files(const outputters::outputter::value_type& o) const {
    if (knitting_options_.troubleshooting().stop_after_formatting()) {
        BOOST_LOG_SEV(lg, warn) << "Stopping after formatting, so no output.";
        return;
    }

    if (o.empty()) {
        BOOST_LOG_SEV(lg, warn) << "No files were generated, so no output.";
        return;
    }

    const auto lambda([&](outputters::outputter::ptr p) { p->output(o); });
    outputters::factory f(knitting_options_.output(), output_);
    boost::for_each(f.create(), lambda);
}

void workflow::create_files_for_backend(backends::backend& b) const {
    const auto files(b.generate());
    output_files(files);

    if (!housekeeping_required())
        return;

    housekeep(files, b.managed_directories());
}

std::forward_list<dynamic::schema::ownership_hierarchy> workflow::
obtain_ownership_hierarchy_activity() const {
    const auto rg(backend::workflow::registrar());
    std::forward_list<dynamic::schema::ownership_hierarchy> r;
    for (const auto b : rg.backends())
        r.splice_after(r.before_begin(), b->ownership_hierarchy());

    return r;
}

dynamic::schema::repository workflow::setup_schema_repository_activity(
    const std::forward_list<dynamic::schema::ownership_hierarchy>& oh) const {
    using namespace dogen::utility::filesystem;
    const auto dir(data_files_directory() / fields_dir);
    dynamic::schema::repository_workflow w;
    return w.execute(oh, std::forward_list<boost::filesystem::path> { dir });
}

void workflow::generate_model_activity(const dynamic::schema::repository& rp,
    const sml::model& m) const {
    try {
        backends::factory f(knitting_options_, rp, m);
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
    BOOST_LOG_SEV(lg, debug) << "Knitting options: " << knitting_options_;

    try {
        const auto oh(obtain_ownership_hierarchy_activity());
        const auto rp(setup_schema_repository_activity(oh));

        frontend_to_middle_end_workflow fmw(knitting_options_, rp);
        const auto m(fmw.execute());

        if (knitting_options_.troubleshooting().stop_after_merging()) {
            BOOST_LOG_SEV(lg, info) << "Stopping after merging.";
            return;
        }

        if (!m.has_generatable_types()) {
            BOOST_LOG_SEV(lg, warn) << "No generatable types found.";
            return;
        }

        generate_model_activity(rp, m);
    } catch (boost::exception& e) {
        e << errmsg_workflow(code_generation_failure);
        throw;
    }
    BOOST_LOG_SEV(lg, info) << "Workflow finished.";
}

} }
