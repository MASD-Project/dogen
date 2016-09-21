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
#include "dogen/yarn/test_data/generalization_annotations_td.hpp"

namespace {

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

boost::optional<bool>
create_boost_optional_bool(unsigned int position) {
    boost::optional<bool> r(
        create_bool(position));
    return r;
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

boost::optional<std::string>
create_boost_optional_std_string(unsigned int position) {
    boost::optional<std::string> r(
        create_std_string(position));
    return r;
}

}

namespace dogen {
namespace yarn {

generalization_annotations_generator::generalization_annotations_generator() : position_(0) { }

void generalization_annotations_generator::
populate(const unsigned int position, result_type& v) {
    v.is_final(create_boost_optional_bool(position + 0));
    v.parent(create_boost_optional_std_string(position + 1));
}

generalization_annotations_generator::result_type
generalization_annotations_generator::create(const unsigned int position) {
    generalization_annotations r;
    generalization_annotations_generator::populate(position, r);
    return r;
}

generalization_annotations_generator::result_type*
generalization_annotations_generator::create_ptr(const unsigned int position) {
    generalization_annotations* p = new generalization_annotations();
    generalization_annotations_generator::populate(position, *p);
    return p;
}

generalization_annotations_generator::result_type
generalization_annotations_generator::operator()() {
    return create(position_++);
}

} }
