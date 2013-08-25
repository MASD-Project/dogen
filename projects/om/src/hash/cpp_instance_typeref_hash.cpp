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
#include "dogen/om/hash/cpp_instance_typeref_hash.hpp"
#include "dogen/om/hash/cpp_memory_types_hash.hpp"
#include "dogen/om/hash/cpp_typeref_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value)
{
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_list_std_string(const std::list<std::string>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_std_list_dogen_om_cpp_typeref(const std::list<dogen::om::cpp_typeref>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

}

namespace dogen {
namespace om {

std::size_t cpp_instance_typeref_hasher::hash(const cpp_instance_typeref&v) {
    std::size_t seed(0);

    combine(seed, v.is_const());
    combine(seed, v.start_at_global_scope());
    combine(seed, hash_std_list_std_string(v.namespaces()));
    combine(seed, v.name());
    combine(seed, hash_std_list_dogen_om_cpp_typeref(v.type_arguments()));
    combine(seed, v.memory_type());

    return seed;
}

} }
