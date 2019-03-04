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
#include "masd.dogen.coding/io/meta_model/model_io.hpp"
#include "masd.dogen.coding/types/helpers/model_pre_processing_validator.hpp"
#include "masd.dogen.coding/types/transforms/context.hpp"
#include "masd.dogen.coding/types/transforms/modules_transform.hpp"
#include "masd.dogen.coding/types/transforms/origin_transform.hpp"
#include "masd.dogen.coding/types/transforms/language_transform.hpp"
#include "masd.dogen.coding/types/transforms/type_params_transform.hpp"
#include "masd.dogen.coding/types/transforms/parsing_transform.hpp"
#include "masd.dogen.coding/types/transforms/primitives_transform.hpp"
#include "masd.dogen.coding/types/transforms/extraction_properties_transform.hpp"
#include "masd.dogen.coding/types/transforms/model_pre_processing_chain.hpp"

namespace {

const std::string transform_id(
    "coding.transforms.model_pre_processing_chain");

using namespace masd::dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace masd::dogen::coding::transforms {

bool model_pre_processing_chain::is_language_relevant(
    const std::unordered_set<meta_model::languages>& relevant_languages,
    const meta_model::model& em) {
    const auto l(em.input_language());
    const auto i(relevant_languages.find(l));
    if (i == relevant_languages.end()) {
        BOOST_LOG_SEV(lg, warn) << "Reference model language does not"
                                << " match target model language."
                                << " Model: " << em.name().id()
                                << " Language: " << l
                                << " Aborting expansion.";
        return false;
    }

    BOOST_LOG_SEV(lg, debug) << "Reference model language is compatible."
                             << " Model: " << em.name().id()
                             << " Language: " << l;
    return true;
}

void model_pre_processing_chain::
apply_first_set_of_transforms(const context& ctx, meta_model::model& em) {
    /*
     * Module transform must be done before origin and language
     * transforms to get these properties populated on the new
     * modules.
     */
    modules_transform::transform(ctx, em);
    language_transform::transform(ctx, em);
}

void model_pre_processing_chain::
apply_second_set_of_transforms(const context& ctx, meta_model::model& em) {
    /*
     * There are no particular dependencies on the next set of
     * transforms.
     */
    origin_transform::transform(ctx, em);
    type_params_transform::transform(ctx, em);
    parsing_transform::transform(ctx, em);
    extraction_properties_transform::transform(ctx, em);

    /*
     * Primitive expansion requires parsing expansion to populate the
     * underlying elements.
     */
    primitives_transform::transform(ctx, em);

    /*
     * Ensure the model is valid.
     */
    helpers::model_pre_processing_validator::validate(em);
}

void model_pre_processing_chain::
transform(const context& ctx, meta_model::model& em) {
    tracing::scoped_chain_tracer stp(lg, "pre-processing chain",
        transform_id, em.name().id(), *ctx.tracer(), em);

    apply_first_set_of_transforms(ctx, em);
    apply_second_set_of_transforms(ctx, em);

    stp.end_chain(em);
}

bool model_pre_processing_chain::try_transform(const context& ctx,
    const std::unordered_set<meta_model::languages>& relevant_languages,
    meta_model::model& em) {
    tracing::scoped_chain_tracer stp(lg, "pre-processing chain",
        transform_id, em.name().id(), *ctx.tracer(), em);

    /*
     * We must apply the first set of transforms because language
     * expansion is required.
     */

    apply_first_set_of_transforms(ctx, em);

    /*
     * Now we can check the predicate: we only want to process those
     * types which are of the same language as target.
     */
    if (!is_language_relevant(relevant_languages, em)) {
        BOOST_LOG_SEV(lg, debug) << "Finished pre-processing chain.";
        return false;
    }

    apply_second_set_of_transforms(ctx, em);

    stp.end_chain(em);
    BOOST_LOG_SEV(lg, debug) << "Finished pre-processing chain.";
    return true;
}

}
