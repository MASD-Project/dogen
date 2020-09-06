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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.logical/types/transforms/context.hpp"
#include "dogen.logical/types/entities/visual_studio/project.hpp"
#include "dogen.logical/types/entities/visual_studio/solution.hpp"
#include "dogen.logical/types/helpers/visual_studio_project_type_mapper.hpp"
#include "dogen.logical/types/transforms/visual_studio_project_type_transform.hpp"

namespace {

const std::string transform_id(
    "logical.transforms.visual_studio_project_type_transform");
using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace dogen::logical::transforms {

void visual_studio_project_type_transform::
apply(const context& ctx, const logical::entities::model& m) {
    const auto id(m.name().id());
    tracing::scoped_transform_tracer stp(lg,
        "visual studio project type transform", transform_id, id.value(),
        *ctx.tracer(), m);

    const auto ts(m.input_technical_space());
    helpers::visual_studio_project_type_mapper tm;
    const auto pt_guid(tm.from_technical_space(ts));
    BOOST_LOG_SEV(lg, debug) << "Project type for technical space: " << pt_guid;

    for (auto& pair : m.visual_studio_elements().projects()) {
        auto& proj(*pair.second);
        proj.type_guid(pt_guid);
    }

    for (auto& pair : m.visual_studio_elements().solutions()) {
        for (auto& ppb : pair.second->project_persistence_blocks())
            ppb.type_guid(pt_guid);
    }

    stp.end_transform(m);
}

}
