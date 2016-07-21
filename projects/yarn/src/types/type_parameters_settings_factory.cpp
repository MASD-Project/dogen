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
#include "dogen/yarn/types/type_parameters_settings_factory.hpp"

namespace dogen {
namespace yarn {

type_parameters_settings_factory::
type_parameters_settings_factory(const dynamic::repository& rp)
    : field_definitions_(make_field_definitions(rp)) { }

type_parameters_settings_factory::field_definitions
type_parameters_settings_factory::make_field_definitions(
    const dynamic::repository& rp) const {

    field_definitions r;
    const dynamic::repository_selector s(rp);
    const auto& vnp(traits::variable_number_of_parameters());
    r.variable_number_of_parameters = s.select_field_by_name(vnp);

    const auto& tpc(traits::type_parameters_count());
    r.type_parameters_count = s.select_field_by_name(tpc);

    const auto& aih(traits::type_parameters_always_in_heap());
    r.type_parameters_always_in_heap = s.select_field_by_name(aih);

    return r;
}

type_parameters_settings type_parameters_settings_factory::
make(const dynamic::object& /*o*/) const {
    type_parameters_settings r;
    /*const dynamic::field_selector fs(o);
    r.variable_number_of_parameters(
        if (fs.has_field(fd))
            return fs.get_boolean_content(fd);

        );
    r.count();
    r.always_in_heap();*/
    return r;
}

} }
