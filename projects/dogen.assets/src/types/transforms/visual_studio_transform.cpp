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
#include "dogen.assets/io/meta_model/model_io.hpp"
#include "dogen.assets/types/transforms/context.hpp"
#include "dogen.assets/types/helpers/name_flattener.hpp"
#include "dogen.assets/lexical_cast/meta_model/technical_space_lc.hpp"
#include "dogen.assets/types/helpers/visual_studio_project_type_mapper.hpp"
#include "dogen.assets/types/transforms/transformation_error.hpp"
#include "dogen.assets/types/meta_model/visual_studio/project.hpp"
#include "dogen.assets/types/meta_model/visual_studio/solution.hpp"
#include "dogen.assets/types/transforms/visual_studio_transform.hpp"

namespace {

const std::string transform_id("assets.transforms.visual_studio_transform");
using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string dot(".");

const std::string too_many_projects(
    "Expected at most one Visual Studio project per model. Found: ");
const std::string too_many_solutions(
    "Expected at most one Visual Studio solution per model. Found: ");

}

namespace dogen::assets::transforms {

std::string
visual_studio_transform::project_name(const meta_model::name& n) {
    assets::helpers::name_flattener nfl(false/*detect_model_name*/);
    const auto ns(nfl.flatten(n));
    const auto r(boost::algorithm::join(ns, dot));
    return r;
}

void visual_studio_transform::
apply(const context& ctx, const assets::meta_model::model& m) {
    const auto id(m.name().qualified().dot());
    tracing::scoped_transform_tracer stp(lg, "mapping transform", transform_id,
        id, *ctx.tracer(), m);

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
    using meta_model::visual_studio::project_persistence_block;
    std::list<project_persistence_block> ppbs;
    for (auto& pair : m.visual_studio_elements().projects()) {
        auto& proj(*pair.second);
        if (proj.guid().empty()) {
            BOOST_LOG_SEV(lg, warn) << "User did not supply project GUID.";
            const auto uuid = boost::uuids::random_generator()();
            BOOST_LOG_SEV(lg, warn) << "Generated project GUID: " << uuid;
            proj.guid(boost::uuids::to_string(uuid));
        }

        /*
         * If the technical space is "agnostic", we need to leave it
         * for after mapping. Else we should attempt to map it now.
         */
        const auto ts(m.input_technical_space());
        if (ts != meta_model::technical_space::agnostic) {
            helpers::visual_studio_project_type_mapper tm;
            proj.type_guid(tm.from_technical_space(ts));
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
