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
#include "dogen.engine/types/transforms/context.hpp"
#include "dogen.variability/types/transforms/profile_binding_transform.hpp"
#include "dogen.assets/types/helpers/configuration_model_set_adapter.hpp"
#include "dogen.engine/types/transforms/profile_repository_transform.hpp"
#include "dogen.engine/types/transforms/profile_template_adaption_transform.hpp"
#include "dogen.engine/types/transforms/variability_data_chain.hpp"

namespace {

const std::string transform_id("engine.transforms.variability_data_chain");
using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

}
namespace dogen::engine::transforms {

void variability_data_chain::
apply(const context& ctx, assets::meta_model::model_set& ms) {
    const auto model_name(ms.target().name().qualified().dot());
    tracing::scoped_chain_tracer stp(lg, "variability data",
        transform_id, model_name, *ctx.assets_context().tracer());

    /*
     * First we need to retrieve the variability data structures -
     * i.e. profile templates - from the models, across all model
     * sets.
     */
    const auto pts(profile_template_adaption_transform::apply(ctx, ms));

    /*
     * If some templates were found, we need to process them.
     */
    if (!pts.empty()) {
        /*
         * First we need to create a repository of all profiles,
         * organised for querying.
         */
        const auto prp(profile_repository_transform::apply(ctx, pts, ms));

        /*
         * Then we need to extract the configuration models from the
         * assets model set.
         */
        using assets::helpers::configuration_model_set_adapter;
        auto cms(configuration_model_set_adapter::adapt(ms));

        /*
         * We then bind the profiles to the relevant configurations.
         */
        const auto& fm(*ctx.injection_context().feature_model());
        const auto& vctx(ctx.variability_context());
        using variability::transforms::profile_binding_transform;
        profile_binding_transform::apply(vctx, fm, prp, cms);
    }
}

}
