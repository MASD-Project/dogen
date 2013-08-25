/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/om/test_data/cmake_file_td.hpp"
#include "dogen/om/test_data/cpp_file_td.hpp"
#include "dogen/om/test_data/cpp_project_td.hpp"
#include "dogen/om/test_data/odb_options_file_td.hpp"

namespace {

dogen::om::cmake_file
create_dogen_om_cmake_file(const unsigned int position) {
    return dogen::om::cmake_file_generator::create(position);
}

std::list<dogen::om::cmake_file> create_std_list_dogen_om_cmake_file(unsigned int position) {
    std::list<dogen::om::cmake_file> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_dogen_om_cmake_file(position + i));
    }
    return r;
}

dogen::om::odb_options_file
create_dogen_om_odb_options_file(const unsigned int position) {
    return dogen::om::odb_options_file_generator::create(position);
}

boost::optional<dogen::om::odb_options_file>
create_boost_optional_dogen_om_odb_options_file(unsigned int position) {
    boost::optional<dogen::om::odb_options_file> r(
        create_dogen_om_odb_options_file(position));
    return r;
}

dogen::om::cpp_file
create_dogen_om_cpp_file(const unsigned int position) {
    return dogen::om::cpp_file_generator::create(position);
}

std::list<dogen::om::cpp_file> create_std_list_dogen_om_cpp_file(unsigned int position) {
    std::list<dogen::om::cpp_file> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_dogen_om_cpp_file(position + i));
    }
    return r;
}

}

namespace dogen {
namespace om {

cpp_project_generator::cpp_project_generator() : position_(0) { }

void cpp_project_generator::
populate(const unsigned int position, result_type& v) {
    v.makefiles(create_std_list_dogen_om_cmake_file(position + 0));
    v.odb_options(create_boost_optional_dogen_om_odb_options_file(position + 1));
    v.cpp_files(create_std_list_dogen_om_cpp_file(position + 2));
}

cpp_project_generator::result_type
cpp_project_generator::create(const unsigned int position) {
    cpp_project r;
    cpp_project_generator::populate(position, r);
    return r;
}
cpp_project_generator::result_type*
cpp_project_generator::create_ptr(const unsigned int position) {
    cpp_project* p = new cpp_project();
    cpp_project_generator::populate(position, *p);
    return p;
}

cpp_project_generator::result_type
cpp_project_generator::operator()() {
    return create(position_++);
}

} }
