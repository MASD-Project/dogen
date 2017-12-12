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
#include "dogen.utility/log/logger.hpp"
#include "dogen.annotations/io/type_io.hpp"
#include "dogen.annotations/types/entry_selector.hpp"
#include "dogen.annotations/types/type_repository_selector.hpp"
#include "dogen.probing/types/scoped_prober.hpp"
#include "dogen.yarn/types/traits.hpp"
#include "dogen.yarn/io/meta_model/endomodel_io.hpp"
#include "dogen.yarn/types/transforms/context.hpp"
#include "dogen.yarn/types/transforms/transformation_error.hpp"
#include "dogen.yarn/types/transforms/primitives_transform.hpp"

namespace {

const std::string transform_id("yarn.transforms.primitives_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace dogen {
namespace yarn {
namespace transforms {

std::ostream&
operator<<(std::ostream& s, const primitives_transform::type_group& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::yarn::primitives_transform::type_group\""
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
transform(const context& ctx, meta_model::endomodel& em) {
    probing::scoped_transform_prober stp(lg, "primitives transform",
        transform_id, em.name().id(), ctx.prober(), em);

    const auto tg(make_type_group(ctx.type_repository()));
    for (auto& pair : em.primitives()) {
        const auto& id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Transforming: " << id;

        auto& p(*pair.second);
        populate_from_annotations(tg, p);
    }

    stp.end_transform(em);
}

} } }
