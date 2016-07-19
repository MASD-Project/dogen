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
#include "dogen/test_models/std_model/hash/class_j_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_pair_int_int(const std::pair<int, int>& v) {
    std::size_t seed(0);

    combine(seed, v.first);
    combine(seed, v.second);
    return seed;
}

inline std::size_t hash_std_pair_std_string_std_string(const std::pair<std::string, std::string>& v) {
    std::size_t seed(0);

    combine(seed, v.first);
    combine(seed, v.second);
    return seed;
}

inline std::size_t hash_std_pair_std_string_int(const std::pair<std::string, int>& v) {
    std::size_t seed(0);

    combine(seed, v.first);
    combine(seed, v.second);
    return seed;
}

inline std::size_t hash_std_vector_std_pair_std_string_int(const std::vector<std::pair<std::string, int> >& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, hash_std_pair_std_string_int(i));
    }
    return seed;
}

}

namespace dogen {
namespace test_models {
namespace std_model {

std::size_t class_j_hasher::hash(const class_j& v) {
    std::size_t seed(0);

    combine(seed, hash_std_pair_int_int(v.prop_0()));
    combine(seed, hash_std_pair_std_string_std_string(v.prop_1()));
    combine(seed, hash_std_vector_std_pair_std_string_int(v.prop_2()));

    return seed;
}

} } }
