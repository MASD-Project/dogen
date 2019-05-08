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
#include "masd.dogen.coding/test_data/meta_model/name_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/static_stereotypes_td.hpp"
#include "masd.dogen.variability/test_data/meta_model/configuration_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/structural/enumerator_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

masd::dogen::coding::meta_model::name
create_masd_dogen_coding_meta_model_name(const unsigned int position) {
    return masd::dogen::coding::meta_model::name_generator::create(position);
}

masd::dogen::variability::meta_model::configuration*
create_masd_dogen_variability_meta_model_configuration_ptr(const unsigned int position) {
    return masd::dogen::variability::meta_model::configuration_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::variability::meta_model::configuration>
create_boost_shared_ptr_masd_dogen_variability_meta_model_configuration(unsigned int position) {
    boost::shared_ptr<masd::dogen::variability::meta_model::configuration> r(
        create_masd_dogen_variability_meta_model_configuration_ptr(position));
    return r;
}

masd::dogen::coding::meta_model::static_stereotypes
create_masd_dogen_coding_meta_model_static_stereotypes(const unsigned int position) {
    return masd::dogen::coding::meta_model::static_stereotypes_generator::create(position);
}

std::list<masd::dogen::coding::meta_model::static_stereotypes> create_std_list_masd_dogen_coding_meta_model_static_stereotypes(unsigned int position) {
    std::list<masd::dogen::coding::meta_model::static_stereotypes> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_masd_dogen_coding_meta_model_static_stereotypes(position + i));
    }
    return r;
}

std::list<std::string> create_std_list_std_string(unsigned int position) {
    std::list<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_string(position + i));
    }
    return r;
}

}

namespace masd::dogen::coding::meta_model::structural {

enumerator_generator::enumerator_generator() : position_(0) { }

void enumerator_generator::
populate(const unsigned int position, result_type& v) {
    v.documentation(create_std_string(position + 0));
    v.name(create_masd_dogen_coding_meta_model_name(position + 1));
    v.configuration(create_boost_shared_ptr_masd_dogen_variability_meta_model_configuration(position + 2));
    v.static_stereotypes(create_std_list_masd_dogen_coding_meta_model_static_stereotypes(position + 3));
    v.dynamic_stereotypes(create_std_list_std_string(position + 4));
    v.value(create_std_string(position + 5));
}

enumerator_generator::result_type
enumerator_generator::create(const unsigned int position) {
    enumerator r;
    enumerator_generator::populate(position, r);
    return r;
}

enumerator_generator::result_type*
enumerator_generator::create_ptr(const unsigned int position) {
    enumerator* p = new enumerator();
    enumerator_generator::populate(position, *p);
    return p;
}

enumerator_generator::result_type
enumerator_generator::operator()() {
    return create(position_++);
}

}
