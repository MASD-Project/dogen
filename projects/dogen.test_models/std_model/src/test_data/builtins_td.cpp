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
#include "dogen/test_models/std_model/test_data/builtins_td.hpp"

namespace {

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

std::uint8_t create_std_uint8_t(const unsigned int position) {
    return static_cast<std::uint8_t>(((position % 95) + 32) == 34) ? 35 : ((position % 95) + 32);
}

std::uint16_t create_std_uint16_t(const unsigned int position) {
    return static_cast<std::uint16_t>(position);
}

std::uint32_t create_std_uint32_t(const unsigned int position) {
    return static_cast<std::uint32_t>(position);
}

std::uint64_t create_std_uint64_t(const unsigned int position) {
    return static_cast<std::uint64_t>(position);
}

}

namespace dogen {
namespace test_models {
namespace std_model {

builtins_generator::builtins_generator() : position_(0) { }

void builtins_generator::
populate(const unsigned int position, result_type& v) {
    v.prop_0(create_std_int8_t(position + 0));
    v.prop_1(create_std_int16_t(position + 1));
    v.prop_2(create_std_int32_t(position + 2));
    v.prop_3(create_std_int64_t(position + 3));
    v.prop_4(create_std_uint8_t(position + 4));
    v.prop_5(create_std_uint16_t(position + 5));
    v.prop_6(create_std_uint32_t(position + 6));
    v.prop_7(create_std_uint64_t(position + 7));
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
