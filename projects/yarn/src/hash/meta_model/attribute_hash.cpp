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
#include "dogen/yarn/hash/meta_model/name_hash.hpp"
#include "dogen/annotations/hash/annotation_hash.hpp"
#include "dogen/yarn/hash/meta_model/attribute_hash.hpp"
#include "dogen/yarn/hash/meta_model/name_tree_hash.hpp"
#include "dogen/yarn/hash/meta_model/orm_attribute_properties_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_boost_optional_dogen_yarn_meta_model_orm_attribute_properties(const boost::optional<dogen::yarn::meta_model::orm_attribute_properties>& v) {
    std::size_t seed(0);

    if (!v)
        return seed;

    combine(seed, *v);
    return seed;
}

}

namespace dogen {
namespace yarn {
namespace meta_model {

std::size_t attribute_hasher::hash(const attribute& v) {
    std::size_t seed(0);

    combine(seed, v.documentation());
    combine(seed, v.annotation());
    combine(seed, v.name());
    combine(seed, v.unparsed_type());
    combine(seed, v.parsed_type());
    combine(seed, v.is_immutable());
    combine(seed, v.is_fluent());
    combine(seed, hash_boost_optional_dogen_yarn_meta_model_orm_attribute_properties(v.orm_properties()));

    return seed;
}

} } }
