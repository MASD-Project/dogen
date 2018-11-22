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
#include "masd.dogen.coding/hash/meta_model/name_hash.hpp"
#include "masd.dogen.coding/hash/meta_model/languages_hash.hpp"
#include "masd.dogen.coding/hash/meta_model/name_tree_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_list_masd_dogen_coding_meta_model_name_tree(const std::list<masd::dogen::coding::meta_model::name_tree>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_std_map_masd_dogen_coding_meta_model_languages_std_string(const std::map<masd::dogen::coding::meta_model::languages, std::string>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

}

namespace masd::dogen::coding::meta_model {

std::size_t name_tree_hasher::hash(const name_tree& v) {
    std::size_t seed(0);

    combine(seed, v.current());
    combine(seed, hash_std_list_masd_dogen_coding_meta_model_name_tree(v.children()));
    combine(seed, v.are_children_opaque());
    combine(seed, v.is_circular_dependency());
    combine(seed, hash_std_map_masd_dogen_coding_meta_model_languages_std_string(v.qualified()));
    combine(seed, v.identifiable());
    combine(seed, v.is_current_simple_type());
    combine(seed, v.is_floating_point());

    return seed;
}

}
