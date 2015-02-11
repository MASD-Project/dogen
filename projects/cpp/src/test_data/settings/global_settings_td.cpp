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
#include "dogen/cpp/test_data/settings/cpp_settings_td.hpp"
#include "dogen/cpp/test_data/settings/facet_settings_td.hpp"
#include "dogen/cpp/test_data/settings/global_formatter_settings_td.hpp"
#include "dogen/cpp/test_data/settings/global_settings_td.hpp"
#include "dogen/formatters/test_data/general_settings_td.hpp"

namespace {

dogen::formatters::general_settings
create_dogen_formatters_general_settings(const unsigned int position) {
    return dogen::formatters::general_settings_generator::create(position);
}

dogen::cpp::settings::cpp_settings
create_dogen_cpp_settings_cpp_settings(const unsigned int position) {
    return dogen::cpp::settings::cpp_settings_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::cpp::settings::facet_settings
create_dogen_cpp_settings_facet_settings(const unsigned int position) {
    return dogen::cpp::settings::facet_settings_generator::create(position);
}

std::unordered_map<std::string, dogen::cpp::settings::facet_settings> create_std_unordered_map_std_string_dogen_cpp_settings_facet_settings(unsigned int position) {
    std::unordered_map<std::string, dogen::cpp::settings::facet_settings> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_cpp_settings_facet_settings(position + i)));
    }
    return r;
}

dogen::cpp::settings::global_formatter_settings
create_dogen_cpp_settings_global_formatter_settings(const unsigned int position) {
    return dogen::cpp::settings::global_formatter_settings_generator::create(position);
}

std::unordered_map<std::string, dogen::cpp::settings::global_formatter_settings> create_std_unordered_map_std_string_dogen_cpp_settings_global_formatter_settings(unsigned int position) {
    std::unordered_map<std::string, dogen::cpp::settings::global_formatter_settings> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_cpp_settings_global_formatter_settings(position + i)));
    }
    return r;
}

}

namespace dogen {
namespace cpp {
namespace settings {

global_settings_generator::global_settings_generator() : position_(0) { }

void global_settings_generator::
populate(const unsigned int position, result_type& v) {
    v.general_settings(create_dogen_formatters_general_settings(position + 0));
    v.cpp_settings(create_dogen_cpp_settings_cpp_settings(position + 1));
    v.facet_settings(create_std_unordered_map_std_string_dogen_cpp_settings_facet_settings(position + 2));
    v.formatter_settings(create_std_unordered_map_std_string_dogen_cpp_settings_global_formatter_settings(position + 3));
}

global_settings_generator::result_type
global_settings_generator::create(const unsigned int position) {
    global_settings r;
    global_settings_generator::populate(position, r);
    return r;
}
global_settings_generator::result_type*
global_settings_generator::create_ptr(const unsigned int position) {
    global_settings* p = new global_settings();
    global_settings_generator::populate(position, *p);
    return p;
}

global_settings_generator::result_type
global_settings_generator::operator()() {
    return create(position_++);
}

} } }
