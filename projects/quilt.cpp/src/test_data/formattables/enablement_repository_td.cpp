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
#include "dogen/yarn/test_data/name_td.hpp"
#include "dogen/quilt.cpp/test_data/formattables/enablement_repository_td.hpp"

namespace {

dogen::yarn::name
create_dogen_yarn_name(const unsigned int position) {
    return dogen::yarn::name_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

std::unordered_map<std::string, bool> create_std_unordered_map_std_string_bool(unsigned int position) {
    std::unordered_map<std::string, bool> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_bool(position + i)));
    }
    return r;
}

std::unordered_map<dogen::yarn::name, std::unordered_map<std::string, bool> > create_std_unordered_map_dogen_yarn_name_std_unordered_map_std_string_bool(unsigned int position) {
    std::unordered_map<dogen::yarn::name, std::unordered_map<std::string, bool> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_yarn_name(position + i), create_std_unordered_map_std_string_bool(position + i)));
    }
    return r;
}

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

enablement_repository_generator::enablement_repository_generator() : position_(0) { }

void enablement_repository_generator::
populate(const unsigned int position, result_type& v) {
    v.by_name(create_std_unordered_map_dogen_yarn_name_std_unordered_map_std_string_bool(position + 0));
}

enablement_repository_generator::result_type
enablement_repository_generator::create(const unsigned int position) {
    enablement_repository r;
    enablement_repository_generator::populate(position, r);
    return r;
}

enablement_repository_generator::result_type*
enablement_repository_generator::create_ptr(const unsigned int position) {
    enablement_repository* p = new enablement_repository();
    enablement_repository_generator::populate(position, *p);
    return p;
}

enablement_repository_generator::result_type
enablement_repository_generator::operator()() {
    return create(position_++);
}

} } } }
