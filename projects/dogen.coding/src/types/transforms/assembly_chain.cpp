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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.coding/io/meta_model/model_io.hpp"
#include "dogen.coding/types/transforms/context.hpp"
#include "dogen.coding/types/transforms/mapping_transform.hpp"
#include "dogen.coding/types/transforms/merge_transform.hpp"
#include "dogen.coding/types/transforms/assembly_chain.hpp"

namespace {

const std::string transform_id("coding.transforms.assembly_chain");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace dogen::coding::transforms {

meta_model::model assembly_chain::apply(const context& ctx,
    const meta_model::technical_space ts, const meta_model::model& target,
    const std::list<meta_model::model>& refs) {
    tracing::scoped_chain_tracer stp(lg, "model assembly chain",
        transform_id, target.name().qualified().dot(), *ctx.tracer());

    /*
     * Perform all the technical space mapping required for the target
     * model.
     */
    const auto mapped_target(mapping_transform::apply(ctx, target, ts));

    /*
     * Now do the same for the references.
     */
    std::list<meta_model::model> mapped_refs;
    for (const auto& ref : refs) {
        /*
         * Note that we have all references for all the output
         * technical spaces requested by the target model. We are only
         * concerned with those that require mapping into ts - i.e., a
         * subset of that set. We need to exclude all models which are
         * not mappable to ts, such as for example the system models.
         */
        if (!mapping_transform::is_mappable(ref.input_technical_space(), ts)) {
            BOOST_LOG_SEV(lg, debug) << "Skipping reference: "
                                     << ref.name().qualified().dot();
            continue;
        }
        mapped_refs.push_back(mapping_transform::apply(ctx, ref, ts));
    }

    /*
     * Merge the mapped models.
     */
    const auto r(merge_transform::apply(ctx, mapped_target, mapped_refs));

    stp.end_chain(r);
    return r;
}

}
