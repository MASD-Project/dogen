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
#include "dogen/utility/io/list_io.hpp"
#include "dogen.probing/types/scoped_prober.hpp"
#include "dogen/yarn/io/meta_model/model_io.hpp"
#include "dogen/yarn/types/transforms/endomodel_generation_chain.hpp"
#include "dogen/yarn/types/transforms/endomodel_to_model_transform.hpp"
#include "dogen/yarn/types/transforms/model_post_processing_chain.hpp"
#include "dogen/yarn/types/transforms/model_generation_chain.hpp"

namespace {

const std::string transform_id("yarn.transforms.model_generation_chain");
using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace dogen {
namespace yarn {
namespace transforms {

std::list<meta_model::model>
model_generation_chain::transform(const context& ctx) {
    probing::scoped_chain_prober stp(lg, "model generation chain",
        transform_id, ctx.prober());

    /*
     * First we generate the endomodels.
     */
    const auto endomodels(endomodel_generation_chain::transform(ctx));

    /*
     * We then we convert them to their final representation.
     */
    auto r(endomodel_to_model_transform::transform(ctx, endomodels));

    /*
     * Finally, we apply all of the post-processing transforms to the
     * model.
     */
    for (auto& m : r)
        model_post_processing_chain::transform(ctx, m);

    stp.end_chain(r);
    return r;
}

} } }
