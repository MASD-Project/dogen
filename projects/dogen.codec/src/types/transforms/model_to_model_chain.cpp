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
#include "dogen.codec/types/entities/model.hpp"
#include "dogen.codec/types/transforms/context.hpp"
#include "dogen.codec/types/transforms/transformation_error.hpp"
#include "dogen.codec/types/transforms/model_production_chain.hpp"
#include "dogen.codec/types/transforms/file_to_artefact_transform.hpp"
#include "dogen.codec/types/transforms/artefact_to_file_transform.hpp"
#include "dogen.codec/types/transforms/artefact_to_model_chain.hpp"
#include "dogen.codec/types/transforms/model_to_artefact_chain.hpp"
#include "dogen.codec/types/transforms/model_to_model_chain.hpp"
#include "dogen.codec/types/transforms/documentation_trimming_transform.hpp"
#include <boost/test/tree/test_unit.hpp>

namespace {

const std::string transform_id("codec.transforms.model_to_model_chain");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string transform_not_supported("Cannot transform into: ");

}

namespace dogen::codec::transforms {

using boost::filesystem::path;

void model_to_model_chain::apply(const transforms::context& ctx,
    const path& src, const path& dst) {
    tracing::scoped_chain_tracer stp(lg, "model to model chain",
        transform_id, *ctx.tracer());

    /*
     * Convert the source path into an artefact. Note that we infer
     * the codec to use from the supplied path.
     */
    const auto src_a(file_to_artefact_transform::apply(ctx, src));

    /*
     * Convert the source artefact into a model.
     */
    auto src_m(artefact_to_model_chain::apply(ctx, src_a));

    /*
     * Trim all the unnecessary whitespace.
     */
    documentation_trimming_transform::apply(ctx, src_m);

    /*
     * Convert the source model into the destination model. Note that
     * we infer the codec to use from the requested path.
     */
    const auto dst_a(model_to_artefact_chain::apply(ctx, dst, src_m));

    /*
     * Write the destination artefact into a file.
     */
    artefact_to_file_transform::apply(ctx, dst_a);
}

}
