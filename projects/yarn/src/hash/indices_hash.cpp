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
#include "dogen/yarn/hash/indices_hash.hpp"
#include "dogen/annotations/hash/scribble_group_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_unordered_set_std_string(const std::unordered_set<std::string>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_std_string_dogen_annotations_scribble_group(const std::unordered_map<std::string, dogen::annotations::scribble_group>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

}

namespace dogen {
namespace yarn {

std::size_t indices_hasher::hash(const indices& v) {
    std::size_t seed(0);

    combine(seed, hash_std_unordered_set_std_string(v.objects_always_in_heap()));
    combine(seed, hash_std_unordered_set_std_string(v.elements_referable_by_attributes()));
    combine(seed, hash_std_unordered_map_std_string_dogen_annotations_scribble_group(v.scribble_groups()));
    combine(seed, hash_std_unordered_set_std_string(v.primitive_underliers()));
    combine(seed, hash_std_unordered_set_std_string(v.enumeration_underliers()));
    combine(seed, hash_std_unordered_set_std_string(v.abstract_elements()));

    return seed;
}

} }
