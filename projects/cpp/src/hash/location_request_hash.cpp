/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/config/hash/cpp_facet_types_hash.hpp"
#include "dogen/cpp/hash/aspect_types_hash.hpp"
#include "dogen/cpp/hash/file_types_hash.hpp"
#include "dogen/cpp/hash/location_request_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value)
{
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_list_std_string(const std::list<std::string>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

}

namespace dogen {
namespace cpp {

std::size_t location_request_hasher::hash(const location_request&v) {
    std::size_t seed(0);

    combine(seed, v.facet_type());
    combine(seed, v.file_type());
    combine(seed, v.aspect_type());
    combine(seed, v.model_name());
    combine(seed, hash_std_list_std_string(v.external_package_path()));
    combine(seed, hash_std_list_std_string(v.package_path()));
    combine(seed, v.file_name());

    return seed;
}

} }
