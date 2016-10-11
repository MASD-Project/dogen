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
#include "dogen/annotations/test_data/annotation_td.hpp"
#include "dogen/annotations/test_data/field_instance_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::annotations::field_instance
create_dogen_annotations_field_instance(const unsigned int position) {
    return dogen::annotations::field_instance_generator::create(position);
}

std::unordered_map<std::string, dogen::annotations::field_instance> create_std_unordered_map_std_string_dogen_annotations_field_instance(unsigned int position) {
    std::unordered_map<std::string, dogen::annotations::field_instance> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_annotations_field_instance(position + i)));
    }
    return r;
}

}

namespace dogen {
namespace annotations {

annotation_generator::annotation_generator() : position_(0) { }

void annotation_generator::
populate(const unsigned int position, result_type& v) {
    v.body(create_std_unordered_map_std_string_dogen_annotations_field_instance(position + 0));
}

annotation_generator::result_type
annotation_generator::create(const unsigned int position) {
    annotation r;
    annotation_generator::populate(position, r);
    return r;
}

annotation_generator::result_type*
annotation_generator::create_ptr(const unsigned int position) {
    annotation* p = new annotation();
    annotation_generator::populate(position, *p);
    return p;
}

annotation_generator::result_type
annotation_generator::operator()() {
    return create(position_++);
}

} }
