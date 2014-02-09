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
#include "dogen/formatters/hash/code_generation_marker_property_sheet_hash.hpp"
#include "dogen/formatters/hash/general_property_sheet_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value)
{
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_list_std_string(const std::list<std::string>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

}

namespace dogen {
namespace formatters {

std::size_t general_property_sheet_hasher::hash(const general_property_sheet&v) {
    std::size_t seed(0);

    combine(seed, v.enabled());
    combine(seed, v.generate_preamble());
    combine(seed, hash_std_list_std_string(v.copyright()));
    combine(seed, v.licence_name());
    combine(seed, v.modeline_group_name());
    combine(seed, v.code_generation_marker());
    combine(seed, v.feature_directory_name());
    combine(seed, v.enable_facet_directories());
    combine(seed, v.facet_directory_name());
    combine(seed, v.facet_postfix());
    combine(seed, v.overwrite());
    combine(seed, v.file_name());
    combine(seed, v.file_postfix());
    combine(seed, v.extension());
    combine(seed, v.enable_unique_file_names());

    return seed;
}

} }
