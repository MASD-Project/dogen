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
#include "dogen.text/io/entities/model_io.hpp"
#include "dogen.physical/io/entities/artefact_repository_io.hpp"
#include "dogen.orchestration/types/transforms/physical_artefact_repository_transform.hpp"

namespace {

const std::string
transform_id("orchestration.transforms.physical_artefact_repository_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace dogen::orchestration::transforms {

physical::entities::artefact_repository
physical_artefact_repository_transform::
apply(const text::transforms::context& ctx, const text::entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "text model production chain",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    physical::entities::artefact_repository r;

    stp.end_transform(r);
    return r;
}

}
