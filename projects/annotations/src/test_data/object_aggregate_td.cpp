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
#include "dogen/annotations/test_data/object_td.hpp"
#include "dogen/annotations/test_data/object_aggregate_td.hpp"

namespace {

dogen::annotations::object
create_dogen_annotations_object(const unsigned int position) {
    return dogen::annotations::object_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::unordered_map<std::string, dogen::annotations::object> create_std_unordered_map_std_string_dogen_annotations_object(unsigned int position) {
    std::unordered_map<std::string, dogen::annotations::object> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_annotations_object(position + i)));
    }
    return r;
}

}

namespace dogen {
namespace annotations {

object_aggregate_generator::object_aggregate_generator() : position_(0) { }

void object_aggregate_generator::
populate(const unsigned int position, result_type& v) {
    v.element(create_dogen_annotations_object(position + 0));
    v.attributes(create_std_unordered_map_std_string_dogen_annotations_object(position + 1));
}

object_aggregate_generator::result_type
object_aggregate_generator::create(const unsigned int position) {
    object_aggregate r;
    object_aggregate_generator::populate(position, r);
    return r;
}

object_aggregate_generator::result_type*
object_aggregate_generator::create_ptr(const unsigned int position) {
    object_aggregate* p = new object_aggregate();
    object_aggregate_generator::populate(position, *p);
    return p;
}

object_aggregate_generator::result_type
object_aggregate_generator::operator()() {
    return create(position_++);
}

} }
