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
#include "dogen/config/test_data/modeling_settings_td.hpp"
#include "dogen/config/test_data/reference_td.hpp"

namespace {

boost::filesystem::path
create_boost_filesystem_path(const unsigned int position) {
    std::ostringstream s;
    s << "/a/path/number_" << position;
    return boost::filesystem::path(s.str());
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::config::reference
create_dogen_config_reference(const unsigned int position) {
    return dogen::config::reference_generator::create(position);
}

std::vector<dogen::config::reference> create_std_vector_dogen_config_reference(unsigned int position) {
    std::vector<dogen::config::reference> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_dogen_config_reference(position + i));
    }
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

}

namespace dogen {
namespace config {

modeling_settings_generator::modeling_settings_generator() : position_(0) { }

void modeling_settings_generator::
populate(const unsigned int position, result_type& v) {
    v.target(create_boost_filesystem_path(position + 0));
    v.external_package_path(create_std_string(position + 1));
    v.references(create_std_vector_dogen_config_reference(position + 2));
    v.verbose(create_bool(position + 3));
    v.disable_model_package(create_bool(position + 4));
}

modeling_settings_generator::result_type
modeling_settings_generator::create(const unsigned int position) {
    modeling_settings r;
    modeling_settings_generator::populate(position, r);
    return r;
}
modeling_settings_generator::result_type*
modeling_settings_generator::create_ptr(const unsigned int position) {
    modeling_settings* p = new modeling_settings();
    modeling_settings_generator::populate(position, *p);
    return p;
}

modeling_settings_generator::result_type
modeling_settings_generator::operator()() {
    return create(position_++);
}

} }
