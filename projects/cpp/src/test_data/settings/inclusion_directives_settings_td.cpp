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
#include "dogen/cpp/test_data/settings/inclusion_directives_settings_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::unordered_map<std::string, std::string> create_std_unordered_map_std_string_std_string(unsigned int position) {
    std::unordered_map<std::string, std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_std_string(position + i)));
    }
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

}

namespace dogen {
namespace cpp {
namespace settings {

inclusion_directives_settings_generator::inclusion_directives_settings_generator() : position_(0) { }

void inclusion_directives_settings_generator::
populate(const unsigned int position, result_type& v) {
    v.inclusion_directives(create_std_unordered_map_std_string_std_string(position + 0));
    v.requires_inclusion_directives(create_bool(position + 1));
}

inclusion_directives_settings_generator::result_type
inclusion_directives_settings_generator::create(const unsigned int position) {
    inclusion_directives_settings r;
    inclusion_directives_settings_generator::populate(position, r);
    return r;
}
inclusion_directives_settings_generator::result_type*
inclusion_directives_settings_generator::create_ptr(const unsigned int position) {
    inclusion_directives_settings* p = new inclusion_directives_settings();
    inclusion_directives_settings_generator::populate(position, *p);
    return p;
}

inclusion_directives_settings_generator::result_type
inclusion_directives_settings_generator::operator()() {
    return create(position_++);
}

} } }
