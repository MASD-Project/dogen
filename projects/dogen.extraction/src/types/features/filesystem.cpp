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
#include "dogen.extraction/types/features/filesystem.hpp"
#include "dogen.variability/types/helpers/value_factory.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"

namespace dogen::extraction::features {

namespace {

dogen::variability::meta_model::feature
make_masd_extraction_force_write() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("force_write");
    r.name().qualified("masd.extraction.force_write");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "false" }));

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature
make_masd_extraction_delete_extra_files() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("delete_extra_files");
    r.name().qualified("masd.extraction.delete_extra_files");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "true" }));

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature
make_masd_extraction_ignore_files_matching_regex() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("ignore_files_matching_regex");
    r.name().qualified("masd.extraction.ignore_files_matching_regex");
    const auto vt(value_type::text_collection);
    r.value_type(vt);
    r.binding_point(binding_point::global);

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature
make_masd_extraction_delete_empty_directories() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("delete_empty_directories");
    r.name().qualified("masd.extraction.delete_empty_directories");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "false" }));

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature
make_masd_extraction_enable_backend_directories() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("enable_backend_directories");
    r.name().qualified("masd.extraction.enable_backend_directories");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "false" }));

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

}

filesystem::feature_group
filesystem::make_feature_group(const dogen::variability::meta_model::feature_model& fm) {
    feature_group r;
    const dogen::variability::helpers::feature_selector s(fm);

    r.force_write = s.get_by_name("masd.extraction.force_write");
    r.delete_extra_files = s.get_by_name("masd.extraction.delete_extra_files");
    r.ignore_files_matching_regex = s.get_by_name("masd.extraction.ignore_files_matching_regex");
    r.delete_empty_directories = s.get_by_name("masd.extraction.delete_empty_directories");
    r.enable_backend_directories = s.get_by_name("masd.extraction.enable_backend_directories");

    return r;
}

filesystem::static_configuration filesystem::make_static_configuration(
    const feature_group& fg,
    const dogen::variability::meta_model::configuration& cfg) {

    static_configuration r;
    const dogen::variability::helpers::configuration_selector s(cfg);
    r.force_write = s.get_boolean_content_or_default(fg.force_write);
    r.delete_extra_files = s.get_boolean_content_or_default(fg.delete_extra_files);
    if (s.has_configuration_point(fg.ignore_files_matching_regex))
        r.ignore_files_matching_regex = s.get_text_collection_content(fg.ignore_files_matching_regex);
    r.delete_empty_directories = s.get_boolean_content_or_default(fg.delete_empty_directories);
    r.enable_backend_directories = s.get_boolean_content_or_default(fg.enable_backend_directories);
    return r;
}

std::list<dogen::variability::meta_model::feature>
filesystem::make_features() {
    using namespace dogen::variability::meta_model;
    std::list<dogen::variability::meta_model::feature> r;
    r.push_back(make_masd_extraction_force_write());
    r.push_back(make_masd_extraction_delete_extra_files());
    r.push_back(make_masd_extraction_ignore_files_matching_regex());
    r.push_back(make_masd_extraction_delete_empty_directories());
    r.push_back(make_masd_extraction_enable_backend_directories());
    return r;
}

}
