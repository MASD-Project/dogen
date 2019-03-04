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
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.utility/types/io/list_io.hpp"
#include "masd.dogen.utility/types/filesystem/file.hpp"
#include "masd.dogen.annotations/io/type_io.hpp"
#include "masd.dogen.annotations/types/entry_selector.hpp"
#include "masd.dogen.annotations/types/type_repository_selector.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.coding/types/traits.hpp"
#include "masd.dogen.coding/io/meta_model/model_io.hpp"
#include "masd.dogen.coding/io/meta_model/languages_io.hpp"
#include "masd.dogen.coding/types/transforms/context.hpp"
#include "masd.dogen.coding/types/transforms/model_assembly_chain.hpp"
#include "masd.dogen.coding/types/transforms/model_post_processing_chain.hpp"
#include "masd.dogen.coding/types/transforms/injection_model_set_to_coding_model_set_transform.hpp"
#include "masd.dogen.coding/types/transforms/model_set_pre_processing_chain.hpp"
#include "masd.dogen.coding/types/transforms/model_generation_chain.hpp"

namespace {

const std::string transform_id("coding.transforms.model_generation_chain");

using namespace masd::dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace masd::dogen::coding::transforms {

std::list<meta_model::model>
model_generation_chain::transform(const context& ctx,
    const injection::meta_model::model_set& ims) {

    /*
     * First we transform the injection model set into a coding model
     * set.
     */
    using inj_transform = injection_model_set_to_coding_model_set_transform;
    auto cms(inj_transform::transform(ctx, ims));

    /*
     * Then we apply a set of post-processing transforms to the model
     * set.
     */
    model_set_pre_processing_chain::transform(ctx, cms);

    /*
     * Note that we've obtained the target given the user options;
     * that is, the target is either a Platform Specific Model (PSM) -
     * in which case the input language and the output language are
     * one and the same - or it is a Platform Independent Model (PIM),
     * making use of LAM types (the Language Agnostic Model) and thus
     * requiring mapping to a PSM.
     *
     * With regards to the references, note that we are not filtering
     * them at all; we include all references that the user deemed
     * necessary, regardlesss of compatibility with the target
     * language. In practice, the reference and target permutations
     * should fall into the one of the following categories:
     *
     * - the target model is a PIM and the reference is also a PIM,
     *   thus both require mapping to a PSM.
     *
     * - the target model is a PIM, and the reference model is a PSM
     *   in a language which the user is interested in - i.e. its one
     *   of the target model's output language.
     *
     * - the target model is a PSM and the reference model is also a
     *   PSM, and they share the same language.
     *
     * The below code takes into account all of these permutations,
     * performing mapping as required.
     */
    std::list<meta_model::model> r;
    for (const auto ol : cms.target().output_languages()) {
        /*
         * Execute the assembly chain for each of the requested output
         * languages.
         */
        auto m(model_assembly_chain::transform(ctx, ol, cms.target(),
                cms.references()));

        /*
         * Then apply all of the post-processing transforms to the
         * assembled model.
         */
        model_post_processing_chain::transform(ctx, m);
        r.push_back(m);
    }
    return r;
}

}
