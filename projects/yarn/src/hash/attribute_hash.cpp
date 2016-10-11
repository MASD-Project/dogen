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
#include "dogen/yarn/hash/attribute_hash.hpp"
#include "dogen/yarn/hash/name_tree_hash.hpp"
#include "dogen/annotations/hash/annotation_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

}

namespace dogen {
namespace yarn {

std::size_t attribute_hasher::hash(const attribute& v) {
    std::size_t seed(0);

    combine(seed, v.documentation());
    combine(seed, v.annotation());
    combine(seed, v.name());
    combine(seed, v.unparsed_type());
    combine(seed, v.parsed_type());
    combine(seed, v.is_immutable());
    combine(seed, v.is_fluent());

    return seed;
}

} }
