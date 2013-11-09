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
#include "dogen/cpp/test_data/cmakelists_info_td.hpp"
#include "dogen/cpp/test_data/odb_options_info_td.hpp"
#include "dogen/cpp/test_data/project_td.hpp"
#include "dogen/cpp/test_data/source_file_td.hpp"

namespace {

dogen::cpp::source_file
create_dogen_cpp_source_file(const unsigned int position) {
    return dogen::cpp::source_file_generator::create(position);
}

std::list<dogen::cpp::source_file> create_std_list_dogen_cpp_source_file(unsigned int position) {
    std::list<dogen::cpp::source_file> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_cpp_source_file(position + i));
    }
    return r;
}

dogen::cpp::odb_options_info
create_dogen_cpp_odb_options_info(const unsigned int position) {
    return dogen::cpp::odb_options_info_generator::create(position);
}

dogen::cpp::cmakelists_info
create_dogen_cpp_cmakelists_info(const unsigned int position) {
    return dogen::cpp::cmakelists_info_generator::create(position);
}

boost::optional<dogen::cpp::cmakelists_info>
create_boost_optional_dogen_cpp_cmakelists_info(unsigned int position) {
    boost::optional<dogen::cpp::cmakelists_info> r(
        create_dogen_cpp_cmakelists_info(position));
    return r;
}

}

namespace dogen {
namespace cpp {

project_generator::project_generator() : position_(0) { }

void project_generator::
populate(const unsigned int position, result_type& v) {
    v.files(create_std_list_dogen_cpp_source_file(position + 0));
    v.odb_options(create_dogen_cpp_odb_options_info(position + 1));
    v.src_cmakelists(create_dogen_cpp_cmakelists_info(position + 2));
    v.include_cmakelists(create_boost_optional_dogen_cpp_cmakelists_info(position + 3));
}

project_generator::result_type
project_generator::create(const unsigned int position) {
    project r;
    project_generator::populate(position, r);
    return r;
}
project_generator::result_type*
project_generator::create_ptr(const unsigned int position) {
    project* p = new project();
    project_generator::populate(position, *p);
    return p;
}

project_generator::result_type
project_generator::operator()() {
    return create(position_++);
}

} }
