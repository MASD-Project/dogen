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
#include "dogen/stitch/test_data/segment_td.hpp"
#include "dogen/stitch/test_data/segment_types_td.hpp"

namespace {

dogen::stitch::segment_types
create_dogen_stitch_segment_types(const unsigned int position) {
    return dogen::stitch::segment_types_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

}

namespace dogen {
namespace stitch {

segment_generator::segment_generator() : position_(0) { }

void segment_generator::
populate(const unsigned int position, result_type& v) {
    v.type(create_dogen_stitch_segment_types(position + 0));
    v.content(create_std_string(position + 1));
}

segment_generator::result_type
segment_generator::create(const unsigned int position) {
    segment r;
    segment_generator::populate(position, r);
    return r;
}

segment_generator::result_type*
segment_generator::create_ptr(const unsigned int position) {
    segment* p = new segment();
    segment_generator::populate(position, *p);
    return p;
}

segment_generator::result_type
segment_generator::operator()() {
    return create(position_++);
}

} }
