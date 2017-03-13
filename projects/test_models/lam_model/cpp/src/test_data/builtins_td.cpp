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
#include "dogen/test_models/lam_model/test_data/builtins_td.hpp"

namespace {

char create_char(const unsigned int position) {
    return static_cast<char>(((position % 95) + 32) == 34) ? 35 : ((position % 95) + 32);
}

unsigned char create_unsigned_char(const unsigned int position) {
    return static_cast<unsigned char>(((position % 95) + 32) == 34) ? 35 : ((position % 95) + 32);
}

std::int8_t create_std_int8_t(const unsigned int position) {
    return static_cast<std::int8_t>(((position % 95) + 32) == 34) ? 35 : ((position % 95) + 32);
}

std::int16_t create_std_int16_t(const unsigned int position) {
    return static_cast<std::int16_t>(position);
}

std::int32_t create_std_int32_t(const unsigned int position) {
    return static_cast<std::int32_t>(position);
}

std::int64_t create_std_int64_t(const unsigned int position) {
    return static_cast<std::int64_t>(position);
}

int create_int(const unsigned int position) {
    return static_cast<int>(position);
}

float create_float(const unsigned int position) {
    return static_cast<float>(position);
}

double create_double(const unsigned int position) {
    return static_cast<double>(position);
}

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

}

namespace dogen {
namespace test_models {
namespace lam_model {

builtins_generator::builtins_generator() : position_(0) { }

void builtins_generator::
populate(const unsigned int position, result_type& v) {
    v.prop_0(create_char(position + 0));
    v.prop_1(create_unsigned_char(position + 1));
    v.prop_2(create_std_int8_t(position + 2));
    v.prop_3(create_std_int16_t(position + 3));
    v.prop_4(create_std_int32_t(position + 4));
    v.prop_5(create_std_int64_t(position + 5));
    v.prop_6(create_int(position + 6));
    v.prop_7(create_float(position + 7));
    v.prop_8(create_double(position + 8));
    v.prop_9(create_bool(position + 9));
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
