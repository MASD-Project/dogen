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
#include "dogen.logical/types/features/physical_helpers.hpp"
#include "dogen.variability/types/helpers/value_factory.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"

namespace dogen::logical::features {

namespace {

dogen::variability::entities::feature
make_masd_physical_helpers_family() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("family");
    r.name().qualified("masd.physical.helpers.family");
    r.description(R"(
)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    return r;
}

dogen::variability::entities::feature
make_masd_physical_helpers_owning_formatters() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("owning_formatters");
    r.name().qualified("masd.physical.helpers.owning_formatters");
    r.description(R"(
)");
    const auto vt(value_type::text_collection);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    return r;
}

dogen::variability::entities::feature
make_masd_physical_helpers_owning_facets() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("owning_facets");
    r.name().qualified("masd.physical.helpers.owning_facets");
    r.description(R"(
)");
    const auto vt(value_type::text_collection);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    return r;
}

dogen::variability::entities::feature
make_masd_physical_helpers_wale_template_reference() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("wale_template_reference");
    r.name().qualified("masd.physical.helpers.wale_template_reference");
    r.description(R"(
)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    return r;
}

}

physical_helpers::feature_group
physical_helpers::make_feature_group(const dogen::variability::entities::feature_model& fm) {
    feature_group r;
    const dogen::variability::helpers::feature_selector s(fm);

    r.family = s.get_by_name("masd.physical.helpers.family");
    r.owning_formatters = s.get_by_name("masd.physical.helpers.owning_formatters");
    r.owning_facets = s.get_by_name("masd.physical.helpers.owning_facets");
    r.wale_template_reference = s.get_by_name("masd.physical.helpers.wale_template_reference");

    return r;
}

physical_helpers::static_configuration physical_helpers::make_static_configuration(
    const feature_group& fg,
    const dogen::variability::entities::configuration& cfg) {

    static_configuration r;
    const dogen::variability::helpers::configuration_selector s(cfg);
    r.family = s.get_text_content(fg.family);
    r.owning_formatters = s.get_text_collection_content(fg.owning_formatters);
    if (s.has_configuration_point(fg.owning_facets))
        r.owning_facets = s.get_text_collection_content(fg.owning_facets);
    if (s.has_configuration_point(fg.wale_template_reference))
        r.wale_template_reference = s.get_text_content(fg.wale_template_reference);
    return r;
}

std::list<dogen::variability::entities::feature>
physical_helpers::make_features() {
    using namespace dogen::variability::entities;
    std::list<dogen::variability::entities::feature> r;
    r.push_back(make_masd_physical_helpers_family());
    r.push_back(make_masd_physical_helpers_owning_formatters());
    r.push_back(make_masd_physical_helpers_owning_facets());
    r.push_back(make_masd_physical_helpers_wale_template_reference());
    return r;
}

}
