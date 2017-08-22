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
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/annotations/io/type_io.hpp"
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/yarn/types/traits.hpp"
#include "dogen/yarn/io/meta_model/model_io.hpp"
#include "dogen/yarn/io/meta_model/languages_io.hpp"
#include "dogen/yarn/types/transforms/context.hpp"
#include "dogen/yarn/types/transforms/initial_target_chain.hpp"
#include "dogen/yarn/types/transforms/references_chain.hpp"
#include "dogen/yarn/types/transforms/model_assembly_chain.hpp"
#include "dogen/yarn/types/transforms/endomodel_generation_chain.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.transforms.endomodel_generation_chain"));

}

namespace dogen {
namespace yarn {
namespace transforms {

std::list<meta_model::model>
endomodel_generation_chain::transform(const context& ctx) {
    BOOST_LOG_SEV(lg, info) << "Executing the model generation chain.";

    /*
     * Obtain the initial target, given the user options. The initial
     * target is either a Platform Specific Model (PSM), in which case
     * the input language and the output language are one and the
     * same; or it is a Platform Independent Model (PIM), making use
     * of LAM types (the Language Agnostic Model).
     */
    const auto target(initial_target_chain::transform(ctx));

    /*
     * Obain the references. Note that we are filtering them to only
     * include those which have languages compatible with the target
     * language. These fall into the one of the following categories:
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
     */
    const auto refs(references_chain::transform(ctx, target));

    /*
     * Execute the assembly chain for each of the requested output
     * languages.
     */
    std::list<meta_model::model> r;
    for (const auto ol : target.output_languages())
        r.push_back(model_assembly_chain::transform(ctx, ol, target, refs));

    BOOST_LOG_SEV(lg, info) << "Executed the model generation chain. Result: "
                            << r;

    return r;
}

} } }
