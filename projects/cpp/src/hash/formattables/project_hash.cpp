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
#include "dogen/cpp/hash/formattables/project_hash.hpp"
#include "dogen/cpp/hash/formattables/file_info_hash.hpp"
#include "dogen/cpp/hash/formattables/cmakelists_info_hash.hpp"
#include "dogen/cpp/hash/formattables/odb_options_info_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_list_dogen_cpp_formattables_file_info(const std::list<dogen::cpp::formattables::file_info>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_boost_optional_dogen_cpp_formattables_cmakelists_info(const boost::optional<dogen::cpp::formattables::cmakelists_info>& v) {
    std::size_t seed(0);

    if (!v)
        return seed;

    combine(seed, *v);
    return seed;
}

}

namespace dogen {
namespace cpp {
namespace formattables {

std::size_t project_hasher::hash(const project& v) {
    std::size_t seed(0);

    combine(seed, hash_std_list_dogen_cpp_formattables_file_info(v.files()));
    combine(seed, v.odb_options());
    combine(seed, v.src_cmakelists());
    combine(seed, hash_boost_optional_dogen_cpp_formattables_cmakelists_info(v.include_cmakelists()));

    return seed;
}

} } }
