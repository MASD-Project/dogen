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
#include "dogen/quilt.cpp/hash/formattables/facet_profile_hash.hpp"
#include "dogen/quilt.cpp/hash/formattables/profile_group_hash.hpp"
#include "dogen/quilt.cpp/hash/formattables/profile_types_hash.hpp"
#include "dogen/quilt.cpp/hash/formattables/formatter_profile_hash.hpp"
#include "dogen/quilt.cpp/hash/formattables/decoration_profile_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_list_std_string(const std::list<std::string>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_boost_optional_dogen_quilt_cpp_formattables_decoration_profile(const boost::optional<dogen::quilt::cpp::formattables::decoration_profile>& v) {
    std::size_t seed(0);

    if (!v)
        return seed;

    combine(seed, *v);
    return seed;
}

inline std::size_t hash_boost_optional_dogen_quilt_cpp_formattables_facet_profile(const boost::optional<dogen::quilt::cpp::formattables::facet_profile>& v) {
    std::size_t seed(0);

    if (!v)
        return seed;

    combine(seed, *v);
    return seed;
}

inline std::size_t hash_boost_optional_dogen_quilt_cpp_formattables_formatter_profile(const boost::optional<dogen::quilt::cpp::formattables::formatter_profile>& v) {
    std::size_t seed(0);

    if (!v)
        return seed;

    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_unordered_map_std_string_dogen_quilt_cpp_formattables_facet_profile(const std::unordered_map<std::string, dogen::quilt::cpp::formattables::facet_profile>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_std_string_dogen_quilt_cpp_formattables_formatter_profile(const std::unordered_map<std::string, dogen::quilt::cpp::formattables::formatter_profile>& v) {
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

std::size_t profile_group_hasher::hash(const profile_group& v) {
    std::size_t seed(0);

    combine(seed, v.name());
    combine(seed, hash_std_list_std_string(v.parents()));
    combine(seed, v.profile_type());
    combine(seed, v.bind_to_stereotype());
    combine(seed, hash_boost_optional_dogen_quilt_cpp_formattables_decoration_profile(v.decoration_profile()));
    combine(seed, hash_boost_optional_dogen_quilt_cpp_formattables_facet_profile(v.default_facet_profile()));
    combine(seed, hash_boost_optional_dogen_quilt_cpp_formattables_formatter_profile(v.default_formatter_profile()));
    combine(seed, hash_std_unordered_map_std_string_dogen_quilt_cpp_formattables_facet_profile(v.facet_profiles()));
    combine(seed, hash_std_unordered_map_std_string_dogen_quilt_cpp_formattables_formatter_profile(v.formatter_profiles()));

    return seed;
}

} } } }
