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
#include "dogen/boost_model/test_data/class_f_td.hpp"

namespace {

boost::filesystem::path
create_boost_filesystem_path(const unsigned int position) {
    std::ostringstream s;
    s << "/a/path/number_" << position;
    return boost::filesystem::path(s.str());
}

boost::gregorian::date
create_boost_gregorian_date(const unsigned int position) {
    unsigned int day(position % 28);
    boost::gregorian::date r(2002, 2, day);
    return r;
}

boost::posix_time::ptime
create_boost_posix_time_ptime(const unsigned int position) {
    unsigned int day(position % 28);
    using boost::gregorian::date;
    using boost::posix_time::ptime;
    using boost::posix_time::time_duration;
    date d(2002, 2, day);    ptime r(d, time_duration(1,2,3));
    return r;
}

}

namespace dogen {
namespace boost_model {

class_f_generator::class_f_generator() : position_(0) { }

void class_f_generator::
populate(const unsigned int position, result_type& v) {
    v.prop_0(create_boost_filesystem_path(position + 0));
    v.prop_1(create_boost_gregorian_date(position + 1));
    v.prop_2(create_boost_posix_time_ptime(position + 2));
}

class_f_generator::result_type
class_f_generator::create(const unsigned int position) {
    class_f r;
    class_f_generator::populate(position, r);
    return r;
}
class_f_generator::result_type*
class_f_generator::create_ptr(const unsigned int position) {
    class_f* p = new class_f();
    class_f_generator::populate(position, *p);
    return p;
}

class_f_generator::result_type
class_f_generator::operator()() {
    return create(position_++);
}

} }
