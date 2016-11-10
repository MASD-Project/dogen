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
#include "dogen/options/test_data/input_options_td.hpp"

namespace {

boost::filesystem::path
create_boost_filesystem_path(const unsigned int position) {
    std::ostringstream s;
    s << "/a/path/number_" << position;
    return boost::filesystem::path(s.str());
}

}

namespace dogen {
namespace options {

input_options_generator::input_options_generator() : position_(0) { }

void input_options_generator::
populate(const unsigned int position, result_type& v) {
    v.target(create_boost_filesystem_path(position + 0));
}

input_options_generator::result_type
input_options_generator::create(const unsigned int position) {
    input_options r;
    input_options_generator::populate(position, r);
    return r;
}

input_options_generator::result_type*
input_options_generator::create_ptr(const unsigned int position) {
    input_options* p = new input_options();
    input_options_generator::populate(position, *p);
    return p;
}

input_options_generator::result_type
input_options_generator::operator()() {
    return create(position_++);
}

} }
