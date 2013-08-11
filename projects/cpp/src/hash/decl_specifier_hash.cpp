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
#include "dogen/cpp/hash/decl_specifier_hash.hpp"
#include "dogen/cpp/hash/function_specifier_types_hash.hpp"
#include "dogen/cpp/hash/storage_class_types_hash.hpp"
#include "dogen/cpp/hash/type_specifier_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value)
{
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

}

namespace dogen {
namespace cpp {

std::size_t decl_specifier_hasher::hash(const decl_specifier&v) {
    std::size_t seed(0);

    combine(seed, v.storage_class_type());
    combine(seed, v.type_specifier());
    combine(seed, v.function_specifier());
    combine(seed, v.is_friend());
    combine(seed, v.is_typedef());

    return seed;
}

} }
