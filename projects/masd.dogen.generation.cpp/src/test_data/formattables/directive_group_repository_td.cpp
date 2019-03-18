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
#include "masd.dogen.generation.cpp/test_data/formattables/directive_group_td.hpp"
#include "masd.dogen.generation.cpp/test_data/formattables/directive_group_repository_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

masd::dogen::generation::cpp::formattables::directive_group
create_masd_dogen_generation_cpp_formattables_directive_group(const unsigned int position) {
    return masd::dogen::generation::cpp::formattables::directive_group_generator::create(position);
}

std::unordered_map<std::string, masd::dogen::generation::cpp::formattables::directive_group> create_std_unordered_map_std_string_masd_dogen_generation_cpp_formattables_directive_group(unsigned int position) {
    std::unordered_map<std::string, masd::dogen::generation::cpp::formattables::directive_group> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_masd_dogen_generation_cpp_formattables_directive_group(position + i)));
    }
    return r;
}

std::unordered_map<std::string, std::unordered_map<std::string, masd::dogen::generation::cpp::formattables::directive_group> > create_std_unordered_map_std_string_std_unordered_map_std_string_masd_dogen_generation_cpp_formattables_directive_group(unsigned int position) {
    std::unordered_map<std::string, std::unordered_map<std::string, masd::dogen::generation::cpp::formattables::directive_group> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_std_unordered_map_std_string_masd_dogen_generation_cpp_formattables_directive_group(position + i)));
    }
    return r;
}

}

namespace masd::dogen::generation::cpp::formattables {

directive_group_repository_generator::directive_group_repository_generator() : position_(0) { }

void directive_group_repository_generator::
populate(const unsigned int position, result_type& v) {
    v.by_id(create_std_unordered_map_std_string_std_unordered_map_std_string_masd_dogen_generation_cpp_formattables_directive_group(position + 0));
}

directive_group_repository_generator::result_type
directive_group_repository_generator::create(const unsigned int position) {
    directive_group_repository r;
    directive_group_repository_generator::populate(position, r);
    return r;
}

directive_group_repository_generator::result_type*
directive_group_repository_generator::create_ptr(const unsigned int position) {
    directive_group_repository* p = new directive_group_repository();
    directive_group_repository_generator::populate(position, *p);
    return p;
}

directive_group_repository_generator::result_type
directive_group_repository_generator::operator()() {
    return create(position_++);
}

}
