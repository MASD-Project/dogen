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
#include "dogen.assets/test_data/meta_model/name_td.hpp"
#include "dogen.assets/test_data/meta_model/element_td.hpp"
#include "dogen.assets/test_data/meta_model/variability/feature_bundle_td.hpp"
#include "dogen.assets/test_data/meta_model/variability/feature_template_td.hpp"

namespace {

dogen::assets::meta_model::name
create_dogen_assets_meta_model_name(const unsigned int position) {
    return dogen::assets::meta_model::name_generator::create(position);
}

std::list<dogen::assets::meta_model::name> create_std_list_dogen_assets_meta_model_name(unsigned int position) {
    std::list<dogen::assets::meta_model::name> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_assets_meta_model_name(position + i));
    }
    return r;
}

dogen::assets::meta_model::variability::feature_template
create_dogen_assets_meta_model_variability_feature_template(const unsigned int position) {
    return dogen::assets::meta_model::variability::feature_template_generator::create(position);
}

std::list<dogen::assets::meta_model::variability::feature_template> create_std_list_dogen_assets_meta_model_variability_feature_template(unsigned int position) {
    std::list<dogen::assets::meta_model::variability::feature_template> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_assets_meta_model_variability_feature_template(position + i));
    }
    return r;
}

}

namespace dogen::assets::meta_model::variability {

feature_bundle_generator::feature_bundle_generator() : position_(0) { }

void feature_bundle_generator::
populate(const unsigned int position, result_type& v) {
    dogen::assets::meta_model::element_generator::populate(position, v);
    v.transparent_associations(create_std_list_dogen_assets_meta_model_name(position + 0));
    v.opaque_associations(create_std_list_dogen_assets_meta_model_name(position + 1));
    v.feature_templates(create_std_list_dogen_assets_meta_model_variability_feature_template(position + 2));
}

feature_bundle_generator::result_type
feature_bundle_generator::create(const unsigned int position) {
    feature_bundle r;
    feature_bundle_generator::populate(position, r);
    return r;
}

feature_bundle_generator::result_type*
feature_bundle_generator::create_ptr(const unsigned int position) {
    feature_bundle* p = new feature_bundle();
    feature_bundle_generator::populate(position, *p);
    return p;
}

feature_bundle_generator::result_type
feature_bundle_generator::operator()() {
    return create(position_++);
}

}
