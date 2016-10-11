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
#include "dogen/annotations/hash/repository_hash.hpp"
#include "dogen/annotations/hash/field_definition_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_list_dogen_annotations_field_definition(const std::list<dogen::annotations::type>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_std_string_dogen_annotations_field_definition(const std::unordered_map<std::string, dogen::annotations::type>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_std_string_std_list_dogen_annotations_field_definition(const std::unordered_map<std::string, std::list<dogen::annotations::type> >& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, hash_std_list_dogen_annotations_field_definition(i.second));
    }
    return seed;
}

}

namespace dogen {
namespace annotations {

std::size_t repository_hasher::hash(const repository& v) {
    std::size_t seed(0);

    combine(seed, hash_std_list_dogen_annotations_field_definition(v.all_field_definitions()));
    combine(seed, hash_std_unordered_map_std_string_dogen_annotations_field_definition(v.field_definitions_by_name()));
    combine(seed, hash_std_unordered_map_std_string_std_list_dogen_annotations_field_definition(v.field_definitions_by_facet_name()));
    combine(seed, hash_std_unordered_map_std_string_std_list_dogen_annotations_field_definition(v.field_definitions_by_formatter_name()));
    combine(seed, hash_std_unordered_map_std_string_std_list_dogen_annotations_field_definition(v.field_definitions_by_model_name()));

    return seed;
}

} }
