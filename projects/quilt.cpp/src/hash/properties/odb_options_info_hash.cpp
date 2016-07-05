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
#include "dogen/formatters/hash/file_properties_hash.hpp"
#include "dogen/quilt.cpp/hash/properties/formattable_hash.hpp"
#include "dogen/quilt.cpp/hash/properties/odb_options_info_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_boost_filesystem_path(const boost::filesystem::path& v) {
    std::size_t seed(0);
    combine(seed, v.generic_string());
    return seed;
}

inline std::size_t hash_boost_optional_dogen_formatters_file_properties(const boost::optional<dogen::formatters::file_properties>& v) {
    std::size_t seed(0);

    if (!v)
        return seed;

    combine(seed, *v);
    return seed;
}

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

std::size_t odb_options_info_hasher::hash(const odb_options_info& v) {
    std::size_t seed(0);

    combine(seed, dynamic_cast<const dogen::quilt::cpp::properties::formattable&>(v));

    combine(seed, v.model_name());
    combine(seed, v.product_name());
    combine(seed, hash_boost_filesystem_path(v.file_path()));
    combine(seed, v.file_name());
    combine(seed, v.odb_folder());
    combine(seed, hash_boost_optional_dogen_formatters_file_properties(v.file_properties()));

    return seed;
}

} } } }
