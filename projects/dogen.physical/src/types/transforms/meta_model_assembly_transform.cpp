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
#include <boost/make_shared.hpp>
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/shared_ptr_io.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.physical/io/entities/backend_io.hpp"
#include "dogen.physical/io/entities/meta_model_io.hpp"
#include "dogen.identification/types/helpers/physical_meta_name_builder.hpp"
#include "dogen.physical/types/transforms/meta_model_assembly_transform.hpp"

namespace {

const std::string
transform_id("physical.transforms.meta_model_assembly_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace dogen::physical::transforms {

boost::shared_ptr<physical::entities::meta_model>
meta_model_assembly_transform::
apply(const physical::transforms::minimal_context& ctx,
    const std::list<entities::backend>& bes) {
    tracing::scoped_transform_tracer stp(lg, "meta model assembly chain",
        transform_id, "physical-meta-model", *ctx.tracer(), bes);

    using physical::entities::meta_model;
    auto r(boost::make_shared<meta_model>());

    identification::helpers::physical_meta_name_builder b;
    b.meta_model("masd");

    for (const auto& be : bes)
        r->backends().push_back(be);

    stp.end_transform(r);
    return r;
}

}
