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
#include "dogen.physical/types/transforms/transform_exception.hpp"
#include "dogen.physical/types/transforms/global_enablement_transform.hpp"
#include "dogen.physical/types/transforms/local_enablement_transform.hpp"
#include "dogen.physical/types/transforms/formatting_transform.hpp"
#include "dogen.physical/types/transforms/generability_transform.hpp"
#include "dogen.physical/types/transforms/artefact_repository_population_chain.hpp"

namespace {

const std::string transform_id(
    "physical.transforms.write_artefacts_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace dogen::physical::transforms {

void artefact_repository_population_chain::
apply(const context& ctx, entities::artefact_repository& arp) {
    tracing::scoped_chain_tracer stp(lg, "artefact repository population",
        transform_id, arp.identifier(), *ctx.tracer(), arp);

    /*
     * The global enablement transform must be executed before the
     * local one.
     */
    global_enablement_transform::apply(ctx, arp);

    /*
     * Update enablement for all artefacts.
     */
    local_enablement_transform::apply(ctx, arp);

    /*
     * The formatting and generability transforms have no
     * dependencies.
     */
    formatting_transform::apply(ctx, arp);
    generability_transform::apply(ctx, arp);

    stp.end_chain(arp);
}

}
