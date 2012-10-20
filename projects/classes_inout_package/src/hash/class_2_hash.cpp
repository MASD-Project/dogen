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
#include "dogen/classes_inout_package/hash/class_2_hash.hpp"
#include "dogen/classes_inout_package/hash/versioned_key_hash.hpp"
#include "dogen/utility/hash/combine.hpp"

namespace dogen {
namespace classes_inout_package {

std::size_t class_2_hasher::hash(const class_2& v) {
    using dogen::utility::hash::combine;
    std::size_t seed(0);

    combine(seed, v.versioned_key());
    return seed;
}

} }
