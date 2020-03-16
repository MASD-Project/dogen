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
#include "dogen.logical/types/meta_model/structural/module.hpp"
#include "dogen.logical/types/meta_model/structural/object.hpp"
#include "dogen.logical/types/meta_model/structural/builtin.hpp"
#include "dogen.logical/types/meta_model/element.hpp"
#include "dogen.logical/types/meta_model/structural/exception.hpp"
#include "dogen.logical/types/meta_model/structural/primitive.hpp"
#include "dogen.logical/types/meta_model/structural/enumeration.hpp"
#include "dogen.logical/types/meta_model/structural/object_template.hpp"
#include "dogen.generation/io/meta_model/model_io.hpp"
#include "dogen.generation/types/transforms/generability_transform.hpp"

namespace {

const std::string
transform_id("generation.transforms.generability_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace dogen::generation::transforms {

bool generability_transform::
is_generatable(const logical::meta_model::element& e) {
    const auto ot(e.origin_type());
    return ot == logical::meta_model::origin_types::target;
}

bool generability_transform::
has_generatable_types(const meta_model::model& m) {
    for (const auto ptr : m.elements()) {
        if (is_generatable(*ptr))
            return true;
    }

    return false;
}

void generability_transform::
apply(const context& ctx, meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg, "generability transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);
    m.has_generatable_types(has_generatable_types(m));
    stp.end_transform(m);
}

}
