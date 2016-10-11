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
#include "dogen/annotations/hash/name_hash.hpp"
#include "dogen/annotations/hash/value_hash.hpp"
#include "dogen/annotations/hash/scope_types_hash.hpp"
#include "dogen/annotations/hash/value_types_hash.hpp"
#include "dogen/annotations/hash/field_definition_hash.hpp"
#include "dogen/annotations/hash/ownership_hierarchy_hash.hpp"
#include "dogen/annotations/hash/field_definition_types_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_boost_shared_ptr_dogen_annotations_value(const boost::shared_ptr<dogen::annotations::value>& v) {
    std::size_t seed(0);
    combine(seed, *v);
    return seed;
}

}

namespace dogen {
namespace annotations {

std::size_t field_definition_hasher::hash(const type& v) {
    std::size_t seed(0);

    combine(seed, v.name());
    combine(seed, v.value_type());
    combine(seed, v.scope());
    combine(seed, v.ownership_hierarchy());
    combine(seed, hash_boost_shared_ptr_dogen_annotations_value(v.default_value()));
    combine(seed, v.definition_type());

    return seed;
}

} }
