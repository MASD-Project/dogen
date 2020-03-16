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
#include "dogen.generation/types/features/enablement.hpp"
#include "dogen.variability/types/helpers/value_factory.hpp"

namespace dogen::generation::features {

namespace {

dogen::variability::entities::feature_template
make_enabled() {
    using namespace dogen::variability::entities;
    feature_template r;
    r.name().simple("enabled");
    r.description(R"(If true, decorations are enabled on this modeling element.

)");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    r.instantiation_domain_name("masd");
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "true" }));
    return r;
}

}


std::list<dogen::variability::entities::feature_template>
enablement::make_templates() {
    using namespace dogen::variability::entities;
    std::list<dogen::variability::entities::feature_template> r;
    r.push_back(make_enabled());
    return r;
}

}
