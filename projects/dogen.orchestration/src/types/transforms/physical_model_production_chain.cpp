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
#include "dogen.injection/types/transforms/model_set_production_chain.hpp"
#include "dogen.logical/types/transforms/model_production_chain.hpp"
#include "dogen.m2t/types/transforms/model_generation_chain.hpp"
#include "dogen.physical/io/entities/model_io.hpp"
#include "dogen.physical/types/transforms/model_production_chain.hpp"
#include "dogen.orchestration/types/transforms/injection_model_set_to_logical_input_model_set_chain.hpp"
#include "dogen.orchestration/types/transforms/logical_model_to_m2t_model_transform.hpp"
#include "dogen.orchestration/types/transforms/context.hpp"
#include "dogen.orchestration/types/transforms/m2t_model_to_physical_model_transform.hpp"
#include "dogen.orchestration/types/transforms/physical_model_production_chain.hpp"

namespace {

const std::string
transform_id("orchestration.transforms.physical_model_production_chain");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace dogen::orchestration::transforms {

physical::entities::model
physical_model_production_chain::apply(const context& ctx,
    const boost::filesystem::path& target) {
    BOOST_LOG_SEV(lg, info) << "Starting physical model production.";
    BOOST_LOG_SEV(lg, debug) << "Target: " << target.generic();

    const auto model_name(target.filename().string());
    const auto& tracer(*ctx.injection_context().tracer());
    tracing::scoped_chain_tracer stp(lg, "physical model production chain",
        transform_id, model_name, tracer);

    /*
     * Obtain the injection model set.
     */
    using injection::transforms::model_set_production_chain;
    const auto ims(model_set_production_chain::apply(
            ctx.injection_context(), target));

    /*
     * Convert the injection model set into a logical model set.
     */
    const auto lmset(injection_model_set_to_logical_input_model_set_chain::
        apply(ctx, ims));

    /*
     * Run all the logical transforms against the model set.
     */
    const auto lms(logical::transforms::model_production_chain::
        apply(ctx.logical_context(), lmset));

    /*
     * Obtain the M2T model set
     */
    auto m2tms(logical_model_to_m2t_model_transform::
        apply(ctx.generation_context(), lms));

    /*
     * Run all the M2T chain against the models.
     */
    m2t::transforms::model_generation_chain::
        apply(ctx.generation_context(), m2tms);

    /*
     * Obtain the physical models.
     */
    const auto pms(transforms::m2t_model_to_physical_model_transform::
        apply(ctx.generation_context(), m2tms));

    /*
     * Run all of the physical transforms against the physical models.
     */
    const auto r(physical::transforms::model_production_chain::
        apply(ctx.physical_context(), pms));

    stp.end_chain(r);
    BOOST_LOG_SEV(lg, info) << "Finished physical model production.";

    return r;
}


}
