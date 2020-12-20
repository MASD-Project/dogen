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
#include "dogen.org/types/transforms/string_to_document_transform.hpp"
#include "dogen.codec/types/transforms/org_artefact_to_model_transform.hpp"

namespace {

const std::string
transform_id("codec.transforms.org_artefact_to_model_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace dogen::codec::transforms {

entities::model org_artefact_to_model_transform::
apply(const transforms::context& ctx, const entities::artefact& a) {
    const auto fn(a.path().filename().stem().generic_string());
    const auto t(ctx.tracer());
    tracing::scoped_transform_tracer stp(lg, "org artefact to model",
        transform_id, fn, *t, a);

    BOOST_LOG_SEV(lg, debug) << "Processing org-mode document.";
    using org::transforms::string_to_document_transform;
    const auto d(string_to_document_transform::apply(t, a.content()));

    BOOST_LOG_SEV(lg, debug) << "Processed org-mode document.";
    entities::model r;
    stp.end_transform(r);
    return r;
}

}
