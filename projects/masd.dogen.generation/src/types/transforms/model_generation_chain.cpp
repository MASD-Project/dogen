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
#include "masd.dogen.utility/types/io/list_io.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.generation/io/meta_model/model_io.hpp"
#include "masd.dogen.generation/types/transforms/model_post_processing_chain.hpp"
#include "masd.dogen.generation/types/transforms/model_generation_chain.hpp"

namespace {

const std::string
transform_id("generation.transforms.model_generation_chain");

using namespace masd::dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace masd::dogen::generation::transforms {

void model_generation_chain::transform(const context& ctx,
    std::list<meta_model::model>& gms) {
    tracing::scoped_chain_tracer stp(lg, "model generation chain",
        transform_id, *ctx.tracer());

    /*
     * Apply all of the post-processing transforms to the model.
     */
    for (auto& m : gms)
        model_post_processing_chain::transform(ctx, m);

    stp.end_chain(gms);
}

}
