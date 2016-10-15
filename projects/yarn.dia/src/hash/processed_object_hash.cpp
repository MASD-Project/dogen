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
#include "dogen/yarn.dia/hash/dia_object_types_hash.hpp"
#include "dogen/yarn.dia/hash/processed_object_hash.hpp"
#include "dogen/yarn.dia/hash/processed_comment_hash.hpp"
#include "dogen/yarn.dia/hash/yarn_object_types_hash.hpp"
#include "dogen/yarn.dia/hash/processed_attribute_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_pair_std_string_std_string(const std::pair<std::string, std::string>& v) {
    std::size_t seed(0);

    combine(seed, v.first);
    combine(seed, v.second);
    return seed;
}

inline std::size_t hash_boost_optional_std_pair_std_string_std_string(const boost::optional<std::pair<std::string, std::string> >& v) {
    std::size_t seed(0);

    if (!v)
        return seed;

    combine(seed, hash_std_pair_std_string_std_string(*v));
    return seed;
}

inline std::size_t hash_std_list_dogen_yarn_dia_processed_attribute(const std::list<dogen::yarn::dia::processed_attribute>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

}

namespace dogen {
namespace yarn {
namespace dia {

std::size_t processed_object_hasher::hash(const processed_object& v) {
    std::size_t seed(0);

    combine(seed, v.id());
    combine(seed, v.name());
    combine(seed, v.dia_object_type());
    combine(seed, v.yarn_object_type());
    combine(seed, v.stereotype());
    combine(seed, v.comment());
    combine(seed, v.child_node_id());
    combine(seed, hash_boost_optional_std_pair_std_string_std_string(v.connection()));
    combine(seed, hash_std_list_dogen_yarn_dia_processed_attribute(v.attributes()));

    return seed;
}

} } }
