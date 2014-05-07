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
#include "dogen/config/test_data/annotation_settings_td.hpp"
#include "dogen/config/test_data/cpp_settings_td.hpp"
#include "dogen/config/test_data/formatting_settings_td.hpp"

namespace {

dogen::config::cpp_settings
create_dogen_config_cpp_settings(const unsigned int position) {
    return dogen::config::cpp_settings_generator::create(position);
}

dogen::config::annotation_settings
create_dogen_config_annotation_settings(const unsigned int position) {
    return dogen::config::annotation_settings_generator::create(position);
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

}

namespace dogen {
namespace config {

formatting_settings_generator::formatting_settings_generator() : position_(0) { }

void formatting_settings_generator::
populate(const unsigned int position, result_type& v) {
    v.cpp(create_dogen_config_cpp_settings(position + 0));
    v.annotation(create_dogen_config_annotation_settings(position + 1));
    v.disable_model_module(create_bool(position + 2));
}

formatting_settings_generator::result_type
formatting_settings_generator::create(const unsigned int position) {
    formatting_settings r;
    formatting_settings_generator::populate(position, r);
    return r;
}
formatting_settings_generator::result_type*
formatting_settings_generator::create_ptr(const unsigned int position) {
    formatting_settings* p = new formatting_settings();
    formatting_settings_generator::populate(position, *p);
    return p;
}

formatting_settings_generator::result_type
formatting_settings_generator::operator()() {
    return create(position_++);
}

} }
