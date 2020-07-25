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
#include "dogen.orchestration/types/transforms/context.hpp"
#include "dogen.orchestration/types/transforms/injection_model_to_logical_model_transform.hpp"
#include "dogen.orchestration/types/transforms/injection_model_set_to_logical_input_model_set_chain.hpp"

namespace {

const std::string transform_id(
    "orchestration.transforms.injection_model_set_to_logical_input_model_set_chain");
using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace dogen::orchestration::transforms {

logical::entities::input_model_set
injection_model_set_to_logical_input_model_set_chain::
apply(const context& ctx, const injection::entities::model_set& ms) {
    const auto model_name(ms.target().name().simple());
    tracing::scoped_chain_tracer stp(lg,
        "injection model set to logical model set", transform_id, model_name,
        *ctx.logical_context().tracer());

    /*
     * First we convert the target injection model into an logical
     * model. We must set the origin of the target model to target so
     * that further transforms can be applied such as the origin
     * transform.
     */
    logical::entities::input_model_set r;
    using tf = injection_model_to_logical_model_transform;
    r.target(tf::apply(ctx, ms.target()));
    using identification::entities::model_type;
    r.target().provenance().model_type(model_type::target);

    /*
     * Now we do the same conversion to the reference models.
     */
    for (const auto& ref : ms.references())
        r.references().push_back(tf::apply(ctx, ref));

    return r;
}

}
