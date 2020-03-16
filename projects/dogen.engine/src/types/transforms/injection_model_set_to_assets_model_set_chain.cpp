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
#include "dogen.engine/types/transforms/injection_model_to_assets_model_transform.hpp"
#include "dogen.engine/types/transforms/injection_model_set_to_assets_model_set_chain.hpp"

namespace {

const std::string transform_id(
    "engine.transforms.injection_model_set_to_assets_model_set_chain");
using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace dogen::engine::transforms {

logical::meta_model::model_set
injection_model_set_to_assets_model_set_chain::
apply(const context& ctx, const injection::meta_model::model_set& ms) {
    const auto model_name(ms.target().name());
    tracing::scoped_chain_tracer stp(lg,
        "injection model set to assets model set", transform_id, model_name,
        *ctx.assets_context().tracer());

    /*
     * First we convert the target injection model into an assets
     * model. We must set the origin of the target model to target so
     * that further transforms can be applied such as the origin
     * transform.
     */
    logical::meta_model::model_set r;
    using tf = injection_model_to_assets_model_transform;
    r.target(tf::apply(ctx, ms.target()));
    r.target().origin_type(logical::meta_model::origin_types::target);

    /*
     * Now we do the same conversion to the reference models.
     */
    for (const auto& ref : ms.references())
        r.references().push_back(tf::apply(ctx, ref));

    return r;
}

}
