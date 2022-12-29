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
#include "dogen.codec/types/transforms/org_artefact_to_model_transform.hpp"
#include "dogen.codec/types/transforms/transformation_error.hpp"
#include "dogen.codec/types/transforms/artefact_to_model_chain.hpp"

namespace {

const std::string transform_id("codec.transforms.artefact_to_model_chain");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string org_codec_name("org");
const std::string unsupported_codec("No transform are available for codec: ");

}

namespace dogen::codec::transforms {

entities::model artefact_to_model_chain::
apply(const context& ctx, const entities::artefact& a) {
    const auto model_name(a.path().stem().generic_string());
    tracing::scoped_chain_tracer stp(lg, "artefact to model",
        transform_id, model_name, *ctx.tracer());

    if (a.codec_name() == org_codec_name) {
        const auto r(org_artefact_to_model_transform::apply(ctx, a));
        stp.end_chain(r);
        return r;
    }

    BOOST_LOG_SEV(lg, error) << unsupported_codec << a.codec_name();
    BOOST_THROW_EXCEPTION(
        transformation_error(unsupported_codec + a.codec_name()));
}

}
