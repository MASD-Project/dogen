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
#include "masd.dogen.generation/test_data/formatters/comment_style_td.hpp"

namespace masd::dogen::generation::formatters {

comment_style_generator::comment_style_generator() : position_(0) { }
void comment_style_generator::
populate(const unsigned int position, result_type& v) {
    v = static_cast<comment_style>(position % 7);
}

comment_style_generator::result_type
comment_style_generator::create(const unsigned int  position) {
    result_type r;
    comment_style_generator::populate(position, r);
    return r;
}

comment_style_generator::result_type
comment_style_generator::operator()() {
    return create(position_++);
}

}
