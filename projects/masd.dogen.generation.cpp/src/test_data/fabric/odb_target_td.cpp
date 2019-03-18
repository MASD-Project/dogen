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
#include "masd.dogen.generation.cpp/test_data/fabric/odb_target_td.hpp"

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

}

namespace masd::dogen::generation::cpp::fabric {

odb_target_generator::odb_target_generator() : position_(0) { }

void odb_target_generator::
populate(const unsigned int position, result_type& v) {
    v.name(create_std_string(position + 0));
    v.comment(create_std_string(position + 1));
    v.output_directory(create_std_string(position + 2));
    v.types_file(create_std_string(position + 3));
    v.move_parameters(create_std_list_std_pair_std_string_std_string(position + 4));
    v.object_odb_options(create_std_string(position + 5));
}

odb_target_generator::result_type
odb_target_generator::create(const unsigned int position) {
    odb_target r;
    odb_target_generator::populate(position, r);
    return r;
}

odb_target_generator::result_type*
odb_target_generator::create_ptr(const unsigned int position) {
    odb_target* p = new odb_target();
    odb_target_generator::populate(position, *p);
    return p;
}

odb_target_generator::result_type
odb_target_generator::operator()() {
    return create(position_++);
}

}
