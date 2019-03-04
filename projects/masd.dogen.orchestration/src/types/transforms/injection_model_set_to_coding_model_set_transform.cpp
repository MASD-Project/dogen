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
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.coding/types/transforms/context.hpp"
#include "masd.dogen.orchestration/types/transforms/injection_model_to_coding_model_transform.hpp"
#include "masd.dogen.orchestration/types/transforms/injection_model_set_to_coding_model_set_transform.hpp"

namespace {

const std::string transform_id(
    "orchestration.transforms.injection_model_set_to_coding_model_set_transform");
using namespace masd::dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace masd::dogen::orchestration::transforms {

coding::meta_model::model_set
injection_model_set_to_coding_model_set_transform::
transform(const coding::transforms::context& ctx,
    const injection::meta_model::model_set& ms) {
    const auto model_name(ms.target().name());
    tracing::scoped_chain_tracer stp(lg,
        "injection model set to coding model set", transform_id, model_name,
        *ctx.tracer());

    /*
     * First we convert the target injection model into a coding
     * model. We must set the origin of the target model to target so
     * that further transforms can be applied such as the origin
     * transform.
     */
    coding::meta_model::model_set r;
    using tf = injection_model_to_coding_model_transform;
    r.target(tf::transform(ctx, ms.target()));
    r.target().origin_type(coding::meta_model::origin_types::target);

    /*
     * Now we do the same thing to the reference models.
     */
    for (const auto& ref : ms.references())
        r.references().push_back(tf::transform(ctx, ref));

    return r;
}

}
