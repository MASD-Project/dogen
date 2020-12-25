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
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"

namespace dogen::templating::stitch {

namespace {

dogen::variability::entities::feature
make_masd_stitch_stream_variable_name() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("stream_variable_name");
    r.name().qualified("masd.stitch.stream_variable_name");
    r.description(R"(Which name to use for the variable with the stream.
)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "stream_" }));
    return r;
}

dogen::variability::entities::feature
make_masd_stitch_relative_output_directory() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("relative_output_directory");
    r.name().qualified("masd.stitch.relative_output_directory");
    r.description(R"(Relative path to the output directory.
)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    return r;
}

dogen::variability::entities::feature
make_masd_stitch_inclusion_dependency() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("inclusion_dependency");
    r.name().qualified("masd.stitch.inclusion_dependency");
    r.description(R"(C++ Include header.
)");
    const auto vt(value_type::text_collection);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    return r;
}

dogen::variability::entities::feature
make_masd_stitch_containing_namespaces() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("containing_namespaces");
    r.name().qualified("masd.stitch.containing_namespaces");
    r.description(R"(Namespaces that contain the class represented by the template.
)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    return r;
}

dogen::variability::entities::feature
make_masd_stitch_wale_text_template() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("text_template");
    r.name().qualified("masd.stitch.wale.text_template");
    r.description(R"(Name of the wale text template to instantiate, if any.
)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    return r;
}

dogen::variability::entities::feature
make_masd_stitch_wale_kvp() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("kvp");
    r.name().qualified("masd.stitch.wale.kvp");
    r.description(R"(Array of wale KVPs to use in template instantiation.
)");
    const auto vt(value_type::key_value_pair);
    r.value_type(vt);
    r.is_partially_matchable(true);
    r.binding_point(binding_point::any);
    return r;
}

}

features::feature_group
features::make_feature_group(const dogen::variability::entities::feature_model& fm) {
    feature_group r;
    const dogen::variability::helpers::feature_selector s(fm);

    r.stream_variable_name = s.get_by_name("masd.stitch.stream_variable_name");
    r.relative_output_directory = s.get_by_name("masd.stitch.relative_output_directory");
    r.inclusion_dependency = s.get_by_name("masd.stitch.inclusion_dependency");
    r.containing_namespaces = s.get_by_name("masd.stitch.containing_namespaces");
    r.text_template = s.get_by_name("masd.stitch.wale.text_template");
    r.kvp = s.get_by_name("masd.stitch.wale.kvp");

    return r;
}

features::static_configuration features::make_static_configuration(
    const feature_group& fg,
    const dogen::variability::entities::configuration& cfg) {

    static_configuration r;
    const dogen::variability::helpers::configuration_selector s(cfg);
    r.stream_variable_name = s.get_text_content_or_default(fg.stream_variable_name);
    if (s.has_configuration_point(fg.relative_output_directory))
        r.relative_output_directory = s.get_text_content(fg.relative_output_directory);
    if (s.has_configuration_point(fg.inclusion_dependency))
        r.inclusion_dependency = s.get_text_collection_content(fg.inclusion_dependency);
    r.containing_namespaces = s.get_text_content(fg.containing_namespaces);
    if (s.has_configuration_point(fg.text_template))
        r.text_template = s.get_text_content(fg.text_template);
    if (s.has_configuration_point(fg.kvp))
        r.kvp = s.get_key_value_pair_content(fg.kvp);
    return r;
}

std::list<dogen::variability::entities::feature>
features::make_features() {
    using namespace dogen::variability::entities;
    std::list<dogen::variability::entities::feature> r;
    r.push_back(make_masd_stitch_stream_variable_name());
    r.push_back(make_masd_stitch_relative_output_directory());
    r.push_back(make_masd_stitch_inclusion_dependency());
    r.push_back(make_masd_stitch_containing_namespaces());
    r.push_back(make_masd_stitch_wale_text_template());
    r.push_back(make_masd_stitch_wale_kvp());
    return r;
}

}
