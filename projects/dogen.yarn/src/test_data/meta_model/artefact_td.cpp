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
#include "dogen.yarn/test_data/meta_model/artefact_td.hpp"

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

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

std::vector<boost::filesystem::path> create_std_vector_boost_filesystem_path(unsigned int position) {
    std::vector<boost::filesystem::path> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_boost_filesystem_path(position + i));
    }
    return r;
}

}

namespace dogen {
namespace yarn {
namespace meta_model {

artefact_generator::artefact_generator() : position_(0) { }

void artefact_generator::
populate(const unsigned int position, result_type& v) {
    v.path(create_boost_filesystem_path(position + 0));
    v.content(create_std_string(position + 1));
    v.overwrite(create_bool(position + 2));
    v.dependencies(create_std_vector_boost_filesystem_path(position + 3));
}

artefact_generator::result_type
artefact_generator::create(const unsigned int position) {
    artefact r;
    artefact_generator::populate(position, r);
    return r;
}

artefact_generator::result_type*
artefact_generator::create_ptr(const unsigned int position) {
    artefact* p = new artefact();
    artefact_generator::populate(position, *p);
    return p;
}

artefact_generator::result_type
artefact_generator::operator()() {
    return create(position_++);
}

} } }
