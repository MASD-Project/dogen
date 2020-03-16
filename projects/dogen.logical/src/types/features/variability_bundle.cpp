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
#include "dogen.logical/types/features/variability_bundle.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"

namespace dogen::logical::features {

namespace {

dogen::variability::meta_model::feature
make_masd_variability_generate_registration() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("generate_registration");
    r.name().qualified("masd.variability.generate_registration");
    r.description(R"(If true, generates code to register the features.

@pre Features must not already exist.

)");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "true" }));
    return r;
}

dogen::variability::meta_model::feature
make_masd_variability_generate_static_configuration() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("generate_static_configuration");
    r.name().qualified("masd.variability.generate_static_configuration");
    r.description(R"(If true, generates a c++ class to contain the configuration at compile time.

)");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "true" }));
    return r;
}

dogen::variability::meta_model::feature
make_masd_variability_default_binding_point() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("default_binding_point");
    r.name().qualified("masd.variability.default_binding_point");
    r.description(R"(Where does this bundle bind to.

)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    return r;
}

dogen::variability::meta_model::feature
make_masd_variability_instantiation_domain_name() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("instantiation_domain_name");
    r.name().qualified("masd.variability.instantiation_domain_name");
    r.description(R"(Template instantiation domain name to use when instantiating template.

)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    return r;
}

dogen::variability::meta_model::feature
make_masd_variability_key_prefix() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("key_prefix");
    r.name().qualified("masd.variability.key_prefix");
    r.description(R"(Prefix to apply to construct the qualified name, if any.

)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    return r;
}

}

variability_bundle::feature_group
variability_bundle::make_feature_group(const dogen::variability::meta_model::feature_model& fm) {
    feature_group r;
    const dogen::variability::helpers::feature_selector s(fm);

    r.generate_registration = s.get_by_name("masd.variability.generate_registration");
    r.generate_static_configuration = s.get_by_name("masd.variability.generate_static_configuration");
    r.default_binding_point = s.get_by_name("masd.variability.default_binding_point");
    r.instantiation_domain_name = s.get_by_name("masd.variability.instantiation_domain_name");
    r.key_prefix = s.get_by_name("masd.variability.key_prefix");

    return r;
}

variability_bundle::static_configuration variability_bundle::make_static_configuration(
    const feature_group& fg,
    const dogen::variability::meta_model::configuration& cfg) {

    static_configuration r;
    const dogen::variability::helpers::configuration_selector s(cfg);
    r.generate_registration = s.get_boolean_content_or_default(fg.generate_registration);
    r.generate_static_configuration = s.get_boolean_content_or_default(fg.generate_static_configuration);
    if (s.has_configuration_point(fg.default_binding_point))
        r.default_binding_point = s.get_text_content(fg.default_binding_point);
    if (s.has_configuration_point(fg.instantiation_domain_name))
        r.instantiation_domain_name = s.get_text_content(fg.instantiation_domain_name);
    if (s.has_configuration_point(fg.key_prefix))
        r.key_prefix = s.get_text_content(fg.key_prefix);
    return r;
}

std::list<dogen::variability::meta_model::feature>
variability_bundle::make_features() {
    using namespace dogen::variability::meta_model;
    std::list<dogen::variability::meta_model::feature> r;
    r.push_back(make_masd_variability_generate_registration());
    r.push_back(make_masd_variability_generate_static_configuration());
    r.push_back(make_masd_variability_default_binding_point());
    r.push_back(make_masd_variability_instantiation_domain_name());
    r.push_back(make_masd_variability_key_prefix());
    return r;
}

}
