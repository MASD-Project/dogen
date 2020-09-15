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
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/join.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.physical/types/transforms/transform_exception.hpp"
#include "dogen.identification/io/entities/physical_meta_id_io.hpp"
#include "dogen.physical/io/entities/artefact_repository_io.hpp"
#include "dogen.physical/types/transforms/paths_transform.hpp"

namespace {

const std::string transform_id("physical.transforms.enablement_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string dot(".");

const std::string backend_directories_not_enabled(
    "More than one backend is enabled but backend directories are not.");

const std::string missing_backend_directory(
    "Enable backend directory is on but backend directory is empty.");

}

namespace dogen::physical::transforms {

boost::filesystem::path
paths_transform::compute_component_path(const context& ctx,
    const identification::entities::logical_name& ln) {
    boost::filesystem::path r(ctx.output_directory_path());
    const auto& mm(ln.location().model_modules());
    r /= boost::algorithm::join(mm, dot);
    return r;
}

void paths_transform::
compute_backend_paths(const boost::filesystem::path& component_path,
    std::unordered_map<identification::entities::physical_meta_id,
    physical::entities::backend_properties>& bps) {

    /*
     * Populate the backend path for each configured backend.
     */
    const bool backend_directories_should_be_enabled(bps.size() > 1);
    for (auto& pair : bps) {
        const auto& id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Processing backend: " << id;

        /*
         * If the backend directories are not enabled and we did not
         * expect they should have been, then we can just take the
         * component path and go on our merry way.
         */
        auto& bp(pair.second);
        if (!bp.enable_backend_directories() &&
            !backend_directories_should_be_enabled) {
            bp.file_path(component_path);
            continue;
        }

        /*
         * If the backend directories should have been enabled but
         * weren't, we need to throw.
         */
        if (!bp.enable_backend_directories() &&
            backend_directories_should_be_enabled)  {
            BOOST_LOG_SEV(lg, error) << backend_directories_not_enabled;
            BOOST_THROW_EXCEPTION(
                transform_exception(backend_directories_not_enabled));
        }

        /*
         * Since the backend directories have been enabled, we expect
         * a directory name to have been supplied.
         */
        if (bp.directory().empty()) {
            BOOST_LOG_SEV(lg, error) << missing_backend_directory;
            BOOST_THROW_EXCEPTION(
                transform_exception(missing_backend_directory));
        }

        bp.file_path(component_path / bp.directory());
    }
}

void paths_transform::
apply(const context& ctx, entities::artefact_repository& arp) {
    tracing::scoped_transform_tracer stp(lg, "paths",
        transform_id, arp.provenance().logical_name().id().value(),
        *ctx.tracer(), arp);

    /*
     * We start by calculating the top-most path which is the
     * component path.
     */
    const auto& ln(arp.provenance().logical_name());
    auto& mmp(arp.meta_model_properties());
    const auto cp(compute_component_path(ctx, ln));
    mmp.file_path(cp);

    /*
     * Now calculate the backend paths.
     */
    compute_backend_paths(cp, mmp.backend_properties());

    stp.end_transform(arp);
}

}
