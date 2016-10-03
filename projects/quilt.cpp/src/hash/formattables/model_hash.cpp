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
#include "dogen/quilt.cpp/hash/formattables/model_hash.hpp"
#include "dogen/quilt.cpp/hash/formattables/formattable_hash.hpp"
#include "dogen/quilt.cpp/hash/formattables/facet_configuration_hash.hpp"
#include "dogen/quilt.cpp/hash/annotations/streaming_annotations_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_unordered_map_std_string_dogen_quilt_cpp_annotations_streaming_annotations(const std::unordered_map<std::string, dogen::quilt::cpp::annotations::streaming_annotations>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_std_string_std_string(const std::unordered_map<std::string, std::string>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_std_string_dogen_quilt_cpp_formattables_formattable(const std::unordered_map<std::string, dogen::quilt::cpp::formattables::formattable>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_std_string_dogen_quilt_cpp_formattables_facet_configuration(const std::unordered_map<std::string, dogen::quilt::cpp::formattables::facet_configuration>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

std::size_t model_hasher::hash(const model& v) {
    std::size_t seed(0);

    combine(seed, hash_std_unordered_map_std_string_dogen_quilt_cpp_annotations_streaming_annotations(v.streaming_annotations()));
    combine(seed, hash_std_unordered_map_std_string_std_string(v.facet_directory_for_facet()));
    combine(seed, hash_std_unordered_map_std_string_dogen_quilt_cpp_formattables_formattable(v.formattables()));
    combine(seed, hash_std_unordered_map_std_string_dogen_quilt_cpp_formattables_facet_configuration(v.facet_configurations()));

    return seed;
}

} } } }
