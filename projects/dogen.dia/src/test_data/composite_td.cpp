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
#include "dogen.dia/test_data/attribute_td.hpp"
#include "dogen.dia/test_data/composite_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::dia::attribute*
create_dogen_dia_attribute_ptr(const unsigned int position) {
    return dogen::dia::attribute_generator::create_ptr(position);
}

boost::shared_ptr<dogen::dia::attribute>
create_boost_shared_ptr_dogen_dia_attribute(unsigned int position) {
    boost::shared_ptr<dogen::dia::attribute> r(
        create_dogen_dia_attribute_ptr(position));
    return r;
}

std::vector<boost::shared_ptr<dogen::dia::attribute> > create_std_vector_boost_shared_ptr_dogen_dia_attribute(unsigned int position) {
    std::vector<boost::shared_ptr<dogen::dia::attribute> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_boost_shared_ptr_dogen_dia_attribute(position + i));
    }
    return r;
}

dogen::dia::composite*
create_dogen_dia_composite_ptr(const unsigned int) {
    return nullptr;
}

boost::shared_ptr<dogen::dia::composite>
create_boost_shared_ptr_dogen_dia_composite(unsigned int position) {
    boost::shared_ptr<dogen::dia::composite> r(
        create_dogen_dia_composite_ptr(position));
    return r;
}

}

namespace dogen::dia {

composite_generator::composite_generator() : position_(0) { }

void composite_generator::
populate(const unsigned int position, result_type& v) {
    v.type(create_std_string(position + 0));
    v.value(create_std_vector_boost_shared_ptr_dogen_dia_attribute(position + 1));
    v.inner_composite(create_boost_shared_ptr_dogen_dia_composite(position + 2));
}

composite_generator::result_type
composite_generator::create(const unsigned int position) {
    composite r;
    composite_generator::populate(position, r);
    return r;
}

composite_generator::result_type*
composite_generator::create_ptr(const unsigned int position) {
    composite* p = new composite();
    composite_generator::populate(position, *p);
    return p;
}

composite_generator::result_type
composite_generator::operator()() {
    return create(position_++);
}

}
