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
#include "masd.dogen.coding/test_data/meta_model/element_td.hpp"
#include "masd.dogen.generation.cpp/test_data/fabric/common_odb_options_td.hpp"

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

namespace masd::dogen::generation::cpp::fabric {

common_odb_options_generator::common_odb_options_generator() : position_(0) { }

void common_odb_options_generator::
populate(const unsigned int position, result_type& v) {
    masd::dogen::coding::meta_model::element_generator::populate(position, v);
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
