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
#include "dogen/config/test_data/annotation_settings_td.hpp"
#include "dogen/config/test_data/code_generation_marker_settings_td.hpp"

namespace {

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::list<std::string> create_std_list_std_string(unsigned int position) {
    std::list<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_string(position + i));
    }
    return r;
}

dogen::config::code_generation_marker_settings
create_dogen_config_code_generation_marker_settings(const unsigned int position) {
    return dogen::config::code_generation_marker_settings_generator::create(position);
}

}

namespace dogen {
namespace config {

annotation_settings_generator::annotation_settings_generator() : position_(0) { }

void annotation_settings_generator::
populate(const unsigned int position, result_type& v) {
    v.generate_preamble(create_bool(position + 0));
    v.copyright(create_std_list_std_string(position + 1));
    v.licence_name(create_std_string(position + 2));
    v.modeline_group_name(create_std_list_std_string(position + 3));
    v.code_generation_marker(create_dogen_config_code_generation_marker_settings(position + 4));
}

annotation_settings_generator::result_type
annotation_settings_generator::create(const unsigned int position) {
    annotation_settings r;
    annotation_settings_generator::populate(position, r);
    return r;
}
annotation_settings_generator::result_type*
annotation_settings_generator::create_ptr(const unsigned int position) {
    annotation_settings* p = new annotation_settings();
    annotation_settings_generator::populate(position, *p);
    return p;
}

annotation_settings_generator::result_type
annotation_settings_generator::operator()() {
    return create(position_++);
}

} }
