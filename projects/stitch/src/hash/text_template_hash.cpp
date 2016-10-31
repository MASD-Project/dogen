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
#include "dogen/stitch/hash/line_hash.hpp"
#include "dogen/stitch/hash/properties_hash.hpp"
#include "dogen/stitch/hash/text_template_hash.hpp"
#include "dogen/annotations/hash/annotation_hash.hpp"
#include "dogen/annotations/hash/scribble_group_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_list_dogen_stitch_line(const std::list<dogen::stitch::line>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

}

namespace dogen {
namespace stitch {

std::size_t text_template_hasher::hash(const text_template& v) {
    std::size_t seed(0);

    combine(seed, v.properties());
    combine(seed, v.scribble_group());
    combine(seed, v.annotation());
    combine(seed, hash_std_list_dogen_stitch_line(v.lines()));

    return seed;
}

} }
