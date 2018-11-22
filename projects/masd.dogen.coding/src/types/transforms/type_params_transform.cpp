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
#include "masd.dogen.utility/log/logger.hpp"
#include "masd.dogen.annotations/types/entry_selector.hpp"
#include "masd.dogen.annotations/types/type_repository_selector.hpp"
#include "masd.dogen.probing/types/scoped_prober.hpp"
#include "masd.dogen.coding/types/traits.hpp"
#include "masd.dogen.coding/types/meta_model/object.hpp"
#include "masd.dogen.coding/io/meta_model/endomodel_io.hpp"
#include "masd.dogen.coding/types/transforms/context.hpp"
#include "masd.dogen.coding/types/transforms/type_params_transform.hpp"

namespace {

const std::string transform_id("yarn.type_params_transform");

using namespace masd::dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace masd::dogen::coding::transforms {

type_params_transform::type_group type_params_transform::
make_type_group(const annotations::type_repository& atrp) {

    type_group r;
    const annotations::type_repository_selector s(atrp);
    const auto& vnp(traits::type_parameters::variable_number_of_parameters());
    r.variable_number_of_parameters = s.select_type_by_name(vnp);

    const auto& tpc(traits::type_parameters::type_parameters_count());
    r.type_parameters_count = s.select_type_by_name(tpc);

    const auto& aih(traits::type_parameters::type_parameters_always_in_heap());
    r.type_parameters_always_in_heap = s.select_type_by_name(aih);

    return r;
}

meta_model::type_parameters
type_params_transform::make_type_parameters(const type_group& tg,
    const annotations::annotation& a) {
    meta_model::type_parameters r;
    const annotations::entry_selector s(a);

    const auto& vnp(tg.variable_number_of_parameters);
    r.variable_number_of_parameters(s.get_boolean_content_or_default(vnp));

    const auto& tpc(tg.type_parameters_count);
    r.count(static_cast<unsigned int>(s.get_number_content_or_default(tpc)));

    const auto& aih(tg.type_parameters_always_in_heap);
    r.always_in_heap(s.get_boolean_content_or_default(aih));

    return r;
}

void type_params_transform::
expand_type_parameters(const type_group& tg, meta_model::object& o) {
    const auto tp(make_type_parameters(tg, o.annotation()));
    o.type_parameters(tp);
}

void type_params_transform::
transform(const context& ctx, meta_model::endomodel& em) {
    probing::scoped_transform_prober stp(lg, "type params transform",
        transform_id, em.name().id(), ctx.prober(), em);

    const auto tg(make_type_group(ctx.type_repository()));
    for (auto& pair : em.objects()) {
        auto& o(*pair.second);
        expand_type_parameters(tg, o);
    }

    stp.end_transform(em);
}

}
