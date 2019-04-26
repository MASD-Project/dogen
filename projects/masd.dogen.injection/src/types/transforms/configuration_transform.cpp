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
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.variability/types/meta_model/binding_point.hpp"
#include "masd.dogen.variability/types/helpers/configuration_factory.hpp"
#include "masd.dogen.injection/io/meta_model/model_io.hpp"
#include "masd.dogen.injection/types/transforms/context.hpp"
#include "masd.dogen.injection/types/transforms/configuration_transform.hpp"

namespace {

const std::string transform_id("injector.transforms.configuration_transform");

using namespace masd::dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace masd::dogen::injection::transforms {

void configuration_transform::
apply(const transforms::context& ctx, meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg, "annotations transform",
        transform_id, m.name(), *ctx.tracer(), m);

    BOOST_LOG_SEV(lg, debug) << "Transforming model: " << m.name()
                             << "Total elements: " << m.elements().size();

    using bp = variability::meta_model::binding_point;
    variability::helpers::configuration_factory f(
        *ctx.archetype_location_repository(),
        *ctx.feature_model(),
        ctx.compatibility_mode());

    m.configuration(f.make_shared_ptr(m.tagged_values(), bp::global));
    m.configuration()->name().simple(m.name());
    for (auto& e : m.elements()) {
        e.configuration(f.make_shared_ptr(e.tagged_values(), bp::element));
        e.configuration()->name().simple(e.name());

        for (auto& a : e.attributes()) {
            a.configuration(f.make_shared_ptr(a.tagged_values(), bp::property));
            a.configuration()->name().simple(a.name());
        }
    }

    stp.end_transform(m);
    BOOST_LOG_SEV(lg, debug) << "Transformed model.";
}

}
