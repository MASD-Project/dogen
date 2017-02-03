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
#include "dogen/test_models/boost_model/test_data/time_duration_primitive_td.hpp"

namespace {

boost::posix_time::time_duration
create_boost_posix_time_time_duration(const unsigned int position) {
    unsigned int hour(position % 55);
    using boost::posix_time::time_duration;
    time_duration r(hour, 2, 3);
    return r;
}

}

namespace dogen {
namespace test_models {
namespace boost_model {

time_duration_primitive_generator::time_duration_primitive_generator() : position_(0) { }

void time_duration_primitive_generator::
populate(const unsigned int position, result_type& v) {
    v.value(create_boost_posix_time_time_duration(position + 1));
}

time_duration_primitive_generator::result_type
time_duration_primitive_generator::create(const unsigned int position) {
    time_duration_primitive r;
    time_duration_primitive_generator::populate(position, r);
    return r;
}

time_duration_primitive_generator::result_type*
time_duration_primitive_generator::create_ptr(const unsigned int position) {
    time_duration_primitive* r = new time_duration_primitive();
    time_duration_primitive_generator::populate(position, *r);
    return r;
}

time_duration_primitive_generator::result_type
time_duration_primitive_generator::operator()() {
    return create(position_++);
}

} } }
