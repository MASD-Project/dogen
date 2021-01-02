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
#include "dogen.codec/io/entities/artefact_io.hpp"
#include "dogen.codec/types/transforms/artefact_to_model_chain.hpp"
#include "dogen.codec/types/transforms/model_to_artefact_chain.hpp"
#include "dogen.codec/types/transforms/documentation_trimming_transform.hpp"
#include "dogen.codec/types/transforms/artefact_to_artefact_chain.hpp"

namespace {

const std::string transform_id("codec.transforms.artefact_to_artefact_chain");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace dogen::codec::transforms {

entities::artefact artefact_to_artefact_chain::
apply(const transforms::context& ctx, const entities::artefact& input,
    const boost::filesystem::path& output_path) {
    const auto id(input.path().filename().generic_string());
    tracing::scoped_chain_tracer stp(lg, "artefact to artefact",
        transform_id, id, *ctx.tracer(), input);

    /*
     * Convert the source artefact into a model.
     */
    auto input_model(artefact_to_model_chain::apply(ctx, input));

    /*
     * Trim all the unnecessary whitespace.
     */
    documentation_trimming_transform::apply(ctx, input_model);

    /*
     * Convert the source model into the destination model. Note that
     * we infer the codec to use from the requested path.
     */
    const auto r(model_to_artefact_chain::apply(ctx, output_path, input_model));

    stp.end_chain(r);
    return r;
}

}
