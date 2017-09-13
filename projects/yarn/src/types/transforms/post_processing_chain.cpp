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
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/io/meta_model/endomodel_io.hpp"
#include "dogen/yarn/types/helpers/indexer.hpp"
#include "dogen/yarn/types/helpers/post_processing_validator.hpp"
#include "dogen/yarn/types/transforms/context.hpp"
#include "dogen/yarn/types/transforms/enumerations_transform.hpp"
#include "dogen/yarn/types/transforms/generalization_transform.hpp"
#include "dogen/yarn/types/transforms/stereotypes_transform.hpp"
#include "dogen/yarn/types/transforms/object_templates_transform.hpp"
#include "dogen/yarn/types/transforms/containment_transform.hpp"
#include "dogen/yarn/types/transforms/orm_transform.hpp"
#include "dogen/yarn/types/transforms/resolver_transform.hpp"
#include "dogen/yarn/types/transforms/attributes_transform.hpp"
#include "dogen/yarn/types/transforms/associations_transform.hpp"
#include "dogen/yarn/types/transforms/generability_transform.hpp"
#include "dogen/yarn/types/transforms/dynamic_transforms_chain.hpp"
#include "dogen/yarn/types/transforms/enablement_transform.hpp"
#include "dogen/yarn/types/transforms/artefact_properties_transform.hpp"
#include "dogen/yarn/types/transforms/meta_naming_transform.hpp"
#include "dogen/yarn/types/transforms/post_processing_chain.hpp"

namespace {

const std::string id("yarn.transforms.post_processing_chain");

using namespace dogen::utility::log;
auto lg(logger_factory(id));

}

namespace dogen {
namespace yarn {
namespace transforms {

void post_processing_chain::
transform(const context& ctx, meta_model::endomodel& em) {
    BOOST_LOG_SEV(lg, debug) << "Executing post-processing chain.";

    /*
     * Enumeration transform must be done after merging as we need the
     * built-in types; these are required in order to find the default
     * enumeration underlying element.
     */
    ctx.prober().start_chain(id, em.name().id(), em);
    enumerations_transform::transform(ctx, em);

    /*
     * Create all indices first as its needed by generalisation. Note
     * that this means generated types (such as visitor etc) are not
     * part of indices, which is not ideal - but for now, its not a
     * major problem.
     */
    const auto idx(helpers::indexer::index(em));

    /*
     * We must expand generalisation relationships before we apply the
     * stereotypes transform because we need to know about leaves
     * before we can generate visitors. Note also that generalisations
     * must be expanded after merging models because we may inherit
     * across models.
     */
    generalization_transform::transform(ctx, idx, em);

    /*
     * Stereotypes transform must be done before object templates
     * because we obtain object template information from the
     * stereotypes.
     */
    stereotypes_transform::transform(ctx, em);
    object_templates_transform::transform(ctx, em);
    containment_transform::transform(ctx, em);

    /*
     * Meta-name transform must be applied after all transforms that
     * inject new meta-model types for the yarn model. At present that
     * is stereotypes and containment transforms. This is also why we
     * cannot apply this transform at the exomodel level.
     */
    meta_naming_transform::transform(ctx, em);

    /*
     * ORM properties must be expanded after stereotypes and
     * containment.
     */
    orm_transform::transform(ctx, em);

    /*
     * Resolution must be done after system elements have been
     * generated (such as visitor, etc) or else it will fail to find
     * any references to those elements. This is done in stereotype
     * expansion.
     */
    resolver_transform::transform(ctx, idx, em);

    /*
     * We can only expand attributes after we've expanded:
     *
     * - object templates, as we rely on all attributes obtained from
     *   instantiating an object template on already being present.
     * - stereotypes, as we need settings such as immutability and
     *   fluency to be populated.
     *  - resolution, else we will copy unresolved attributes.
     */
    attributes_transform::transform(ctx, em);

    /*
     * We must expand associations after attributes have been expanded
     * as it relies on the various attribute containers being
     * populated.
     */
    associations_transform::transform(ctx, em);
    generability_transform::transform(ctx, em);

    /*
     * We can perform dynamic expansion last as no one should be
     * relying on these expansions. These are kernel specific.
     */
    dynamic_transforms_chain::transform(ctx, em);

    /*
     * Expand the artefact properties against the suitable archetype
     * locations. Must be done before enablement transform and any
     * other transform that populates these properties.
     */
    artefact_properties_transform::transform(ctx, em);

    /*
     * Enablement transform must be applied after the external
     * transform chain as it needs to compute enablement for any
     * kernel specific types that might have been added.
     */
    enablement_transform::transform(ctx, em);

    /*
     * Ensure the model is valid.
     */
    helpers::post_processing_validator::validate(idx, em);

    BOOST_LOG_SEV(lg, debug) << "Executed post-processing chain.";
    ctx.prober().end_chain(em);
}

} } }
