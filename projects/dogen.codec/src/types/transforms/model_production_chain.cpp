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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.codec/io/entities/model_io.hpp"
#include "dogen.codec/types/transforms/context.hpp"
#include "dogen.codec/types/transforms/provenance_transform.hpp"
#include "dogen.codec/types/transforms/input_technical_space_transform.hpp"
#include "dogen.codec/types/transforms/references_transform.hpp"
#include "dogen.codec/types/transforms/configuration_transform.hpp"
#include "dogen.codec/types/transforms/tagged_values_overrides_transform.hpp"
#include "dogen.codec/types/transforms/file_to_artefact_transform.hpp"
#include "dogen.codec/types/transforms/json_artefact_to_model_transform.hpp"
#include "dogen.codec/types/transforms/transformation_error.hpp"
#include "dogen.codec/types/transforms/artefact_to_model_chain.hpp"
#include "dogen.codec/types/transforms/meta_data_transform.hpp"
#include "dogen.codec/types/transforms/documentation_trimming_transform.hpp"
#include "dogen.codec/types/transforms/model_production_chain.hpp"

namespace {

const std::string transform_id("codec.transforms.model_production_chain");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string json_codec_name("json");
const std::string unsupported_codec("No transform are available for codec: ");

}

namespace dogen::codec::transforms {

entities::model model_production_chain::
apply(const context& ctx, const boost::filesystem::path& p) {
    const auto model_name(p.stem().generic_string());
    tracing::scoped_chain_tracer stp(lg, "codec model production", transform_id,
        model_name, *ctx.tracer());

    /*
     * Convert the file into an artefact.
     */
    const auto a(file_to_artefact_transform::apply(ctx, p));

    /*
     * Transform the external model to the internal representation of
     * a codec model.
     */
    auto r(artefact_to_model_chain::apply(ctx, a));

    /*
     * Trim all the unnecessary whitespace.
     */
    documentation_trimming_transform::apply(ctx, r);

    /*
     * Update the provenance properties.
     */
    provenance_transform::apply(ctx, p, r);

    /*
     * Process the variability overrides.
     */
    tagged_values_overrides_transform::apply(ctx, r);

    /*
     * Generate the configuration from tagged values.
     */
    configuration_transform::apply(ctx, r);

    /*
     * Read the input technical space.
     */
    input_technical_space_transform::apply(ctx, r);

    /*
     * Read the model references.
     */
    references_transform::apply(ctx, r);

    /*
     * Read all meta-data for elements and attributes.
     */
    meta_data_transform::apply(ctx, r);

    stp.end_chain(r);
    return r;
}

}
