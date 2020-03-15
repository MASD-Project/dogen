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
#include "dogen.generation/types/features/archetype_features.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"

namespace dogen::generation::features {

namespace {

dogen::variability::meta_model::feature_template
make_postfix() {
    using namespace dogen::variability::meta_model;
    feature_template r;
    r.name().simple("postfix");
    r.description(R"(
)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.instantiation_domain_name("masd.archetype");
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));
    r.default_value_overrides().push_back(
        default_value_override("forward_declarations",
            f.make(vt, std::list<std::string>{ "fwd" })));
    return r;
}

dogen::variability::meta_model::feature_template
make_overwrite() {
    using namespace dogen::variability::meta_model;
    feature_template r;
    r.name().simple("overwrite");
    r.description(R"(
)");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    r.instantiation_domain_name("masd.archetype");
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "true" }));
    return r;
}

}

archetype_features::feature_group
archetype_features::make_feature_group(const dogen::variability::meta_model::feature_model& fm) {
    feature_group r;
    const dogen::variability::helpers::feature_selector s(fm);

    r.postfix = s.get_by_name("postfix");
    r.overwrite = s.get_by_name("overwrite");

    return r;
}

archetype_features::static_configuration archetype_features::make_static_configuration(
    const feature_group& fg,
    const dogen::variability::meta_model::configuration& cfg) {

    static_configuration r;
    const dogen::variability::helpers::configuration_selector s(cfg);
    r.postfix = s.get_text_content_or_default(fg.postfix);
    r.overwrite = s.get_boolean_content_or_default(fg.overwrite);
    return r;
}

std::list<dogen::variability::meta_model::feature_template>
archetype_features::make_templates() {
    using namespace dogen::variability::meta_model;
    std::list<dogen::variability::meta_model::feature_template> r;
    r.push_back(make_postfix());
    r.push_back(make_overwrite());
    return r;
}

}
