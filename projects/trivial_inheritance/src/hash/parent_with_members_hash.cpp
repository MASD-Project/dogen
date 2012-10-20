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
#include "dogen/trivial_inheritance/hash/parent_with_members_hash.hpp"
#include "dogen/trivial_inheritance/hash/versioned_key_hash.hpp"
#include "dogen/utility/hash/combine.hpp"

namespace dogen {
namespace trivial_inheritance {

std::size_t parent_with_members_hasher::hash(const parent_with_members& v) {
    using dogen::utility::hash::combine;
    std::size_t seed(0);

    combine(seed, v.prop_0());
    combine(seed, v.versioned_key());

    return seed;
}

} }
