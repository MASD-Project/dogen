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
#include "dogen/cpp/test_data/formattables/entity_td.hpp"
#include "dogen/cpp/test_data/formattables/visitor_info_td.hpp"
#include "dogen/cpp/test_data/formattables/visited_type_info_td.hpp"

namespace {

dogen::cpp::formattables::visited_type_info
create_dogen_cpp_formattables_visited_type_info(const unsigned int position) {
    return dogen::cpp::formattables::visited_type_info_generator::create(position);
}

std::list<dogen::cpp::formattables::visited_type_info> create_std_list_dogen_cpp_formattables_visited_type_info(unsigned int position) {
    std::list<dogen::cpp::formattables::visited_type_info> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_cpp_formattables_visited_type_info(position + i));
    }
    return r;
}

}

namespace dogen {
namespace cpp {
namespace formattables {

visitor_info_generator::visitor_info_generator() : position_(0) { }

void visitor_info_generator::
populate(const unsigned int position, result_type& v) {
    dogen::cpp::formattables::entity_generator::populate(position, v);
    v.types(create_std_list_dogen_cpp_formattables_visited_type_info(position + 0));
}

visitor_info_generator::result_type
visitor_info_generator::create(const unsigned int position) {
    visitor_info r;
    visitor_info_generator::populate(position, r);
    return r;
}

visitor_info_generator::result_type*
visitor_info_generator::create_ptr(const unsigned int position) {
    visitor_info* p = new visitor_info();
    visitor_info_generator::populate(position, *p);
    return p;
}

visitor_info_generator::result_type
visitor_info_generator::operator()() {
    return create(position_++);
}

} } }
