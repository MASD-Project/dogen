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
#include <boost/filesystem.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/knit/types/housekeeper.hpp"
#include "dogen/knit/types/outputters/factory.hpp"
#include "dogen/knit/types/backends/factory.hpp"
#include "dogen/knit/types/middle_end_to_backend_workflow.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("knit.middle_end_to_backend_workflow"));

}

namespace dogen {
namespace knit {

middle_end_to_backend_workflow::
middle_end_to_backend_workflow(const config::knitting_options& o,
    const dynamic::schema::repository& rp, const output_fn& of)
    : knitting_options_(o), repository_(rp), output_(of) {}

bool middle_end_to_backend_workflow::housekeeping_required() const {
    return
        !knitting_options_.troubleshooting().stop_after_merging() &&
        !knitting_options_.troubleshooting().stop_after_formatting() &&
        knitting_options_.output().delete_extra_files() &&
        knitting_options_.output().output_to_file();
}

void middle_end_to_backend_workflow::
perform_housekeeping_activity(
    const std::forward_list<formatters::file>& files,
    const std::forward_list<boost::filesystem::path>& dirs) const {

    if (!housekeeping_required())
        return;

    std::set<boost::filesystem::path> expected_files;
    for (const auto file : files)
        expected_files.insert(file.path().generic_string());

    const auto& ip(knitting_options_.output().ignore_patterns());
    std::forward_list<std::string> ignore_patterns(ip.begin(), ip.end());
    housekeeper hk(ignore_patterns, dirs, expected_files);
    hk.tidy_up();
}

void middle_end_to_backend_workflow::output_files_activity(
    const std::forward_list<formatters::file>& files) const {
    if (knitting_options_.troubleshooting().stop_after_formatting()) {
        BOOST_LOG_SEV(lg, warn) << "Stopping after formatting, so no output.";
        return;
    }

    if (files.empty()) {
        BOOST_LOG_SEV(lg, warn) << "No files were generated, so no output.";
        return;
    }

    outputters::factory f(knitting_options_.output(), output_);
    for (const auto outputter : f.make())
        outputter->output(files);
}

void middle_end_to_backend_workflow::execute(const sml::model& m) const {
    backends::factory f(knitting_options_);
    for (const auto b : f.make()) {
        const auto files(b->generate(knitting_options_, repository_, m));
        output_files_activity(files);

        const auto md(b->managed_directories(knitting_options_, m));
        perform_housekeeping_activity(files, md);
    }
}

} }
