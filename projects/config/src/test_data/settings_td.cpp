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
#include "dogen/config/test_data/cpp_settings_td.hpp"
#include "dogen/config/test_data/modeling_settings_td.hpp"
#include "dogen/config/test_data/output_settings_td.hpp"
#include "dogen/config/test_data/settings_td.hpp"
#include "dogen/config/test_data/troubleshooting_settings_td.hpp"

namespace {

dogen::config::modeling_settings
create_dogen_config_modeling_settings(const unsigned int position) {
    return dogen::config::modeling_settings_generator::create(position);
}

dogen::config::cpp_settings
create_dogen_config_cpp_settings(const unsigned int position) {
    return dogen::config::cpp_settings_generator::create(position);
}

dogen::config::troubleshooting_settings
create_dogen_config_troubleshooting_settings(const unsigned int position) {
    return dogen::config::troubleshooting_settings_generator::create(position);
}

dogen::config::output_settings
create_dogen_config_output_settings(const unsigned int position) {
    return dogen::config::output_settings_generator::create(position);
}

}

namespace dogen {
namespace config {

settings_generator::settings_generator() : position_(0) { }

void settings_generator::
populate(const unsigned int position, result_type& v) {
    v.modeling(create_dogen_config_modeling_settings(position + 0));
    v.cpp(create_dogen_config_cpp_settings(position + 1));
    v.troubleshooting(create_dogen_config_troubleshooting_settings(position + 2));
    v.output(create_dogen_config_output_settings(position + 3));
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

} }
