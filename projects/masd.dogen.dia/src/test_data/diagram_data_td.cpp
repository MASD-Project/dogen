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
#include "masd.dogen.dia/test_data/attribute_td.hpp"
#include "masd.dogen.dia/test_data/diagram_data_td.hpp"

namespace {

masd::dogen::dia::attribute
create_masd_dogen_dia_attribute(const unsigned int position) {
    return masd::dogen::dia::attribute_generator::create(position);
}

std::vector<masd::dogen::dia::attribute> create_std_vector_masd_dogen_dia_attribute(unsigned int position) {
    std::vector<masd::dogen::dia::attribute> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_masd_dogen_dia_attribute(position + i));
    }
    return r;
}

}

namespace masd::dogen::dia {

diagram_data_generator::diagram_data_generator() : position_(0) { }

void diagram_data_generator::
populate(const unsigned int position, result_type& v) {
    v.attributes(create_std_vector_masd_dogen_dia_attribute(position + 0));
}

diagram_data_generator::result_type
diagram_data_generator::create(const unsigned int position) {
    diagram_data r;
    diagram_data_generator::populate(position, r);
    return r;
}

diagram_data_generator::result_type*
diagram_data_generator::create_ptr(const unsigned int position) {
    diagram_data* p = new diagram_data();
    diagram_data_generator::populate(position, *p);
    return p;
}

diagram_data_generator::result_type
diagram_data_generator::operator()() {
    return create(position_++);
}

}
