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
#include "dogen.variability/types/helpers/value_factory.hpp"
#include "dogen.assets/types/features/variability_tagging.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"

namespace dogen::assets::features {

namespace {

dogen::variability::meta_model::feature
make_masd_variability_tag() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("tag");
    r.name().qualified("masd.variability.tag");
    const auto vt(value_type::key_value_pair);
    r.value_type(vt);
    r.is_partially_matchable(true);
    r.binding_point(binding_point::any);

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

}

variability_tagging::feature_group
variability_tagging::make_feature_group(const dogen::variability::meta_model::feature_model& fm) {
    feature_group r;
    const dogen::variability::helpers::feature_selector s(fm);

    r.tag = s.get_by_name("masd.variability.tag");

    return r;
}

variability_tagging::static_configuration variability_tagging::make_static_configuration(
    const feature_group& fg,
    const dogen::variability::meta_model::configuration& cfg) {

    static_configuration r;
    const dogen::variability::helpers::configuration_selector s(cfg);
    if (s.has_configuration_point(fg.tag))
        r.tag = s.get_key_value_pair_content(fg.tag);
    return r;
}

std::list<dogen::variability::meta_model::feature>
variability_tagging::make_features() {
    using namespace dogen::variability::meta_model;
    std::list<dogen::variability::meta_model::feature> r;
    r.push_back(make_masd_variability_tag());
    return r;
}

}
