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
#include "dogen/cpp/test_data/abilities_td.hpp"

namespace {

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

}

namespace dogen {
namespace cpp {

abilities_generator::abilities_generator() : position_(0) { }

void abilities_generator::
populate(const unsigned int position, result_type& v) {
    v.is_comparable(create_bool(position + 0));
    v.is_visitable(create_bool(position + 1));
    v.is_immutable(create_bool(position + 2));
    v.is_original_parent_visitable(create_bool(position + 3));
}

abilities_generator::result_type
abilities_generator::create(const unsigned int position) {
    abilities r;
    abilities_generator::populate(position, r);
    return r;
}
abilities_generator::result_type*
abilities_generator::create_ptr(const unsigned int position) {
    abilities* p = new abilities();
    abilities_generator::populate(position, *p);
    return p;
}

abilities_generator::result_type
abilities_generator::operator()() {
    return create(position_++);
}

} }
