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
#include "dogen/tack/test_data/generation_types_td.hpp"
#include "dogen/cpp/test_data/formattables/entity_td.hpp"
#include "dogen/cpp/test_data/formattables/class_info_td.hpp"
#include "dogen/cpp/test_data/formattables/parent_info_td.hpp"
#include "dogen/cpp/test_data/formattables/property_info_td.hpp"

namespace {

dogen::cpp::formattables::property_info
create_dogen_cpp_formattables_property_info(const unsigned int position) {
    return dogen::cpp::formattables::property_info_generator::create(position);
}

std::list<dogen::cpp::formattables::property_info> create_std_list_dogen_cpp_formattables_property_info(unsigned int position) {
    std::list<dogen::cpp::formattables::property_info> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_cpp_formattables_property_info(position + i));
    }
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

dogen::cpp::formattables::parent_info
create_dogen_cpp_formattables_parent_info(const unsigned int position) {
    return dogen::cpp::formattables::parent_info_generator::create(position);
}

std::list<dogen::cpp::formattables::parent_info> create_std_list_dogen_cpp_formattables_parent_info(unsigned int position) {
    std::list<dogen::cpp::formattables::parent_info> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_cpp_formattables_parent_info(position + i));
    }
    return r;
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

dogen::tack::generation_types
create_dogen_tack_generation_types(const unsigned int position) {
    return dogen::tack::generation_types_generator::create(position);
}

}

namespace dogen {
namespace cpp {
namespace formattables {

class_info_generator::class_info_generator() : position_(0) { }

void class_info_generator::
populate(const unsigned int position, result_type& v) {
    dogen::cpp::formattables::entity_generator::populate(position, v);
    v.properties(create_std_list_dogen_cpp_formattables_property_info(position + 0));
    v.all_properties(create_std_list_dogen_cpp_formattables_property_info(position + 1));
    v.requires_stream_manipulators(create_bool(position + 2));
    v.requires_manual_move_constructor(create_bool(position + 3));
    v.requires_manual_default_constructor(create_bool(position + 4));
    v.parents(create_std_list_dogen_cpp_formattables_parent_info(position + 5));
    v.is_parent(create_bool(position + 6));
    v.original_parent_name(create_std_string(position + 7));
    v.original_parent_name_qualified(create_std_string(position + 8));
    v.leaves(create_std_list_std_string(position + 9));
    v.is_visitable(create_bool(position + 10));
    v.is_immutable(create_bool(position + 11));
    v.is_original_parent_visitable(create_bool(position + 12));
    v.generation_type(create_dogen_tack_generation_types(position + 13));
    v.is_final(create_bool(position + 14));
}

class_info_generator::result_type
class_info_generator::create(const unsigned int position) {
    class_info r;
    class_info_generator::populate(position, r);
    return r;
}

class_info_generator::result_type*
class_info_generator::create_ptr(const unsigned int position) {
    class_info* p = new class_info();
    class_info_generator::populate(position, *p);
    return p;
}

class_info_generator::result_type
class_info_generator::operator()() {
    return create(position_++);
}

} } }
