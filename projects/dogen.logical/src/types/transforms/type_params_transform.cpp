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
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.logical/types/traits.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/transforms/context.hpp"
#include "dogen.logical/types/transforms/type_params_transform.hpp"

namespace {

const std::string transform_id("logical.transforms.type_params_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace dogen::logical::transforms {

void type_params_transform::populate_type_parameters(
    const features::type_parameters::feature_group& fg,
    entities::structural::object& o) {
    using features::type_parameters;
    const auto scfg(type_parameters::make_static_configuration(fg, o));
    auto& tp(o.type_parameters());
    tp.variable_number_of_parameters(scfg.variable_number_of_parameters);
    tp.count(static_cast<unsigned int>(scfg.count));
    tp.always_in_heap(scfg.always_in_heap);
}

void type_params_transform::apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "type params transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    const auto& fm(*ctx.feature_model());
    const auto fg(features::type_parameters::make_feature_group(fm));
    for (auto& pair : m.structural_elements().objects()) {
        auto& o(*pair.second);
        populate_type_parameters(fg, o);
    }
    stp.end_transform(m);
}

}
