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
#include "dogen/test_models/boost_model/test_data/ptime_primitive_td.hpp"

namespace {

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
namespace boost_model {

ptime_primitive_generator::ptime_primitive_generator() : position_(0) { }

void ptime_primitive_generator::
populate(const unsigned int position, result_type& v) {
    v.value(create_boost_posix_time_ptime(position + 1));
}

ptime_primitive_generator::result_type
ptime_primitive_generator::create(const unsigned int position) {
    ptime_primitive r;
    ptime_primitive_generator::populate(position, r);
    return r;
}

ptime_primitive_generator::result_type*
ptime_primitive_generator::create_ptr(const unsigned int position) {
    ptime_primitive* r = new ptime_primitive();
    ptime_primitive_generator::populate(position, *r);
    return r;
}

ptime_primitive_generator::result_type
ptime_primitive_generator::operator()() {
    return create(position_++);
}

} } }
