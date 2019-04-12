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
#include <boost/throw_exception.hpp>
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.variability/types/entry_selector.hpp"
#include "masd.dogen.variability/types/type_repository_selector.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.injection/io/meta_model/model_io.hpp"
#include "masd.dogen.injection/types/traits.hpp"
#include "masd.dogen.injection/io/meta_model/model_io.hpp"
#include "masd.dogen.injection/types/transforms/context.hpp"
#include "masd.dogen.injection/types/transforms/transformation_error.hpp"
#include "masd.dogen.injection/types/transforms/input_technical_space_transform.hpp"

namespace {

const std::string transform_id(
    "injection.transforms.input_technical_space_transform");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace masd::dogen::injection::transforms {

input_technical_space_transform::type_group input_technical_space_transform::
make_type_group(const variability::type_repository& atrp) {
    type_group r;
    const variability::type_repository_selector s(atrp);
    r.input_technical_space = s.select_type_by_name(traits::input_technical_space());
    return r;
}

std::string input_technical_space_transform::
make_input_technical_space(const type_group& tg,
    const variability::annotation& a) {
    const variability::entry_selector s(a);
    return s.get_text_content_or_default(tg.input_technical_space);
}

void input_technical_space_transform::
apply(const context& ctx, meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg, "technical space transform",
        transform_id, m.name(), *ctx.tracer(), m);

    const auto& tg(make_type_group(*ctx.type_repository()));
    const auto ra(m.annotation());
    m.input_technical_space(make_input_technical_space(tg, ra));

    stp.end_transform(m);
}

}
