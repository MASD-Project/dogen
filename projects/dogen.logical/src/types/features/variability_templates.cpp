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
#include "dogen.logical/types/features/variability_templates.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"

namespace dogen::logical::features {

namespace {

dogen::variability::entities::feature
make_masd_variability_binding_point() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("binding_point");
    r.name().qualified("masd.variability.binding_point");
    r.description(R"(Where does this feature bind into.)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    return r;
}

dogen::variability::entities::feature
make_masd_variability_stereotype() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("stereotype");
    r.name().qualified("masd.variability.stereotype");
    r.description(R"(Stereotype for this profile. Must be globally unique.)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    return r;
}

dogen::variability::entities::feature
make_masd_variability_value() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("value");
    r.name().qualified("masd.variability.value");
    r.description(R"(Value for a facet or profile template.

Value as meta-data should be used only for collections, for single values prefer
the default value field if available.)");
    const auto vt(value_type::text_collection);
    r.value_type(vt);
    r.binding_point(binding_point::property);
    return r;
}

dogen::variability::entities::feature
make_masd_variability_is_optional() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("is_optional");
    r.name().qualified("masd.variability.is_optional");
    r.description(R"(If true, the feature template provides an optional feature.)");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::property);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "false" }));
    return r;
}

dogen::variability::entities::feature
make_masd_variability_default_value_override() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("default_value_override");
    r.name().qualified("masd.variability.default_value_override");
    r.description(R"(Default values to override the "default" default value.

These match on keys ending with the specified string.)");
    const auto vt(value_type::key_value_pair);
    r.value_type(vt);
    r.is_partially_matchable(true);
    r.binding_point(binding_point::property);
    return r;
}

}

variability_templates::feature_group
variability_templates::make_feature_group(const dogen::variability::entities::feature_model& fm) {
    feature_group r;
    const dogen::variability::helpers::feature_selector s(fm);

    r.binding_point = s.get_by_name("masd.variability.binding_point");
    r.stereotype = s.get_by_name("masd.variability.stereotype");
    r.value = s.get_by_name("masd.variability.value");
    r.is_optional = s.get_by_name("masd.variability.is_optional");
    r.default_value_override = s.get_by_name("masd.variability.default_value_override");

    return r;
}

variability_templates::static_configuration variability_templates::make_static_configuration(
    const feature_group& fg,
    const dogen::variability::entities::configuration& cfg) {

    static_configuration r;
    const dogen::variability::helpers::configuration_selector s(cfg);
    if (s.has_configuration_point(fg.binding_point))
        r.binding_point = s.get_text_content(fg.binding_point);
    if (s.has_configuration_point(fg.stereotype))
        r.stereotype = s.get_text_content(fg.stereotype);
    if (s.has_configuration_point(fg.value))
        r.value = s.get_text_collection_content(fg.value);
    r.is_optional = s.get_boolean_content_or_default(fg.is_optional);
    if (s.has_configuration_point(fg.default_value_override))
        r.default_value_override = s.get_key_value_pair_content(fg.default_value_override);
    return r;
}

std::list<dogen::variability::entities::feature>
variability_templates::make_features() {
    using namespace dogen::variability::entities;
    std::list<dogen::variability::entities::feature> r;
    r.push_back(make_masd_variability_binding_point());
    r.push_back(make_masd_variability_stereotype());
    r.push_back(make_masd_variability_value());
    r.push_back(make_masd_variability_is_optional());
    r.push_back(make_masd_variability_default_value_override());
    return r;
}

}
