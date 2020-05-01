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
#include <ostream>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.utility/types/filesystem/file.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.logical/types/traits.hpp"
#include "dogen.logical/io/entities/output_model_set_io.hpp"
#include "dogen.logical/io/entities/input_model_set_io.hpp"
#include "dogen.logical/types/transforms/context.hpp"
#include "dogen.logical/types/transforms/assembly_chain.hpp"
#include "dogen.logical/types/transforms/post_assembly_chain.hpp"
#include "dogen.logical/types/transforms/pre_assembly_chain.hpp"
#include "dogen.logical/types/transforms/model_production_chain.hpp"

namespace {

const std::string transform_id("logical.transforms.model_production_chain");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace dogen::logical::transforms {

entities::output_model_set
model_production_chain::apply(const context& ctx,
    logical::entities::input_model_set ms) {
    tracing::scoped_chain_tracer stp(lg, "logical model production chain",
        transform_id, ms.target().name().qualified().dot(), *ctx.tracer(), ms);

    /*
     * We start by applying a set of pre-processing transforms to the
     * model set, in order to get it into shape for assembly.
     */
    pre_assembly_chain::apply(ctx, ms);

    /*
     * Setup the output model set. Its name is always the target
     * model. All models in the output model set are just different
     * representations of the target model.
     */
    entities::output_model_set r;
    r.name(ms.target().name());

    /*
     * Note that we've obtained the target given the user options;
     * that is, the target is either a Platform Specific Model (PSM) -
     * in which case input and output technical spaces are one and the
     * same - or it is a Platform Independent Model (PIM), making use
     * of LAM types (the Language Agnostic Model) and thus requiring
     * mapping to a PSM.
     *
     * With regards to the references, note that we are not filtering
     * them at all; we include all references that the user deemed
     * necessary, regardlesss of compatibility with the target
     * technical space. In practice, the reference and target
     * permutations should fall into the one of the following
     * categories:
     *
     * - the target model is a PIM and the reference is also a PIM,
     *   thus both require mapping to a PSM.
     *
     * - the target model is a PIM, and the reference model is a PSM
     *   in a technical space which the user is interested in -
     *   i.e. its one of the target model's output technical spaces.
     *
     * - the target model is a PSM and the reference model is also a
     *   PSM, and they share the same technical space.
     *
     * The below code takes into account all of these permutations,
     * performing mapping as required.
     */
    for (const auto ots : ms.target().output_technical_spaces()) {
        /*
         * Execute the assembly chain for each of the requested output
         * technical spaces.
         */
        auto m(assembly_chain::apply(ctx, ots, ms));

        /*
         * Then apply all of the post-processing transforms to the
         * assembled model.
         */
        post_assembly_chain::apply(ctx, m);
        r.models().push_back(m);
    }

    stp.end_chain(r);
    return r;
}

}
