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
#include <boost/filesystem.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/filesystem/file.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.physical/io/entities/model_io.hpp"
#include "dogen.physical/io/entities/operation_type_io.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.physical/types/transforms/transform_exception.hpp"
#include "dogen.physical/types/transforms/write_artefacts_transform.hpp"

namespace {

const std::string transform_id(
    "physical.transforms.write_artefacts_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string using_dir_message("Using directory: ");
const std::string created_dir_message("Created directory: ");
const std::string empty_file_name("Empty file name supplied.");

}

namespace dogen::physical::transforms {

void write_artefacts_transform::create_directories(
    const boost::filesystem::path& file_path) {
    const auto dir(file_path.parent_path());
    if (dir.empty() || dir.generic_string() == "/")
        return;

    using boost::filesystem::create_directories;
    const bool created(create_directories(dir));
    BOOST_LOG_SEV(lg, trace) << (created ? created_dir_message :
        using_dir_message) << dir.generic_string();
}

void write_artefacts_transform::
apply(const context& ctx, const entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "writting transform",
        transform_id, m.name().simple(), *ctx.tracer(), m);

    /*
     * If the user requested a dry run, we cannot execute.
     */
    if (ctx.dry_run_mode_enabled()) {
        BOOST_LOG_SEV(lg, warn) << "Dry run mode is enabled, not executing.";
        return;
    }

    /*
     * Write each artefact that has been marked with a "write"
     * operation to the filesystem. Ignore all other artefacts.
     */
    unsigned int files_written(0);
    for (auto& as_pair : m.artefact_sets_by_logical_id()) {
        auto& as(as_pair.second);
        for (auto& a_pair : as.artefacts_by_archetype()) {
            auto& a(*a_pair.second);
            const auto p(a.name().qualified());
            const auto gs(p.generic_string());
            BOOST_LOG_SEV(lg, trace) << "Processing file: " << p;

            if (gs.empty()) {
                BOOST_LOG_SEV(lg, error) << empty_file_name;
                BOOST_THROW_EXCEPTION(transform_exception(empty_file_name));
            }

            using physical::entities::operation_type;
            const auto ot(a.operation().type());
            if (ot != operation_type::write) {
                BOOST_LOG_SEV(lg, trace) << "Ignoring operation: " << ot;
                continue;
            }

            ++files_written;
            BOOST_LOG_SEV(lg, trace) << "Writing file.";
            create_directories(p);
            using dogen::utility::filesystem::write_file_content;
            write_file_content(p, a.content());
        }
    }

    BOOST_LOG_SEV(lg, info) << "Total files written: " << files_written;

    stp.end_transform(m);
}

}
