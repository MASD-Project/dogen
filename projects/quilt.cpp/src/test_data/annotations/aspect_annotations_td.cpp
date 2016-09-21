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
#include "dogen/quilt.cpp/test_data/annotations/aspect_annotations_td.hpp"

namespace {

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace annotations {

aspect_annotations_generator::aspect_annotations_generator() : position_(0) { }

void aspect_annotations_generator::
populate(const unsigned int position, result_type& v) {
    v.requires_manual_default_constructor(create_bool(position + 0));
    v.requires_manual_move_constructor(create_bool(position + 1));
    v.requires_stream_manipulators(create_bool(position + 2));
}

aspect_annotations_generator::result_type
aspect_annotations_generator::create(const unsigned int position) {
    aspect_annotations r;
    aspect_annotations_generator::populate(position, r);
    return r;
}

aspect_annotations_generator::result_type*
aspect_annotations_generator::create_ptr(const unsigned int position) {
    aspect_annotations* p = new aspect_annotations();
    aspect_annotations_generator::populate(position, *p);
    return p;
}

aspect_annotations_generator::result_type
aspect_annotations_generator::operator()() {
    return create(position_++);
}

} } } }
