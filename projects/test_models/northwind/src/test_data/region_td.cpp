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
#include "zango/northwind/test_data/region_td.hpp"
#include "zango/northwind/test_data/region_id_td.hpp"

namespace {

zango::northwind::region_id
create_zango_northwind_region_id(const unsigned int position) {
    return zango::northwind::region_id_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

}

namespace zango {
namespace northwind {

region_generator::region_generator() : position_(0) { }

void region_generator::
populate(const unsigned int position, result_type& v) {
    v.region_id(create_zango_northwind_region_id(position + 0));
    v.region_description(create_std_string(position + 1));
}

region_generator::result_type
region_generator::create(const unsigned int position) {
    region r;
    region_generator::populate(position, r);
    return r;
}

region_generator::result_type*
region_generator::create_ptr(const unsigned int position) {
    region* p = new region();
    region_generator::populate(position, *p);
    return p;
}

region_generator::result_type
region_generator::operator()() {
    return create(position_++);
}

} }
