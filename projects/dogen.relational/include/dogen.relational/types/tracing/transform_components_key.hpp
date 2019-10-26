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
#ifndef DOGEN_RELATIONAL_TYPES_TRACING_TRANSFORM_COMPONENTS_KEY_HPP
#define DOGEN_RELATIONAL_TYPES_TRACING_TRANSFORM_COMPONENTS_KEY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen.relational/types/tracing/transform_id.hpp"

namespace dogen::relational::tracing {

class transform_components_key final {
public:
    transform_components_key() = default;
    transform_components_key(const transform_components_key&) = default;
    transform_components_key(transform_components_key&&) = default;
    ~transform_components_key() = default;

public:
    transform_components_key(
        const dogen::relational::tracing::transform_id& parent_id,
        const dogen::relational::tracing::transform_id& component_id);

public:
    const dogen::relational::tracing::transform_id& parent_id() const;
    dogen::relational::tracing::transform_id& parent_id();
    void parent_id(const dogen::relational::tracing::transform_id& v);
    void parent_id(const dogen::relational::tracing::transform_id&& v);

    const dogen::relational::tracing::transform_id& component_id() const;
    dogen::relational::tracing::transform_id& component_id();
    void component_id(const dogen::relational::tracing::transform_id& v);
    void component_id(const dogen::relational::tracing::transform_id&& v);

public:
    bool operator==(const transform_components_key& rhs) const;
    bool operator!=(const transform_components_key& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(transform_components_key& other) noexcept;
    transform_components_key& operator=(transform_components_key other);

private:
    dogen::relational::tracing::transform_id parent_id_;
    dogen::relational::tracing::transform_id component_id_;
};

}

namespace std {

template<>
inline void swap(
    dogen::relational::tracing::transform_components_key& lhs,
    dogen::relational::tracing::transform_components_key& rhs) {
    lhs.swap(rhs);
}

}

#endif
