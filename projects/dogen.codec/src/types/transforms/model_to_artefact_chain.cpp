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
#include "dogen.codec/io/entities/artefact_io.hpp"
#include "dogen.codec/types/transforms/model_to_json_artefact_transform.hpp"
#include "dogen.codec/types/transforms/model_to_org_artefact_transform.hpp"
#include "dogen.codec/types/transforms/transformation_error.hpp"
#include "dogen.codec/types/transforms/model_to_artefact_chain.hpp"

namespace {

const std::string transform_id("codec.transforms.model_to_artefact_chain");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string json_codec_name("json");
const std::string org_codec_name("org");

const std::string unsupported_codec("No transform are available for codec: ");

}

namespace dogen::codec::transforms {

entities::artefact model_to_artefact_chain::
apply(const context& ctx, const std::string& codec_name,
    const boost::filesystem::path& p, const entities::model& m) {
    tracing::scoped_chain_tracer stp(lg, "model to artefact",
        transform_id, m.name().qualified(), *ctx.tracer());

    if (codec_name == json_codec_name) {
        const auto r(model_to_json_artefact_transform::apply(ctx, p, m));
        stp.end_chain(r);
        return r;
    } else if (codec_name == org_codec_name) {
        const auto r(model_to_org_artefact_transform::apply(ctx, p, m));
        stp.end_chain(r);
        return r;
    }

    BOOST_LOG_SEV(lg, error) << unsupported_codec << codec_name;
    BOOST_THROW_EXCEPTION(transformation_error(unsupported_codec + codec_name));
}

}
