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
#include "masd.dogen.variability/test_data/annotation_td.hpp"
#include "masd.dogen.injection/test_data/meta_model/model_td.hpp"
#include "masd.dogen.injection/test_data/meta_model/element_td.hpp"

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

masd::dogen::variability::annotation
create_masd_dogen_variability_annotation(const unsigned int position) {
    return masd::dogen::variability::annotation_generator::create(position);
}

masd::dogen::injection::meta_model::element
create_masd_dogen_injection_meta_model_element(const unsigned int position) {
    return masd::dogen::injection::meta_model::element_generator::create(position);
}

std::list<masd::dogen::injection::meta_model::element> create_std_list_masd_dogen_injection_meta_model_element(unsigned int position) {
    std::list<masd::dogen::injection::meta_model::element> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_masd_dogen_injection_meta_model_element(position + i));
    }
    return r;
}

}

namespace masd::dogen::injection::meta_model {

model_generator::model_generator() : position_(0) { }

void model_generator::
populate(const unsigned int position, result_type& v) {
    v.tagged_values(create_std_list_std_pair_std_string_std_string(position + 0));
    v.stereotypes(create_std_list_std_string(position + 1));
    v.documentation(create_std_string(position + 2));
    v.name(create_std_string(position + 3));
    v.annotation(create_masd_dogen_variability_annotation(position + 4));
    v.elements(create_std_list_masd_dogen_injection_meta_model_element(position + 5));
    v.input_technical_space(create_std_string(position + 6));
    v.references(create_std_list_std_string(position + 7));
}

model_generator::result_type
model_generator::create(const unsigned int position) {
    model r;
    model_generator::populate(position, r);
    return r;
}

model_generator::result_type*
model_generator::create_ptr(const unsigned int position) {
    model* p = new model();
    model_generator::populate(position, *p);
    return p;
}

model_generator::result_type
model_generator::operator()() {
    return create(position_++);
}

}
