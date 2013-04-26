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
#include "dogen/dia_to_sml/hash/object_profile_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value)
{
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

}

namespace dogen {
namespace dia_to_sml {

std::size_t object_profile_hasher::hash(const object_profile&v) {
    std::size_t seed(0);

    combine(seed, v.is_uml_large_package());
    combine(seed, v.is_uml_class());
    combine(seed, v.is_uml_generalization());
    combine(seed, v.is_uml_association());
    combine(seed, v.is_uml_note());
    combine(seed, v.is_uml_message());
    combine(seed, v.is_uml_realization());
    combine(seed, v.is_enumeration());
    combine(seed, v.is_exception());
    combine(seed, v.is_entity());
    combine(seed, v.is_value());
    combine(seed, v.is_service());
    combine(seed, v.is_non_generatable());
    combine(seed, v.is_versioned());
    combine(seed, v.is_keyed());
    combine(seed, v.is_visitable());
    combine(seed, v.is_immutable());
    combine(seed, v.is_fluent());
    combine(seed, v.is_aggregate_root());
    combine(seed, v.is_string_table());

    return seed;
}

} }
