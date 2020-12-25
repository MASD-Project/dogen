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
#include "dogen.logical/types/features/mapping.hpp"
#include "dogen.variability/types/helpers/value_factory.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"

namespace dogen::logical::features {

namespace {

dogen::variability::entities::feature
make_masd_mapping_target() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("target");
    r.name().qualified("masd.mapping.target");
    r.description(R"(Type that is the source of the mapping.
)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    return r;
}

dogen::variability::entities::feature
make_masd_mapping_destination() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("destination");
    r.name().qualified("masd.mapping.destination");
    r.description(R"(Type that is the destination of the mapping.
)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    return r;
}

}

mapping::feature_group
mapping::make_feature_group(const dogen::variability::entities::feature_model& fm) {
    feature_group r;
    const dogen::variability::helpers::feature_selector s(fm);

    r.target = s.get_by_name("masd.mapping.target");
    r.destination = s.get_by_name("masd.mapping.destination");

    return r;
}

mapping::static_configuration mapping::make_static_configuration(
    const feature_group& fg,
    const dogen::variability::entities::configuration& cfg) {

    static_configuration r;
    const dogen::variability::helpers::configuration_selector s(cfg);
    if (s.has_configuration_point(fg.target))
        r.target = s.get_text_content(fg.target);
    if (s.has_configuration_point(fg.destination))
        r.destination = s.get_text_content(fg.destination);
    return r;
}

std::list<dogen::variability::entities::feature>
mapping::make_features() {
    using namespace dogen::variability::entities;
    std::list<dogen::variability::entities::feature> r;
    r.push_back(make_masd_mapping_target());
    r.push_back(make_masd_mapping_destination());
    return r;
}

}
