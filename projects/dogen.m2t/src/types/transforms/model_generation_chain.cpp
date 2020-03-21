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
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.m2t/io/entities/model_io.hpp"
#include "dogen.m2t/types/transforms/generability_transform.hpp"
#include "dogen.m2t/types/transforms/artefact_properties_transform.hpp"
#include "dogen.m2t/types/transforms/enablement_transform.hpp"
#include "dogen.m2t/types/transforms/formatting_transform.hpp"
#include "dogen.m2t/types/transforms/archetype_location_properties_transform.hpp"
#include "dogen.m2t/types/transforms/technical_space_transform.hpp"
#include "dogen.m2t/types/transforms/decoration_transform.hpp"
#include "dogen.m2t/types/transforms/model_generation_chain.hpp"

namespace {

const std::string
transform_id("m2t.transforms.model_generation_chain");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace dogen::m2t::transforms {

void model_generation_chain::apply(const context& ctx,
    std::list<entities::model>& ms) {

    /*
     * If we don't have any models in the set, there is nothing to
     * do. Don't even bother setup the tracer.
     */
    if (ms.empty()) {
        BOOST_LOG_SEV(lg, debug) << "Model set is empty, nothing to do.";
        return;
    }

    const auto id(ms.front().name().qualified().dot());
    tracing::scoped_chain_tracer stp(lg, "model generation chain",
        transform_id, id, *ctx.tracer(), ms);

    /*
     * Apply all of the post-processing transforms to the model.
     */
    for (auto& m : ms) {
        /*
         * Technical spaces transform must be done after the dynamic
         * transform but before decorations.
         */
        technical_space_transform::apply(ctx, m);

        /*
         * Decoration transform must be applied after dynamic
         * transform because we need the new model elements.
         */
        decoration_transform::apply(ctx, m);

        /*
         * Next we apply the generability transform. We do this after
         * dynamic transforms to cater for any new elements they may have
         * inserted.
         */
        generability_transform::apply(ctx, m);

        /*
         * Expand the artefact properties against the suitable archetype
         * locations. Must be done before enablement transform and any
         * other transform that populates these properties.
         */
        artefact_properties_transform::apply(ctx, m);

        /*
         * The archetype location properties transform must be executed
         * before the enablement transform.
         */
        archetype_location_properties_transform::apply(ctx, m);

        /*
         * Enablement transform must be applied after the dynamic
         * transform chain as it needs to compute enablement for any
         * backend specific types that might have been added.
         */
        enablement_transform::apply(ctx, m);

        /*
         * The formatting transform and the locator properties transform
         * have no dependencies in the post-processing chain.
         */
        formatting_transform::apply(ctx, m);
    }

    stp.end_chain(ms);
}

}
