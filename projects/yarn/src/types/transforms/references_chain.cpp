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
#include "dogen/yarn/types/transforms/context.hpp"
#include "dogen/yarn/types/transforms/exogenous_model_chain.hpp"
#include "dogen/yarn/types/transforms/pre_processing_chain.hpp"
#include "dogen/yarn/types/transforms/reference_paths_extractor.hpp"
#include "dogen/yarn/types/transforms/references_chain.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.transforms.initial_target_chain"));

const std::string non_absolute_target("Target path is not absolute: ");

}

namespace dogen {
namespace yarn {
namespace transforms {

std::unordered_set<languages> references_chain::
obtain_relevant_languages(const intermediate_model& target) {
    std::unordered_set<languages> r;
    r.insert(target.input_language());

    for (const auto ol : target.output_languages())
        r.insert(ol);

    return r;
}

std::list<intermediate_model> references_chain::
transform(const context& ctx, const intermediate_model& target) {
    BOOST_LOG_SEV(lg, debug) << "Executing the reference models chain.";

    /*
     * Obtain the absolute paths to all reference models - system and
     * user.
     */
    const auto rps(reference_paths_extractor::extract(ctx, target));

    /*
     * Obtain all languages that the target model is interested in. We
     * will use these to filter the references - in particular the
     * system models, since these span all languages supported by
     * dogen.
     */
    const auto rl(obtain_relevant_languages(target));

    /*
     * Load each reference model from the reference path, filter and
     * pre-process them.
     */
    std::list<intermediate_model> r;
    for (const auto& rp : rps) {
        /*
         * Obtain the reference model exactly as it was read out from
         * the exogenous transformer.
         */
        auto rm(exogenous_model_chain::transform(rp));

        /*
         * Apply all of the pre-processing transforms to the reference
         * model if its language is part of our set of relevant
         * languages. If not, its no use to us so drop it. Note that
         * this is not ideal for two reasons:
         *
         * - we are still loading system references for our langugage
         *   which may not be needed by the target and references
         *   models.
         *
         * - we still need to do some pre-processing before we can
         *   figure out the model's language. We could use the model's
         *   name as a clue to its language so we don't need to load
         *   it at all.
         *
         * Given that the list of system models is very small at
         * present, we are ignoring these problems.
         */
        if (pre_processing_chain::try_transform(ctx, rl, rm))
            r.push_back(rm);
    }

    BOOST_LOG_SEV(lg, debug) << "Reference models chain executed.";
    return r;
}

} } }
