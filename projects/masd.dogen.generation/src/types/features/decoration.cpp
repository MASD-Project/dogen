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
#include "masd.dogen.generation/types/features/decoration.hpp"
#include "masd.dogen.variability/types/helpers/value_factory.hpp"

namespace masd::dogen::generation::features {

namespace {

masd::dogen::variability::meta_model::feature_template
make_masd_generation_decoration_enabled() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("enabled");
    r.name().qualified("masd.generation.decoration.enabled");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    r.kind(template_kind::instance);

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

masd::dogen::variability::meta_model::feature_template
make_masd_generation_decoration_copyright_notice() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("copyright_notice");
    r.name().qualified("masd.generation.decoration.copyright_notice");
    const auto vt(value_type::text_collection);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    r.kind(template_kind::instance);

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

masd::dogen::variability::meta_model::feature_template
make_masd_generation_decoration_licence_name() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("licence_name");
    r.name().qualified("masd.generation.decoration.licence_name");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    r.kind(template_kind::instance);

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

masd::dogen::variability::meta_model::feature_template
make_masd_generation_decoration_modeline_group_name() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("modeline_group_name");
    r.name().qualified("masd.generation.decoration.modeline_group_name");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    r.kind(template_kind::instance);

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

masd::dogen::variability::meta_model::feature_template
make_masd_generation_decoration_marker_name() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("marker_name");
    r.name().qualified("masd.generation.decoration.marker_name");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    r.kind(template_kind::instance);

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

}

std::list<masd::dogen::variability::meta_model::feature_template>
decoration::make_templates() {
    using namespace masd::dogen::variability::meta_model;
    std::list<feature_template> r;
    r.push_back(make_masd_generation_decoration_enabled());
    r.push_back(make_masd_generation_decoration_copyright_notice());
    r.push_back(make_masd_generation_decoration_licence_name());
    r.push_back(make_masd_generation_decoration_modeline_group_name());
    r.push_back(make_masd_generation_decoration_marker_name());
    return r;
}

}
