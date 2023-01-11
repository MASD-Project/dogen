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
#include "dogen.identification/hash/entities/logical_id_hash.hpp"
#include "dogen.logical/hash/entities/decoration/licence_hash.hpp"
#include "dogen.logical/hash/entities/decoration/modeline_hash.hpp"
#include "dogen.logical/hash/entities/decoration/modeline_group_hash.hpp"
#include "dogen.logical/hash/entities/decoration/generation_marker_hash.hpp"
#include "dogen.logical/hash/entities/decoration/element_repository_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_boost_shared_ptr_dogen_logical_entities_decoration_modeline_group(const boost::shared_ptr<dogen::logical::entities::decoration::modeline_group>& v) {
    std::size_t seed(0);
    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_unordered_map_dogen_identification_entities_logical_id_boost_shared_ptr_dogen_logical_entities_decoration_modeline_group(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::decoration::modeline_group> >& v) {
    std::size_t seed(0);
    for (const auto& i : v) {
        combine(seed, i.first);
        combine(seed, hash_boost_shared_ptr_dogen_logical_entities_decoration_modeline_group(i.second));
    }
    return seed;
}

inline std::size_t hash_boost_shared_ptr_dogen_logical_entities_decoration_modeline(const boost::shared_ptr<dogen::logical::entities::decoration::modeline>& v) {
    std::size_t seed(0);
    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_unordered_map_dogen_identification_entities_logical_id_boost_shared_ptr_dogen_logical_entities_decoration_modeline(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::decoration::modeline> >& v) {
    std::size_t seed(0);
    for (const auto& i : v) {
        combine(seed, i.first);
        combine(seed, hash_boost_shared_ptr_dogen_logical_entities_decoration_modeline(i.second));
    }
    return seed;
}

inline std::size_t hash_boost_shared_ptr_dogen_logical_entities_decoration_licence(const boost::shared_ptr<dogen::logical::entities::decoration::licence>& v) {
    std::size_t seed(0);
    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_unordered_map_dogen_identification_entities_logical_id_boost_shared_ptr_dogen_logical_entities_decoration_licence(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::decoration::licence> >& v) {
    std::size_t seed(0);
    for (const auto& i : v) {
        combine(seed, i.first);
        combine(seed, hash_boost_shared_ptr_dogen_logical_entities_decoration_licence(i.second));
    }
    return seed;
}

inline std::size_t hash_boost_shared_ptr_dogen_logical_entities_decoration_generation_marker(const boost::shared_ptr<dogen::logical::entities::decoration::generation_marker>& v) {
    std::size_t seed(0);
    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_unordered_map_dogen_identification_entities_logical_id_boost_shared_ptr_dogen_logical_entities_decoration_generation_marker(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::decoration::generation_marker> >& v) {
    std::size_t seed(0);
    for (const auto& i : v) {
        combine(seed, i.first);
        combine(seed, hash_boost_shared_ptr_dogen_logical_entities_decoration_generation_marker(i.second));
    }
    return seed;
}

}

namespace dogen::logical::entities::decoration {

std::size_t element_repository_hasher::hash(const element_repository& v) {
    std::size_t seed(0);

    combine(seed, hash_std_unordered_map_dogen_identification_entities_logical_id_boost_shared_ptr_dogen_logical_entities_decoration_modeline_group(v.modeline_groups()));
    combine(seed, hash_std_unordered_map_dogen_identification_entities_logical_id_boost_shared_ptr_dogen_logical_entities_decoration_modeline(v.modelines()));
    combine(seed, hash_std_unordered_map_dogen_identification_entities_logical_id_boost_shared_ptr_dogen_logical_entities_decoration_licence(v.licences()));
    combine(seed, hash_std_unordered_map_dogen_identification_entities_logical_id_boost_shared_ptr_dogen_logical_entities_decoration_generation_marker(v.generation_markers()));

    return seed;
}

}
