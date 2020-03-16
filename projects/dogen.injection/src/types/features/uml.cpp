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
#include "dogen.injection/types/features/uml.hpp"
#include "dogen.variability/types/helpers/value_factory.hpp"

namespace dogen::injection::features {

namespace {

dogen::variability::entities::feature
make_masd_injection_dia_comment() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("comment");
    r.name().qualified("masd.injection.dia.comment");
    r.description(R"(If true, the UML comment is linked to the containing package.

If the containing package is the model itself, it is linked to the model's module.

)");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    return r;
}

}


std::list<dogen::variability::entities::feature>
uml::make_features() {
    using namespace dogen::variability::entities;
    std::list<dogen::variability::entities::feature> r;
    r.push_back(make_masd_injection_dia_comment());
    return r;
}

}
