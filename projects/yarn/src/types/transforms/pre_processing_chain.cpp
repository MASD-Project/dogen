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
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/io/languages_io.hpp"
#include "dogen/yarn/types/transforms/annotations_transform.hpp"
#include "dogen/yarn/types/transforms/modules_transform.hpp"
#include "dogen/yarn/types/transforms/origin_transform.hpp"
#include "dogen/yarn/types/transforms/language_transform.hpp"
#include "dogen/yarn/types/transforms/type_params_transform.hpp"
#include "dogen/yarn/types/transforms/parsing_transform.hpp"
#include "dogen/yarn/types/transforms/primitives_transform.hpp"
#include "dogen/yarn/types/transforms/first_stage_validator.hpp"
#include "dogen/yarn/types/transforms/pre_processing_chain.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.transforms.pre_processing_chain"));

}

namespace dogen {
namespace yarn {
namespace transforms {

bool pre_processing_chain::are_languages_compatible(
    const languages target_language, intermediate_model& im) {

    const auto l(im.input_language());
    if (l == target_language) {
        BOOST_LOG_SEV(lg, warn) << "Reference model language does not"
                                << " match target model language."
                                << " Model: " << im.name().id()
                                << " Language: " << l
                                << " Aborting expansion.";
        return false;
    }

    BOOST_LOG_SEV(lg, debug) << "Reference model language is compatible."
                             << " Model: " << im.name().id()
                             << " Language: " << l;
    return true;
}

void pre_processing_chain::
apply_first_set_of_transforms(const context& ctx, intermediate_model& im) {
    /*
     * We must transform annotations before we transform modules to
     * ensure the root module is populated with entries before being
     * copied over.
     */
    annotations_transform::transform(ctx, im);

    /*
     * Module transform must be done before origin and language
     * transforms to get these properties populated on the new
     * modules.
     */
    modules_transform::transform(im);
    language_transform::transform(ctx, im);
}

void pre_processing_chain::
apply_second_set_of_transforms(const context& ctx, intermediate_model& im) {
    /*
     * There are no particular dependencies on the next set of
     * transforms.
     */
    origin_transform::transform(ctx, im);
    type_params_transform::transform(ctx, im);
    parsing_transform::transform(ctx, im);

    /*
     * Primitive expansion requires parsing expansion to populate the
     * underlying elements.
     */
    primitives_transform::transform(ctx, im);

    /*
     * Ensure the model is valid.
     */
    first_stage_validator::validate(im);
}

void pre_processing_chain::
transform(const context& ctx, intermediate_model& im) {
    apply_first_set_of_transforms(ctx, im);
    apply_second_set_of_transforms(ctx, im);
}

bool pre_processing_chain::try_transform(const context& ctx,
    const languages target_language, intermediate_model& im) {
    /*
     * We must apply the first set of transforms because language
     * expansion is required; we only want to process those types
     * which are of the same language as target.
     */
    apply_first_set_of_transforms(ctx, im);
    if (!are_languages_compatible(target_language, im))
        return false;

    apply_second_set_of_transforms(ctx, im);
    return true;
}

} } }
