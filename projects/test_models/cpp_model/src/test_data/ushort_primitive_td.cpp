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
#include "dogen/test_models/cpp_model/test_data/ushort_primitive_td.hpp"

namespace {

unsigned short create_unsigned_short(const unsigned int position) {
    return static_cast<unsigned short>(position);
}

}

namespace dogen {
namespace test_models {
namespace cpp_model {

ushort_primitive_generator::ushort_primitive_generator() : position_(0) { }

void ushort_primitive_generator::
populate(const unsigned int position, result_type& v) {
    v.value(create_unsigned_short(position + 1));
}

ushort_primitive_generator::result_type
ushort_primitive_generator::create(const unsigned int position) {
    ushort_primitive r;
    ushort_primitive_generator::populate(position, r);
    return r;
}

ushort_primitive_generator::result_type*
ushort_primitive_generator::create_ptr(const unsigned int position) {
    ushort_primitive* r = new ushort_primitive();
    ushort_primitive_generator::populate(position, *r);
    return r;
}

ushort_primitive_generator::result_type
ushort_primitive_generator::operator()() {
    return create(position_++);
}

} } }
