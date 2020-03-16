/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
`` * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#include "dogen.logical/io/meta_model/model_io.hpp"
#include "dogen.logical/types/transforms/context.hpp"
#include "dogen.logical/types/transforms/merge_transform.hpp"
#include "dogen.logical/types/transforms/extensible_mapping_transform.hpp"
#include "dogen.logical/types/transforms/assembly_chain.hpp"

namespace {

const std::string transform_id("assets.transforms.assembly_chain");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace dogen::logical::transforms {

meta_model::model assembly_chain::apply(const context& ctx,
    const meta_model::technical_space ts, logical::meta_model::model_set ms) {
    const auto ms_id(ms.target().name().qualified().dot());
    tracing::scoped_chain_tracer stp(lg, "model assembly chain", transform_id,
        ms_id, *ctx.tracer());

    /*
     * First map the model set, if required.
     */
    const auto mapped_set(extensible_mapping_transform::apply(ctx, ms, ts));

    /*
     * Then merge the mapped set.
     */
    const auto r(merge_transform::apply(ctx, mapped_set));

    stp.end_chain(r);
    return r;
}

}
