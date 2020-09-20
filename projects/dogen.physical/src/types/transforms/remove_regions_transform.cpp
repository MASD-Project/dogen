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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.identification/io/entities/physical_id_io.hpp"
#include "dogen.identification/io/entities/logical_id_io.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.physical/types/entities/region.hpp"
#include "dogen.physical/io/entities/model_io.hpp"
#include "dogen.physical/types/transforms/transform_exception.hpp"
#include "dogen.physical/types/transforms/remove_regions_transform.hpp"

namespace {

const std::string transform_id("physical.transforms.remove_regions_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace dogen::physical::transforms {

void remove_regions_transform::apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "enablement",
        transform_id, m.name().id().value(), *ctx.tracer(), m);

    /*
     * Loop through all of the physical regions in the model, and
     * extract only those with artefacts that can be written to the
     * file-system.
     */
    using identification::entities::logical_id;
    std::unordered_map<logical_id, entities::region> filtered_regions;
    for (const auto& pr_pair : m.regions_by_logical_id()) {
        const auto& lid(pr_pair.first);
        const auto& original_region(pr_pair.second);

        /*
         * Start with the original region but remove all artefacts
         * from it. With this we keep any other properties.
         */
        entities::region filtered_region(original_region);
        filtered_region.artefacts_by_archetype().clear();

        /*
         * Go through all the artefacts and the original region and
         * keep only those that need writing.
         */
        for (const auto& a_pair : original_region.artefacts_by_archetype()) {
            const auto archetype_id(a_pair.first);
            const auto aptr(a_pair.second);

            /*
             * If the artefact does not have a path, ignore it
             * it. Normally these are artefacts that belong to
             * external models.
             *
             * FIXME: we should have additional checks here.
             */
            if (aptr->file_path().empty()) {
                BOOST_LOG_SEV(lg, trace) << "Artefact has an empty path. ID:"
                                         << aptr->name().id();
                continue;
            }

            filtered_region.artefacts_by_archetype().insert(a_pair);
        }

        /*
         * If the region does not have any artefacts, ignore the
         * entire region.
         */
        if (filtered_region.artefacts_by_archetype().empty()) {
            BOOST_LOG_SEV(lg, trace) << "Region has no artefacts. ID:" << lid;
            continue;
        }

        /*
         * Insert the region after filtering.
         */
        auto pair(std::make_pair(lid, filtered_region));
        filtered_regions.insert(pair);
    }

    m.regions_by_logical_id(filtered_regions);

    stp.end_transform(m);
}

}
