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
#include "dogen/annotations/test_data/ownership_hierarchy_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

}

namespace dogen {
namespace annotations {

ownership_hierarchy_generator::ownership_hierarchy_generator() : position_(0) { }

void ownership_hierarchy_generator::
populate(const unsigned int position, result_type& v) {
    v.model_name(create_std_string(position + 0));
    v.facet_name(create_std_string(position + 1));
    v.formatter_name(create_std_string(position + 2));
}

ownership_hierarchy_generator::result_type
ownership_hierarchy_generator::create(const unsigned int position) {
    ownership_hierarchy r;
    ownership_hierarchy_generator::populate(position, r);
    return r;
}

ownership_hierarchy_generator::result_type*
ownership_hierarchy_generator::create_ptr(const unsigned int position) {
    ownership_hierarchy* p = new ownership_hierarchy();
    ownership_hierarchy_generator::populate(position, *p);
    return p;
}

ownership_hierarchy_generator::result_type
ownership_hierarchy_generator::operator()() {
    return create(position_++);
}

} }
