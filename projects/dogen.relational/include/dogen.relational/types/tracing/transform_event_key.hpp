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
#ifndef DOGEN_RELATIONAL_TYPES_TRACING_TRANSFORM_EVENT_KEY_HPP
#define DOGEN_RELATIONAL_TYPES_TRACING_TRANSFORM_EVENT_KEY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen.relational/types/tracing/event_type.hpp"
#include "dogen.relational/types/tracing/transform_instance_id.hpp"

namespace dogen::relational::tracing {

class transform_event_key final {
public:
    transform_event_key(const transform_event_key&) = default;
    transform_event_key(transform_event_key&&) = default;
    ~transform_event_key() = default;

public:
    transform_event_key();

public:
    transform_event_key(
        const dogen::relational::tracing::transform_instance_id& transform_instance_id,
        const dogen::relational::tracing::event_type event_type);

public:
    const dogen::relational::tracing::transform_instance_id& transform_instance_id() const;
    dogen::relational::tracing::transform_instance_id& transform_instance_id();
    void transform_instance_id(const dogen::relational::tracing::transform_instance_id& v);
    void transform_instance_id(const dogen::relational::tracing::transform_instance_id&& v);

    dogen::relational::tracing::event_type event_type() const;
    void event_type(const dogen::relational::tracing::event_type v);

public:
    bool operator==(const transform_event_key& rhs) const;
    bool operator!=(const transform_event_key& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(transform_event_key& other) noexcept;
    transform_event_key& operator=(transform_event_key other);

private:
    dogen::relational::tracing::transform_instance_id transform_instance_id_;
    dogen::relational::tracing::event_type event_type_;
};

}

namespace std {

template<>
inline void swap(
    dogen::relational::tracing::transform_event_key& lhs,
    dogen::relational::tracing::transform_event_key& rhs) {
    lhs.swap(rhs);
}

}

#endif
