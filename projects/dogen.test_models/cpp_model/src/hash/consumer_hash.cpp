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
#include "dogen/test_models/cpp_model/hash/consumer_hash.hpp"
#include "dogen/test_models/cpp_model/hash/int_primitive_hash.hpp"
#include "dogen/test_models/cpp_model/hash/bool_primitive_hash.hpp"
#include "dogen/test_models/cpp_model/hash/char_primitive_hash.hpp"
#include "dogen/test_models/cpp_model/hash/long_primitive_hash.hpp"
#include "dogen/test_models/cpp_model/hash/uint_primitive_hash.hpp"
#include "dogen/test_models/cpp_model/hash/float_primitive_hash.hpp"
#include "dogen/test_models/cpp_model/hash/short_primitive_hash.hpp"
#include "dogen/test_models/cpp_model/hash/uchar_primitive_hash.hpp"
#include "dogen/test_models/cpp_model/hash/ulong_primitive_hash.hpp"
#include "dogen/test_models/cpp_model/hash/double_primitive_hash.hpp"
#include "dogen/test_models/cpp_model/hash/ushort_primitive_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

}

namespace dogen {
namespace test_models {
namespace cpp_model {

std::size_t consumer_hasher::hash(const consumer& v) {
    std::size_t seed(0);

    combine(seed, v.prop0());
    combine(seed, v.prop1());
    combine(seed, v.prop2());
    combine(seed, v.prop3());
    combine(seed, v.prop4());
    combine(seed, v.prop5());
    combine(seed, v.prop6());
    combine(seed, v.prop7());
    combine(seed, v.prop8());
    combine(seed, v.prop9());
    combine(seed, v.prop10());

    return seed;
}

} } }
