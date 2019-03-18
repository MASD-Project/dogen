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
#include "masd.dogen.generation.cpp/test_data/formattables/artefact_properties_td.hpp"

namespace {

boost::filesystem::path
create_boost_filesystem_path(const unsigned int position) {
    std::ostringstream s;
    s << "/a/path/number_" << position;
    return boost::filesystem::path(s.str());
}

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

namespace masd::dogen::generation::cpp::formattables {

artefact_properties_generator::artefact_properties_generator() : position_(0) { }

void artefact_properties_generator::
populate(const unsigned int position, result_type& v) {
    v.file_path(create_boost_filesystem_path(position + 0));
    v.header_guard(create_std_string(position + 1));
    v.inclusion_dependencies(create_std_list_std_string(position + 2));
}

artefact_properties_generator::result_type
artefact_properties_generator::create(const unsigned int position) {
    artefact_properties r;
    artefact_properties_generator::populate(position, r);
    return r;
}

artefact_properties_generator::result_type*
artefact_properties_generator::create_ptr(const unsigned int position) {
    artefact_properties* p = new artefact_properties();
    artefact_properties_generator::populate(position, *p);
    return p;
}

artefact_properties_generator::result_type
artefact_properties_generator::operator()() {
    return create(position_++);
}

}
