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
#include "dogen.physical/types/features/backend_features.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"

namespace dogen::physical::features {

namespace {

dogen::variability::entities::feature_template
make_directory_name() {
    using namespace dogen::variability::entities;
    feature_template r;
    r.name().simple("directory_name");
    r.description(R"(Directory in which to place this backend.

)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.instantiation_domain_name("masd.backend");
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));
    r.default_value_overrides().push_back(
        default_value_override("cpp",
            f.make(vt, std::list<std::string>{ "cpp" })));
    r.default_value_overrides().push_back(
        default_value_override("csharp",
            f.make(vt, std::list<std::string>{ "cs" })));
    return r;
}

}

backend_features::feature_group
backend_features::make_feature_group(const dogen::variability::entities::feature_model& fm) {
    feature_group r;
    const dogen::variability::helpers::feature_selector s(fm);

    r.directory_name = s.get_by_name("directory_name");

    return r;
}

backend_features::static_configuration backend_features::make_static_configuration(
    const feature_group& fg,
    const dogen::variability::entities::configuration& cfg) {

    static_configuration r;
    const dogen::variability::helpers::configuration_selector s(cfg);
    r.directory_name = s.get_text_content_or_default(fg.directory_name);
    return r;
}

std::list<dogen::variability::entities::feature_template>
backend_features::make_templates() {
    using namespace dogen::variability::entities;
    std::list<dogen::variability::entities::feature_template> r;
    r.push_back(make_directory_name());
    return r;
}

}
