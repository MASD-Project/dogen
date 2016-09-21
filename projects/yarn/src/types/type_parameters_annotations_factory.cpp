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
#include "dogen/dynamic/types/repository_selector.hpp"
#include "dogen/yarn/types/traits.hpp"
#include "dogen/yarn/types/building_error.hpp"
#include "dogen/yarn/types/type_parameters_annotations_factory.hpp"

namespace dogen {
namespace yarn {

type_parameters_annotations_factory::
type_parameters_annotations_factory(const dynamic::repository& rp)
    : field_definitions_(make_field_definitions(rp)) { }

type_parameters_annotations_factory::field_definitions
type_parameters_annotations_factory::make_field_definitions(
    const dynamic::repository& rp) const {

    field_definitions r;
    const dynamic::repository_selector s(rp);
    const auto& vnp(traits::type_parameters::variable_number_of_parameters());
    r.variable_number_of_parameters = s.select_field_by_name(vnp);

    const auto& tpc(traits::type_parameters::type_parameters_count());
    r.type_parameters_count = s.select_field_by_name(tpc);

    const auto& aih(traits::type_parameters::type_parameters_always_in_heap());
    r.type_parameters_always_in_heap = s.select_field_by_name(aih);

    return r;
}

type_parameters_annotations type_parameters_annotations_factory::
make(const dynamic::object& o) const {
    type_parameters_annotations r;
    const dynamic::field_selector fs(o);

    const auto& vnp(field_definitions_.variable_number_of_parameters);
    r.variable_number_of_parameters(fs.get_boolean_content_or_default(vnp));

    const auto& tpc(field_definitions_.type_parameters_count);
    r.count(fs.get_number_content_or_default(tpc));

    const auto& aih(field_definitions_.type_parameters_always_in_heap);
    r.always_in_heap(fs.get_boolean_content_or_default(aih));

    return r;
}

} }
