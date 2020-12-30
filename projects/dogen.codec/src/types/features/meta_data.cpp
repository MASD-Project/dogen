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
#include "dogen.codec/types/features/meta_data.hpp"
#include "dogen.variability/types/helpers/value_factory.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"

namespace dogen::codec::features {

namespace {

dogen::variability::entities::feature
make_masd_codec_stereotypes() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("stereotypes");
    r.name().qualified("masd.codec.stereotypes");
    r.description(R"(Stereotypes associated with this element or attribute.)");
    const auto vt(value_type::comma_separated);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    return r;
}

dogen::variability::entities::feature
make_masd_codec_type() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("type");
    r.name().qualified("masd.codec.type");
    r.description(R"(Type associated with this attribute.)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    return r;
}

dogen::variability::entities::feature
make_masd_codec_value() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("value");
    r.name().qualified("masd.codec.value");
    r.description(R"(Value associated with this attribute.)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    return r;
}

dogen::variability::entities::feature
make_masd_codec_parent() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("parent");
    r.name().qualified("masd.codec.parent");
    r.description(R"(Parent associated with this element.)");
    const auto vt(value_type::comma_separated);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    return r;
}

dogen::variability::entities::feature
make_masd_codec_can_be_primitive_underlier() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("can_be_primitive_underlier");
    r.name().qualified("masd.codec.can_be_primitive_underlier");
    r.description(R"()");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    return r;
}

dogen::variability::entities::feature
make_masd_codec_in_global_module() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("in_global_module");
    r.name().qualified("masd.codec.in_global_module");
    r.description(R"()");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    return r;
}

dogen::variability::entities::feature
make_masd_codec_can_be_enumeration_underlier() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("can_be_enumeration_underlier");
    r.name().qualified("masd.codec.can_be_enumeration_underlier");
    r.description(R"()");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    return r;
}

dogen::variability::entities::feature
make_masd_codec_is_default_enumeration_type() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("is_default_enumeration_type");
    r.name().qualified("masd.codec.is_default_enumeration_type");
    r.description(R"()");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    return r;
}

dogen::variability::entities::feature
make_masd_codec_is_associative_container() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("is_associative_container");
    r.name().qualified("masd.codec.is_associative_container");
    r.description(R"()");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    return r;
}

dogen::variability::entities::feature
make_masd_codec_is_floating_point() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("is_floating_point");
    r.name().qualified("masd.codec.is_floating_point");
    r.description(R"()");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    return r;
}

dogen::variability::entities::feature
make_masd_codec_preserve_original() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("preserve_original");
    r.name().qualified("masd.codec.preserve_original");
    r.description(R"()");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    return r;
}

}

meta_data::feature_group
meta_data::make_feature_group(const dogen::variability::entities::feature_model& fm) {
    feature_group r;
    const dogen::variability::helpers::feature_selector s(fm);

    r.stereotypes = s.get_by_name("masd.codec.stereotypes");
    r.type = s.get_by_name("masd.codec.type");
    r.value = s.get_by_name("masd.codec.value");
    r.parent = s.get_by_name("masd.codec.parent");
    r.can_be_primitive_underlier = s.get_by_name("masd.codec.can_be_primitive_underlier");
    r.in_global_module = s.get_by_name("masd.codec.in_global_module");
    r.can_be_enumeration_underlier = s.get_by_name("masd.codec.can_be_enumeration_underlier");
    r.is_default_enumeration_type = s.get_by_name("masd.codec.is_default_enumeration_type");
    r.is_associative_container = s.get_by_name("masd.codec.is_associative_container");
    r.is_floating_point = s.get_by_name("masd.codec.is_floating_point");
    r.preserve_original = s.get_by_name("masd.codec.preserve_original");

    return r;
}

meta_data::static_configuration meta_data::make_static_configuration(
    const feature_group& fg,
    const dogen::variability::entities::configuration& cfg) {

    static_configuration r;
    const dogen::variability::helpers::configuration_selector s(cfg);
    if (s.has_configuration_point(fg.stereotypes))
        r.stereotypes = s.get_comma_separated_content(fg.stereotypes);
    if (s.has_configuration_point(fg.type))
        r.type = s.get_text_content(fg.type);
    if (s.has_configuration_point(fg.value))
        r.value = s.get_text_content(fg.value);
    if (s.has_configuration_point(fg.parent))
        r.parent = s.get_comma_separated_content(fg.parent);
    if (s.has_configuration_point(fg.can_be_primitive_underlier))
        r.can_be_primitive_underlier = s.get_boolean_content(fg.can_be_primitive_underlier);
    if (s.has_configuration_point(fg.in_global_module))
        r.in_global_module = s.get_boolean_content(fg.in_global_module);
    if (s.has_configuration_point(fg.can_be_enumeration_underlier))
        r.can_be_enumeration_underlier = s.get_boolean_content(fg.can_be_enumeration_underlier);
    if (s.has_configuration_point(fg.is_default_enumeration_type))
        r.is_default_enumeration_type = s.get_boolean_content(fg.is_default_enumeration_type);
    if (s.has_configuration_point(fg.is_associative_container))
        r.is_associative_container = s.get_boolean_content(fg.is_associative_container);
    if (s.has_configuration_point(fg.is_floating_point))
        r.is_floating_point = s.get_boolean_content(fg.is_floating_point);
    if (s.has_configuration_point(fg.preserve_original))
        r.preserve_original = s.get_boolean_content(fg.preserve_original);
    return r;
}

std::list<dogen::variability::entities::feature>
meta_data::make_features() {
    using namespace dogen::variability::entities;
    std::list<dogen::variability::entities::feature> r;
    r.push_back(make_masd_codec_stereotypes());
    r.push_back(make_masd_codec_type());
    r.push_back(make_masd_codec_value());
    r.push_back(make_masd_codec_parent());
    r.push_back(make_masd_codec_can_be_primitive_underlier());
    r.push_back(make_masd_codec_in_global_module());
    r.push_back(make_masd_codec_can_be_enumeration_underlier());
    r.push_back(make_masd_codec_is_default_enumeration_type());
    r.push_back(make_masd_codec_is_associative_container());
    r.push_back(make_masd_codec_is_floating_point());
    r.push_back(make_masd_codec_preserve_original());
    return r;
}

}
