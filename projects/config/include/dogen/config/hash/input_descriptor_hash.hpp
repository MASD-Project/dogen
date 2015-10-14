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
#ifndef DOGEN_CONFIG_HASH_INPUT_DESCRIPTOR_HASH_HPP
#define DOGEN_CONFIG_HASH_INPUT_DESCRIPTOR_HASH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <functional>
#include "dogen/config/types/input_descriptor.hpp"

namespace dogen {
namespace config {

struct input_descriptor_hasher {
public:
    static std::size_t hash(const input_descriptor& v);
};

} }

namespace std {

template<>
struct hash<dogen::config::input_descriptor> {
public:
    size_t operator()(const dogen::config::input_descriptor& v) const {
        return dogen::config::input_descriptor_hasher::hash(v);
    }
};

}
#endif
