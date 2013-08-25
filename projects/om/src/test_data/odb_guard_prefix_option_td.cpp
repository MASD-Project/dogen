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
#include "dogen/om/test_data/odb_guard_prefix_option_td.hpp"
#include "dogen/om/test_data/odb_option_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

}

namespace dogen {
namespace om {

odb_guard_prefix_option_generator::odb_guard_prefix_option_generator() : position_(0) { }

void odb_guard_prefix_option_generator::
populate(const unsigned int position, result_type& v) {
    dogen::om::odb_option_generator::populate(position, v);
    v.guard_prefix(create_std_string(position + 0));
}

odb_guard_prefix_option_generator::result_type
odb_guard_prefix_option_generator::create(const unsigned int position) {
    odb_guard_prefix_option r;
    odb_guard_prefix_option_generator::populate(position, r);
    return r;
}
odb_guard_prefix_option_generator::result_type*
odb_guard_prefix_option_generator::create_ptr(const unsigned int position) {
    odb_guard_prefix_option* p = new odb_guard_prefix_option();
    odb_guard_prefix_option_generator::populate(position, *p);
    return p;
}

odb_guard_prefix_option_generator::result_type
odb_guard_prefix_option_generator::operator()() {
    return create(position_++);
}

} }
