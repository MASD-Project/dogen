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
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"
#include "dogen.generation.cpp/types/formatters/archetype_features.hpp"

namespace dogen::generation::cpp::formatters {

namespace {

dogen::variability::meta_model::feature_template
make_overwrite() {
    using namespace dogen::variability::meta_model;
    feature_template r;
    r.name().simple("overwrite");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    r.kind(template_kind::archetype_template);
    r.instantiation_domain_name("masd.generation.cpp.archetype");

    archetypes::location al;
    al.kernel("masd");
    al.backend("masd.generation.cpp");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature_template
make_primary_inclusion_directive() {
    using namespace dogen::variability::meta_model;
    feature_template r;
    r.name().simple("primary_inclusion_directive");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    r.kind(template_kind::archetype_template);
    r.instantiation_domain_name("masd.generation.cpp.archetype");

    archetypes::location al;
    al.kernel("masd");
    al.backend("masd.generation.cpp");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature_template
make_secondary_inclusion_directive() {
    using namespace dogen::variability::meta_model;
    feature_template r;
    r.name().simple("secondary_inclusion_directive");
    const auto vt(value_type::text_collection);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    r.kind(template_kind::archetype_template);
    r.instantiation_domain_name("masd.generation.cpp.archetype");

    archetypes::location al;
    al.kernel("masd");
    al.backend("masd.generation.cpp");

    r.location(al);
    return r;
}

}

archetype_features::feature_group
archetype_features::make_feature_group(const dogen::variability::meta_model::feature_model& fm) {
    feature_group r;
    const dogen::variability::helpers::feature_selector s(fm);

    r.overwrite = s.get_by_name("overwrite");
    r.primary_inclusion_directive = s.get_by_name("primary_inclusion_directive");
    r.secondary_inclusion_directive = s.get_by_name("secondary_inclusion_directive");

    return r;
}

archetype_features::static_configuration archetype_features::make_static_configuration(
    const feature_group& fg,
    const dogen::variability::meta_model::configuration& cfg) {

    static_configuration r;
    const dogen::variability::helpers::configuration_selector s(cfg);
    r.overwrite = s.get_boolean_content(fg.overwrite);
    r.primary_inclusion_directive = s.get_text_content(fg.primary_inclusion_directive);
    r.secondary_inclusion_directive = s.get_text_collection_content(fg.secondary_inclusion_directive);
    return r;
}

std::list<dogen::variability::meta_model::feature_template>
archetype_features::make_templates() {
    using namespace dogen::variability::meta_model;
    std::list<dogen::variability::meta_model::feature_template> r;
    r.push_back(make_overwrite());
    r.push_back(make_primary_inclusion_directive());
    r.push_back(make_secondary_inclusion_directive());
    return r;
}

}
