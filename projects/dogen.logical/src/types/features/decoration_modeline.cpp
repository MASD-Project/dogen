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
#include "dogen.logical/types/features/decoration_modeline.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"

namespace dogen::logical::features {

namespace {

dogen::variability::meta_model::feature
make_masd_decoration_modeline_editor() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("editor");
    r.name().qualified("masd.decoration.modeline.editor");
    r.description(R"(Editor to use in this modeline.

)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    return r;
}

dogen::variability::meta_model::feature
make_masd_decoration_modeline_location() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("location");
    r.name().qualified("masd.decoration.modeline.location");
    r.description(R"(Where to place the modeline.

)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    return r;
}

dogen::variability::meta_model::feature
make_masd_decoration_modeline_technical_space() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("technical_space");
    r.name().qualified("masd.decoration.modeline.technical_space");
    r.description(R"(Technical space targeted by the modeline.

)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    return r;
}

}

decoration_modeline::feature_group
decoration_modeline::make_feature_group(const dogen::variability::meta_model::feature_model& fm) {
    feature_group r;
    const dogen::variability::helpers::feature_selector s(fm);

    r.editor = s.get_by_name("masd.decoration.modeline.editor");
    r.location = s.get_by_name("masd.decoration.modeline.location");
    r.technical_space = s.get_by_name("masd.decoration.modeline.technical_space");

    return r;
}

decoration_modeline::static_configuration decoration_modeline::make_static_configuration(
    const feature_group& fg,
    const dogen::variability::meta_model::configuration& cfg) {

    static_configuration r;
    const dogen::variability::helpers::configuration_selector s(cfg);
    if (s.has_configuration_point(fg.editor))
        r.editor = s.get_text_content(fg.editor);
    if (s.has_configuration_point(fg.location))
        r.location = s.get_text_content(fg.location);
    if (s.has_configuration_point(fg.technical_space))
        r.technical_space = s.get_text_content(fg.technical_space);
    return r;
}

std::list<dogen::variability::meta_model::feature>
decoration_modeline::make_features() {
    using namespace dogen::variability::meta_model;
    std::list<dogen::variability::meta_model::feature> r;
    r.push_back(make_masd_decoration_modeline_editor());
    r.push_back(make_masd_decoration_modeline_location());
    r.push_back(make_masd_decoration_modeline_technical_space());
    return r;
}

}
