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
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/shared_ptr_io.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.physical/io/entities/backend_io.hpp"
#include "dogen.physical/io/entities/meta_model_io.hpp"
#include "dogen.physical/types/transforms/meta_model_assembly_transform.hpp"
#include "dogen.physical/types/transforms/compute_name_indices_transform.hpp"
#include "dogen.physical/types/transforms/compute_template_instantiation_domains.hpp"
#include "dogen.physical/types/helpers/meta_model_validator.hpp"
#include "dogen.physical/types/transforms/meta_model_production_chain.hpp"

namespace {

const std::string
transform_id("physical.transforms.meta_model_production_chain");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace dogen::physical::transforms {

boost::shared_ptr<physical::entities::meta_model>
meta_model_production_chain::
apply(const physical::transforms::minimal_context& ctx,
    const std::list<entities::backend>& bes) {
    tracing::scoped_chain_tracer stp(lg, "meta model production chain",
        transform_id, "physical-meta-model", *ctx.tracer(), bes);


    /*
     * Assemble the parts into a meta-model.
     */
    auto r(meta_model_assembly_transform::apply(ctx, bes));

    /*
     * Compute all meta-name indices.
     */
    compute_name_indices_transform::apply(ctx, *r);

    /*
     * Compute the template instantiation domains.
     */
    compute_template_instantiation_domains::apply(ctx, *r);

    /*
     * Validate the generated model.
     */
    helpers::meta_model_validator::validate(*r);

    stp.end_chain(*r);

    return r;
}

}
