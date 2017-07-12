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
#include "dogen/yarn/hash/meta_model/letter_cases_hash.hpp"
#include "dogen/yarn/hash/meta_model/orm_object_properties_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_boost_optional_dogen_yarn_meta_model_letter_cases(const boost::optional<dogen::yarn::meta_model::letter_cases>& v) {
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

std::size_t orm_object_properties_hasher::hash(const orm_object_properties& v) {
    std::size_t seed(0);

    combine(seed, v.generate_mapping());
    combine(seed, v.schema_name());
    combine(seed, v.table_name());
    combine(seed, v.is_value());
    combine(seed, v.has_primary_key());
    combine(seed, hash_boost_optional_dogen_yarn_meta_model_letter_cases(v.letter_case()));

    return seed;
}

} } }
