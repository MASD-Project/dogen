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
#include "dogen.formatting/test_data/repository_td.hpp"
#include "dogen.formatting/test_data/modeline_group_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::formatting::modeline_group
create_dogen_formatting_modeline_group(const unsigned int position) {
    return dogen::formatting::modeline_group_generator::create(position);
}

std::unordered_map<std::string, dogen::formatting::modeline_group> create_std_unordered_map_std_string_dogen_formatting_modeline_group(unsigned int position) {
    std::unordered_map<std::string, dogen::formatting::modeline_group> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_formatting_modeline_group(position + i)));
    }
    return r;
}

std::unordered_map<std::string, std::string> create_std_unordered_map_std_string_std_string(unsigned int position) {
    std::unordered_map<std::string, std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_std_string(position + i)));
    }
    return r;
}

}

namespace dogen {
namespace formatting {

repository_generator::repository_generator() : position_(0) { }

void repository_generator::
populate(const unsigned int position, result_type& v) {
    v.modeline_groups(create_std_unordered_map_std_string_dogen_formatting_modeline_group(position + 0));
    v.licence_texts(create_std_unordered_map_std_string_std_string(position + 1));
}

repository_generator::result_type
repository_generator::create(const unsigned int position) {
    repository r;
    repository_generator::populate(position, r);
    return r;
}

repository_generator::result_type*
repository_generator::create_ptr(const unsigned int position) {
    repository* p = new repository();
    repository_generator::populate(position, *p);
    return p;
}

repository_generator::result_type
repository_generator::operator()() {
    return create(position_++);
}

} }
