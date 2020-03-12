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
#include "dogen.variability/types/transforms/context.hpp"
#include "dogen.variability/types/transforms/profile_binding_transform.hpp"
#include "dogen.variability/types/transforms/profile_repository_production_chain.hpp"
#include "dogen.assets/types/transforms/context.hpp"
#include "dogen.assets/io/meta_model/model_set_io.hpp"
#include "dogen.assets/types/helpers/profile_adapter.hpp"
#include "dogen.assets/types/helpers/configuration_model_set_adapter.hpp"
#include "dogen.assets/types/transforms/variability_profiles_transform.hpp"
#include "dogen.assets/types/transforms/variability_profiles_chain.hpp"

namespace {

const std::string transform_id("assets.transforms.variability_profiles_chain");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace dogen::assets::transforms {

variability::transforms::context
variability_profiles_chain::adapt(const context& ctx) {
    variability::transforms::context r;
    r.tracer(ctx.tracer());
    r.compatibility_mode(ctx.compatibility_mode());
    r.template_instantiation_domains(ctx.template_instantiation_domains());
    return r;
}

void variability_profiles_chain::
apply(const context& ctx, assets::meta_model::model_set& ms) {
    const auto model_name(ms.target().name().qualified().dot());
    tracing::scoped_chain_tracer stp(lg, "variability profiles",
        transform_id, model_name, *ctx.tracer());

    /*
     * We start by updating all the profile-like meta-model elements
     * (e.g. profiles and profile templates). This entails reading any
     * associated meta-data and populating the respective attributes
     * with it.
     */
    variability_profiles_transform::apply(ctx,ms);

    /*
     * Now we adapt all the profile-like elements into their
     * variability counterparts.
     */
    const auto& fm(*ctx.feature_model());
    using assets::helpers::profile_adapter;
    const auto inputs(profile_adapter::adapt(fm, ms));

    /*
     * If there are no profile-like elements, we have nothing to do.
     */
    if (inputs.templates().empty() && inputs.profiles().empty())
        return;

    /*
     * We need to expand all profile templates into proper
     * profiles. We start by creating a repository of all profiles,
     * organised for querying. The chain takes care of instantiating
     * templates into profiles.
     */
    const auto vctx(adapt(ctx));
    using prpc = variability::transforms::profile_repository_production_chain;
    const auto prp(prpc::apply(vctx, fm, inputs));

    /*
     * Then we need to extract the configuration models from the
     * assets model set. It is against these that the binding will
     * take place.
     */
    using assets::helpers::configuration_model_set_adapter;
    auto cms(configuration_model_set_adapter::adapt(ms));

    /*
     * Finally, we bind the profiles to the relevant configurations.
     */
    using variability::transforms::profile_binding_transform;
    profile_binding_transform::apply(vctx, fm, prp, cms);
}

}
