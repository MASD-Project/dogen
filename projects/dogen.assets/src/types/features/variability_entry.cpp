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
#include "dogen.assets/types/features/variability_entry.hpp"
#include "dogen.variability/types/helpers/value_factory.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"

namespace dogen::assets::features {
variability_entry::feature_group
variability_entry::make_feature_group(const dogen::variability::meta_model::feature_model& fm) {
    feature_group r;
    const dogen::variability::helpers::feature_selector s(fm);

    r.binding_point = s.get_by_name("masd.variability.binding_point");
    r.kernel = s.get_by_name("masd.variability.archetype_location.kernel");
    r.backend = s.get_by_name("masd.variability.archetype_location.backend");
    r.facet = s.get_by_name("masd.variability.archetype_location.facet");
    r.archetype = s.get_by_name("masd.variability.archetype_location.archetype");
    r.template_kind = s.get_by_name("masd.variability.template_kind");
    r.value = s.get_by_name("masd.variability.value");

    return r;
}

variability_entry::static_configuration variability_entry::make_static_configuration(
    const feature_group& fg,
    const dogen::variability::meta_model::configuration& cfg) {

    static_configuration r;
    const dogen::variability::helpers::configuration_selector s(cfg);
    if (s.has_configuration_point(fg.binding_point))
        r.binding_point = s.get_text_content(fg.binding_point);
    r.kernel = s.get_text_content(fg.kernel);
    if (s.has_configuration_point(fg.backend))
        r.backend = s.get_text_content(fg.backend);
    if (s.has_configuration_point(fg.facet))
        r.facet = s.get_text_content(fg.facet);
    if (s.has_configuration_point(fg.archetype))
        r.archetype = s.get_text_content(fg.archetype);
    r.template_kind = s.get_text_content(fg.template_kind);
    if (s.has_configuration_point(fg.value))
        r.value = s.get_text_collection_content(fg.value);
    return r;
}
}
