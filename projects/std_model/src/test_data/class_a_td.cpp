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
#include "dogen/std_model/test_data/class_a_td.hpp"
#include "dogen/std_model/test_data/versioned_key_td.hpp"

namespace {

std::string create_std_string(const std::string& prefix, const unsigned int position) {
    std::ostringstream s;
    s << prefix << "_" << position;

    return s.str();
}

dogen::std_model::versioned_key
create_dogen_std_model_versioned_key(const unsigned int position) {
    return dogen::std_model::versioned_key_generator::create(position);
}

}

namespace dogen {
namespace std_model {

class_a_generator::class_a_generator() : position_(0) { }

void class_a_generator::
populate(const unsigned int position, result_type& v) {
    v.prop0(create_std_string("prop0", position + 0));
    v.versioned_key(create_dogen_std_model_versioned_key(position + 0));
}

class_a_generator::result_type
class_a_generator::create(const unsigned int position) {
    class_a r;
    class_a_generator::populate(position, r);
    return r;
}

class_a_generator::result_type
class_a_generator::operator()() {
    return create(position_++);
}

} }
