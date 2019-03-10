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
#include "masd.dogen.extraction/io/meta_model/model_io.hpp"
#include "masd.dogen.extraction/types/transforms/code_generation_chain.hpp"
#include "masd.dogen.orchestration/types/transforms/context.hpp"
#include "masd.dogen.orchestration/types/transforms/extraction_model_production_chain.hpp"
#include "masd.dogen.orchestration/types/transforms/code_generation_chain.hpp"

namespace {

const std::string
transform_id("orchestration.transforms.code_generation_chain");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace masd::dogen::orchestration::transforms {

void code_generation_chain::transform(const context& ctx,
    const boost::filesystem::path& target) {
    BOOST_LOG_SEV(lg, info) << "Starting code generation.";
    BOOST_LOG_SEV(lg, debug) << "Target: " << target.generic();

    const auto model_name(target.filename().string());
    const auto& tracer(*ctx.injection_context().tracer());
    tracing::scoped_chain_tracer stp(lg, "code generation chain",
        transform_id, model_name, tracer);

    /*
     * Obtain the extraction model.
     */
    using transforms::extraction_model_production_chain;
    const auto m(extraction_model_production_chain::transform(ctx, target));

    /*
     * Runn all of the extraction transforms against the extraction models.
     */
    using extraction::transforms::code_generation_chain;
    code_generation_chain::apply(ctx.extraction_context(), m);

    stp.end_chain(m);

    BOOST_LOG_SEV(lg, info) << "Finished code generation.";
}

}
