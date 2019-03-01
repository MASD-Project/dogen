/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
`` * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#include "masd.dogen.coding/io/meta_model/model_io.hpp"
#include "masd.dogen.coding/types/transforms/context.hpp"
#include "masd.dogen.coding/types/transforms/mapping_transform.hpp"
#include "masd.dogen.coding/types/transforms/merge_transform.hpp"
#include "masd.dogen.coding/types/transforms/model_assembly_chain.hpp"

namespace {

const std::string transform_id("coding.transforms.model_assembly_chain");

using namespace masd::dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace masd::dogen::coding::transforms {

meta_model::model model_assembly_chain::transform(const context& ctx,
    const meta_model::languages l, const meta_model::model& target,
    const std::list<meta_model::model>& refs) {
    tracing::scoped_chain_tracer stp(lg, "model assembly chain",
        transform_id, target.name().id(), ctx.tracer());

    /*
     * Perform all the language mapping required for target and
     * references.
     */
    const auto mapped_target(mapping_transform::transform(ctx, target, l));

    /*
     * Now do the same for the references.
     */
    std::list<meta_model::model> mapped_refs;
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
    const auto r(merge_transform::transform(ctx, mapped_target, mapped_refs));

    stp.end_chain(r);
    return r;
}

}
