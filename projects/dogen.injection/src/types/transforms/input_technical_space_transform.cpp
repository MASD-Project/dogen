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
#include "dogen.injection/io/entities/model_io.hpp"
#include "dogen.injection/types/features/input_technical_space.hpp"
#include "dogen.injection/types/transforms/context.hpp"
#include "dogen.injection/types/transforms/input_technical_space_transform.hpp"

namespace {

const std::string transform_id(
    "injection.transforms.input_technical_space_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace dogen::injection::transforms {

void input_technical_space_transform::
apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "technical space transform",
        transform_id, m.name().simple(), *ctx.tracer(), m);

    const auto& fm(*ctx.feature_model());
    using features::input_technical_space;
    const auto fg(input_technical_space::make_feature_group(fm));
    const auto scfg(input_technical_space::make_static_configuration(fg, m));
    m.input_technical_space(scfg.input_technical_space);

    stp.end_transform(m);
}

}
