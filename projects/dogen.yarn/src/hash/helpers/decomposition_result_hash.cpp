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
#include "dogen/yarn/hash/meta_model/name_hash.hpp"
#include "dogen/yarn/hash/meta_model/name_tree_hash.hpp"
#include "dogen/yarn/hash/helpers/decomposition_result_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_pair_std_string_dogen_yarn_meta_model_name(const std::pair<std::string, dogen::yarn::meta_model::name>& v) {
    std::size_t seed(0);

    combine(seed, v.first);
    combine(seed, v.second);
    return seed;
}

inline std::size_t hash_std_list_std_pair_std_string_dogen_yarn_meta_model_name(const std::list<std::pair<std::string, dogen::yarn::meta_model::name> >& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, hash_std_pair_std_string_dogen_yarn_meta_model_name(i));
    }
    return seed;
}

inline std::size_t hash_std_pair_std_string_dogen_yarn_meta_model_name_tree(const std::pair<std::string, dogen::yarn::meta_model::name_tree>& v) {
    std::size_t seed(0);

    combine(seed, v.first);
    combine(seed, v.second);
    return seed;
}

inline std::size_t hash_std_list_std_pair_std_string_dogen_yarn_meta_model_name_tree(const std::list<std::pair<std::string, dogen::yarn::meta_model::name_tree> >& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, hash_std_pair_std_string_dogen_yarn_meta_model_name_tree(i));
    }
    return seed;
}

}

namespace dogen {
namespace yarn {
namespace helpers {

std::size_t decomposition_result_hasher::hash(const decomposition_result& v) {
    std::size_t seed(0);

    combine(seed, hash_std_list_std_pair_std_string_dogen_yarn_meta_model_name(v.names()));
    combine(seed, hash_std_list_std_pair_std_string_dogen_yarn_meta_model_name(v.meta_names()));
    combine(seed, hash_std_list_std_pair_std_string_dogen_yarn_meta_model_name_tree(v.name_trees()));
    combine(seed, hash_std_list_std_pair_std_string_dogen_yarn_meta_model_name(v.injected_names()));

    return seed;
}

} } }
