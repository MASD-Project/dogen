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
#include "masd.dogen.annotations/types/entry_selector.hpp"
#include "masd.dogen.annotations/types/type_repository_selector.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.injection/io/meta_model/model_io.hpp"
#include "masd.dogen.injection/types/traits.hpp"
#include "masd.dogen.injection/io/meta_model/model_io.hpp"
#include "masd.dogen.injection/types/transforms/context.hpp"
#include "masd.dogen.injection/types/transforms/transformation_error.hpp"
#include "masd.dogen.injection/types/transforms/language_transform.hpp"

namespace {

const std::string transform_id("injection.transforms.language_transform");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace masd::dogen::injection::transforms {

language_transform::type_group
language_transform::make_type_group(const annotations::type_repository& atrp) {
    type_group r;
    const annotations::type_repository_selector s(atrp);
    r.input_language = s.select_type_by_name(traits::input_language());
    return r;
}

std::string language_transform::make_input_language(const type_group& tg,
    const annotations::annotation& a) {
    const annotations::entry_selector s(a);
    return s.get_text_content_or_default(tg.input_language);
}

void language_transform::transform(const context& ctx, meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg, "referencestransform",
        transform_id, m.name(), ctx.tracer(), m);

    const auto tg(make_type_group(ctx.type_repository()));
    const auto ra(m.annotation());
    const auto l(make_input_language(tg, ra));
    m.language(l);

    stp.end_transform(m);
}

}
