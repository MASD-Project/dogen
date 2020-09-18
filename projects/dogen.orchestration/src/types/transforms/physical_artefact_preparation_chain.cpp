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
#include "dogen.text/io/entities/model_set_io.hpp"
#include "dogen.physical/types/transforms/artefact_repository_population_chain.hpp"
#include "dogen.orchestration/types/transforms/physical_artefact_repository_transform.hpp"
#include "dogen.orchestration/types/transforms/context.hpp"
#include "dogen.orchestration/types/transforms/physical_artefact_preparation_chain.hpp"

namespace {

const std::string
transform_id("orchestration.transforms.physical_artefact_preparation_chain");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace dogen::orchestration::transforms {

void physical_artefact_preparation_chain::apply(const context& ctx,
    text::entities::model_set& ms) {
    const auto id(ms.provenance().logical_name().id());
    const auto& tctx(ctx.text_context());
    const auto& tracer(*tctx.tracer());
    tracing::scoped_chain_tracer stp(lg, "physical artefact preparation chain",
        transform_id, id.value(), tracer, ms);

    for (auto& m : ms.models()) {
        /*
         * First we need to extract an artefact repository from each
         * text model. Note that the artefact repository contains
         * pointers to the original artefacts in the text model set.
         */
        auto ar(physical_artefact_repository_transform::apply(tctx, m));

        /*
         * Populate all artefacts.
         */
        using physical::transforms::artefact_repository_population_chain;
        artefact_repository_population_chain::apply(ctx.physical_context(), ar);

        m.has_generatable_types(ar.has_generatable_artefacts());
        m.facet_properties(ar.meta_model_properties().facet_properties());
        m.enabled_archetype_for_element(
            ar.meta_model_properties().enabled_archetype_for_element());
        m.extraction_properties(
            ar.meta_model_properties().extraction_properties());
    }

    stp.end_chain(ms);
}

}
