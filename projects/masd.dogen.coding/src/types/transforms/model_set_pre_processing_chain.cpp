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
#include "masd.dogen.coding/io/meta_model/languages_io.hpp"
#include "masd.dogen.coding/io/meta_model/model_set_io.hpp"
#include "masd.dogen.coding/types/helpers/model_pre_processing_validator.hpp"
#include "masd.dogen.coding/types/transforms/context.hpp"
#include "masd.dogen.coding/types/transforms/modules_transform.hpp"
#include "masd.dogen.coding/types/transforms/origin_transform.hpp"
#include "masd.dogen.coding/types/transforms/language_transform.hpp"
#include "masd.dogen.coding/types/transforms/type_params_transform.hpp"
#include "masd.dogen.coding/types/transforms/parsing_transform.hpp"
#include "masd.dogen.coding/types/transforms/primitives_transform.hpp"
#include "masd.dogen.coding/types/transforms/extraction_properties_transform.hpp"
#include "masd.dogen.coding/types/transforms/model_set_pre_processing_chain.hpp"

namespace {

const std::string transform_id(
    "coding.transforms.model_set_pre_processing_chain");

using namespace masd::dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace masd::dogen::coding::transforms {

void model_set_pre_processing_chain::
transform(const context& ctx, meta_model::model& m) {
    /*
     * Module transform must be done before origin and language
     * transforms to get these properties populated on the new
     * modules.
     */
    modules_transform::transform(ctx, m);
    language_transform::transform(ctx, m);

    /*
     * There are no particular dependencies on the next set of
     * transforms.
     */
    origin_transform::transform(ctx, m);
    type_params_transform::transform(ctx, m);
    parsing_transform::transform(ctx, m);
    extraction_properties_transform::transform(ctx, m);

    /*
     * Primitive expansion requires parsing expansion to populate the
     * underlying elements.
     */
    primitives_transform::transform(ctx, m);

    /*
     * Ensure the model is valid.
     */
    helpers::model_pre_processing_validator::validate(m);
}

void model_set_pre_processing_chain::
transform(const context& ctx, meta_model::model_set& ms) {
    tracing::scoped_chain_tracer stp(lg, "model set pre-processing chain",
        transform_id, ms.target().name().id(), *ctx.tracer(), ms);

    /*
     * Apply all of the pre-processing transforms to the target.
     */
    transform(ctx, ms.target());

    /*
     * Now we do the same thing but for the reference models.
     */
    for (auto& ref : ms.references())
        transform(ctx, ref);

    stp.end_chain(ms);
}


}
