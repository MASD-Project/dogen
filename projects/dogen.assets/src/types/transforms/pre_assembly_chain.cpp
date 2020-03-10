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
#include "dogen.assets/io/meta_model/model_set_io.hpp"
#include "dogen.assets/types/helpers/pre_assembly_validator.hpp"
#include "dogen.assets/types/transforms/context.hpp"
#include "dogen.assets/types/transforms/modelines_transform.hpp"
#include "dogen.assets/types/transforms/modules_transform.hpp"
#include "dogen.assets/types/transforms/origin_transform.hpp"
#include "dogen.assets/types/transforms/technical_space_transform.hpp"
#include "dogen.assets/types/transforms/type_params_transform.hpp"
#include "dogen.assets/types/transforms/parsing_transform.hpp"
#include "dogen.assets/types/transforms/primitives_transform.hpp"
#include "dogen.assets/types/transforms/containment_transform.hpp"
#include "dogen.assets/types/transforms/mapping_elements_transform.hpp"
#include "dogen.assets/types/transforms/extraction_properties_transform.hpp"
#include "dogen.assets/types/transforms/variability_entities_transform.hpp"
#include "dogen.assets/types/transforms/visual_studio_transform.hpp"
#include "dogen.assets/types/transforms/dynamic_stereotypes_transform.hpp"
#include "dogen.assets/types/transforms/variability_application_transform.hpp"
#include "dogen.assets/types/transforms/pre_assembly_chain.hpp"

namespace {

const std::string transform_id("assets.transforms.pre_assembly_chain");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace dogen::assets::transforms {

void pre_assembly_chain::apply(const context& ctx,
    const std::unordered_map<std::string, std::string>& fixed_mappings,
    meta_model::model& m) {
    /*
     * Module transform must be done before origin and technical space
     * transforms to get these properties populated on the new
     * modules; it must be done before the containment transform
     * because we rely on implicit modules being present.
     */
    modules_transform::apply(ctx, m);
    containment_transform::apply(ctx, m);

    /*
     * Modelines transform must be done after the containment
     * transform to ensure we can see the modelines for a group.
     */
    modelines_transform::apply(ctx, m);

    /*
     * There are no particular dependencies on the next set of
     * transforms.
     */
    technical_space_transform::apply(ctx, m);
    origin_transform::apply(ctx, m);
    type_params_transform::apply(ctx, m);
    extraction_properties_transform::apply(ctx, m);
    variability_entities_transform::apply(ctx, fixed_mappings, m);
    visual_studio_transform::apply(ctx, m);

    /*
     * Primitive transform must happen before parsing transform, as it
     * parses the attribute for the underlying element.
     */
    primitives_transform::apply(ctx, m);

    /*
     * Parsing must happen after variability feature bundles have been
     * transformed because we rely on the mapped type being populated.
     */
    parsing_transform::apply(ctx, m);

    /*
     * Ensure the model is valid.
     */
    helpers::pre_assembly_validator::validate(m);
}

void pre_assembly_chain::apply(const context& ctx, meta_model::model_set& ms) {
    tracing::scoped_chain_tracer stp(lg, "pre-assembly chain",
        transform_id, ms.target().name().qualified().dot(), *ctx.tracer(), ms);

    /*
     * First we handle the processing of mapping elements. There is no
     * particular reason to do this first as it has no dependencies in
     * this chain.
     */
    mapping_elements_transform::apply(ctx, ms);

    /*
     * The second part of this chain handles variability
     * processing. For this we delegate to the variability chain.
     */
    variability_application_transform::apply(ctx, ms);

    /*
     * The final step is to retrieve stereotypes which did not bind to
     * a profile, and mark them as dynamic stereotypes. These are then
     * further processed within the assets model chain.
     */
    using assets::transforms::dynamic_stereotypes_transform;
    dynamic_stereotypes_transform::apply(ctx, ms);

    /*
     * Apply all of the pre-processing transforms to the target.
     */
    apply(ctx, ms.fixed_mappings(), ms.target());

    /*
     * Now we do the same thing but for the reference models.
     */
    for (auto& ref : ms.references())
        apply(ctx, ms.fixed_mappings(), ref);

    stp.end_chain(ms);
}


}
