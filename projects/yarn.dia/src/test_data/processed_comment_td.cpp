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
#include "dogen/yarn.dia/test_data/processed_comment_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::pair<std::string, std::string>
create_std_pair_std_string_std_string(unsigned int position) {
    std::pair<std::string, std::string> r(
        create_std_string(position),
        create_std_string(position));
    return r;
}

std::list<std::pair<std::string, std::string> > create_std_list_std_pair_std_string_std_string(unsigned int position) {
    std::list<std::pair<std::string, std::string> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_pair_std_string_std_string(position + i));
    }
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

}

namespace dogen {
namespace yarn {
namespace dia {

processed_comment_generator::processed_comment_generator() : position_(0) { }

void processed_comment_generator::
populate(const unsigned int position, result_type& v) {
    v.documentation(create_std_string(position + 0));
    v.key_value_pairs(create_std_list_std_pair_std_string_std_string(position + 1));
    v.applicable_to_parent_object(create_bool(position + 2));
    v.original_content(create_std_string(position + 3));
    v.external_modules(create_std_string(position + 4));
}

processed_comment_generator::result_type
processed_comment_generator::create(const unsigned int position) {
    processed_comment r;
    processed_comment_generator::populate(position, r);
    return r;
}

processed_comment_generator::result_type*
processed_comment_generator::create_ptr(const unsigned int position) {
    processed_comment* p = new processed_comment();
    processed_comment_generator::populate(position, *p);
    return p;
}

processed_comment_generator::result_type
processed_comment_generator::operator()() {
    return create(position_++);
}

} } }
