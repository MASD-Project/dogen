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
#include "dogen.logical/types/features/physical.hpp"
#include "dogen.variability/types/helpers/value_factory.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"

namespace dogen::logical::features {

namespace {

dogen::variability::entities::feature
make_masd_physical_backend_name() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("backend_name");
    r.name().qualified("masd.physical.backend_name");
    r.description(R"(Simple name of the backend.

FIXME: temporary until we rename the namespaces.

)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    return r;
}

dogen::variability::entities::feature
make_masd_physical_part_id() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("part_id");
    r.name().qualified("masd.physical.part_id");
    r.description(R"(Fully qualified physical name of the part this artefact belongs to.

FIXME: optional for now.

)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    return r;
}

dogen::variability::entities::feature
make_masd_physical_logical_meta_element_id() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("logical_meta_element_id");
    r.name().qualified("masd.physical.logical_meta_element_id");
    r.description(R"(Fully qualified name of the logical model element.

FIXME: optional for now.

)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    return r;
}

dogen::variability::entities::feature
make_masd_physical_major_technical_space() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("major_technical_space");
    r.name().qualified("masd.physical.major_technical_space");
    r.description(R"(Major technical space to which this element belongs to.

)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    return r;
}

}

physical::feature_group
physical::make_feature_group(const dogen::variability::entities::feature_model& fm) {
    feature_group r;
    const dogen::variability::helpers::feature_selector s(fm);

    r.backend_name = s.get_by_name("masd.physical.backend_name");
    r.part_id = s.get_by_name("masd.physical.part_id");
    r.logical_meta_element_id = s.get_by_name("masd.physical.logical_meta_element_id");
    r.major_technical_space = s.get_by_name("masd.physical.major_technical_space");

    return r;
}

physical::static_configuration physical::make_static_configuration(
    const feature_group& fg,
    const dogen::variability::entities::configuration& cfg) {

    static_configuration r;
    const dogen::variability::helpers::configuration_selector s(cfg);
    if (s.has_configuration_point(fg.backend_name))
        r.backend_name = s.get_text_content(fg.backend_name);
    if (s.has_configuration_point(fg.part_id))
        r.part_id = s.get_text_content(fg.part_id);
    if (s.has_configuration_point(fg.logical_meta_element_id))
        r.logical_meta_element_id = s.get_text_content(fg.logical_meta_element_id);
    if (s.has_configuration_point(fg.major_technical_space))
        r.major_technical_space = s.get_text_content(fg.major_technical_space);
    return r;
}

std::list<dogen::variability::entities::feature>
physical::make_features() {
    using namespace dogen::variability::entities;
    std::list<dogen::variability::entities::feature> r;
    r.push_back(make_masd_physical_backend_name());
    r.push_back(make_masd_physical_part_id());
    r.push_back(make_masd_physical_logical_meta_element_id());
    r.push_back(make_masd_physical_major_technical_space());
    return r;
}

}
