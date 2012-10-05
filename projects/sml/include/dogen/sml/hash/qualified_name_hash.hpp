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
 * You should have received a copy of the GNU General PublicLicense
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#ifndef DOGEN_SML_HASH_QUALIFIED_NAME_HASH_HPP
#define DOGEN_SML_HASH_QUALIFIED_NAME_HASH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <functional>
#include "dogen/utility/hash/combine.hpp"
#include "dogen/sml/hash/meta_types_hash.hpp"
#include "dogen/sml/domain/qualified_name.hpp"

namespace std {

template<>
class hash<dogen::sml::qualified_name> {
public:
    size_t operator()(dogen::sml::qualified_name value) const {
        std::size_t seed(0);

        dogen::utility::hash::combine(seed, value.model_name());
        dogen::utility::hash::combine(seed, value.type_name());
        dogen::utility::hash::combine(seed, value.meta_type());

        for (auto package_name : value.package_path())
            dogen::utility::hash::combine(seed, package_name);

        return seed;
    }
};

}

#endif
