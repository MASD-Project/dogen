/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/config/test_data/output_options_td.hpp"

namespace {

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::vector<std::string> create_std_vector_std_string(unsigned int position) {
    std::vector<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_string(position + i));
    }
    return r;
}

}

namespace dogen {
namespace config {

output_options_generator::output_options_generator() : position_(0) { }

void output_options_generator::
populate(const unsigned int position, result_type& v) {
    v.output_to_stdout(create_bool(position + 0));
    v.output_to_file(create_bool(position + 1));
    v.delete_extra_files(create_bool(position + 2));
    v.force_write(create_bool(position + 3));
    v.ignore_patterns(create_std_vector_std_string(position + 4));
}

output_options_generator::result_type
output_options_generator::create(const unsigned int position) {
    output_options r;
    output_options_generator::populate(position, r);
    return r;
}

output_options_generator::result_type*
output_options_generator::create_ptr(const unsigned int position) {
    output_options* p = new output_options();
    output_options_generator::populate(position, *p);
    return p;
}

output_options_generator::result_type
output_options_generator::operator()() {
    return create(position_++);
}

} }
