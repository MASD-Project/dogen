/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#include "dogen/quilt.csharp/test_data/formattables/helper_configuration_td.hpp"

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

}

namespace dogen {
namespace quilt {
namespace csharp {
namespace formattables {

helper_configuration_generator::helper_configuration_generator() : position_(0) { }

void helper_configuration_generator::
populate(const unsigned int position, result_type& v) {
    v.helper_families(create_std_unordered_map_std_string_std_string(position + 0));
}

helper_configuration_generator::result_type
helper_configuration_generator::create(const unsigned int position) {
    helper_configuration r;
    helper_configuration_generator::populate(position, r);
    return r;
}

helper_configuration_generator::result_type*
helper_configuration_generator::create_ptr(const unsigned int position) {
    helper_configuration* p = new helper_configuration();
    helper_configuration_generator::populate(position, *p);
    return p;
}

helper_configuration_generator::result_type
helper_configuration_generator::operator()() {
    return create(position_++);
}

} } } }
