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
#include "dogen.relational/test_data/tracing/log_td.hpp"
#include "dogen.relational/test_data/tracing/transform_id_td.hpp"

namespace {

dogen::relational::tracing::transform_id
create_dogen_relational_tracing_transform_id(const unsigned int position) {
    return dogen::relational::tracing::transform_id_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

}

namespace dogen::relational::tracing {

log_generator::log_generator() : position_(0) { }

void log_generator::
populate(const unsigned int position, result_type& v) {
    v.transform_id(create_dogen_relational_tracing_transform_id(position + 0));
    v.component(create_std_string(position + 1));
    v.message(create_std_string(position + 2));
}

log_generator::result_type
log_generator::create(const unsigned int position) {
    log r;
    log_generator::populate(position, r);
    return r;
}

log_generator::result_type*
log_generator::create_ptr(const unsigned int position) {
    log* p = new log();
    log_generator::populate(position, *p);
    return p;
}

log_generator::result_type
log_generator::operator()() {
    return create(position_++);
}

}
