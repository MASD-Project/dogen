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
#include "dogen.modeling/hash/helpers/mapping_hash.hpp"
#include "dogen.modeling/hash/meta_model/languages_hash.hpp"
#include "dogen.modeling/hash/helpers/mapping_value_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_unordered_map_dogen_modeling_meta_model_languages_dogen_modeling_helpers_mapping_value(const std::unordered_map<dogen::modeling::meta_model::languages, dogen::modeling::helpers::mapping_value>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

}

namespace dogen::modeling::helpers {

std::size_t mapping_hasher::hash(const mapping& v) {
    std::size_t seed(0);

    combine(seed, v.lam_id());
    combine(seed, hash_std_unordered_map_dogen_modeling_meta_model_languages_dogen_modeling_helpers_mapping_value(v.by_language()));

    return seed;
}

}
