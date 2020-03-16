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
#include "dogen.generation/types/features/decoration.hpp"
#include "dogen.variability/types/helpers/value_factory.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"

namespace dogen::generation::features {

namespace {

dogen::variability::entities::feature
make_masd_generation_decoration_enabled() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("enabled");
    r.name().qualified("masd.generation.decoration.enabled");
    r.description(R"(If true, decorations are enabled on this modeling element.

)");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    return r;
}

dogen::variability::entities::feature
make_masd_generation_decoration_copyright_notice() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("copyright_notice");
    r.name().qualified("masd.generation.decoration.copyright_notice");
    r.description(R"(Copyright notices for this modeling element.

)");
    const auto vt(value_type::text_collection);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    return r;
}

dogen::variability::entities::feature
make_masd_generation_decoration_licence_name() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("licence_name");
    r.name().qualified("masd.generation.decoration.licence_name");
    r.description(R"(Name of the licence to use for this modeling element.

)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    return r;
}

dogen::variability::entities::feature
make_masd_generation_decoration_modeline_group_name() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("modeline_group_name");
    r.name().qualified("masd.generation.decoration.modeline_group_name");
    r.description(R"(Name of the modeline group for this modeling element.

)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    return r;
}

dogen::variability::entities::feature
make_masd_generation_decoration_marker_name() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("marker_name");
    r.name().qualified("masd.generation.decoration.marker_name");
    r.description(R"(Name of the decoration marker to use for this modeling element.

)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    return r;
}

}

decoration::feature_group
decoration::make_feature_group(const dogen::variability::entities::feature_model& fm) {
    feature_group r;
    const dogen::variability::helpers::feature_selector s(fm);

    r.enabled = s.get_by_name("masd.generation.decoration.enabled");
    r.copyright_notice = s.get_by_name("masd.generation.decoration.copyright_notice");
    r.licence_name = s.get_by_name("masd.generation.decoration.licence_name");
    r.modeline_group_name = s.get_by_name("masd.generation.decoration.modeline_group_name");
    r.marker_name = s.get_by_name("masd.generation.decoration.marker_name");

    return r;
}

decoration::static_configuration decoration::make_static_configuration(
    const feature_group& fg,
    const dogen::variability::entities::configuration& cfg) {

    static_configuration r;
    const dogen::variability::helpers::configuration_selector s(cfg);
    if (s.has_configuration_point(fg.enabled))
        r.enabled = s.get_boolean_content(fg.enabled);
    if (s.has_configuration_point(fg.copyright_notice))
        r.copyright_notice = s.get_text_collection_content(fg.copyright_notice);
    if (s.has_configuration_point(fg.licence_name))
        r.licence_name = s.get_text_content(fg.licence_name);
    if (s.has_configuration_point(fg.modeline_group_name))
        r.modeline_group_name = s.get_text_content(fg.modeline_group_name);
    if (s.has_configuration_point(fg.marker_name))
        r.marker_name = s.get_text_content(fg.marker_name);
    return r;
}

std::list<dogen::variability::entities::feature>
decoration::make_features() {
    using namespace dogen::variability::entities;
    std::list<dogen::variability::entities::feature> r;
    r.push_back(make_masd_generation_decoration_enabled());
    r.push_back(make_masd_generation_decoration_copyright_notice());
    r.push_back(make_masd_generation_decoration_licence_name());
    r.push_back(make_masd_generation_decoration_modeline_group_name());
    r.push_back(make_masd_generation_decoration_marker_name());
    return r;
}

}
