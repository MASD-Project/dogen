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
#include "dogen/stitch/test_data/segment_td.hpp"
#include "dogen/stitch/test_data/mixed_content_line_td.hpp"

namespace {

dogen::stitch::segment
create_dogen_stitch_segment(const unsigned int position) {
    return dogen::stitch::segment_generator::create(position);
}

std::list<dogen::stitch::segment> create_std_list_dogen_stitch_segment(unsigned int position) {
    std::list<dogen::stitch::segment> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_stitch_segment(position + i));
    }
    return r;
}

}

namespace dogen {
namespace stitch {

mixed_content_line_generator::mixed_content_line_generator() : position_(0) { }

void mixed_content_line_generator::
populate(const unsigned int position, result_type& v) {
    v.segments(create_std_list_dogen_stitch_segment(position + 0));
}

mixed_content_line_generator::result_type
mixed_content_line_generator::create(const unsigned int position) {
    mixed_content_line r;
    mixed_content_line_generator::populate(position, r);
    return r;
}
mixed_content_line_generator::result_type*
mixed_content_line_generator::create_ptr(const unsigned int position) {
    mixed_content_line* p = new mixed_content_line();
    mixed_content_line_generator::populate(position, *p);
    return p;
}

mixed_content_line_generator::result_type
mixed_content_line_generator::operator()() {
    return create(position_++);
}

} }
