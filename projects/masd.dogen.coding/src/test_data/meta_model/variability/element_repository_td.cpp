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
#include <sstream>
#include "masd.dogen.coding/test_data/meta_model/variability/profile_template_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/variability/element_repository_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/variability/feature_template_group_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/variability/feature_template_initializer_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

masd::dogen::coding::meta_model::variability::profile_template*
create_masd_dogen_coding_meta_model_variability_profile_template_ptr(const unsigned int position) {
    return masd::dogen::coding::meta_model::variability::profile_template_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::coding::meta_model::variability::profile_template>
create_boost_shared_ptr_masd_dogen_coding_meta_model_variability_profile_template(unsigned int position) {
    boost::shared_ptr<masd::dogen::coding::meta_model::variability::profile_template> r(
        create_masd_dogen_coding_meta_model_variability_profile_template_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::profile_template> > create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_variability_profile_template(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::profile_template> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_masd_dogen_coding_meta_model_variability_profile_template(position + i)));
    }
    return r;
}

masd::dogen::coding::meta_model::variability::feature_template_group*
create_masd_dogen_coding_meta_model_variability_feature_template_group_ptr(const unsigned int position) {
    return masd::dogen::coding::meta_model::variability::feature_template_group_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_group>
create_boost_shared_ptr_masd_dogen_coding_meta_model_variability_feature_template_group(unsigned int position) {
    boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_group> r(
        create_masd_dogen_coding_meta_model_variability_feature_template_group_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_group> > create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_variability_feature_template_group(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_group> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_masd_dogen_coding_meta_model_variability_feature_template_group(position + i)));
    }
    return r;
}

masd::dogen::coding::meta_model::variability::feature_template_initializer*
create_masd_dogen_coding_meta_model_variability_feature_template_initializer_ptr(const unsigned int position) {
    return masd::dogen::coding::meta_model::variability::feature_template_initializer_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_initializer>
create_boost_shared_ptr_masd_dogen_coding_meta_model_variability_feature_template_initializer(unsigned int position) {
    boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_initializer> r(
        create_masd_dogen_coding_meta_model_variability_feature_template_initializer_ptr(position));
    return r;
}

}

namespace masd::dogen::coding::meta_model::variability {

element_repository_generator::element_repository_generator() : position_(0) { }

void element_repository_generator::
populate(const unsigned int position, result_type& v) {
    v.profile_templates(create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_variability_profile_template(position + 0));
    v.feature_template_groups(create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_variability_feature_template_group(position + 1));
    v.feature_template_initializer(create_boost_shared_ptr_masd_dogen_coding_meta_model_variability_feature_template_initializer(position + 2));
}

element_repository_generator::result_type
element_repository_generator::create(const unsigned int position) {
    element_repository r;
    element_repository_generator::populate(position, r);
    return r;
}

element_repository_generator::result_type*
element_repository_generator::create_ptr(const unsigned int position) {
    element_repository* p = new element_repository();
    element_repository_generator::populate(position, *p);
    return p;
}

element_repository_generator::result_type
element_repository_generator::operator()() {
    return create(position_++);
}

}
