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
#include <boost/throw_exception.hpp>
#include "masd.dogen.utility/log/logger.hpp"
#include "masd.dogen.probing/types/scoped_prober.hpp"
#include "masd.dogen.modeling/io/meta_model/endomodel_io.hpp"
#include "masd.dogen.modeling/types/transforms/context.hpp"
#include "masd.dogen.injection/types/transforms/context.hpp"
#include "masd.dogen.injection/types/transforms/model_generation_chain.hpp"
#include "masd.dogen.modeling/types/transforms/external_model_to_endomodel_transform.hpp"
// #include "masd.dogen.modeling/types/transforms/exomodel_generation_chain.hpp"
// #include "masd.dogen.modeling/types/transforms/exomodel_to_endomodel_transform.hpp"
#include "masd.dogen.modeling/types/transforms/endomodel_pre_processing_chain.hpp"
#include "masd.dogen.modeling/types/transforms/initial_target_chain.hpp"

namespace {

const std::string transform_id("yarn.transforms.initial_target_chain");
using namespace masd::dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace masd::dogen::modeling::transforms {

meta_model::endomodel
initial_target_chain::transform(const context& ctx) {
    const auto tp(ctx.transform_options().target());
    const auto model_name(tp.filename().string());
    probing::scoped_chain_prober stp(lg, "initial target chain",
        transform_id, model_name, ctx.prober());

    /*
     * First we obtain the target model in the internal representation
     * of the exogenous model.
     */
    // const auto em(exomodel_generation_chain::transform(ctx, tp));
    const injection::transforms::context ext_ctx(ctx.prober());
    const auto m(injection::transforms::model_generation_chain::transform(ext_ctx, tp));

    /*
     * Then we convert the internal representation of the exogenous
     * model into an endogenous model, ready for further processing.
     */
    // auto r(exomodel_to_endomodel_transform::transform(ctx, em));
    auto r(external_model_to_endomodel_transform::transform(ctx, m));

    /*
     * Next, we set the origin of the target model to target so that
     * further transforms can be applied such as the origin transform.
     */
    r.origin_type(meta_model::origin_types::target);

    /*
     * Finally, we apply all of the pre-processing transforms to the
     * target.
     */
    endomodel_pre_processing_chain::transform(ctx, r);

    stp.end_chain(r);
    return r;
}

}
