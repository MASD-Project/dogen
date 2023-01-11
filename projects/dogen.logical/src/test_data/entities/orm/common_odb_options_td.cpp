/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * These files are code-generated via overrides to test dogen. Do not commit them.
 *
 * Generation timestamp: 2022-10-20T10:20:30
 * WARNING: do not edit this file manually.
 * Generated by MASD Dogen v1.0.33
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
#include "dogen.logical/test_data/entities/element_td.hpp"
#include "dogen.logical/test_data/entities/orm/common_odb_options_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::list<std::string> create_std_list_std_string(unsigned int position) {
    std::list<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_string(position + i));
    }
    return r;
}

}

namespace dogen::logical::entities::orm {

common_odb_options_generator::common_odb_options_generator() : position_(0) { }

void common_odb_options_generator::
populate(const unsigned int position, result_type& v) {
    dogen::logical::entities::element_generator::populate(position, v);
    v.sql_name_case(create_std_string(position + 0));
    v.databases(create_std_list_std_string(position + 1));
}

common_odb_options_generator::result_type
common_odb_options_generator::create(const unsigned int position) {
    common_odb_options r;
    common_odb_options_generator::populate(position, r);
    return r;
}

common_odb_options_generator::result_type*
common_odb_options_generator::create_ptr(const unsigned int position) {
    common_odb_options* p = new common_odb_options();
    common_odb_options_generator::populate(position, *p);
    return p;
}

common_odb_options_generator::result_type
common_odb_options_generator::operator()() {
    return create(position_++);
}

}