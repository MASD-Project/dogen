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
#include "dogen/quilt.cpp/test_data/formattables/facet_profile_td.hpp"

namespace {

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

facet_profile_generator::facet_profile_generator() : position_(0) { }

void facet_profile_generator::
populate(const unsigned int position, result_type& v) {
    v.enabled(create_bool(position + 0));
    v.overwrite(create_bool(position + 1));
}

facet_profile_generator::result_type
facet_profile_generator::create(const unsigned int position) {
    facet_profile r;
    facet_profile_generator::populate(position, r);
    return r;
}

facet_profile_generator::result_type*
facet_profile_generator::create_ptr(const unsigned int position) {
    facet_profile* p = new facet_profile();
    facet_profile_generator::populate(position, *p);
    return p;
}

facet_profile_generator::result_type
facet_profile_generator::operator()() {
    return create(position_++);
}

} } } }
