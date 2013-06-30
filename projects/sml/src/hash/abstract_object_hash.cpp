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
#include "dogen/sml/hash/abstract_object_hash.hpp"
#include "dogen/sml/hash/generation_types_hash.hpp"
#include "dogen/sml/hash/operation_hash.hpp"
#include "dogen/sml/hash/property_hash.hpp"
#include "dogen/sml/hash/qname_hash.hpp"
#include "dogen/sml/hash/type_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value)
{
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_list_dogen_sml_property(const std::list<dogen::sml::property>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_std_list_dogen_sml_operation(const std::list<dogen::sml::operation>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_boost_optional_dogen_sml_qname(const boost::optional<dogen::sml::qname>& v){
    std::size_t seed(0);

    if (!v)
        return seed;

    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_list_dogen_sml_qname(const std::list<dogen::sml::qname>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

}

namespace dogen {
namespace sml {

std::size_t abstract_object_hasher::hash(const abstract_object&v) {
    std::size_t seed(0);

    combine(seed, dynamic_cast<const dogen::sml::type&>(v));

    combine(seed, hash_std_list_dogen_sml_property(v.properties()));
    combine(seed, hash_std_list_dogen_sml_operation(v.operations()));
    combine(seed, hash_boost_optional_dogen_sml_qname(v.parent_name()));
    combine(seed, hash_boost_optional_dogen_sml_qname(v.original_parent_name()));
    combine(seed, hash_std_list_dogen_sml_qname(v.leaves()));
    combine(seed, v.is_parent());
    combine(seed, v.number_of_type_arguments());
    combine(seed, v.is_visitable());
    combine(seed, v.is_immutable());
    combine(seed, v.is_versioned());
    combine(seed, v.is_comparable());
    combine(seed, v.is_fluent());
    combine(seed, hash_std_list_dogen_sml_qname(v.modeled_concepts()));

    return seed;
}

} }
