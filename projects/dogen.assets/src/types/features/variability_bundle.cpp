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
#include "dogen.assets/types/features/variability_bundle.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"

namespace dogen::assets::features {

namespace {

dogen::variability::meta_model::feature
make_masd_variability_generate_registration() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("generate_registration");
    r.name().qualified("masd.variability.generate_registration");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "true" }));

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature
make_masd_variability_generate_static_configuration() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("generate_static_configuration");
    r.name().qualified("masd.variability.generate_static_configuration");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "true" }));

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature
make_masd_variability_archetype_location_kernel() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("kernel");
    r.name().qualified("masd.variability.archetype_location.kernel");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::any);

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature
make_masd_variability_archetype_location_backend() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("backend");
    r.name().qualified("masd.variability.archetype_location.backend");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::any);

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature
make_masd_variability_archetype_location_facet() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("facet");
    r.name().qualified("masd.variability.archetype_location.facet");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::any);

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature
make_masd_variability_archetype_location_archetype() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("archetype");
    r.name().qualified("masd.variability.archetype_location.archetype");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::any);

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature
make_masd_variability_template_kind() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("template_kind");
    r.name().qualified("masd.variability.template_kind");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::any);

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature
make_masd_variability_default_binding_point() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("default_binding_point");
    r.name().qualified("masd.variability.default_binding_point");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::any);

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

}

variability_bundle::feature_group
variability_bundle::make_feature_group(const dogen::variability::meta_model::feature_model& fm) {
    feature_group r;
    const dogen::variability::helpers::feature_selector s(fm);

    r.generate_registration = s.get_by_name("masd.variability.generate_registration");
    r.generate_static_configuration = s.get_by_name("masd.variability.generate_static_configuration");
    r.kernel = s.get_by_name("masd.variability.archetype_location.kernel");
    r.backend = s.get_by_name("masd.variability.archetype_location.backend");
    r.facet = s.get_by_name("masd.variability.archetype_location.facet");
    r.archetype = s.get_by_name("masd.variability.archetype_location.archetype");
    r.template_kind = s.get_by_name("masd.variability.template_kind");
    r.default_binding_point = s.get_by_name("masd.variability.default_binding_point");

    return r;
}

variability_bundle::static_configuration variability_bundle::make_static_configuration(
    const feature_group& fg,
    const dogen::variability::meta_model::configuration& cfg) {

    static_configuration r;
    const dogen::variability::helpers::configuration_selector s(cfg);
    r.generate_registration = s.get_boolean_content_or_default(fg.generate_registration);
    r.generate_static_configuration = s.get_boolean_content_or_default(fg.generate_static_configuration);
    r.kernel = s.get_text_content(fg.kernel);
    if (s.has_configuration_point(fg.backend))
        r.backend = s.get_text_content(fg.backend);
    if (s.has_configuration_point(fg.facet))
        r.facet = s.get_text_content(fg.facet);
    if (s.has_configuration_point(fg.archetype))
        r.archetype = s.get_text_content(fg.archetype);
    r.template_kind = s.get_text_content(fg.template_kind);
    if (s.has_configuration_point(fg.default_binding_point))
        r.default_binding_point = s.get_text_content(fg.default_binding_point);
    return r;
}

std::list<dogen::variability::meta_model::feature>
variability_bundle::make_features() {
    using namespace dogen::variability::meta_model;
    std::list<dogen::variability::meta_model::feature> r;
    r.push_back(make_masd_variability_generate_registration());
    r.push_back(make_masd_variability_generate_static_configuration());
    r.push_back(make_masd_variability_archetype_location_kernel());
    r.push_back(make_masd_variability_archetype_location_backend());
    r.push_back(make_masd_variability_archetype_location_facet());
    r.push_back(make_masd_variability_archetype_location_archetype());
    r.push_back(make_masd_variability_template_kind());
    r.push_back(make_masd_variability_default_binding_point());
    return r;
}

}
