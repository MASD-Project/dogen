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
#include "dogen/annotations/hash/type_hash.hpp"
#include "dogen/annotations/hash/type_repository_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_list_dogen_annotations_type(const std::list<dogen::annotations::type>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_std_string_dogen_annotations_type(const std::unordered_map<std::string, dogen::annotations::type>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_std_string_std_list_dogen_annotations_type(const std::unordered_map<std::string, std::list<dogen::annotations::type> >& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, hash_std_list_dogen_annotations_type(i.second));
    }
    return seed;
}

}

namespace dogen {
namespace annotations {

std::size_t type_repository_hasher::hash(const type_repository& v) {
    std::size_t seed(0);

    combine(seed, hash_std_list_dogen_annotations_type(v.all_types()));
    combine(seed, hash_std_unordered_map_std_string_dogen_annotations_type(v.types_by_name()));
    combine(seed, hash_std_unordered_map_std_string_std_list_dogen_annotations_type(v.types_by_facet_name()));
    combine(seed, hash_std_unordered_map_std_string_std_list_dogen_annotations_type(v.types_by_formatter_name()));
    combine(seed, hash_std_unordered_map_std_string_std_list_dogen_annotations_type(v.types_by_model_name()));

    return seed;
}

} }
