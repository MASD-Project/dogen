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
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.engine/types/transforms/context.hpp"
#include "masd.dogen.engine/types/transforms/profile_binding_transform.hpp"
#include "masd.dogen.engine/types/transforms/profile_repository_transform.hpp"
#include "masd.dogen.engine/types/transforms/injection_model_to_coding_model_transform.hpp"
#include "masd.dogen.engine/types/transforms/coding_model_set_to_configuration_model_set_transform.hpp"
#include "masd.dogen.engine/types/transforms/profile_template_adaption_transform.hpp"
#include "masd.dogen.engine/types/transforms/dynamic_stereotypes_transform.hpp"
#include "masd.dogen.engine/types/transforms/injection_model_set_to_coding_model_set_chain.hpp"

namespace {

const std::string transform_id(
    "engine.transforms.injection_model_set_to_coding_model_set_chain");
using namespace masd::dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace masd::dogen::engine::transforms {

coding::meta_model::model_set
injection_model_set_to_coding_model_set_chain::
apply(const context& ctx, const injection::meta_model::model_set& ms) {
    const auto model_name(ms.target().name());
    tracing::scoped_chain_tracer stp(lg,
        "injection model set to coding model set", transform_id, model_name,
        *ctx.coding_context().tracer());

    /*
     * First we convert the target injection model into a coding
     * model. We must set the origin of the target model to target so
     * that further transforms can be applied such as the origin
     * transform.
     */
    coding::meta_model::model_set r;
    using tf = injection_model_to_coding_model_transform;
    r.target(tf::apply(ctx, ms.target()));
    r.target().origin_type(coding::meta_model::origin_types::target);

    /*
     * Now we do the same conversion to the reference models.
     */
    for (const auto& ref : ms.references())
        r.references().push_back(tf::apply(ctx, ref));

    /*
     * The second part of this chain handles variability
     * processing. First we need to retrieve the variability data
     * structures - i.e. profile templates - from the models, across
     * all model sets.
     */
    const auto pts(profile_template_adaption_transform::apply(ctx, r));

    /*
     * If some templates were found, we need to process them.
     */
    if (!pts.empty()) {
        /*
         * First we need to create a repository of all profiles,
         * organised for querying.
         */
        const auto prp(profile_repository_transform::apply(ctx, pts, r));

        /*
         * Then we need to extract the configuration models from the
         * coding model set.
         */
        auto cms(coding_model_set_to_configuration_model_set_transform::
            apply(ctx, r));

        /*
         * We then bind the profiles to the relevant configurations.
         */
        profile_binding_transform::apply(ctx, prp, cms);
    }

    /*
     * The final step is to retrieve stereotypes which did not bind to
     * a profile, and mark them as dynamic stereotypes. These are then
     * further processed within the coding model chain.
     */
    dynamic_stereotypes_transform::apply(ctx.coding_context(), r);

    return r;
}

}
