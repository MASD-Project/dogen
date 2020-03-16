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
#include <unordered_map>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.logical/types/entities/technical_space.hpp"
#include "dogen.logical/hash/entities/technical_space_hash.hpp"
#include "dogen.logical/io/entities/technical_space_io.hpp"
#include "dogen.generation/io/entities/model_io.hpp"
#include "dogen.generation/types/transforms/technical_space_transform.hpp"

namespace {

const std::string
transform_id("generation.transforms.technical_space_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace dogen::generation::transforms {

void technical_space_transform::
apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "technical space transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    std::unordered_set<logical::entities::technical_space> ats;
    const auto its(m.input_technical_space());
    ats.insert(its);
    BOOST_LOG_SEV(lg, trace) << "Input technical space: " << its;

    const auto ots(m.output_technical_space());
    ats.insert(ots);
    BOOST_LOG_SEV(lg, trace) << "Output technical space: " << ots;

    /*
     * FIXME: hackery for ODB options, XML and CMake.
     */
    using namespace logical::entities;
    ats.insert(technical_space::odb);
    ats.insert(technical_space::xml);
    ats.insert(technical_space::cmake);

    for (const auto& ptr : m.elements()) {
        const auto id(ptr->name().qualified().dot());
        const auto ts(ptr->intrinsic_technical_space());

        /*
         * Skip agnostic as it is an abstract technical space.
         */
        if (ts == technical_space::agnostic)
            continue;

        const auto i(ats.insert(ts));
        if (i.second) {
            BOOST_LOG_SEV(lg, trace) << "Inserted technical space: " << ts
                                     << " from element: " << id;
        }
    }

    m.all_technical_spaces(ats);
    stp.end_transform(m);
}

}
