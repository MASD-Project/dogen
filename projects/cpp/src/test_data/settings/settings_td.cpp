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
#include "dogen/cpp/test_data/settings/global_settings_td.hpp"
#include "dogen/cpp/test_data/settings/local_settings_td.hpp"
#include "dogen/cpp/test_data/settings/settings_td.hpp"

namespace {

dogen::cpp::settings::global_settings
create_dogen_cpp_settings_global_settings(const unsigned int position) {
    return dogen::cpp::settings::global_settings_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::cpp::settings::local_settings
create_dogen_cpp_settings_local_settings(const unsigned int position) {
    return dogen::cpp::settings::local_settings_generator::create(position);
}

std::unordered_map<std::string, dogen::cpp::settings::local_settings> create_std_unordered_map_std_string_dogen_cpp_settings_local_settings(unsigned int position) {
    std::unordered_map<std::string, dogen::cpp::settings::local_settings> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_cpp_settings_local_settings(position + i)));
    }
    return r;
}

std::unordered_map<std::string, std::unordered_map<std::string, dogen::cpp::settings::local_settings> > create_std_unordered_map_std_string_std_unordered_map_std_string_dogen_cpp_settings_local_settings_(unsigned int position) {
    std::unordered_map<std::string, std::unordered_map<std::string, dogen::cpp::settings::local_settings> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_std_unordered_map_std_string_dogen_cpp_settings_local_settings(position + i)));
    }
    return r;
}

}

namespace dogen {
namespace cpp {
namespace settings {

settings_generator::settings_generator() : position_(0) { }

void settings_generator::
populate(const unsigned int position, result_type& v) {
    v.global_settings(create_dogen_cpp_settings_global_settings(position + 0));
    v.local_settings(create_std_unordered_map_std_string_std_unordered_map_std_string_dogen_cpp_settings_local_settings_(position + 1));
}

settings_generator::result_type
settings_generator::create(const unsigned int position) {
    settings r;
    settings_generator::populate(position, r);
    return r;
}
settings_generator::result_type*
settings_generator::create_ptr(const unsigned int position) {
    settings* p = new settings();
    settings_generator::populate(position, *p);
    return p;
}

settings_generator::result_type
settings_generator::operator()() {
    return create(position_++);
}

} } }
