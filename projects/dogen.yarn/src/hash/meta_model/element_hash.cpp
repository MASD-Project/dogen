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
#include "dogen.annotations/hash/annotation_hash.hpp"
#include "dogen/yarn/hash/meta_model/element_hash.hpp"
#include "dogen/yarn/hash/meta_model/origin_types_hash.hpp"
#include "dogen/formatters/hash/decoration_properties_hash.hpp"
#include "dogen/yarn/hash/meta_model/static_stereotypes_hash.hpp"
#include "dogen/yarn/hash/meta_model/artefact_properties_hash.hpp"
#include "dogen/yarn/hash/meta_model/local_archetype_location_properties_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_boost_optional_dogen_yarn_meta_model_name(const boost::optional<dogen::yarn::meta_model::name>& v) {
    std::size_t seed(0);

    if (!v)
        return seed;

    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_list_dogen_yarn_meta_model_static_stereotypes(const std::list<dogen::yarn::meta_model::static_stereotypes>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_std_list_std_string(const std::list<std::string>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_std_string_dogen_yarn_meta_model_artefact_properties(const std::unordered_map<std::string, dogen::yarn::meta_model::artefact_properties>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_std_string_dogen_yarn_meta_model_local_archetype_location_properties(const std::unordered_map<std::string, dogen::yarn::meta_model::local_archetype_location_properties>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

}

namespace dogen {
namespace yarn {
namespace meta_model {

std::size_t element_hasher::hash(const element& v) {
    std::size_t seed(0);

    combine(seed, v.name());
    combine(seed, v.documentation());
    combine(seed, v.annotation());
    combine(seed, v.origin_type());
    combine(seed, hash_boost_optional_dogen_yarn_meta_model_name(v.contained_by()));
    combine(seed, v.in_global_module());
    combine(seed, hash_std_list_dogen_yarn_meta_model_static_stereotypes(v.static_stereotypes()));
    combine(seed, hash_std_list_std_string(v.dynamic_stereotypes()));
    combine(seed, v.meta_name());
    combine(seed, v.is_element_extension());
    combine(seed, v.decoration_properties());
    combine(seed, hash_std_unordered_map_std_string_dogen_yarn_meta_model_artefact_properties(v.artefact_properties()));
    combine(seed, hash_std_unordered_map_std_string_dogen_yarn_meta_model_local_archetype_location_properties(v.archetype_location_properties()));

    return seed;
}

} } }
