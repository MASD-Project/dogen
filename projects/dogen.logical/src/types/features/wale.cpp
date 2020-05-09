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
#include "dogen.logical/types/features/wale.hpp"
#include "dogen.variability/types/helpers/value_factory.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"

namespace dogen::logical::features {

namespace {

dogen::variability::entities::feature
make_masd_wale_text_template() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("text_template");
    r.name().qualified("masd.wale.text_template");
    r.description(R"(Name of the wale text template to instantiate, if any.

)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    return r;
}

dogen::variability::entities::feature
make_masd_wale_kvp() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("kvp");
    r.name().qualified("masd.wale.kvp");
    r.description(R"(Array of wale KVPs to use in template instantiation.

)");
    const auto vt(value_type::key_value_pair);
    r.value_type(vt);
    r.is_partially_matchable(true);
    r.binding_point(binding_point::any);
    return r;
}

}

wale::feature_group
wale::make_feature_group(const dogen::variability::entities::feature_model& fm) {
    feature_group r;
    const dogen::variability::helpers::feature_selector s(fm);

    r.text_template = s.get_by_name("masd.wale.text_template");
    r.kvp = s.get_by_name("masd.wale.kvp");

    return r;
}

wale::static_configuration wale::make_static_configuration(
    const feature_group& fg,
    const dogen::variability::entities::configuration& cfg) {

    static_configuration r;
    const dogen::variability::helpers::configuration_selector s(cfg);
    if (s.has_configuration_point(fg.text_template))
        r.text_template = s.get_text_content(fg.text_template);
    if (s.has_configuration_point(fg.kvp))
        r.kvp = s.get_key_value_pair_content(fg.kvp);
    return r;
}

std::list<dogen::variability::entities::feature>
wale::make_features() {
    using namespace dogen::variability::entities;
    std::list<dogen::variability::entities::feature> r;
    r.push_back(make_masd_wale_text_template());
    r.push_back(make_masd_wale_kvp());
    return r;
}

}
