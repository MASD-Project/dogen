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
#include "dogen/yarn/types/transforms/parsing_transform.hpp"
#include "dogen/yarn/types/transforms/type_params_transform.hpp"
#include "dogen/yarn/types/transforms/language_transform.hpp"
#include "dogen/yarn/types/transforms/origin_transform.hpp"
#include "dogen/yarn/types/transforms/modules_transform.hpp"
#include "dogen/yarn/types/transforms/annotations_transform.hpp"
#include "dogen/yarn/types/transforms/pre_processing_chain.hpp"

namespace dogen {
namespace yarn {
namespace transforms {

void pre_processing_chain::
transform(const context& ctx, intermediate_model& im) {
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
    origin_transform::transform(ctx, im);
    language_transform::transform(ctx, im);

    /*
     * There are no particular dependencies on the next set of
     * transforms.
     */
    type_params_transform::transform(ctx, im);
    parsing_transform::transform(ctx, im);
}

} } }
