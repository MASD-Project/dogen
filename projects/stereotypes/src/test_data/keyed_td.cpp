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
#include "dogen/stereotypes/test_data/keyed_td.hpp"
#include "dogen/stereotypes/test_data/keyed_versioned_key_td.hpp"

namespace {

int create_int(const unsigned int position) {
    return position;
}

dogen::stereotypes::keyed_versioned_key
create_dogen_stereotypes_keyed_versioned_key(const unsigned int position) {
    return dogen::stereotypes::keyed_versioned_key_generator::create(position);
}

}

namespace dogen {
namespace stereotypes {

keyed_generator::keyed_generator() : position_(0) { }

void keyed_generator::
populate(const unsigned int position, result_type& v) {
    v.prop_0(create_int(position + 0));
    v.versioned_key(create_dogen_stereotypes_keyed_versioned_key(position + 1));
}

keyed_generator::result_type
keyed_generator::create(const unsigned int position) {
    keyed r;
    keyed_generator::populate(position, r);
    return r;
}
keyed_generator::result_type*
keyed_generator::create_ptr(const unsigned int position) {
    keyed* p = new keyed();
    keyed_generator::populate(position, *p);
    return p;
}

keyed_generator::result_type
keyed_generator::operator()() {
    return create(position_++);
}

} }
