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
#include "dogen.codec/types/features/input_technical_space.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"

namespace dogen::codec::features {

namespace {

dogen::variability::entities::feature
make_masd_codec_input_technical_space() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("input_technical_space");
    r.name().qualified("masd.codec.input_technical_space");
    r.description(R"(Input technical space for this model.
)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "agnostic" }));
    return r;
}

}

input_technical_space::feature_group
input_technical_space::make_feature_group(const dogen::variability::entities::feature_model& fm) {
    feature_group r;
    const dogen::variability::helpers::feature_selector s(fm);

    r.input_technical_space = s.get_by_name("masd.codec.input_technical_space");

    return r;
}

input_technical_space::static_configuration input_technical_space::make_static_configuration(
    const feature_group& fg,
    const dogen::variability::entities::configuration& cfg) {

    static_configuration r;
    const dogen::variability::helpers::configuration_selector s(cfg);
    r.input_technical_space = s.get_text_content_or_default(fg.input_technical_space);
    return r;
}

std::list<dogen::variability::entities::feature>
input_technical_space::make_features() {
    using namespace dogen::variability::entities;
    std::list<dogen::variability::entities::feature> r;
    r.push_back(make_masd_codec_input_technical_space());
    return r;
}

}
