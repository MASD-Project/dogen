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
#include "dogen/upsilon/hash/tag_hash.hpp"
#include "dogen/upsilon/hash/type_hash.hpp"
#include "dogen/upsilon/hash/schema_hash.hpp"
#include "dogen/upsilon/hash/dependency_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_vector_dogen_upsilon_dependency(const std::vector<dogen::upsilon::dependency>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_std_vector_dogen_upsilon_tag(const std::vector<dogen::upsilon::tag>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_boost_shared_ptr_dogen_upsilon_type(const boost::shared_ptr<dogen::upsilon::type>& v) {
    std::size_t seed(0);
    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_vector_boost_shared_ptr_dogen_upsilon_type(const std::vector<boost::shared_ptr<dogen::upsilon::type> >& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, hash_boost_shared_ptr_dogen_upsilon_type(i));
    }
    return seed;
}

inline std::size_t hash_boost_filesystem_path(const boost::filesystem::path& v) {
    std::size_t seed(0);
    combine(seed, v.generic_string());
    return seed;
}

}

namespace dogen {
namespace upsilon {

std::size_t schema_hasher::hash(const schema& v) {
    std::size_t seed(0);

    combine(seed, v.name());
    combine(seed, v.id_min());
    combine(seed, v.id_max());
    combine(seed, v.base_guid());
    combine(seed, hash_std_vector_dogen_upsilon_dependency(v.dependencies()));
    combine(seed, hash_std_vector_dogen_upsilon_tag(v.tags()));
    combine(seed, hash_std_vector_boost_shared_ptr_dogen_upsilon_type(v.types()));
    combine(seed, hash_boost_filesystem_path(v.file_path()));

    return seed;
}

} }
