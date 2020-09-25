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
#include "dogen.physical/io/entities/model_io.hpp"
#include "dogen.physical/types/transforms/paths_transform.hpp"

namespace {

const std::string transform_id("physical.transforms.paths_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string dot(".");

const std::string backend_directories_not_enabled(
    "More than one backend is enabled but backend directories are not.");

const std::string missing_backend_directory(
    "Enable backend directory is on but backend directory is empty.");

}

namespace dogen::physical::transforms {

boost::filesystem::path paths_transform::
compute_project_path(const boost::filesystem::path& output_directory,
    const identification::entities::logical_name& ln) {
    /*
     * The component path is defined as the directory chosen by the
     * user for the output plus the model name, separated by dots.
     */
    boost::filesystem::path r(output_directory);
    const auto& mm(ln.location().model_modules());
    r /= boost::algorithm::join(mm, dot);
    return r;
}

void paths_transform::
compute_backend_paths(const boost::filesystem::path& project_path,
    std::unordered_map<identification::entities::physical_meta_id,
    physical::entities::backend_properties>& bps) {

    /*
     * Populate the backend path for each configured backend.
     */
    for (auto& pair : bps) {
        const auto& id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Processing backend: " << id;

        /*
         * There are two possibilities: either the backend directory
         * is the same as the component directory - in the case of a
         * component that only has a single backend, unless the user
         * said otherwise; or the backend directory is a child of the
         * component directory, using the directory name from the
         * backend properties. This is commonly the case for
         * components with more than one backend.
         */
        auto& bp(pair.second);
        BOOST_LOG_SEV(lg, trace) << "Enable backend directories: "
                                 << bp.enable_backend_directories();

        /*
         * If the backend directories are not enabled, then we can
         * just take the component path and go on our merry way.
         */
        if (!bp.enable_backend_directories()) {
            bp.file_path(project_path);
            continue;
        }

        /*
         * Since the backend directories have been enabled, we expect
         * a directory name to have been supplied.
         */
        if (bp.directory_name().empty()) {
            BOOST_LOG_SEV(lg, error) << missing_backend_directory;
            BOOST_THROW_EXCEPTION(
                transform_exception(missing_backend_directory));
        }

        bp.file_path(project_path / bp.directory_name());
    }
}

void paths_transform::apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "paths",
        transform_id, m.name().id().value(), *ctx.tracer(), m);

    /*
     * We start by calculating the top-most path which is the
     * project path. All other paths will depend on this path.
     */
    const auto& ln(m.provenance().logical_name());
    const auto pp(compute_project_path(ctx.output_directory_path(), ln));
    auto& mmp(m.meta_model_properties());
    mmp.file_path(pp);

    /*
     * Calculate the backend paths.
     */
    compute_backend_paths(pp, mmp.backend_properties());




    stp.end_transform(m);
}

}
