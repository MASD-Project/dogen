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
#include "dogen.templating/types/stitch/features.hpp"
#include "dogen.variability/types/helpers/value_factory.hpp"

namespace dogen::templating::stitch {

namespace {

dogen::variability::meta_model::feature_template
make_masd_stitch_stream_variable_name() {
    using namespace dogen::variability::meta_model;
    feature_template r;
    r.name().simple("stream_variable_name");
    r.name().qualified("masd.stitch.stream_variable_name");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.kind(template_kind::instance);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "stream_" }));

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

dogen::variability::meta_model::feature_template
make_masd_stitch_relative_output_directory() {
    using namespace dogen::variability::meta_model;
    feature_template r;
    r.name().simple("relative_output_directory");
    r.name().qualified("masd.stitch.relative_output_directory");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.kind(template_kind::instance);

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

dogen::variability::meta_model::feature_template
make_masd_stitch_inclusion_dependency() {
    using namespace dogen::variability::meta_model;
    feature_template r;
    r.name().simple("inclusion_dependency");
    r.name().qualified("masd.stitch.inclusion_dependency");
    const auto vt(value_type::text_collection);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.kind(template_kind::instance);

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

dogen::variability::meta_model::feature_template
make_masd_stitch_containing_namespaces() {
    using namespace dogen::variability::meta_model;
    feature_template r;
    r.name().simple("containing_namespaces");
    r.name().qualified("masd.stitch.containing_namespaces");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.kind(template_kind::instance);

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

dogen::variability::meta_model::feature_template
make_masd_stitch_wale_template() {
    using namespace dogen::variability::meta_model;
    feature_template r;
    r.name().simple("template");
    r.name().qualified("masd.stitch.wale.template");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.kind(template_kind::instance);

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

dogen::variability::meta_model::feature_template
make_masd_stitch_wale_kvp() {
    using namespace dogen::variability::meta_model;
    feature_template r;
    r.name().simple("kvp");
    r.name().qualified("masd.stitch.wale.kvp");
    const auto vt(value_type::key_value_pair);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.kind(template_kind::instance);

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

}

std::list<dogen::variability::meta_model::feature_template>
features::make_templates() {
    using namespace dogen::variability::meta_model;
    std::list<feature_template> r;
    r.push_back(make_masd_stitch_stream_variable_name());
    r.push_back(make_masd_stitch_relative_output_directory());
    r.push_back(make_masd_stitch_inclusion_dependency());
    r.push_back(make_masd_stitch_containing_namespaces());
    r.push_back(make_masd_stitch_wale_template());
    r.push_back(make_masd_stitch_wale_kvp());
    return r;
}

}
