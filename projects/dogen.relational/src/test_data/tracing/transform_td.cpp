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
#include "dogen.relational/test_data/tracing/run_id_td.hpp"
#include "dogen.relational/test_data/tracing/transform_td.hpp"
#include "dogen.relational/test_data/tracing/transform_id_td.hpp"
#include "dogen.relational/test_data/tracing/transform_type_td.hpp"

namespace {

boost::posix_time::ptime
create_boost_posix_time_ptime(const unsigned int position) {
    const auto day(static_cast<unsigned short>(1 + (position % 27)));
    using boost::gregorian::date;
    using boost::posix_time::ptime;
    using boost::posix_time::time_duration;
    date d(2002, 2, day);
    ptime r(d, time_duration(1,2,3));
    return r;
}

dogen::relational::tracing::transform_id
create_dogen_relational_tracing_transform_id(const unsigned int position) {
    return dogen::relational::tracing::transform_id_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::relational::tracing::run_id
create_dogen_relational_tracing_run_id(const unsigned int position) {
    return dogen::relational::tracing::run_id_generator::create(position);
}

dogen::relational::tracing::transform_type
create_dogen_relational_tracing_transform_type(const unsigned int position) {
    return dogen::relational::tracing::transform_type_generator::create(position);
}

}

namespace dogen::relational::tracing {

transform_generator::transform_generator() : position_(0) { }

void transform_generator::
populate(const unsigned int position, result_type& v) {
    v.start(create_boost_posix_time_ptime(position + 0));
    v.end(create_boost_posix_time_ptime(position + 1));
    v.id(create_dogen_relational_tracing_transform_id(position + 2));
    v.name(create_std_string(position + 3));
    v.description(create_std_string(position + 4));
    v.run_id(create_dogen_relational_tracing_run_id(position + 5));
    v.type(create_dogen_relational_tracing_transform_type(position + 6));
}

transform_generator::result_type
transform_generator::create(const unsigned int position) {
    transform r;
    transform_generator::populate(position, r);
    return r;
}

transform_generator::result_type*
transform_generator::create_ptr(const unsigned int position) {
    transform* p = new transform();
    transform_generator::populate(position, *p);
    return p;
}

transform_generator::result_type
transform_generator::operator()() {
    return create(position_++);
}

}
