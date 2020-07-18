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
#ifndef DOGEN_IDENTIFICATION_TYPES_HELPERS_LOGICAL_LOCATION_BUILDER_HPP
#define DOGEN_IDENTIFICATION_TYPES_HELPERS_LOGICAL_LOCATION_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen.identification/types/entities/logical_location.hpp"

namespace dogen::identification::helpers {

class logical_location_builder final {
public:
    logical_location_builder() = default;
    logical_location_builder(const logical_location_builder&) = default;
    logical_location_builder(logical_location_builder&&) = default;
    ~logical_location_builder() = default;

public:
    explicit logical_location_builder(const dogen::identification::entities::logical_location& location_);

public:
    const dogen::identification::entities::logical_location& location_() const;
    dogen::identification::entities::logical_location& location_();
    void location_(const dogen::identification::entities::logical_location& v);
    void location_(const dogen::identification::entities::logical_location&& v);

public:
    bool operator==(const logical_location_builder& rhs) const;
    bool operator!=(const logical_location_builder& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(logical_location_builder& other) noexcept;
    logical_location_builder& operator=(logical_location_builder other);

private:
    dogen::identification::entities::logical_location location__;
};

}

namespace std {

template<>
inline void swap(
    dogen::identification::helpers::logical_location_builder& lhs,
    dogen::identification::helpers::logical_location_builder& rhs) {
    lhs.swap(rhs);
}

}

#endif
