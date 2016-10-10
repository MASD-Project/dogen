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
#include "dogen/dynamic/types/field_selector.hpp"
#include "dogen/dynamic/types/repository_selector.hpp"
#include "dogen/yarn/types/traits.hpp"
#include "dogen/yarn/types/type_parameters_expander.hpp"

namespace dogen {
namespace yarn {

type_parameters_expander::field_definitions
type_parameters_expander::
make_field_definitions(const dynamic::repository& drp) const {

    field_definitions r;
    const dynamic::repository_selector s(drp);
    const auto& vnp(traits::type_parameters::variable_number_of_parameters());
    r.variable_number_of_parameters = s.select_field_by_name(vnp);

    const auto& tpc(traits::type_parameters::type_parameters_count());
    r.type_parameters_count = s.select_field_by_name(tpc);

    const auto& aih(traits::type_parameters::type_parameters_always_in_heap());
    r.type_parameters_always_in_heap = s.select_field_by_name(aih);

    return r;
}

type_parameters
type_parameters_expander::make_type_parameters(const field_definitions& fds,
    const dynamic::object& o) const {
    type_parameters r;
    const dynamic::field_selector fs(o);

    const auto& vnp(fds.variable_number_of_parameters);
    r.variable_number_of_parameters(fs.get_boolean_content_or_default(vnp));

    const auto& tpc(fds.type_parameters_count);
    r.count(fs.get_number_content_or_default(tpc));

    const auto& aih(fds.type_parameters_always_in_heap);
    r.always_in_heap(fs.get_boolean_content_or_default(aih));

    return r;
}

void type_parameters_expander::
expand_type_parameters(const field_definitions& fds, object& o) const {
    const auto tp(make_type_parameters(fds, o.extensions()));
    o.type_parameters(tp);
}

void type_parameters_expander::
expand(const dynamic::repository& drp, intermediate_model& m) const {
    const auto fds(make_field_definitions(drp));
    for (auto& pair : m.objects()) {
        auto& o(pair.second);
        expand_type_parameters(fds, o);
    }
}

} }
