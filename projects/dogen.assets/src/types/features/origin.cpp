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
#include "dogen.assets/types/features/origin.hpp"
#include "dogen.variability/types/helpers/value_factory.hpp"

namespace dogen::assets::features {

namespace {

dogen::variability::meta_model::feature_template
make_masd_injection_is_proxy_model() {
    using namespace dogen::variability::meta_model;
    feature_template r;
    r.name().simple("is_proxy_model");
    r.name().qualified("masd.injection.is_proxy_model");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.kind(template_kind::instance);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "false" }));

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

}

std::list<dogen::variability::meta_model::feature_template>
origin::make_templates() {
    using namespace dogen::variability::meta_model;
    std::list<feature_template> r;
    r.push_back(make_masd_injection_is_proxy_model());
    return r;
}

}
