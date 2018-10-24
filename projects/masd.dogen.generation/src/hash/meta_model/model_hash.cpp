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
#include "masd.dogen.modeling/hash/meta_model/name_hash.hpp"
#include "masd.dogen.modeling/hash/meta_model/module_hash.hpp"
#include "masd.dogen.generation/hash/meta_model/model_hash.hpp"
#include "masd.dogen.modeling/hash/meta_model/element_hash.hpp"
#include "masd.dogen.modeling/hash/meta_model/languages_hash.hpp"
#include "masd.dogen.modeling/hash/meta_model/origin_types_hash.hpp"
#include "masd.dogen.generation/hash/meta_model/element_archetype_hash.hpp"
#include "masd.dogen.generation/hash/meta_model/locator_properties_hash.hpp"
#include "masd.dogen.modeling/hash/meta_model/orm_model_properties_hash.hpp"
#include "masd.dogen.generation/hash/meta_model/global_archetype_location_properties_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_unordered_map_masd_dogen_modeling_meta_model_name_masd_dogen_modeling_meta_model_origin_types(const std::unordered_map<masd::dogen::modeling::meta_model::name, masd::dogen::modeling::meta_model::origin_types>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_std_unordered_set_masd_dogen_modeling_meta_model_name(const std::unordered_set<masd::dogen::modeling::meta_model::name>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_boost_shared_ptr_masd_dogen_modeling_meta_model_element(const boost::shared_ptr<masd::dogen::modeling::meta_model::element>& v) {
    std::size_t seed(0);
    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_vector_boost_shared_ptr_masd_dogen_modeling_meta_model_element(const std::vector<boost::shared_ptr<masd::dogen::modeling::meta_model::element> >& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, hash_boost_shared_ptr_masd_dogen_modeling_meta_model_element(i));
    }
    return seed;
}

inline std::size_t hash_boost_shared_ptr_masd_dogen_modeling_meta_model_module(const boost::shared_ptr<masd::dogen::modeling::meta_model::module>& v) {
    std::size_t seed(0);
    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_unordered_set_std_string(const std::unordered_set<std::string>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_boost_optional_masd_dogen_modeling_meta_model_orm_model_properties(const boost::optional<masd::dogen::modeling::meta_model::orm_model_properties>& v) {
    std::size_t seed(0);

    if (!v)
        return seed;

    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_unordered_set_masd_dogen_generation_meta_model_element_archetype(const std::unordered_set<masd::dogen::generation::meta_model::element_archetype>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

}

namespace masd::dogen::generation::meta_model {

std::size_t model_hasher::hash(const model& v) {
    std::size_t seed(0);

    combine(seed, v.name());
    combine(seed, v.meta_name());
    combine(seed, hash_std_unordered_map_masd_dogen_modeling_meta_model_name_masd_dogen_modeling_meta_model_origin_types(v.references()));
    combine(seed, hash_std_unordered_set_masd_dogen_modeling_meta_model_name(v.leaves()));
    combine(seed, hash_std_vector_boost_shared_ptr_masd_dogen_modeling_meta_model_element(v.elements()));
    combine(seed, hash_boost_shared_ptr_masd_dogen_modeling_meta_model_module(v.root_module()));
    combine(seed, hash_std_unordered_set_std_string(v.module_ids()));
    combine(seed, v.has_generatable_types());
    combine(seed, v.input_language());
    combine(seed, v.output_language());
    combine(seed, hash_boost_optional_masd_dogen_modeling_meta_model_orm_model_properties(v.orm_properties()));
    combine(seed, hash_std_unordered_set_masd_dogen_generation_meta_model_element_archetype(v.enabled_archetype_for_element()));
    combine(seed, v.locator_properties());
    combine(seed, v.global_archetype_location_properties());

    return seed;
}

}
