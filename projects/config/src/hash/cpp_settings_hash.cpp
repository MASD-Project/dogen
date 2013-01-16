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
#include "dogen/config/hash/cpp_facet_types_hash.hpp"
#include "dogen/config/hash/cpp_settings_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value)
{
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_set_dogen_config_cpp_facet_types(const std::set<dogen::config::cpp_facet_types>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

}

namespace dogen {
namespace config {

std::size_t cpp_settings_hasher::hash(const cpp_settings&v) {
    std::size_t seed(0);

    combine(seed, v.verbose());
    combine(seed, v.split_project());
    combine(seed, v.project_directory().generic_string());
    combine(seed, v.source_directory().generic_string());
    combine(seed, v.include_directory().generic_string());
    combine(seed, v.disable_backend());
    combine(seed, v.disable_cmakelists());
    combine(seed, hash_std_set_dogen_config_cpp_facet_types(v.enabled_facets()));
    combine(seed, v.header_extension());
    combine(seed, v.source_extension());
    combine(seed, v.disable_complete_constructor());
    combine(seed, v.disable_facet_includers());
    combine(seed, v.disable_facet_folders());
    combine(seed, v.disable_unique_file_names());
    combine(seed, v.domain_facet_folder());
    combine(seed, v.hash_facet_folder());
    combine(seed, v.io_facet_folder());
    combine(seed, v.serialization_facet_folder());
    combine(seed, v.test_data_facet_folder());
    combine(seed, v.disable_xml_serialization());
    combine(seed, v.use_integrated_io());
    combine(seed, v.disable_versioning());

    return seed;
}

} }
