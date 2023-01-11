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
#include "dogen.variability/hash/entities/configuration_hash.hpp"
#include "dogen.logical/hash/entities/physical/relations_hash.hpp"
#include "dogen.identification/hash/entities/logical_name_hash.hpp"
#include "dogen.logical/hash/entities/physical/text_templating_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_boost_shared_ptr_dogen_variability_entities_configuration(const boost::shared_ptr<dogen::variability::entities::configuration>& v) {
    std::size_t seed(0);
    combine(seed, *v);
    return seed;
}

inline std::size_t hash_boost_optional_dogen_identification_entities_logical_name(const boost::optional<dogen::identification::entities::logical_name>& v) {
    std::size_t seed(0);

    if (!v)
        return seed;

    combine(seed, *v);
    return seed;
}

}

namespace dogen::logical::entities::physical {

std::size_t text_templating_hasher::hash(const text_templating& v) {
    std::size_t seed(0);

    combine(seed, hash_boost_shared_ptr_dogen_variability_entities_configuration(v.configuration()));
    combine(seed, v.stitch_template_content());
    combine(seed, hash_boost_optional_dogen_identification_entities_logical_name(v.wale_template()));
    combine(seed, v.wale_template_content());
    combine(seed, v.rendered_stitch_template());
    combine(seed, v.relations());

    return seed;
}

}
