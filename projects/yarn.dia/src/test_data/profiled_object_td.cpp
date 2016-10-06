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
#include "dogen/yarn.dia/test_data/profile_td.hpp"
#include "dogen/yarn.dia/test_data/profiled_object_td.hpp"
#include "dogen/yarn.dia/test_data/processed_object_td.hpp"

namespace {

dogen::yarn::dia::processed_object
create_dogen_yarn_dia_processed_object(const unsigned int position) {
    return dogen::yarn::dia::processed_object_generator::create(position);
}

dogen::yarn::dia::profile
create_dogen_yarn_dia_profile(const unsigned int position) {
    return dogen::yarn::dia::profile_generator::create(position);
}

}

namespace dogen {
namespace yarn {
namespace dia {

profiled_object_generator::profiled_object_generator() : position_(0) { }

void profiled_object_generator::
populate(const unsigned int position, result_type& v) {
    v.object(create_dogen_yarn_dia_processed_object(position + 0));
    v.profile(create_dogen_yarn_dia_profile(position + 1));
}

profiled_object_generator::result_type
profiled_object_generator::create(const unsigned int position) {
    profiled_object r;
    profiled_object_generator::populate(position, r);
    return r;
}

profiled_object_generator::result_type*
profiled_object_generator::create_ptr(const unsigned int position) {
    profiled_object* p = new profiled_object();
    profiled_object_generator::populate(position, *p);
    return p;
}

profiled_object_generator::result_type
profiled_object_generator::operator()() {
    return create(position_++);
}

} } }
