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
#include "masd.dogen.utility/log/logger.hpp"
#include "masd.dogen.tracing/types/scoped_prober.hpp"
#include "masd.dogen.coding/io/meta_model/model_io.hpp"
#include "masd.dogen.coding/types/transforms/generability_transform.hpp"
#include "masd.dogen.coding/types/transforms/dynamic_transforms_chain.hpp"
#include "masd.dogen.coding/types/transforms/artefact_properties_transform.hpp"
#include "masd.dogen.coding/types/transforms/enablement_transform.hpp"
#include "masd.dogen.coding/types/transforms/formatting_transform.hpp"
#include "masd.dogen.coding/types/transforms/archetype_location_properties_transform.hpp"
#include "masd.dogen.coding/types/transforms/locator_properties_transform.hpp"
#include "masd.dogen.coding/types/transforms/model_post_processing_chain.hpp"

namespace {

const std::string transform_id(
    "yarn.transforms.model_post_processing_chain");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace masd::dogen::coding::transforms {

void model_post_processing_chain::
transform(const context& ctx, meta_model::model& m) {
    tracing::scoped_chain_prober stp(lg, "model post-processing chain",
        transform_id, m.name().id(), ctx.prober(), m);

    /*
     * Perform dynamic expansion first. These are backend specific.
     */
    dynamic_transforms_chain::transform(ctx, m);

    /*
     * Next we apply the generability transform. We do this after
     * dynamic transforms to cater for any new elements they may have
     * inserted.
     */
    generability_transform::transform(ctx, m);

    /*
     * Expand the artefact properties against the suitable archetype
     * locations. Must be done before enablement transform and any
     * other transform that populates these properties.
     */
    artefact_properties_transform::transform(ctx, m);

    /*
     * The archetype location properties transform must be executed
     * before the enablement transform.
     */
    archetype_location_properties_transform::transform(ctx, m);

    /*
     * Enablement transform must be applied after the dynamic
     * transform chain as it needs to compute enablement for any
     * backend specific types that might have been added.
     */
    enablement_transform::transform(ctx, m);

    /*
     * The formatting transform and the locator properties transform
     * have no dependencies in the post-processing chain.
     */
    formatting_transform::transform(ctx, m);
    locator_properties_transform::transform(ctx, m);

    stp.end_chain(m);
}

}
