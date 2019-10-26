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
#include "dogen.relational/test_data/tracing/transform_components_td.hpp"
#include "dogen.relational/test_data/tracing/transform_components_key_td.hpp"

namespace {

dogen::relational::tracing::transform_components_key
create_dogen_relational_tracing_transform_components_key(const unsigned int position) {
    return dogen::relational::tracing::transform_components_key_generator::create(position);
}

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

}

namespace dogen::relational::tracing {

transform_components_generator::transform_components_generator() : position_(0) { }

void transform_components_generator::
populate(const unsigned int position, result_type& v) {
    v.key(create_dogen_relational_tracing_transform_components_key(position + 0));
    v.start(create_boost_posix_time_ptime(position + 1));
}

transform_components_generator::result_type
transform_components_generator::create(const unsigned int position) {
    transform_components r;
    transform_components_generator::populate(position, r);
    return r;
}

transform_components_generator::result_type*
transform_components_generator::create_ptr(const unsigned int position) {
    transform_components* p = new transform_components();
    transform_components_generator::populate(position, *p);
    return p;
}

transform_components_generator::result_type
transform_components_generator::operator()() {
    return create(position_++);
}

}
