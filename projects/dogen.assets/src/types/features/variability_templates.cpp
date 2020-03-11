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
#include "dogen.assets/types/features/variability_templates.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"

namespace dogen::assets::features {

namespace {

dogen::variability::meta_model::feature
make_masd_variability_binding_point() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("binding_point");
    r.name().qualified("masd.variability.binding_point");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::any);

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature
make_masd_variability_labels() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("labels");
    r.name().qualified("masd.variability.labels");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::element);

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature
make_masd_variability_value() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("value");
    r.name().qualified("masd.variability.value");
    const auto vt(value_type::text_collection);
    r.value_type(vt);
    r.binding_point(binding_point::property);

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature
make_masd_variability_qualified_name() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("qualified_name");
    r.name().qualified("masd.variability.qualified_name");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::property);

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature
make_masd_variability_is_optional() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("is_optional");
    r.name().qualified("masd.variability.is_optional");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::property);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "false" }));

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

}

variability_templates::feature_group
variability_templates::make_feature_group(const dogen::variability::meta_model::feature_model& fm) {
    feature_group r;
    const dogen::variability::helpers::feature_selector s(fm);

    r.binding_point = s.get_by_name("masd.variability.binding_point");
    r.labels = s.get_by_name("masd.variability.labels");
    r.value = s.get_by_name("masd.variability.value");
    r.qualified_name = s.get_by_name("masd.variability.qualified_name");
    r.is_optional = s.get_by_name("masd.variability.is_optional");

    return r;
}

variability_templates::static_configuration variability_templates::make_static_configuration(
    const feature_group& fg,
    const dogen::variability::meta_model::configuration& cfg) {

    static_configuration r;
    const dogen::variability::helpers::configuration_selector s(cfg);
    if (s.has_configuration_point(fg.binding_point))
        r.binding_point = s.get_text_content(fg.binding_point);
    if (s.has_configuration_point(fg.labels))
        r.labels = s.get_text_content(fg.labels);
    if (s.has_configuration_point(fg.value))
        r.value = s.get_text_collection_content(fg.value);
    if (s.has_configuration_point(fg.qualified_name))
        r.qualified_name = s.get_text_content(fg.qualified_name);
    r.is_optional = s.get_boolean_content_or_default(fg.is_optional);
    return r;
}

std::list<dogen::variability::meta_model::feature>
variability_templates::make_features() {
    using namespace dogen::variability::meta_model;
    std::list<dogen::variability::meta_model::feature> r;
    r.push_back(make_masd_variability_binding_point());
    r.push_back(make_masd_variability_labels());
    r.push_back(make_masd_variability_value());
    r.push_back(make_masd_variability_qualified_name());
    r.push_back(make_masd_variability_is_optional());
    return r;
}

}
