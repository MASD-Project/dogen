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
#include "masd.dogen.coding/types/meta_model/modeline_group.hpp"
#include "masd.dogen.generation/types/traits.hpp"
#include "masd.dogen.generation/io/meta_model/model_io.hpp"
#include "masd.dogen.generation/types/transforms/transformation_error.hpp"
#include "masd.dogen.generation/types/helpers/decoration_repository_factory.hpp"
#include "masd.dogen.generation/types/transforms/decoration_transform.hpp"

namespace {

const std::string transform_id("generation.transforms.decoration_transform");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace masd::dogen::generation::transforms {

decoration_transform::type_group decoration_transform::
make_type_group(const annotations::type_repository& atrp) {
    type_group r;
    const annotations::type_repository_selector s(atrp);

    r.enabled = s.select_type_by_name(traits::decoration::enabled());
    r.copyright_notice =
        s.select_type_by_name(traits::decoration::copyright_notice());
    r.licence_name = s.select_type_by_name(traits::decoration::licence_name());;
    r.marker_name = s.select_type_by_name(traits::decoration::marker_name());;

    return r;
}

decoration_configuration decoration_transform::read_decoration_configuration(
    const type_group& tg, const annotations::annotation& a) {

    const annotations::entry_selector s(a);
    decoration_configuration r;
    if (s.has_entry(tg.enabled))
        r.enabled(s.get_boolean_content(tg.enabled));

    return r;
}

void decoration_transform::apply(const context& ctx, meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg, "decoration transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    helpers::decoration_repository_factory f;
    f.make(m);

    stp.end_transform(m);
}

}
