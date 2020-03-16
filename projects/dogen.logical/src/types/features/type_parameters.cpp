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
#include "dogen.logical/types/features/type_parameters.hpp"
#include "dogen.variability/types/helpers/value_factory.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"

namespace dogen::logical::features {

namespace {

dogen::variability::meta_model::feature
make_masd_type_parameters_variable_number_of_parameters() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("variable_number_of_parameters");
    r.name().qualified("masd.type_parameters.variable_number_of_parameters");
    r.description(R"(
)");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "false" }));
    return r;
}

dogen::variability::meta_model::feature
make_masd_type_parameters_count() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("count");
    r.name().qualified("masd.type_parameters.count");
    r.description(R"(
)");
    const auto vt(value_type::number);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "0" }));
    return r;
}

dogen::variability::meta_model::feature
make_masd_type_parameters_always_in_heap() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("always_in_heap");
    r.name().qualified("masd.type_parameters.always_in_heap");
    r.description(R"(
)");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "false" }));
    return r;
}

}

type_parameters::feature_group
type_parameters::make_feature_group(const dogen::variability::meta_model::feature_model& fm) {
    feature_group r;
    const dogen::variability::helpers::feature_selector s(fm);

    r.variable_number_of_parameters = s.get_by_name("masd.type_parameters.variable_number_of_parameters");
    r.count = s.get_by_name("masd.type_parameters.count");
    r.always_in_heap = s.get_by_name("masd.type_parameters.always_in_heap");

    return r;
}

type_parameters::static_configuration type_parameters::make_static_configuration(
    const feature_group& fg,
    const dogen::variability::meta_model::configuration& cfg) {

    static_configuration r;
    const dogen::variability::helpers::configuration_selector s(cfg);
    r.variable_number_of_parameters = s.get_boolean_content_or_default(fg.variable_number_of_parameters);
    r.count = s.get_number_content_or_default(fg.count);
    r.always_in_heap = s.get_boolean_content_or_default(fg.always_in_heap);
    return r;
}

std::list<dogen::variability::meta_model::feature>
type_parameters::make_features() {
    using namespace dogen::variability::meta_model;
    std::list<dogen::variability::meta_model::feature> r;
    r.push_back(make_masd_type_parameters_variable_number_of_parameters());
    r.push_back(make_masd_type_parameters_count());
    r.push_back(make_masd_type_parameters_always_in_heap());
    return r;
}

}
