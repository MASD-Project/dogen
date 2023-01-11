/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * These files are code-generated via overrides to test dogen. Do not commit them.
 *
 * Generation timestamp: 2022-10-20T10:20:30
 * WARNING: do not edit this file manually.
 * Generated by MASD Dogen v1.0.33
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
#ifndef DOGEN_IDENTIFICATION_HASH_ENTITIES_CODEC_PROVENANCE_HASH_HPP
#define DOGEN_IDENTIFICATION_HASH_ENTITIES_CODEC_PROVENANCE_HASH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <functional>
#include "dogen.identification/types/entities/codec_provenance.hpp"

namespace dogen::identification::entities {

struct codec_provenance_hasher {
public:
    static std::size_t hash(const codec_provenance& v);
};

}

namespace std {

template<>
struct hash<dogen::identification::entities::codec_provenance> {
public:
    size_t operator()(const dogen::identification::entities::codec_provenance& v) const {
        return dogen::identification::entities::codec_provenance_hasher::hash(v);
    }
};

}
#endif
