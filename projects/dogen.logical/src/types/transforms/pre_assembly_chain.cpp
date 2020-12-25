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
#include "dogen.logical/io/entities/input_model_set_io.hpp"
#include "dogen.logical/types/helpers/pre_assembly_validator.hpp"
#include "dogen.logical/types/transforms/context.hpp"
#include "dogen.logical/types/transforms/modelines_transform.hpp"
#include "dogen.logical/types/transforms/modules_transform.hpp"
#include "dogen.logical/types/transforms/origin_transform.hpp"
#include "dogen.logical/types/transforms/technical_space_transform.hpp"
#include "dogen.logical/types/transforms/type_params_transform.hpp"
#include "dogen.logical/types/transforms/parsing_transform.hpp"
#include "dogen.logical/types/transforms/primitives_transform.hpp"
#include "dogen.logical/types/transforms/containment_transform.hpp"
#include "dogen.logical/types/transforms/physical_entities_transform.hpp"
#include "dogen.logical/types/transforms/mapping_elements_transform.hpp"
#include "dogen.logical/types/transforms/variability_features_transform.hpp"
#include "dogen.logical/types/transforms/visual_studio_transform.hpp"
#include "dogen.logical/types/transforms/dynamic_stereotypes_transform.hpp"
#include "dogen.logical/types/transforms/variability_profiles_chain.hpp"
#include "dogen.logical/types/transforms/labelling_transform.hpp"
#include "dogen.logical/types/transforms/aspect_properties_transform.hpp"
#include "dogen.logical/types/transforms/assistant_properties_transform.hpp"
#include "dogen.logical/types/transforms/streaming_properties_transform.hpp"
#include "dogen.logical/types/transforms/documentation_transform.hpp"
#include "dogen.logical/types/transforms/pre_assembly_chain.hpp"

namespace {

const std::string transform_id("logical.transforms.pre_assembly_chain");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace dogen::logical::transforms {

void pre_assembly_chain::apply(const context& ctx,
    const std::unordered_map<std::string, std::string>& fixed_mappings,
    entities::model& m) {
    /*
     * Module transform must be done before origin and technical space
     * transforms to get these properties populated on the new
     * modules; it must be done before the containment transform
     * because we rely on implicit modules being present.
     */
    modules_transform::apply(ctx, m);
    containment_transform::apply(ctx, m);

    /*
     * Physical transform must be done before containment transform as
     * we rely on @e contains being populated.
     */
    physical_entities_transform::apply(ctx, m);

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
    variability_features_transform::apply(ctx, fixed_mappings, m);
    visual_studio_transform::apply(ctx, m);
    labelling_transform::apply(ctx, m);
    aspect_properties_transform::apply(ctx, m);
    assistant_properties_transform::apply(ctx, m);
    streaming_properties_transform::apply(ctx, m);
    documentation_transform::apply(ctx, m);

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

void pre_assembly_chain::apply(const context& ctx, entities::input_model_set& ms) {
    tracing::scoped_chain_tracer stp(lg, "pre-assembly chain",
        transform_id, ms.target().name().qualified().dot(), *ctx.tracer(), ms);

    /*
     * First and foremost we must perform the variability processing
     * in the model set. This will read all meta-model elements that
     * contain variability data (e.g. profiles and profile templates),
     * execute the required variability workflows and then bind them
     * as configurations against the appropriate model elements. This
     * ensures all the meta-data is ready for further processing.
     */
    variability_profiles_chain::apply(ctx, ms);

    /*
     * Now we need to figure out which stereotypes are left from
     * profile processing. These will be considered dynamic
     * stereotypes and will processed further down the pipeline.
     */
    dynamic_stereotypes_transform::apply(ctx, ms);

    /*
     * Next we need to process all mapping elements, as these will be
     * used by the remaining transforms. Its important to note that
     * the mapping elements are not required by the first two phases
     * of the variability transforms, only by the third phase (which
     * is why the previous transforms work).
     */
    mapping_elements_transform::apply(ctx, ms);

    /*
     * Finally, we enter the pre-assembly proper: we apply the
     * remaining transforms to all models, starting with the target
     * and then all referenced models.
     */
    apply(ctx, ms.fixed_mappings(), ms.target());
    for (auto& ref : ms.references())
        apply(ctx, ms.fixed_mappings(), ref);

    stp.end_chain(ms);
}

}
