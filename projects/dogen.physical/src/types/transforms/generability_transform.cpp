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
#include "dogen.physical/io/entities/artefact_repository_io.hpp"
#include "dogen.physical/types/transforms/generability_transform.hpp"

namespace {

const std::string
transform_id("physical.transforms.generability_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace dogen::physical::transforms {

void generability_transform::
apply(const context& ctx, entities::artefact_repository& ar) {
    tracing::scoped_transform_tracer stp(lg, "generability",
        transform_id, ar.identifier(), *ctx.tracer(), ar);

    ar.has_generatable_artefacts(false);
    for(const auto& pair : ar.artefact_sets_by_logical_id()) {
        const auto& as(pair.second);
        if (as.is_generatable()) {
            ar.has_generatable_artefacts(true);
            break;
        }
    }

    stp.end_transform(ar);
}

}