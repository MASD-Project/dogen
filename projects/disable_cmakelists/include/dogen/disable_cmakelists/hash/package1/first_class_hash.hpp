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
#ifndef DOGEN_DISABLE_CMAKELISTS_HASH_PACKAGE1_FIRST_CLASS_HASH_HPP
#define DOGEN_DISABLE_CMAKELISTS_HASH_PACKAGE1_FIRST_CLASS_HASH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <functional>
#include "dogen/disable_cmakelists/domain/package1/first_class.hpp"
#include "dogen/disable_cmakelists/hash/versioned_key_hash.hpp"
#include "dogen/utility/hash/combine.hpp"

namespace std {

template<>
class hash<dogen::disable_cmakelists::package1::first_class> {
public:
    size_t operator()(const dogen::disable_cmakelists::package1::first_class& value) const {
        using dogen::utility::hash::combine;
        std::size_t seed(0);

        combine(seed, value.public_attribute());
        combine(seed, value.private_attribute());
        combine(seed, value.versioned_key());
        return seed;
    }
};

}
#endif
