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
#include "dogen.relational/test_data/tracing/run_td.hpp"
#include "dogen.relational/test_data/tracing/json_td.hpp"
#include "dogen.relational/test_data/tracing/run_id_td.hpp"
#include "dogen.relational/test_data/tracing/activity_td.hpp"
#include "dogen.relational/test_data/tracing/transform_id_td.hpp"

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

dogen::relational::tracing::run_id
create_dogen_relational_tracing_run_id(const unsigned int position) {
    return dogen::relational::tracing::run_id_generator::create(position);
}

dogen::relational::tracing::activity
create_dogen_relational_tracing_activity(const unsigned int position) {
    return dogen::relational::tracing::activity_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::relational::tracing::json
create_dogen_relational_tracing_json(const unsigned int position) {
    return dogen::relational::tracing::json_generator::create(position);
}

dogen::relational::tracing::transform_id
create_dogen_relational_tracing_transform_id(const unsigned int position) {
    return dogen::relational::tracing::transform_id_generator::create(position);
}

}

namespace dogen::relational::tracing {

run_generator::run_generator() : position_(0) { }

void run_generator::
populate(const unsigned int position, result_type& v) {
    v.start(create_boost_posix_time_ptime(position + 0));
    v.end(create_boost_posix_time_ptime(position + 1));
    v.id(create_dogen_relational_tracing_run_id(position + 2));
    v.activity(create_dogen_relational_tracing_activity(position + 3));
    v.version(create_std_string(position + 4));
    v.configuration(create_dogen_relational_tracing_json(position + 5));
    v.top_level_transform_id(create_dogen_relational_tracing_transform_id(position + 6));
}

run_generator::result_type
run_generator::create(const unsigned int position) {
    run r;
    run_generator::populate(position, r);
    return r;
}

run_generator::result_type*
run_generator::create_ptr(const unsigned int position) {
    run* p = new run();
    run_generator::populate(position, *p);
    return p;
}

run_generator::result_type
run_generator::operator()() {
    return create(position_++);
}

}
