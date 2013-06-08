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
#include "dogen/dia_to_sml/hash/context_hash.hpp"
#include "dogen/sml/hash/model_hash.hpp"
#include "dogen/sml/hash/qname_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value)
{
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_unordered_map_std_string_std_string(const std::unordered_map<std::string, std::string>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_std_unordered_set_std_string(const std::unordered_set<std::string>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_std_string_dogen_sml_qname(const std::unordered_map<std::string, dogen::sml::qname>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_dogen_sml_qname_dogen_sml_qname(const std::unordered_map<dogen::sml::qname, dogen::sml::qname>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_std_list_dogen_sml_qname(const std::list<dogen::sml::qname>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_dogen_sml_qname_std_list_dogen_sml_qname_(const std::unordered_map<dogen::sml::qname, std::list<dogen::sml::qname> >& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, hash_std_list_dogen_sml_qname(i.second));
    }
    return seed;
}

}

namespace dogen {
namespace dia_to_sml {

std::size_t context_hasher::hash(const context&v) {
    std::size_t seed(0);

    combine(seed, v.is_target());
    combine(seed, hash_std_unordered_map_std_string_std_string(v.child_to_parent()));
    combine(seed, hash_std_unordered_set_std_string(v.parent_ids()));
    combine(seed, hash_std_unordered_map_std_string_dogen_sml_qname(v.dia_id_to_qname()));
    combine(seed, hash_std_unordered_map_dogen_sml_qname_dogen_sml_qname(v.original_parent()));
    combine(seed, hash_std_unordered_map_dogen_sml_qname_std_list_dogen_sml_qname_(v.leaves()));
    combine(seed, hash_std_unordered_set_std_string(v.top_level_module_names()));
    combine(seed, v.model());

    return seed;
}

} }
