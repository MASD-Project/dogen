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
#include "dogen.logical/io/entities/output_model_set_io.hpp"
#include "dogen.text/types/transforms/model_generation_chain.hpp"
#include "dogen.text/io/entities/model_set_io.hpp"
#include "dogen.orchestration/types/transforms/context.hpp"
#include "dogen.orchestration/types/transforms/logical_model_to_text_model_transform.hpp"
#include "dogen.orchestration/types/transforms/text_model_production_chain.hpp"

namespace {

const std::string
transform_id("orchestration.transforms.physical_model_production_chain");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace dogen::orchestration::transforms {

text::entities::model_set text_model_production_chain::apply(const context& ctx,
    const logical::entities::output_model_set& loms) {
    const auto& tctx(ctx.text_context());
    const auto& tracer(*tctx.tracer());
    tracing::scoped_chain_tracer stp(lg, "text model production chain",
        transform_id, loms.name().qualified().dot(), tracer, loms);

    /*
     * Convert the logical model into the text model representation.
     */
    auto r(logical_model_to_text_model_transform::apply(ctx, loms));

    /*
     * Finally, we can run the text chain against the model set. This
     * will execute all text transforms.
     */
    text::transforms::model_generation_chain::apply(tctx, r);

    stp.end_chain(r);
    return r;
}

}
