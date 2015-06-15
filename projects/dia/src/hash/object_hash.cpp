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
#include "dogen/dia/hash/object_hash.hpp"
#include "dogen/dia/hash/attribute_hash.hpp"
#include "dogen/dia/hash/child_node_hash.hpp"
#include "dogen/dia/hash/connection_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_vector_dogen_dia_connection(const std::vector<dogen::dia::connection>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_boost_optional_dogen_dia_child_node(const boost::optional<dogen::dia::child_node>& v) {
    std::size_t seed(0);

    if (!v)
        return seed;

    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_vector_dogen_dia_attribute(const std::vector<dogen::dia::attribute>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

}

namespace dogen {
namespace dia {

std::size_t object_hasher::hash(const object& v) {
    std::size_t seed(0);

    combine(seed, v.type());
    combine(seed, v.version());
    combine(seed, v.id());
    combine(seed, hash_std_vector_dogen_dia_connection(v.connections()));
    combine(seed, hash_boost_optional_dogen_dia_child_node(v.child_node()));
    combine(seed, hash_std_vector_dogen_dia_attribute(v.attributes()));

    return seed;
}

} }
