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
#include "dogen/yarn/hash/name_hash.hpp"
#include "dogen/yarn/hash/concept_hash.hpp"
#include "dogen/yarn/hash/element_hash.hpp"
#include "dogen/yarn/hash/property_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_list_dogen_yarn_property(const std::list<dogen::yarn::property>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_dogen_yarn_name_std_list_dogen_yarn_property_(const std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::property> >& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, hash_std_list_dogen_yarn_property(i.second));
    }
    return seed;
}

inline std::size_t hash_std_list_dogen_yarn_name(const std::list<dogen::yarn::name>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

}

namespace dogen {
namespace yarn {

std::size_t concept_hasher::hash(const concept& v) {
    std::size_t seed(0);

    combine(seed, dynamic_cast<const dogen::yarn::element&>(v));

    combine(seed, hash_std_list_dogen_yarn_property(v.all_properties()));
    combine(seed, hash_std_list_dogen_yarn_property(v.local_properties()));
    combine(seed, hash_std_unordered_map_dogen_yarn_name_std_list_dogen_yarn_property_(v.inherited_properties()));
    combine(seed, hash_std_list_dogen_yarn_name(v.refines()));
    combine(seed, v.is_parent());
    combine(seed, v.is_child());

    return seed;
}

} }
