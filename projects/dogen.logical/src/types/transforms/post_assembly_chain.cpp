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
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.logical/types/helpers/indexer.hpp"
#include "dogen.logical/types/helpers/post_assembly_validator.hpp"
#include "dogen.logical/types/transforms/context.hpp"
#include "dogen.logical/types/transforms/enumerations_transform.hpp"
#include "dogen.logical/types/transforms/generalization_transform.hpp"
#include "dogen.logical/types/transforms/stereotypes_transform.hpp"
#include "dogen.logical/types/transforms/object_templates_transform.hpp"
#include "dogen.logical/types/transforms/global_module_transform.hpp"
#include "dogen.logical/types/transforms/orm_transform.hpp"
#include "dogen.logical/types/transforms/resolver_transform.hpp"
#include "dogen.logical/types/transforms/attributes_transform.hpp"
#include "dogen.logical/types/transforms/associations_transform.hpp"
#include "dogen.logical/types/transforms/meta_naming_transform.hpp"
#include "dogen.logical/types/transforms/type_registrar_transform.hpp"
#include "dogen.logical/types/transforms/odb_options_transform.hpp"
#include "dogen.logical/types/transforms/visual_studio_project_type_transform.hpp"
#include "dogen.logical/types/transforms/all_technical_spaces_transform.hpp"
#include "dogen.logical/types/transforms/template_rendering_transform.hpp"
#include "dogen.logical/types/transforms/decoration_transform.hpp"
#include "dogen.logical/types/transforms/generability_transform.hpp"
#include "dogen.logical/types/transforms/helper_properties_transform.hpp"
#include "dogen.logical/types/transforms/technical_space_properties_transform.hpp"
#include "dogen.logical/types/transforms/post_assembly_chain.hpp"

namespace {

const std::string transform_id(
    "logical.transforms.post_assembly_chain");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace dogen::logical::transforms {

void post_assembly_chain::apply(const context& ctx, entities::model& m) {
    tracing::scoped_chain_tracer stp(lg, "model post-processing chain",
        transform_id, m.name().id().value(), *ctx.tracer(), m);

    /*
     * Visual studio project type transform has no dependencies.
     */
    visual_studio_project_type_transform::apply(ctx, m);

    /*
     * Enumeration transform must be done after merging as we need the
     * built-in types; these are required in order to find the default
     * enumeration underlying element.
     */
    enumerations_transform::apply(ctx, m);

    /*
     * Create all indices first as its needed by generalisation. Note
     * that this means generated types (such as visitor etc) are not
     * part of indices, which is not ideal - but for now, its not a
     * major problem.
     */
    const auto idx(helpers::indexer::index(m));

    /*
     * We must expand generalisation relationships before we apply the
     * stereotypes transform because we need to know about leaves
     * before we can generate visitors. Note also that generalisations
     * must be expanded after merging models because we may inherit
     * across models.
     */
    generalization_transform::apply(ctx, idx, m);

    /*
     * Stereotypes transform must be done before object templates
     * because we obtain object template information from the
     * stereotypes.
     */
    stereotypes_transform::apply(ctx, m);
    object_templates_transform::apply(ctx, m);

    /*
     * Global module transform must be done in the post-assembly phase
     * as we only want a single global module for all models.
     */
    global_module_transform::apply(ctx, m);

    /*
     * Generability must be done after stereotypes and modules transform.
     */
    generability_transform::apply(ctx, m);

    /*
     * Meta-name transform must be applied after all transforms that
     * inject new meta-model types for the logical model. At present that
     * is stereotypes and containment transforms. This is also why we
     * cannot apply this transform at the model level.
     */
    meta_naming_transform::apply(ctx, m);

    /*
     * ORM properties must be expanded after stereotypes and
     * containment.
     */
    orm_transform::apply(ctx, m);

    /*
     * ODB options must be processed after ORM properties have been
     * expanded.
     */
    odb_options_transform::apply(ctx, m);

    /*
     * Resolution must be done after system elements have been
     * generated (such as visitor, etc) or else it will fail to find
     * any references to those elements. This is done in stereotype
     * expansion.
     */
    resolver_transform::apply(ctx, idx, m);

    /*
     * We can only expand attributes after we've expanded:
     *
     * - object templates, as we rely on all attributes obtained from
     *   instantiating an object template on already being present.
     * - stereotypes, as we need settings such as immutability and
     *   fluency to be populated.
     *  - resolution, else we will copy unresolved attributes.
     */
    attributes_transform::apply(ctx, m);

    /*
     * We must expand associations after attributes have been expanded
     * as it relies on the various attribute containers being
     * populated.
     */
    associations_transform::apply(ctx, m);

    /*
     * We leave the type registrar transform for last, but in reality
     * we could probably do it earlier. It only needs leaves
     * (generalisation) and origin (from the pre-assembly chain).
     */
    type_registrar_transform::apply(ctx, m);

    /*
     * Technical spaces must be updated prior to decoration.
     */
    all_technical_spaces_transform::apply(ctx, m);

    /*
     * Must be done after technical spaces are populated.
     */
    decoration_transform::apply(ctx, m);

    /*
     * Render all archetype templates. Must be done after the
     * logic-less template population.
     */
    template_rendering_transform::apply(ctx, m);

    /*
     * These transforms don't have any particular dependencies, other
     * than the model must be merged.
     */
    technical_space_properties_transform::apply(ctx, m);
    // helper_properties_transform::apply(ctx, m);

    /*
     * Ensure the model is valid.
     */
    helpers::post_assembly_validator::validate(idx, m);

    stp.end_chain(m);
}

}
