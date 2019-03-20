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
#include "masd.dogen.annotations/test_data/annotation_td.hpp"
#include "masd.dogen.injection/test_data/meta_model/attribute_td.hpp"

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

masd::dogen::annotations::annotation
create_masd_dogen_annotations_annotation(const unsigned int position) {
    return masd::dogen::annotations::annotation_generator::create(position);
}

}

namespace masd::dogen::injection::meta_model {

attribute_generator::attribute_generator() : position_(0) { }

void attribute_generator::
populate(const unsigned int position, result_type& v) {
    v.tagged_values(create_std_list_std_pair_std_string_std_string(position + 0));
    v.stereotypes(create_std_list_std_string(position + 1));
    v.documentation(create_std_string(position + 2));
    v.name(create_std_string(position + 3));
    v.annotation(create_masd_dogen_annotations_annotation(position + 4));
    v.type(create_std_string(position + 5));
    v.value(create_std_string(position + 6));
}

attribute_generator::result_type
attribute_generator::create(const unsigned int position) {
    attribute r;
    attribute_generator::populate(position, r);
    return r;
}

attribute_generator::result_type*
attribute_generator::create_ptr(const unsigned int position) {
    attribute* p = new attribute();
    attribute_generator::populate(position, *p);
    return p;
}

attribute_generator::result_type
attribute_generator::operator()() {
    return create(position_++);
}

}
