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
#ifndef DOGEN_IDENTIFICATION_TYPES_ENTITIES_LOGICAL_PROVENANCE_HPP
#define DOGEN_IDENTIFICATION_TYPES_ENTITIES_LOGICAL_PROVENANCE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen.identification/types/entities/logical_id.hpp"
#include "dogen.identification/types/entities/injection_provenance.hpp"

namespace dogen::identification::entities {

/**
 * @brief Source of a model element in the logical dimension.
 */
class logical_provenance final {
public:
    logical_provenance() = default;
    logical_provenance(const logical_provenance&) = default;
    logical_provenance(logical_provenance&&) = default;
    ~logical_provenance() = default;

public:
    logical_provenance(
        const dogen::identification::entities::injection_provenance& injection,
        const dogen::identification::entities::logical_id& logical_id);

public:
    /**
     * @brief Provenance of the current element in the injection dimension.
     */
    /**@{*/
    const dogen::identification::entities::injection_provenance& injection() const;
    dogen::identification::entities::injection_provenance& injection();
    void injection(const dogen::identification::entities::injection_provenance& v);
    void injection(const dogen::identification::entities::injection_provenance&& v);
    /**@}*/

    /**
     * @brief Provenance of the current element in the logical dimension.
     */
    /**@{*/
    const dogen::identification::entities::logical_id& logical_id() const;
    dogen::identification::entities::logical_id& logical_id();
    void logical_id(const dogen::identification::entities::logical_id& v);
    void logical_id(const dogen::identification::entities::logical_id&& v);
    /**@}*/

public:
    bool operator==(const logical_provenance& rhs) const;
    bool operator!=(const logical_provenance& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(logical_provenance& other) noexcept;
    logical_provenance& operator=(logical_provenance other);

private:
    dogen::identification::entities::injection_provenance injection_;
    dogen::identification::entities::logical_id logical_id_;
};

}

namespace std {

template<>
inline void swap(
    dogen::identification::entities::logical_provenance& lhs,
    dogen::identification::entities::logical_provenance& rhs) {
    lhs.swap(rhs);
}

}

#endif
