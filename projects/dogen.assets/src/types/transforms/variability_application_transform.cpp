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
#include "dogen.variability/types/transforms/profile_binding_transform.hpp"
#include "dogen.variability/types/transforms/profile_repository_production_chain.hpp"
#include "dogen.assets/types/transforms/context.hpp"
#include "dogen.assets/types/helpers/profile_adapter.hpp"
#include "dogen.assets/types/helpers/configuration_model_set_adapter.hpp"
#include "dogen.assets/types/transforms/variability_application_transform.hpp"

namespace {

const std::string transform_id(
    "assets.transforms.variability_application_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace dogen::assets::transforms {

void variability_application_transform::
apply(const context& ctx, assets::meta_model::model_set& ms) {
    const auto model_name(ms.target().name().qualified().dot());
    tracing::scoped_chain_tracer stp(lg, "variability data",
        transform_id, model_name, *ctx.tracer());

    /*
     * First we need to retrieve the variability data structures -
     * i.e. profile templates - from the models, across all model
     * sets.
     */
    using assets::helpers::profile_adapter;
    const auto& fm(*ctx.feature_model());
    const auto pts(profile_adapter::adapt_profile_templates(fm, ms));

    /*
     * If there are no profile templates, we have nothing to do.
     */
    if (pts.empty())
        return;

    /*
     * We need to process the templates. We start by creating a
     * repository of all profiles, organised for querying. The chain
     * takes care of instantiating templates into profiles.
     */
    variability::transforms::context vctx;
    // vctx.archetype_location_repository(ctx.archetype_location_repository());
    vctx.tracer(ctx.tracer());
    using variability::transforms::profile_repository_production_chain;
    const auto prp(profile_repository_production_chain::apply(vctx, pts, fm));

    /*
     * Then we need to extract the configuration models from the
     * assets model set.
     */
    using assets::helpers::configuration_model_set_adapter;
    auto cms(configuration_model_set_adapter::adapt(ms));

    /*
     * We then bind the profiles to the relevant configurations.
     */
    using variability::transforms::profile_binding_transform;
    profile_binding_transform::apply(vctx, fm, prp, cms);
}

}
