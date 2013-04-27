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
#include "dogen/cpp/hash/relationships_hash.hpp"
#include "dogen/sml/hash/qname_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value)
{
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_unordered_set_dogen_sml_qname(const std::unordered_set<dogen::sml::qname>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

}

namespace dogen {
namespace cpp {

std::size_t relationships_hasher::hash(const relationships&v) {
    std::size_t seed(0);

    combine(seed, hash_std_unordered_set_dogen_sml_qname(v.names()));
    combine(seed, hash_std_unordered_set_dogen_sml_qname(v.forward_decls()));
    combine(seed, hash_std_unordered_set_dogen_sml_qname(v.keys()));
    combine(seed, hash_std_unordered_set_dogen_sml_qname(v.leaves()));
    combine(seed, v.has_std_string());
    combine(seed, v.has_variant());
    combine(seed, v.is_parent());
    combine(seed, v.is_child());
    combine(seed, v.requires_stream_manipulators());
    combine(seed, v.has_std_pair());

    return seed;
}

} }
