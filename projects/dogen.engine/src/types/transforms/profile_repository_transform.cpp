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
#include "dogen.variability/io/meta_model/profile_repository_io.hpp"
#include "dogen.variability/types/transforms/profile_repository_production_chain.hpp"
#include "dogen.assets/io/meta_model/model_set_io.hpp"
#include "dogen.engine/types/transforms/context.hpp"
#include "dogen.engine/types/transforms/profile_repository_transform.hpp"

namespace {

const std::string
transform_id("engine.transforms.profile_repository_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace dogen::engine::transforms {

variability::meta_model::profile_repository
profile_repository_transform::apply(const context& ctx,
    const std::list<variability::meta_model::profile_template>& pts,
    const assets::meta_model::model_set& ms) {
    const auto& vctx(ctx.variability_context());
    tracing::scoped_transform_tracer stp(lg, "profile repository transform",
        transform_id, *vctx.tracer(), ms);

    const auto& fm(*ctx.assets_context().feature_model());
    using variability::transforms::profile_repository_production_chain;
    const auto r(profile_repository_production_chain::apply(vctx, pts, fm));
    stp.end_transform(r);
    return r;
}

}
