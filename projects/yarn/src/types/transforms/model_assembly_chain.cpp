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
#include "dogen/yarn/types/transforms/mapping_transform.hpp"
#include "dogen/yarn/types/transforms/merge_transform.hpp"
#include "dogen/yarn/types/transforms/post_processing_chain.hpp"
#include "dogen/yarn/types/transforms/final_model_transform.hpp"
#include "dogen/yarn/types/transforms/model_assembly_chain.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.transforms.model_assembly_chain"));

}

namespace dogen {
namespace yarn {
namespace transforms {

intermediate_model model_assembly_chain::obtain_merged_model(const context& ctx,
    const languages l, const intermediate_model& target,
    const std::list<intermediate_model>& refs) {

    /*
     * Perform all the language mapping required for target and
     * references.
     */
    const auto mapped_target(mapping_transform::transform(ctx, target, l));

    std::list<intermediate_model> mapped_refs;
    for (const auto& ref : refs) {
        /*
         * We have all references for all the output languages
         * requested by the target model. We are only concerned with
         * l, a member of that set. We need to exclude all models
         * which are not mappable to l such as for example the system
         * models for some of the output languages.
         */
        if (!mapping_transform::is_mappable(ref.input_language(), l)) {
            BOOST_LOG_SEV(lg, debug) << "Reference is not mappable: "
                                     << ref.name().id();
            continue;
        }
        mapped_refs.push_back(mapping_transform::transform(ctx, ref, l));
    }

    /*
     * Merge the mapped models.
     */
    return merge_transform::transform(mapped_target, mapped_refs);
}

model model_assembly_chain::transform(const context& ctx, const languages l,
    const intermediate_model& target,
    const std::list<intermediate_model>& refs) {

    /*
     * First we obtain the merged (and mapped) model.
     */
    auto mm(obtain_merged_model(ctx, l , target, refs));

    /*
     * Then we apply all of the post-processing transforms to the
     * merged model.
     */
    post_processing_chain::transform(ctx, mm);

    /*
     * Lastly, we convert it to the final representation.
     */
    return final_model_transform::transform(mm);
}

} } }
