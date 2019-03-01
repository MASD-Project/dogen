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
#include <ostream>
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.annotations/io/type_io.hpp"
#include "masd.dogen.annotations/types/entry_selector.hpp"
#include "masd.dogen.annotations/types/type_repository_selector.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.coding/types/traits.hpp"
#include "masd.dogen.coding/io/meta_model/model_io.hpp"
#include "masd.dogen.coding/types/transforms/context.hpp"
#include "masd.dogen.coding/types/transforms/transformation_error.hpp"
#include "masd.dogen.coding/types/transforms/primitives_transform.hpp"

namespace {

const std::string transform_id("coding.transforms.primitives_transform");

using namespace masd::dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace masd::dogen::coding::transforms {

std::ostream&
operator<<(std::ostream& s, const primitives_transform::type_group& v) {
    s << " { "
      << "\"__type__\": "
      << "\"masd::dogen::coding::primitives_transform::type_group\""
      << ", " << "\"is_nullable\": " << v.is_nullable << ", "
      << "\"use_type_aliasing\": " << v.use_type_aliasing
      << " }";

    return s;
}

primitives_transform::type_group primitives_transform::
make_type_group(const annotations::type_repository& atrp) {
    BOOST_LOG_SEV(lg, debug) << "Creating type group.";

    type_group r;

    const annotations::type_repository_selector s(atrp);

    const auto in(traits::primitive::is_nullable());
    r.is_nullable = s.select_type_by_name(in);

    const auto uta(traits::primitive::use_type_aliasing());
    r.use_type_aliasing = s.select_type_by_name(uta);

    BOOST_LOG_SEV(lg, debug) << "Created type group. Result" << r;
    return r;
}

void primitives_transform::
populate_from_annotations(const type_group& tg, meta_model::primitive& p) {
    const auto& a(p.annotation());
    const annotations::entry_selector s(a);
    p.is_nullable(s.get_boolean_content_or_default(tg.is_nullable));
    p.use_type_aliasing(s.get_boolean_content_or_default(tg.use_type_aliasing));
}

void primitives_transform::
transform(const context& ctx, meta_model::model& em) {
    tracing::scoped_transform_tracer stp(lg, "primitives transform",
        transform_id, em.name().id(), ctx.tracer(), em);

    const auto tg(make_type_group(ctx.type_repository()));
    for (auto& pair : em.primitives()) {
        const auto& id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Transforming: " << id;

        auto& p(*pair.second);
        populate_from_annotations(tg, p);
    }

    stp.end_transform(em);
}

}
