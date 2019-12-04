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
#include "dogen.extraction/io/meta_model/model_io.hpp"
#include "dogen.extraction/io/meta_model/operation_type_io.hpp"
#include "dogen.extraction/types/transforms/write_artefacts_transform.hpp"

namespace {

const std::string transform_id(
    "extraction.transforms.write_artefacts_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string using_dir_message("Using directory: ");
const std::string created_dir_message("Created directory: ");

}

namespace dogen::extraction::transforms {

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
apply(const context& ctx, const meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg, "writting transform",
        transform_id, m.name(), *ctx.tracer(), m);

    /*
     * If we don't have any artefacts then we're done.
     */
    if (m.artefacts().empty()) {
        BOOST_LOG_SEV(lg, warn) << "No artefacts were generated.";
        return;
    }

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
    for (const auto& a : m.artefacts()) {
        const auto gs(a.path().generic_string());
        BOOST_LOG_SEV(lg, trace) << "Processing file: " << gs;

        if (a.path().empty()) {
            // FIXME: throw
            BOOST_LOG_SEV(lg, error) << "Empty file name supplied.";
            continue;
        }

        using extraction::meta_model::operation_type;
        const auto ot(a.operation().type());
        if (ot != operation_type::write) {
            BOOST_LOG_SEV(lg, trace) << "Ignoring operation: " << ot;
            continue;
        }

        ++files_written;
        BOOST_LOG_SEV(lg, trace) << "Writing file.";
        create_directories(a.path());
        using dogen::utility::filesystem::write_file_content;
        write_file_content(a.path(), a.content());
    }

    BOOST_LOG_SEV(lg, info) << "Total files written: " << files_written;

    stp.end_transform(m);
}

}
