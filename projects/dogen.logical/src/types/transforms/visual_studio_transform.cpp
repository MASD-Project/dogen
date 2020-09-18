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
#include <sstream>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/throw_exception.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/algorithm/string/join.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.identification/types/helpers/logical_name_flattener.hpp"
#include "dogen.identification/io/entities/technical_space_io.hpp"
#include "dogen.identification/lexical_cast/entities/technical_space_lc.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.logical/types/transforms/context.hpp"
#include "dogen.logical/types/transforms/transformation_error.hpp"
#include "dogen.logical/types/entities/visual_studio/project.hpp"
#include "dogen.logical/types/entities/visual_studio/solution.hpp"
#include "dogen.logical/types/transforms/visual_studio_transform.hpp"

namespace {

const std::string transform_id("logical.transforms.visual_studio_transform");
using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string dot(".");

const std::string too_many_projects(
    "Expected at most one Visual Studio project per model. Found: ");
const std::string too_many_solutions(
    "Expected at most one Visual Studio solution per model. Found: ");

}

namespace dogen::logical::transforms {

std::string visual_studio_transform::
project_name(const identification::entities::logical_name& n) {
    using identification::helpers::logical_name_flattener;
    logical_name_flattener nfl(false/*detect_model_name*/);
    const auto ns(nfl.flatten(n));
    const auto r(boost::algorithm::join(ns, dot));
    return r;
}

void visual_studio_transform::
apply(const context& ctx, const logical::entities::model& m) {
    const auto id(m.name().id());
    tracing::scoped_transform_tracer stp(lg, "visual studio",
        transform_id, id.value(), *ctx.tracer(), m);

    /*
     * We expect to have zero or one projects on a model.
     */
    const auto num_projs(m.visual_studio_elements().projects().size());
    if (num_projs > 1) {
        BOOST_LOG_SEV(lg, error) << too_many_projects << num_projs;
        BOOST_THROW_EXCEPTION(transformation_error(too_many_projects +
                std::to_string(num_projs)));
    }

    /*
     * We expect to have zero or one solutions on a model.
     */
    const auto num_slns(m.visual_studio_elements().solutions().size());
    if (num_slns > 1) {
        BOOST_LOG_SEV(lg, error) << too_many_solutions << num_slns;
        BOOST_THROW_EXCEPTION(transformation_error(too_many_solutions +
                std::to_string(num_slns)));
    }

    /*
     * Compute project guids, if none were supplied. Note that if the
     * user does not supply the guid, it will keep changing for each
     * generation. This is nonetheless useful for the first generation
     * so that we do not have to come up with a guid manually.
     */
    using entities::visual_studio::project_persistence_block;
    std::list<project_persistence_block> ppbs;
    for (auto& pair : m.visual_studio_elements().projects()) {
        auto& proj(*pair.second);
        /*
         * Populate the project properties. Note that we do not
         * compute the project type guid here because we do not know
         * the final technical space for the model (it may change
         * after mapping).
         */
        proj.project_name(project_name(proj.name()));

        if (proj.guid().empty()) {
            BOOST_LOG_SEV(lg, warn) << "User did not supply project GUID.";
            const auto uuid = boost::uuids::random_generator()();
            BOOST_LOG_SEV(lg, warn) << "Generated project GUID: " << uuid;
            proj.guid(boost::uuids::to_string(uuid));
        }

        /*
         * Create the project persistence block for this project.
         */
        project_persistence_block ppb;
        ppb.guid(proj.guid());
        ppb.name(project_name(proj.name()));
        ppbs.push_back(ppb);
    }

    /*
     * As with projects, we also need to compute the solution guids if
     * none were supplied. We also need to link the project guids to
     * the solution.
     */
    for (auto& pair : m.visual_studio_elements().solutions()) {
        auto& sln(*pair.second);
        if (sln.guid().empty()) {
            BOOST_LOG_SEV(lg, warn) << "User did not supply solution GUID.";
            const auto uuid = boost::uuids::random_generator()();
            BOOST_LOG_SEV(lg, warn) << "Generated solution GUID: " << uuid;
            sln.guid(boost::uuids::to_string(uuid));
        }
        sln.project_persistence_blocks(ppbs);
    }

    stp.end_transform(m);
}

}
