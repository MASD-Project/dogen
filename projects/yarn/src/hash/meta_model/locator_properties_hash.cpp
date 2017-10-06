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
#include "dogen/yarn/hash/meta_model/locator_properties_hash.hpp"
#include "dogen/yarn/hash/meta_model/model_segment_properties_hash.hpp"
#include "dogen/yarn/hash/meta_model/archetype_group_properties_hash.hpp"
#include "dogen/yarn/hash/meta_model/directory_structure_styles_hash.hpp"
#include "dogen/yarn/hash/meta_model/intra_backend_segment_properties_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_unordered_map_std_string_dogen_yarn_meta_model_intra_backend_segment_properties(const std::unordered_map<std::string, dogen::yarn::meta_model::intra_backend_segment_properties>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_std_string_dogen_yarn_meta_model_archetype_group_properties(const std::unordered_map<std::string, dogen::yarn::meta_model::archetype_group_properties>& v) {
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
namespace meta_model {

std::size_t locator_properties_hasher::hash(const locator_properties& v) {
    std::size_t seed(0);

    combine(seed, v.directory_structure_style());
    combine(seed, v.name_separator());
    combine(seed, v.model_segment_properties());
    combine(seed, hash_std_unordered_map_std_string_dogen_yarn_meta_model_intra_backend_segment_properties(v.intra_backend_segment_properties()));
    combine(seed, hash_std_unordered_map_std_string_dogen_yarn_meta_model_archetype_group_properties(v.archetype_group_properties()));

    return seed;
}

} } }
