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
#include "masd.dogen.injection/io/meta_model/model_io.hpp"
#include "masd.dogen.injection/types/transforms/context.hpp"
#include "masd.dogen.injection/types/transforms/annotations_transform.hpp"

namespace {

const std::string transform_id("injector.transforms.annotations_transform");

using namespace masd::dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace masd::dogen::injection::transforms {

void annotations_transform::apply(const transforms::context& ctx,
    meta_model::model& m) {

    tracing::scoped_transform_tracer stp(lg, "annotations transform",
        transform_id, m.name(), *ctx.tracer(), m);

    BOOST_LOG_SEV(lg, debug) << "Transforming model: " << m.name()
                             << "Total elements: " << m.elements().size();

    const auto& f(*ctx.annotation_factory());
    using masd::dogen::variability::scope_types;
    m.annotation(f.make(m.tagged_values(), scope_types::root_module));

    for (auto& e : m.elements()) {
        e.annotation(f.make(e.tagged_values(), scope_types::entity));

        for (auto& a : e.attributes())
            a.annotation(f.make(a.tagged_values(), scope_types::property));
    }

    stp.end_transform(m);
    BOOST_LOG_SEV(lg, debug) << "Transformed model.";

}

}
