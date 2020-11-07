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
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.identification/io/entities/logical_id_io.hpp"
#include "dogen.physical/types/entities/meta_model.hpp"
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.text/io/entities/model_io.hpp"
#include "dogen.text/types/transforms/context.hpp"
#include "dogen.text/types/entities/logical_physical_region.hpp"
#include "dogen.orchestration/types/transforms/elements_removal_transform.hpp"

namespace {

const std::string
transform_id("orchestration.transforms.elements_removal_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace dogen::orchestration::transforms {

void elements_removal_transform::apply(const text::transforms::context& ctx,
    text::entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "legacy dependencies",
        transform_id, m.logical().name().id().value(), *ctx.tracer(), m);


    const auto& in(ctx.physical_meta_model()->indexed_names());
    const auto& idx(in.archetype_names_by_logical_meta_name());
    std::list<text::entities::logical_physical_region> filtered_regions;
    for (const auto& region : m.logical_physical_regions()) {
        /*
         * If the element has no archetypes, there is no point in it
         * reaching code generation.
         */
        const auto& e(*region.logical_element());
        const auto& mid(e.meta_name().id());
        const auto& id(e.name().id());
        const auto i(idx.find(mid));
        if (i == idx.end()) {
            BOOST_LOG_SEV(lg, debug) << "Element has no archetypes: " << id;
            continue;
        }

        /*
         * If the element is not part of the target model it won't be
         * generated so filter it out.
         */
        using identification::entities::model_type;
        if (e.provenance().model_type() != model_type::target) {
            BOOST_LOG_SEV(lg, debug) << "Element not in target model: " << id;
            continue;
        }

        filtered_regions.push_back(region);
    }
    m.logical_physical_regions(filtered_regions);

    stp.end_transform(m);
}

}
