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
#include "dogen.codec/types/transforms/context.hpp"
#include "dogen.codec/io/entities/model_set_io.hpp"
#include "dogen.codec/types/transforms/reference_graph_data_transform.hpp"

namespace {

const std::string
transform_id("codec.transforms.reference_graph_data_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace dogen::codec::transforms {

entities::reference_graph_data reference_graph_data_transform::
obtain_references_for_model(const entities::model_set& ms) {
    entities::reference_graph_data r;
    const auto sn(ms.target().name().simple());
    r.root(sn);
    r.edges_per_model()[sn] = ms.target().references();
    for (const auto& m : ms.references())
        r.edges_per_model()[m.name().simple()] = m.references();

    return r;
}

void reference_graph_data_transform::
apply(const context& ctx, entities::model_set& ms) {
    const auto mn(ms.target().name().simple());
    tracing::scoped_transform_tracer stp(lg, "reference graph data",
        transform_id, mn, *ctx.tracer());

    const auto rfm(obtain_references_for_model(ms));
    ms.reference_graph_data(rfm);

    stp.end_transform(ms);
}

}
