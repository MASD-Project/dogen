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
#include "dogen/upsilon/test_data/type_information_td.hpp"
#include "dogen/upsilon/test_data/type_information_entry_td.hpp"

namespace {

dogen::upsilon::type_information_entry
create_dogen_upsilon_type_information_entry(const unsigned int position) {
    return dogen::upsilon::type_information_entry_generator::create(position);
}

std::vector<dogen::upsilon::type_information_entry> create_std_vector_dogen_upsilon_type_information_entry(unsigned int position) {
    std::vector<dogen::upsilon::type_information_entry> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_upsilon_type_information_entry(position + i));
    }
    return r;
}

boost::filesystem::path
create_boost_filesystem_path(const unsigned int position) {
    std::ostringstream s;
    s << "/a/path/number_" << position;
    return boost::filesystem::path(s.str());
}

}

namespace dogen {
namespace upsilon {

type_information_generator::type_information_generator() : position_(0) { }

void type_information_generator::
populate(const unsigned int position, result_type& v) {
    v.entries(create_std_vector_dogen_upsilon_type_information_entry(position + 0));
    v.file_name(create_boost_filesystem_path(position + 1));
}

type_information_generator::result_type
type_information_generator::create(const unsigned int position) {
    type_information r;
    type_information_generator::populate(position, r);
    return r;
}

type_information_generator::result_type*
type_information_generator::create_ptr(const unsigned int position) {
    type_information* p = new type_information();
    type_information_generator::populate(position, *p);
    return p;
}

type_information_generator::result_type
type_information_generator::operator()() {
    return create(position_++);
}

} }
