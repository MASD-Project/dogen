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
#ifndef DOGEN_IDENTIFICATION_TYPES_ENTITIES_LOGICAL_META_PHYSICAL_ID_HPP
#define DOGEN_IDENTIFICATION_TYPES_ENTITIES_LOGICAL_META_PHYSICAL_ID_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen.identification/types/entities/logical_id.hpp"
#include "dogen.identification/types/entities/physical_meta_id.hpp"

namespace dogen::identification::entities {

/**
 * @brief ID in the logical-physical space.
 */
class logical_meta_physical_id final {
public:
    logical_meta_physical_id() = default;
    logical_meta_physical_id(const logical_meta_physical_id&) = default;
    logical_meta_physical_id(logical_meta_physical_id&&) = default;
    ~logical_meta_physical_id() = default;

public:
    logical_meta_physical_id(
        const dogen::identification::entities::logical_id& logical_id,
        const dogen::identification::entities::physical_meta_id& physical_id);

public:
    /**
     * @brief ID of the element in the logical dimension.
     */
    /**@{*/
    const dogen::identification::entities::logical_id& logical_id() const;
    dogen::identification::entities::logical_id& logical_id();
    void logical_id(const dogen::identification::entities::logical_id& v);
    void logical_id(const dogen::identification::entities::logical_id&& v);
    /**@}*/

    /**
     * @brief ID of the element in the physical dimension.
     */
    /**@{*/
    const dogen::identification::entities::physical_meta_id& physical_id() const;
    dogen::identification::entities::physical_meta_id& physical_id();
    void physical_id(const dogen::identification::entities::physical_meta_id& v);
    void physical_id(const dogen::identification::entities::physical_meta_id&& v);
    /**@}*/

public:
    bool operator==(const logical_meta_physical_id& rhs) const;
    bool operator!=(const logical_meta_physical_id& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(logical_meta_physical_id& other) noexcept;
    logical_meta_physical_id& operator=(logical_meta_physical_id other);

private:
    dogen::identification::entities::logical_id logical_id_;
    dogen::identification::entities::physical_meta_id physical_id_;
};

}

namespace std {

template<>
inline void swap(
    dogen::identification::entities::logical_meta_physical_id& lhs,
    dogen::identification::entities::logical_meta_physical_id& rhs) {
    lhs.swap(rhs);
}

}

#endif
