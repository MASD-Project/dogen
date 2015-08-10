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
#include "dogen/tack/test_data/name_td.hpp"
#include "dogen/cpp/test_data/settings/bundle_td.hpp"
#include "dogen/cpp/test_data/settings/bundle_repository_td.hpp"

namespace {

dogen::tack::name
create_dogen_tack_name(const unsigned int position) {
    return dogen::tack::name_generator::create(position);
}

dogen::cpp::settings::bundle
create_dogen_cpp_settings_bundle(const unsigned int position) {
    return dogen::cpp::settings::bundle_generator::create(position);
}

std::unordered_map<dogen::tack::name, dogen::cpp::settings::bundle> create_std_unordered_map_dogen_tack_name_dogen_cpp_settings_bundle(unsigned int position) {
    std::unordered_map<dogen::tack::name, dogen::cpp::settings::bundle> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_tack_name(position + i), create_dogen_cpp_settings_bundle(position + i)));
    }
    return r;
}

}

namespace dogen {
namespace cpp {
namespace settings {

bundle_repository_generator::bundle_repository_generator() : position_(0) { }

void bundle_repository_generator::
populate(const unsigned int position, result_type& v) {
    v.bundles_by_name(create_std_unordered_map_dogen_tack_name_dogen_cpp_settings_bundle(position + 0));
}

bundle_repository_generator::result_type
bundle_repository_generator::create(const unsigned int position) {
    bundle_repository r;
    bundle_repository_generator::populate(position, r);
    return r;
}

bundle_repository_generator::result_type*
bundle_repository_generator::create_ptr(const unsigned int position) {
    bundle_repository* p = new bundle_repository();
    bundle_repository_generator::populate(position, *p);
    return p;
}

bundle_repository_generator::result_type
bundle_repository_generator::operator()() {
    return create(position_++);
}

} } }
