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
#include "masd.dogen.injection/types/features/input_technical_space.hpp"

namespace masd::dogen::injection::features {

std::list<masd::dogen::variability::meta_model::feature_template>
input_technical_space::make_templates() {
    using namespace masd::dogen::variability::meta_model;
    std::list<feature_template> r;

    {
        feature_template ft;
        ft.name().simple("input_technical_space");
        ft.name().qualified("masd.injection.input_technical_space");
        ft.value_type(value_type::text);
        ft.binding_point(binding_point::element);
        ft.kind(template_kind::instance);

        archetypes::location al;
        al.kernel("masd");

        ft.location(al);
        r.push_back(ft);
    }

    return r;
}

}
