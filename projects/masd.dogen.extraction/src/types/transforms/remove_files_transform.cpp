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
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.utility/types/filesystem/file.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.extraction/io/meta_model/model_io.hpp"
#include "masd.dogen.extraction/types/transforms/remove_files_transform.hpp"

namespace {

const std::string transform_id("extraction.transforms.remove_files_transform");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace masd::dogen::extraction::transforms {

void remove_files_transform::
apply(const context& ctx, const meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg,
        "remove files transform", transform_id, m.name(), *ctx.tracer());

    /*
     * If we don't have any artefacts then we're done.
     */
    if (m.artefacts().empty()) {
        BOOST_LOG_SEV(lg, info) << "No artefacts were generated.";
        return;
    }

    /*
     * If the user requested a dry run, we cannot execute.
     */
    if (ctx.dry_run_mode_enabled()) {
        BOOST_LOG_SEV(lg, info) << "Dry run mode is enabled, not executing.";
        return;
    }

    /*
     * Collect all the files to remove across the model.
     */
    std::list<boost::filesystem::path> unexpected;
    for (const auto& a : m.artefacts()) {
        using extraction::meta_model::operation_type;
        if (a.operation().type() == operation_type::remove)
            unexpected.push_back(a.path());
    }

    /**
     * @brief If no files were found, we're done. Note that we don't
     * bother removing empty directories if we did not remove any
     * files.
     */
    if (unexpected.empty()) {
        BOOST_LOG_SEV(lg, debug) << "No files found to remove.";
        return;
    }

    /**
     * @brief Remove all unwanted files.
     */
    BOOST_LOG_SEV(lg, debug) << "Starting to remove files.";
    utility::filesystem::remove(unexpected);
    BOOST_LOG_SEV(lg, debug) << "Removed files.";

    /**
     * @brief If requested by the user, get rid of any empty
     * directories caused by the file removal. Note that this is
     * implemented in a bit of an optimistic way:
     *
     * - we can remove empty directories created by the user that are
     *   not related to code generation.
     *
     * - we are not honouring ignore regexes. We probably should not
     *   remove a directory if it matches a ignore regex.
     *
     * For now this approach is good enough.
     */
    if (m.outputting_properties().delete_empty_directories()) {
        BOOST_LOG_SEV(lg, debug) << "Starting to remove empty directories.";
        utility::filesystem::remove_empty_directories(m.managed_directories());
        BOOST_LOG_SEV(lg, debug) << "Removed empty directories.";
    }
}

}
