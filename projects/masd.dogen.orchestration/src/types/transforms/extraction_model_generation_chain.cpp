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
#include "masd.dogen.coding/types/transforms/model_generation_chain.hpp"
#include "masd.dogen.generation/types/transforms/context.hpp"
#include "masd.dogen.generation/types/transforms/model_generation_chain.hpp"
#include "masd.dogen.generation/types/transforms/model_to_extraction_model_chain.hpp"
#include "masd.dogen.extraction/io/meta_model/model_io.hpp"
#include "masd.dogen.orchestration/types/transforms/extraction_model_generation_chain.hpp"

namespace {

const std::string
transform_id("orchestration.transforms.extraction_model_generation_chain");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace masd::dogen::orchestration::transforms {

extraction::meta_model::model
extraction_model_generation_chain::
transform(const coding::transforms::context& ctx) {
    const auto model_name(ctx.transform_options().target().filename().string());
    tracing::scoped_chain_tracer stp(lg, "extraction model generation chain",
        transform_id, model_name, ctx.tracer());

    /*
     * Obtain the coding models.
     */
    const auto cms(coding::transforms::model_generation_chain::transform(ctx));

    /*
     * Obtain the generation models
     */
    const auto ibsp = std::unordered_map<
        std::string,
        generation::meta_model::intra_backend_segment_properties>();

    generation::transforms::context ctx2(
        ctx.data_directories(),
        ctx.archetype_location_repository(),
        ctx.type_repository(),
        ctx.formatting_repository(),
        ctx.tracer(),
        ibsp,
        ctx.transform_options().output_directory_path());
    const auto gms(
        generation::transforms::model_generation_chain::transform(ctx2, cms));

    /*
     * Obtain the extraction models.
     */
    using generation::transforms::model_to_extraction_model_chain;
    const auto r(model_to_extraction_model_chain::transform(ctx2, gms));
    stp.end_chain(r);

    return r;
}

}
