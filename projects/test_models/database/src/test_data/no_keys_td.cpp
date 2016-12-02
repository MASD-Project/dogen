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
#include "dogen/test_models/database/test_data/no_keys_td.hpp"

namespace {

int create_int(const unsigned int position) {
    return position;
}

unsigned int create_unsigned_int(const unsigned int position) {
    return static_cast<unsigned int>(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

boost::posix_time::ptime
create_boost_posix_time_ptime(const unsigned int position) {
    unsigned int day(1 + (position % 27));
    using boost::gregorian::date;
    using boost::posix_time::ptime;
    using boost::posix_time::time_duration;
    date d(2002, 2, day);
    ptime r(d, time_duration(1,2,3));
    return r;
}

}

namespace dogen {
namespace test_models {
namespace database {

no_keys_generator::no_keys_generator() : position_(0) { }

void no_keys_generator::
populate(const unsigned int position, result_type& v) {
    v.prop_0(create_int(position + 0));
    v.prop_1(create_unsigned_int(position + 1));
    v.prop_2(create_std_string(position + 2));
    v.prop_3(create_boost_posix_time_ptime(position + 3));
}

no_keys_generator::result_type
no_keys_generator::create(const unsigned int position) {
    no_keys r;
    no_keys_generator::populate(position, r);
    return r;
}

no_keys_generator::result_type*
no_keys_generator::create_ptr(const unsigned int position) {
    no_keys* p = new no_keys();
    no_keys_generator::populate(position, *p);
    return p;
}

no_keys_generator::result_type
no_keys_generator::operator()() {
    return create(position_++);
}

} } }
