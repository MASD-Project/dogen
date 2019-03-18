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
#include "masd.dogen.dia/test_data/layer_td.hpp"
#include "masd.dogen.dia/test_data/diagram_td.hpp"
#include "masd.dogen.dia/test_data/diagram_data_td.hpp"

namespace {

masd::dogen::dia::diagram_data
create_masd_dogen_dia_diagram_data(const unsigned int position) {
    return masd::dogen::dia::diagram_data_generator::create(position);
}

masd::dogen::dia::layer
create_masd_dogen_dia_layer(const unsigned int position) {
    return masd::dogen::dia::layer_generator::create(position);
}

std::vector<masd::dogen::dia::layer> create_std_vector_masd_dogen_dia_layer(unsigned int position) {
    std::vector<masd::dogen::dia::layer> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_masd_dogen_dia_layer(position + i));
    }
    return r;
}

}

namespace masd::dogen::dia {

diagram_generator::diagram_generator() : position_(0) { }

void diagram_generator::
populate(const unsigned int position, result_type& v) {
    v.diagram_data(create_masd_dogen_dia_diagram_data(position + 0));
    v.layers(create_std_vector_masd_dogen_dia_layer(position + 1));
}

diagram_generator::result_type
diagram_generator::create(const unsigned int position) {
    diagram r;
    diagram_generator::populate(position, r);
    return r;
}

diagram_generator::result_type*
diagram_generator::create_ptr(const unsigned int position) {
    diagram* p = new diagram();
    diagram_generator::populate(position, *p);
    return p;
}

diagram_generator::result_type
diagram_generator::operator()() {
    return create(position_++);
}

}
