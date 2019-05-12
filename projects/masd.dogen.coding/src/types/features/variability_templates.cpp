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
#include "masd.dogen.variability/types/helpers/value_factory.hpp"
#include "masd.dogen.coding/types/features/variability_templates.hpp"

namespace masd::dogen::coding::features {

namespace {

masd::dogen::variability::meta_model::feature_template
make_masd_variability_binding_point() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("binding_point");
    r.name().qualified("masd.variability.binding_point");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    r.kind(template_kind::instance);

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

masd::dogen::variability::meta_model::feature_template
make_masd_variability_labels() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("labels");
    r.name().qualified("masd.variability.labels");
    const auto vt(value_type::text_collection);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    r.kind(template_kind::instance);

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

masd::dogen::variability::meta_model::feature_template
make_masd_variability_archetype_location_kernel() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("kernel");
    r.name().qualified("masd.variability.archetype_location.kernel");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::property);
    r.kind(template_kind::instance);

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

masd::dogen::variability::meta_model::feature_template
make_masd_variability_archetype_location_backend() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("backend");
    r.name().qualified("masd.variability.archetype_location.backend");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::property);
    r.kind(template_kind::instance);

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

masd::dogen::variability::meta_model::feature_template
make_masd_variability_archetype_location_facet() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("facet");
    r.name().qualified("masd.variability.archetype_location.facet");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::property);
    r.kind(template_kind::instance);

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

masd::dogen::variability::meta_model::feature_template
make_masd_variability_archetype_location_archetype() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("archetype");
    r.name().qualified("masd.variability.archetype_location.archetype");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::property);
    r.kind(template_kind::instance);

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

masd::dogen::variability::meta_model::feature_template
make_masd_variability_template_kind() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("template_kind");
    r.name().qualified("masd.variability.template_kind");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::property);
    r.kind(template_kind::instance);

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

masd::dogen::variability::meta_model::feature_template
make_masd_variability_value() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("value");
    r.name().qualified("masd.variability.value");
    const auto vt(value_type::text_collection);
    r.value_type(vt);
    r.binding_point(binding_point::property);
    r.kind(template_kind::instance);

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

}

std::list<masd::dogen::variability::meta_model::feature_template>
variability_templates::make_templates() {
    using namespace masd::dogen::variability::meta_model;
    std::list<feature_template> r;
    r.push_back(make_masd_variability_binding_point());
    r.push_back(make_masd_variability_labels());
    r.push_back(make_masd_variability_archetype_location_kernel());
    r.push_back(make_masd_variability_archetype_location_backend());
    r.push_back(make_masd_variability_archetype_location_facet());
    r.push_back(make_masd_variability_archetype_location_archetype());
    r.push_back(make_masd_variability_template_kind());
    r.push_back(make_masd_variability_value());
    return r;
}

}
