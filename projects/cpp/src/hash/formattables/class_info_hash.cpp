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
#include "dogen/sml/hash/generation_types_hash.hpp"
#include "dogen/cpp/hash/formattables/entity_hash.hpp"
#include "dogen/cpp/hash/formattables/class_info_hash.hpp"
#include "dogen/cpp/hash/formattables/class_types_hash.hpp"
#include "dogen/cpp/hash/formattables/parent_info_hash.hpp"
#include "dogen/cpp/hash/formattables/property_info_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value)
{
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_list_dogen_cpp_formattables_property_info(const std::list<dogen::cpp::formattables::property_info>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_std_list_dogen_cpp_formattables_parent_info(const std::list<dogen::cpp::formattables::parent_info>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
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

inline std::size_t hash_std_pair_std_string_std_string(const std::pair<std::string, std::string>& v){
    std::size_t seed(0);

    combine(seed, v.first);
    combine(seed, v.second);
    return seed;
}

inline std::size_t hash_std_list_std_pair_std_string_std_string_(const std::list<std::pair<std::string, std::string> >& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, hash_std_pair_std_string_std_string(i));
    }
    return seed;
}

}

namespace dogen {
namespace cpp {
namespace formattables {

std::size_t class_info_hasher::hash(const class_info&v) {
    std::size_t seed(0);

    combine(seed, dynamic_cast<const dogen::cpp::formattables::entity&>(v));

    combine(seed, hash_std_list_dogen_cpp_formattables_property_info(v.properties()));
    combine(seed, hash_std_list_dogen_cpp_formattables_property_info(v.all_properties()));
    combine(seed, v.has_primitive_properties());
    combine(seed, v.requires_stream_manipulators());
    combine(seed, v.requires_manual_move_constructor());
    combine(seed, v.requires_manual_default_constructor());
    combine(seed, hash_std_list_dogen_cpp_formattables_parent_info(v.parents()));
    combine(seed, v.is_parent());
    combine(seed, v.original_parent_name());
    combine(seed, v.original_parent_name_qualified());
    combine(seed, hash_std_list_std_string(v.leaves()));
    combine(seed, hash_std_list_std_pair_std_string_std_string_(v.opaque_parameters()));
    combine(seed, v.is_comparable());
    combine(seed, v.is_visitable());
    combine(seed, v.is_immutable());
    combine(seed, v.is_original_parent_visitable());
    combine(seed, v.class_type());
    combine(seed, v.generation_type());
    combine(seed, v.enable_integrated_io());
    combine(seed, v.disable_complete_constructor());
    combine(seed, v.is_final());

    return seed;
}

} } }
