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
#include "dogen/sml/hash/concept_hash.hpp"
#include "dogen/sml/hash/enumeration_hash.hpp"
#include "dogen/sml/hash/model_hash.hpp"
#include "dogen/sml/hash/module_hash.hpp"
#include "dogen/sml/hash/pod_hash.hpp"
#include "dogen/sml/hash/primitive_hash.hpp"
#include "dogen/sml/hash/qname_hash.hpp"
#include "dogen/sml/hash/reference_hash.hpp"
#include "dogen/sml/hash/service_hash.hpp"
#include "dogen/sml/hash/value_object_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value)
{
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_unordered_map_dogen_sml_qname_dogen_sml_pod(const std::unordered_map<dogen::sml::qname, dogen::sml::pod>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_dogen_sml_qname_dogen_sml_primitive(const std::unordered_map<dogen::sml::qname, dogen::sml::primitive>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_dogen_sml_qname_dogen_sml_enumeration(const std::unordered_map<dogen::sml::qname, dogen::sml::enumeration>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_dogen_sml_qname_dogen_sml_value_object(const std::unordered_map<dogen::sml::qname, dogen::sml::value_object>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_std_list_std_string(const std::list<std::string>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_std_string_dogen_sml_reference(const std::unordered_map<std::string, dogen::sml::reference>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_std_unordered_set_dogen_sml_qname(const std::unordered_set<dogen::sml::qname>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_std_pair_std_string_std_string(const std::pair<std::string, std::string>& v){
    std::size_t seed(0);

    combine(seed, v.first);
    combine(seed, v.second);
    return seed;
}

inline std::size_t hash_std_vector_std_pair_std_string_std_string_(const std::vector<std::pair<std::string, std::string> >& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, hash_std_pair_std_string_std_string(i));
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_dogen_sml_qname_dogen_sml_service(const std::unordered_map<dogen::sml::qname, dogen::sml::service>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_dogen_sml_qname_dogen_sml_module(const std::unordered_map<dogen::sml::qname, dogen::sml::module>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_dogen_sml_qname_dogen_sml_concept(const std::unordered_map<dogen::sml::qname, dogen::sml::concept>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

}

namespace dogen {
namespace sml {

std::size_t model_hasher::hash(const model&v) {
    std::size_t seed(0);

    combine(seed, v.name());
    combine(seed, hash_std_unordered_map_dogen_sml_qname_dogen_sml_pod(v.pods()));
    combine(seed, hash_std_unordered_map_dogen_sml_qname_dogen_sml_primitive(v.primitives()));
    combine(seed, hash_std_unordered_map_dogen_sml_qname_dogen_sml_enumeration(v.enumerations()));
    combine(seed, hash_std_unordered_map_dogen_sml_qname_dogen_sml_value_object(v.exceptions()));
    combine(seed, hash_std_list_std_string(v.external_module_path()));
    combine(seed, v.is_system());
    combine(seed, hash_std_unordered_map_std_string_dogen_sml_reference(v.dependencies()));
    combine(seed, hash_std_unordered_set_dogen_sml_qname(v.leaves()));
    combine(seed, v.documentation());
    combine(seed, hash_std_vector_std_pair_std_string_std_string_(v.implementation_specific_parameters()));
    combine(seed, hash_std_unordered_map_dogen_sml_qname_dogen_sml_service(v.services()));
    combine(seed, hash_std_unordered_map_dogen_sml_qname_dogen_sml_module(v.modules()));
    combine(seed, hash_std_unordered_map_dogen_sml_qname_dogen_sml_concept(v.concepts()));

    return seed;
}

} }
