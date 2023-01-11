/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * These files are code-generated via overrides to test dogen. Do not commit them.
 *
 * Generation timestamp: 2022-10-20T10:20:30
 * WARNING: do not edit this file manually.
 * Generated by MASD Dogen v1.0.33
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
#include "dogen.logical/hash/entities/physical/relations_hash.hpp"
#include "dogen.logical/hash/entities/physical/constant_relation_hash.hpp"
#include "dogen.logical/hash/entities/physical/variable_relation_hash.hpp"
#include "dogen.logical/hash/entities/physical/hard_coded_relation_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_list_dogen_logical_entities_physical_constant_relation(const std::list<dogen::logical::entities::physical::constant_relation>& v) {
    std::size_t seed(0);
    for (const auto& i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_std_list_dogen_logical_entities_physical_variable_relation(const std::list<dogen::logical::entities::physical::variable_relation>& v) {
    std::size_t seed(0);
    for (const auto& i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_std_list_dogen_logical_entities_physical_hard_coded_relation(const std::list<dogen::logical::entities::physical::hard_coded_relation>& v) {
    std::size_t seed(0);
    for (const auto& i : v) {
        combine(seed, i);
    }
    return seed;
}

}

namespace dogen::logical::entities::physical {

std::size_t relations_hasher::hash(const relations& v) {
    std::size_t seed(0);

    combine(seed, v.status());
    combine(seed, hash_std_list_dogen_logical_entities_physical_constant_relation(v.constant()));
    combine(seed, hash_std_list_dogen_logical_entities_physical_variable_relation(v.variable()));
    combine(seed, hash_std_list_dogen_logical_entities_physical_hard_coded_relation(v.hard_coded()));

    return seed;
}

}
