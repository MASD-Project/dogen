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
#include "masd.dogen.coding/io/meta_model/model_set_io.hpp"
#include "masd.dogen.coding/types/helpers/pre_assembly_validator.hpp"
#include "masd.dogen.coding/types/transforms/context.hpp"
#include "masd.dogen.coding/types/transforms/modelines_transform.hpp"
#include "masd.dogen.coding/types/transforms/modules_transform.hpp"
#include "masd.dogen.coding/types/transforms/origin_transform.hpp"
#include "masd.dogen.coding/types/transforms/technical_space_transform.hpp"
#include "masd.dogen.coding/types/transforms/type_params_transform.hpp"
#include "masd.dogen.coding/types/transforms/parsing_transform.hpp"
#include "masd.dogen.coding/types/transforms/primitives_transform.hpp"
#include "masd.dogen.coding/types/transforms/extraction_properties_transform.hpp"
#include "masd.dogen.coding/types/transforms/pre_assembly_chain.hpp"

namespace {

const std::string transform_id("coding.transforms.pre_assembly_chain");

using namespace masd::dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace masd::dogen::coding::transforms {

void pre_assembly_chain::apply(const context& ctx, meta_model::model& m) {
    /*
     * Modelines transform can be done anywhere as its dependencies
     * are not within coding transforms at present.
     */
    modelines_transform::apply(ctx, m);

    /*
     * Module transform must be done before origin and technical space
     * transforms to get these properties populated on the new
     * modules.
     */
    modules_transform::apply(ctx, m);
    technical_space_transform::apply(ctx, m);

    /*
     * There are no particular dependencies on the next set of
     * transforms.
     */
    origin_transform::apply(ctx, m);
    type_params_transform::apply(ctx, m);
    parsing_transform::apply(ctx, m);
    extraction_properties_transform::apply(ctx, m);

    /*
     * Primitive transform requires parsing transform to populate the
     * underlying elements.
     */
    primitives_transform::apply(ctx, m);

    /*
     * Ensure the model is valid.
     */
    helpers::pre_assembly_validator::validate(m);
}

void pre_assembly_chain::apply(const context& ctx, meta_model::model_set& ms) {
    tracing::scoped_chain_tracer stp(lg, "pre-assembly chain",
        transform_id, ms.target().name().qualified().dot(), *ctx.tracer(), ms);

    /*
     * Apply all of the pre-processing transforms to the target.
     */
    apply(ctx, ms.target());

    /*
     * Now we do the same thing but for the reference models.
     */
    for (auto& ref : ms.references())
        apply(ctx, ref);

    stp.end_chain(ms);
}


}
