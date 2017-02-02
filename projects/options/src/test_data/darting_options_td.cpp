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
#include "dogen/options/test_data/darting_options_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

bool create_bool(const unsigned int position) {
    if (position == 0)
        return true;
    else if (position == 1)
        return false;
    else
        return (position % 2) == 0;
}

}

namespace dogen {
namespace options {

darting_options_generator::darting_options_generator() : position_(0) { }

void darting_options_generator::
populate(const unsigned int position, result_type& v) {
    v.log_level(create_std_string(position + 0));
    v.force_write(create_bool(position + 1));
    v.product_name(create_std_string(position + 2));
}

darting_options_generator::result_type
darting_options_generator::create(const unsigned int position) {
    darting_options r;
    darting_options_generator::populate(position, r);
    return r;
}

darting_options_generator::result_type*
darting_options_generator::create_ptr(const unsigned int position) {
    darting_options* p = new darting_options();
    darting_options_generator::populate(position, *p);
    return p;
}

darting_options_generator::result_type
darting_options_generator::operator()() {
    return create(position_++);
}

} }
