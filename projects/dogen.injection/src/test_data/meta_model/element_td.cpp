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
#include "dogen.injection/test_data/meta_model/element_td.hpp"
#include "dogen.injection/test_data/meta_model/attribute_td.hpp"
#include "dogen.variability/test_data/meta_model/configuration_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::pair<std::string, std::string>
create_std_pair_std_string_std_string(unsigned int position) {
    std::pair<std::string, std::string> r(
        create_std_string(position),
        create_std_string(position));
    return r;
}

std::list<std::pair<std::string, std::string> > create_std_list_std_pair_std_string_std_string(unsigned int position) {
    std::list<std::pair<std::string, std::string> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_pair_std_string_std_string(position + i));
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

dogen::variability::meta_model::configuration*
create_dogen_variability_meta_model_configuration_ptr(const unsigned int position) {
    return dogen::variability::meta_model::configuration_generator::create_ptr(position);
}

boost::shared_ptr<dogen::variability::meta_model::configuration>
create_boost_shared_ptr_dogen_variability_meta_model_configuration(unsigned int position) {
    boost::shared_ptr<dogen::variability::meta_model::configuration> r(
        create_dogen_variability_meta_model_configuration_ptr(position));
    return r;
}

dogen::injection::meta_model::attribute
create_dogen_injection_meta_model_attribute(const unsigned int position) {
    return dogen::injection::meta_model::attribute_generator::create(position);
}

std::list<dogen::injection::meta_model::attribute> create_std_list_dogen_injection_meta_model_attribute(unsigned int position) {
    std::list<dogen::injection::meta_model::attribute> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_injection_meta_model_attribute(position + i));
    }
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

}

namespace dogen::injection::meta_model {

element_generator::element_generator() : position_(0) { }

void element_generator::
populate(const unsigned int position, result_type& v) {
    v.tagged_values(create_std_list_std_pair_std_string_std_string(position + 0));
    v.stereotypes(create_std_list_std_string(position + 1));
    v.documentation(create_std_string(position + 2));
    v.name(create_std_string(position + 3));
    v.configuration(create_boost_shared_ptr_dogen_variability_meta_model_configuration(position + 4));
    v.parents(create_std_list_std_string(position + 5));
    v.attributes(create_std_list_dogen_injection_meta_model_attribute(position + 6));
    v.fallback_element_type(create_std_string(position + 7));
    v.can_be_primitive_underlier(create_bool(position + 8));
    v.in_global_module(create_bool(position + 9));
    v.can_be_enumeration_underlier(create_bool(position + 10));
    v.is_default_enumeration_type(create_bool(position + 11));
    v.is_associative_container(create_bool(position + 12));
    v.is_floating_point(create_bool(position + 13));
}

element_generator::result_type
element_generator::create(const unsigned int position) {
    element r;
    element_generator::populate(position, r);
    return r;
}

element_generator::result_type*
element_generator::create_ptr(const unsigned int position) {
    element* p = new element();
    element_generator::populate(position, *p);
    return p;
}

element_generator::result_type
element_generator::operator()() {
    return create(position_++);
}

}
