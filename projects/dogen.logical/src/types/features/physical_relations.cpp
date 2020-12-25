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
#include "dogen.logical/types/features/physical_relations.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"

namespace dogen::logical::features {

namespace {

dogen::variability::entities::feature
make_masd_physical_relation_status() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("relation_status");
    r.name().qualified("masd.physical.relation_status");
    r.description(R"(Relation status for the archetype.)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    return r;
}

dogen::variability::entities::feature
make_masd_physical_variable_relation() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("variable_relation");
    r.name().qualified("masd.physical.variable_relation");
    r.description(R"(Define a variable relation between the current archetype and another archetype.)");
    const auto vt(value_type::comma_separated_collection);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    return r;
}

dogen::variability::entities::feature
make_masd_physical_constant_relation() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("constant_relation");
    r.name().qualified("masd.physical.constant_relation");
    r.description(R"(Define a fixed relation between the current archetype and another archetype.)");
    const auto vt(value_type::comma_separated_collection);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    return r;
}

}

physical_relations::feature_group
physical_relations::make_feature_group(const dogen::variability::entities::feature_model& fm) {
    feature_group r;
    const dogen::variability::helpers::feature_selector s(fm);

    r.relation_status = s.get_by_name("masd.physical.relation_status");
    r.variable_relation = s.get_by_name("masd.physical.variable_relation");
    r.constant_relation = s.get_by_name("masd.physical.constant_relation");

    return r;
}

physical_relations::static_configuration physical_relations::make_static_configuration(
    const feature_group& fg,
    const dogen::variability::entities::configuration& cfg) {

    static_configuration r;
    const dogen::variability::helpers::configuration_selector s(cfg);
    if (s.has_configuration_point(fg.relation_status))
        r.relation_status = s.get_text_content(fg.relation_status);
    if (s.has_configuration_point(fg.variable_relation))
        r.variable_relation = s.get_comma_separated_collection_content(fg.variable_relation);
    if (s.has_configuration_point(fg.constant_relation))
        r.constant_relation = s.get_comma_separated_collection_content(fg.constant_relation);
    return r;
}

std::list<dogen::variability::entities::feature>
physical_relations::make_features() {
    using namespace dogen::variability::entities;
    std::list<dogen::variability::entities::feature> r;
    r.push_back(make_masd_physical_relation_status());
    r.push_back(make_masd_physical_variable_relation());
    r.push_back(make_masd_physical_constant_relation());
    return r;
}

}
