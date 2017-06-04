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
#include "dogen/yarn/hash/element_hash.hpp"
#include "dogen/yarn/hash/origin_types_hash.hpp"
#include "dogen/annotations/hash/annotation_hash.hpp"
#include "dogen/yarn/hash/element_properties_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_boost_optional_dogen_yarn_name(const boost::optional<dogen::yarn::name>& v) {
    std::size_t seed(0);

    if (!v)
        return seed;

    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_vector_std_string(const std::vector<std::string>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

}

namespace dogen {
namespace yarn {

std::size_t element_hasher::hash(const element& v) {
    std::size_t seed(0);

    combine(seed, v.documentation());
    combine(seed, v.annotation());
    combine(seed, v.name());
    combine(seed, v.origin_type());
    combine(seed, hash_boost_optional_dogen_yarn_name(v.contained_by()));
    combine(seed, v.in_global_module());
    combine(seed, hash_std_vector_std_string(v.stereotypes()));
    combine(seed, v.is_element_extension());
    combine(seed, v.element_properties());

    return seed;
}

} }
