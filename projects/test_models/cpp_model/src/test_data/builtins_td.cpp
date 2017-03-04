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
#include "dogen/test_models/cpp_model/test_data/builtins_td.hpp"

namespace {

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

char create_char(const unsigned int position) {
    return static_cast<char>(((position % 95) + 32) == 34) ? 35 : ((position % 95) + 32);
}

unsigned char create_unsigned_char(const unsigned int position) {
    return static_cast<unsigned char>(((position % 95) + 32) == 34) ? 35 : ((position % 95) + 32);
}

int create_int(const unsigned int position) {
    return static_cast<int>(position);
}

unsigned int create_unsigned_int(const unsigned int position) {
    return static_cast<unsigned int>(position);
}

long create_long(const unsigned int position) {
    return static_cast<long>(position);
}

unsigned long create_unsigned_long(const unsigned int position) {
    return static_cast<unsigned long>(position);
}

long long create_long_long(const unsigned int position) {
    return static_cast<long long>(position);
}

unsigned long long create_unsigned_long_long(const unsigned int position) {
    return static_cast<unsigned long long>(position);
}

short create_short(const unsigned int position) {
    return static_cast<short>(position);
}

unsigned short create_unsigned_short(const unsigned int position) {
    return static_cast<unsigned short>(position);
}

double create_double(const unsigned int position) {
    return static_cast<double>(position);
}

float create_float(const unsigned int position) {
    return static_cast<float>(position);
}

}

namespace dogen {
namespace test_models {
namespace cpp_model {

builtins_generator::builtins_generator() : position_(0) { }

void builtins_generator::
populate(const unsigned int position, result_type& v) {
    v.bool_property(create_bool(position + 0));
    v.char_property(create_char(position + 1));
    v.uchar_property(create_unsigned_char(position + 2));
    v.int_property(create_int(position + 3));
    v.uint_property(create_unsigned_int(position + 4));
    v.long_property(create_long(position + 5));
    v.ulong_property(create_unsigned_long(position + 6));
    v.long_long_property(create_long_long(position + 7));
    v.ulong_long_property(create_unsigned_long_long(position + 8));
    v.short_property(create_short(position + 9));
    v.ushort_property(create_unsigned_short(position + 10));
    v.double_property(create_double(position + 11));
    v.float_property(create_float(position + 12));
}

builtins_generator::result_type
builtins_generator::create(const unsigned int position) {
    builtins r;
    builtins_generator::populate(position, r);
    return r;
}

builtins_generator::result_type*
builtins_generator::create_ptr(const unsigned int position) {
    builtins* p = new builtins();
    builtins_generator::populate(position, *p);
    return p;
}

builtins_generator::result_type
builtins_generator::operator()() {
    return create(position_++);
}

} } }
