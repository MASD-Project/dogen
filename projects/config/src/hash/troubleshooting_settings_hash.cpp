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
#include "dogen/config/hash/archive_types_hash.hpp"
#include "dogen/config/hash/troubleshooting_settings_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value)
{
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_boost_filesystem_path(const boost::filesystem::path& v) {
    std::size_t seed(0);
    combine(seed, v.generic_string());
    return seed;
}

}

namespace dogen {
namespace config {

std::size_t troubleshooting_settings_hasher::hash(const troubleshooting_settings&v) {
    std::size_t seed(0);

    combine(seed, v.verbose());
    combine(seed, hash_boost_filesystem_path(v.debug_dir()));
    combine(seed, v.save_dia_model());
    combine(seed, v.save_sml_model());
    combine(seed, v.stop_after_formatting());
    combine(seed, v.stop_after_merging());

    return seed;
}

} }
