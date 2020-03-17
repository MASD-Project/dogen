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
#include "dogen.generation/types/transforms/model_generation_chain.hpp"
#include "dogen.generation/types/transforms/model_to_extraction_model_chain.hpp"
#include "dogen.physical/io/entities/model_io.hpp"
#include "dogen.physical/types/transforms/model_production_chain.hpp"
#include "dogen.orchestration/types/transforms/injection_model_set_to_assets_model_set_chain.hpp"
#include "dogen.orchestration/types/transforms/assets_model_to_generation_model_transform.hpp"
#include "dogen.orchestration/types/transforms/context.hpp"
#include "dogen.orchestration/types/transforms/extraction_model_production_chain.hpp"

namespace {

const std::string
transform_id("engine.transforms.extraction_model_production_chain");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace dogen::orchestration::transforms {

physical::entities::model
extraction_model_production_chain::apply(const context& ctx,
    const boost::filesystem::path& target) {
    BOOST_LOG_SEV(lg, info) << "Starting extraction model production.";
    BOOST_LOG_SEV(lg, debug) << "Target: " << target.generic();

    const auto model_name(target.filename().string());
    const auto& tracer(*ctx.injection_context().tracer());
    tracing::scoped_chain_tracer stp(lg, "extraction model production chain",
        transform_id, model_name, tracer);

    /*
     * Obtain the injection model set.
     */
    using injection::transforms::model_set_production_chain;
    const auto ims(model_set_production_chain::apply(
            ctx.injection_context(), target));

    /*
     * Convert the injection model set into a assets model set.
     */
    const auto cmset(injection_model_set_to_assets_model_set_chain::
        apply(ctx, ims));

    /*
     * Run all the assets transforms against the model set.
     */
    const auto cms(logical::transforms::model_production_chain::
        apply(ctx.assets_context(), cmset));

    /*
     * Obtain the generation model set.
     */
    auto gms(transforms::assets_model_to_generation_model_transform::
        apply(ctx.generation_context(), cms));

    /*
     * Run all the generation transforms agains the generation models.
     */
    generation::transforms::model_generation_chain::
        apply(ctx.generation_context(), gms);

    /*
     * Obtain the extraction models.
     */
    using generation::transforms::model_to_extraction_model_chain;
    auto r(model_to_extraction_model_chain::apply(
            ctx.generation_context(), gms));

    /*
     * Runn all of the extraction transforms against the extraction models.
     */
    physical::transforms::model_production_chain::
        apply(ctx.extraction_context(), r);

    stp.end_chain(r);
    BOOST_LOG_SEV(lg, info) << "Finished extraction model production.";

    return r;
}


}
