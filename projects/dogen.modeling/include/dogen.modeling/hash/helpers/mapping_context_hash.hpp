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
#ifndef DOGEN_YARN_HASH_HELPERS_MAPPING_CONTEXT_HASH_HPP
#define DOGEN_YARN_HASH_HELPERS_MAPPING_CONTEXT_HASH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <functional>
#include "dogen.modeling/types/helpers/mapping_context.hpp"

namespace dogen {
namespace modeling {
namespace helpers {

struct mapping_context_hasher {
public:
    static std::size_t hash(const mapping_context& v);
};

} } }

namespace std {

template<>
struct hash<dogen::modeling::helpers::mapping_context> {
public:
    size_t operator()(const dogen::modeling::helpers::mapping_context& v) const {
        return dogen::modeling::helpers::mapping_context_hasher::hash(v);
    }
};

}
#endif
