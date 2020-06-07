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
#include "dogen.physical/io/entities/meta_model_io.hpp"
#include "dogen.physical/types/helpers/template_instantiation_domains_factory.hpp"
#include "dogen.physical/types/transforms/compute_template_instantiation_domains.hpp"

namespace {

const std::string
transform_id("physical.transforms.compute_template_instantiation_domains");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace dogen::physical::transforms {

void compute_template_instantiation_domains::
apply(const physical::transforms::minimal_context& ctx,
    physical::entities::meta_model& mm) {
    tracing::scoped_transform_tracer stp(lg,
        "compute template instantiation domains", transform_id,
        mm.meta_name().simple(), *ctx.tracer(), mm);

    const auto& ina(mm.indexed_names().all());
    using tidf = physical::helpers::template_instantiation_domains_factory;
    const auto tid(tidf::make(ina));
    mm.template_instantiation_domains(tid);

    stp.end_transform(mm);
}

}
