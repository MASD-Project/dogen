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
#include "dogen.physical/types/transforms/context.hpp"
#include "dogen.physical/io/entities/model_io.hpp"
#include "dogen.physical/io/entities/model_set_io.hpp"
#include "dogen.physical/types/transforms/merge_transform.hpp"

namespace {

const std::string transform_id("physical.transforms.merge_transform");
using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace dogen::physical::transforms {

entities::model merge_transform::apply(const physical::transforms::context& ctx,
    const physical::entities::model_set& ms) {
    tracing::scoped_chain_tracer stp(lg, "merge transform", transform_id,
        ms.name().simple(), *ctx.tracer(), ms);

    bool first(true);
    physical::entities::model r;
    for (const auto& m : ms.models()) {
        /*
         * Bit of a hack: we initialise these properties from the
         * first model in the list. They should all be identical
         * anyway.
         */
        if (first) {
            r.logical_name(m.logical_name());
            r.origin_sha1_hash(m.origin_sha1_hash());
            r.name(m.name());
            r.configuration(m.configuration());
            first = false;
        }

        /*
         * Now we copy the stuff that actually matters.
         */
        for (const auto& a : m.artefacts())
            r.artefacts().push_back(a);

        for (const auto& md : m.managed_directories())
            r.managed_directories().push_back(md);
    }

    stp.end_chain(r);
    return r;
}

}
