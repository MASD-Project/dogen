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
#include "dogen/cpp/test_data/cpp_settings_td.hpp"
#include "dogen/cpp/test_data/facet_settings_td.hpp"
#include "dogen/cpp/test_data/settings_bundle_td.hpp"

namespace {

dogen::cpp::facet_settings
create_dogen_cpp_facet_settings(const unsigned int position) {
    return dogen::cpp::facet_settings_generator::create(position);
}

dogen::cpp::cpp_settings
create_dogen_cpp_cpp_settings(const unsigned int position) {
    return dogen::cpp::cpp_settings_generator::create(position);
}

}

namespace dogen {
namespace cpp {

settings_bundle_generator::settings_bundle_generator() : position_(0) { }

void settings_bundle_generator::
populate(const unsigned int position, result_type& v) {
    v.facet_settings(create_dogen_cpp_facet_settings(position + 0));
    v.cpp_settings(create_dogen_cpp_cpp_settings(position + 1));
}

settings_bundle_generator::result_type
settings_bundle_generator::create(const unsigned int position) {
    settings_bundle r;
    settings_bundle_generator::populate(position, r);
    return r;
}
settings_bundle_generator::result_type*
settings_bundle_generator::create_ptr(const unsigned int position) {
    settings_bundle* p = new settings_bundle();
    settings_bundle_generator::populate(position, *p);
    return p;
}

settings_bundle_generator::result_type
settings_bundle_generator::operator()() {
    return create(position_++);
}

} }
