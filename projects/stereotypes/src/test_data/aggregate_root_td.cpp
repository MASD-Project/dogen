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
#include "dogen/stereotypes/test_data/aggregate_root_td.hpp"

namespace {

int create_int(const unsigned int position) {
    return position;
}

}

namespace dogen {
namespace stereotypes {

aggregate_root_generator::aggregate_root_generator() : position_(0) { }

void aggregate_root_generator::
populate(const unsigned int position, result_type& v) {
    v.prop_0(create_int(position + 0));
}

aggregate_root_generator::result_type
aggregate_root_generator::create(const unsigned int position) {
    aggregate_root r;
    aggregate_root_generator::populate(position, r);
    return r;
}
aggregate_root_generator::result_type*
aggregate_root_generator::create_ptr(const unsigned int position) {
    aggregate_root* p = new aggregate_root();
    aggregate_root_generator::populate(position, *p);
    return p;
}

aggregate_root_generator::result_type
aggregate_root_generator::operator()() {
    return create(position_++);
}

} }
