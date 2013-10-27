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
#include "dogen/cpp/hash/nested_type_info_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value)
{
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_list_dogen_cpp_nested_type_info(const std::list<dogen::cpp::nested_type_info>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_std_list_std_string(const std::list<std::string>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

}

namespace dogen {
namespace cpp {

std::size_t nested_type_info_hasher::hash(const nested_type_info&v) {
    std::size_t seed(0);

    combine(seed, v.name());
    combine(seed, v.documentation());
    combine(seed, v.identifiable_name());
    combine(seed, v.complete_name());
    combine(seed, v.complete_identifiable_name());
    combine(seed, v.is_primitive());
    combine(seed, v.is_enumeration());
    combine(seed, v.is_string_like());
    combine(seed, v.is_char_like());
    combine(seed, v.is_int_like());
    combine(seed, v.is_sequence_container());
    combine(seed, v.is_associative_container());
    combine(seed, v.is_smart_pointer());
    combine(seed, v.is_optional_like());
    combine(seed, v.is_variant_like());
    combine(seed, hash_std_list_dogen_cpp_nested_type_info(v.children()));
    combine(seed, hash_std_list_std_string(v.namespaces()));
    combine(seed, v.is_filesystem_path());
    combine(seed, v.is_date());
    combine(seed, v.is_ptime());
    combine(seed, v.is_time_duration());
    combine(seed, v.is_pair());
    combine(seed, v.is_ptree());

    return seed;
}

} }
