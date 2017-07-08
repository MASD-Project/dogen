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
#include "dogen/yarn/types/transforms/context.hpp"
#include "dogen/yarn/types/transforms/enumerations_transform.hpp"
#include "dogen/yarn/types/transforms/indexer.hpp"
#include "dogen/yarn/types/transforms/generalization_transform.hpp"
#include "dogen/yarn/types/transforms/stereotypes_transform.hpp"
#include "dogen/yarn/types/transforms/concepts_transform.hpp"
#include "dogen/yarn/types/transforms/containment_transform.hpp"
#include "dogen/yarn/types/transforms/orm_transform.hpp"
#include "dogen/yarn/types/transforms/resolver_transform.hpp"
#include "dogen/yarn/types/transforms/post_processing_chain.hpp"

namespace dogen {
namespace yarn {
namespace transforms {

void post_processing_chain::
transform(const context& ctx, intermediate_model& im) {
    /*
     * Enumeration transform must be done after merging as we need the
     * built-in types; these are required in order to find the default
     * enumeration underlying element.
     */
    enumerations_transform::transform(ctx, im);

    /*
     * Create all indices first as its needed by generalisation. Note
     * that this means generated types (such as visitor etc) are not
     * part of indices, which is not ideal - but for now, its not a
     * major problem.
     */
    const auto idx(indexer::index(im));

    /*
     * We must expand generalisation relationships before we apply the
     * stereotypes transform because we need to know about leaves
     * before we can generate visitors. Note also that generalisations
     * must be expanded after merging models because we may inherit
     * across models.
     */
    generalization_transform::transform(ctx, idx, im);

    /*
     * Stereotypes transform must be done before concepts because we
     * obtain concept information from the stereotypes.
     */
    stereotypes_transform::transform(im);
    concepts_transform::transform(im);
    containment_transform::transform(im);

    /*
     * ORM properties must be expanded after stereotypes and
     * containment.
     */
    orm_transform::expand(ctx, im);

    /*
     * Resolution must be done after system elements have been
     * generated (such as visitor, etc) or else it will fail to find
     * any references to those elements. This is done in stereotype
     * expansion.
     */
    resolver_transform::transform(idx, im);
}

} } }
