/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * These files are code-generated via overrides to test dogen. Do not commit them.
 *
 * Generation timestamp: 2022-10-20T10:20:30
 * WARNING: do not edit this file manually.
 * Generated by MASD Dogen v1.0.33
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
#include "dogen.logical/hash/entities/element_hash.hpp"
#include "dogen.variability/hash/entities/binding_point_hash.hpp"
#include "dogen.identification/hash/entities/logical_name_hash.hpp"
#include "dogen.logical/hash/entities/variability/abstract_bundle_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_list_dogen_identification_entities_logical_name(const std::list<dogen::identification::entities::logical_name>& v) {
    std::size_t seed(0);
    for (const auto& i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_boost_optional_dogen_variability_entities_binding_point(const boost::optional<dogen::variability::entities::binding_point>& v) {
    std::size_t seed(0);

    if (!v)
        return seed;

    combine(seed, *v);
    return seed;
}

}

namespace dogen::logical::entities::variability {

std::size_t abstract_bundle_hasher::hash(const abstract_bundle& v) {
    std::size_t seed(0);

    combine(seed, dynamic_cast<const dogen::logical::entities::element&>(v));

    combine(seed, hash_std_list_dogen_identification_entities_logical_name(v.transparent_associations()));
    combine(seed, hash_std_list_dogen_identification_entities_logical_name(v.opaque_associations()));
    combine(seed, hash_std_list_dogen_identification_entities_logical_name(v.associative_container_keys()));
    combine(seed, v.key_prefix());
    combine(seed, v.generate_registration());
    combine(seed, v.generate_static_configuration());
    combine(seed, v.requires_manual_default_constructor());
    combine(seed, hash_boost_optional_dogen_variability_entities_binding_point(v.default_binding_point()));

    return seed;
}

}
