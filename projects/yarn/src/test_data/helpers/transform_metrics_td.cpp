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
#include "dogen/yarn/test_data/helpers/transform_metrics_td.hpp"

namespace {

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

dogen::yarn::helpers::transform_metrics*
create_dogen_yarn_helpers_transform_metrics_ptr(const unsigned int) {
    return nullptr;
}

boost::shared_ptr<dogen::yarn::helpers::transform_metrics>
create_boost_shared_ptr_dogen_yarn_helpers_transform_metrics(unsigned int position) {
    boost::shared_ptr<dogen::yarn::helpers::transform_metrics> r(
        create_dogen_yarn_helpers_transform_metrics_ptr(position));
    return r;
}

std::list<boost::shared_ptr<dogen::yarn::helpers::transform_metrics> > create_std_list_boost_shared_ptr_dogen_yarn_helpers_transform_metrics(unsigned int position) {
    std::list<boost::shared_ptr<dogen::yarn::helpers::transform_metrics> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_boost_shared_ptr_dogen_yarn_helpers_transform_metrics(position + i));
    }
    return r;
}

}

namespace dogen {
namespace yarn {
namespace helpers {

transform_metrics_generator::transform_metrics_generator() : position_(0) { }

void transform_metrics_generator::
populate(const unsigned int position, result_type& v) {
    v.id(create_std_string(position + 0));
    v.guid(create_std_string(position + 1));
    v.start(create_boost_posix_time_ptime(position + 2));
    v.finish(create_boost_posix_time_ptime(position + 3));
    v.children(create_std_list_boost_shared_ptr_dogen_yarn_helpers_transform_metrics(position + 4));
}

transform_metrics_generator::result_type
transform_metrics_generator::create(const unsigned int position) {
    transform_metrics r;
    transform_metrics_generator::populate(position, r);
    return r;
}

transform_metrics_generator::result_type*
transform_metrics_generator::create_ptr(const unsigned int position) {
    transform_metrics* p = new transform_metrics();
    transform_metrics_generator::populate(position, *p);
    return p;
}

transform_metrics_generator::result_type
transform_metrics_generator::operator()() {
    return create(position_++);
}

} } }
