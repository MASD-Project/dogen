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
#ifndef DOGEN_RELATIONAL_TYPES_TRACING_RUN_EVENT_KEY_HPP
#define DOGEN_RELATIONAL_TYPES_TRACING_RUN_EVENT_KEY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen.relational/types/tracing/run_id.hpp"
#include "dogen.relational/types/tracing/event_type.hpp"

namespace dogen::relational::tracing {

class run_event_key final {
public:
    run_event_key(const run_event_key&) = default;
    run_event_key(run_event_key&&) = default;
    ~run_event_key() = default;

public:
    run_event_key();

public:
    run_event_key(
        const dogen::relational::tracing::run_id& run_id,
        const dogen::relational::tracing::event_type event_type);

public:
    const dogen::relational::tracing::run_id& run_id() const;
    dogen::relational::tracing::run_id& run_id();
    void run_id(const dogen::relational::tracing::run_id& v);
    void run_id(const dogen::relational::tracing::run_id&& v);

    dogen::relational::tracing::event_type event_type() const;
    void event_type(const dogen::relational::tracing::event_type v);

public:
    bool operator==(const run_event_key& rhs) const;
    bool operator!=(const run_event_key& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(run_event_key& other) noexcept;
    run_event_key& operator=(run_event_key other);

private:
    dogen::relational::tracing::run_id run_id_;
    dogen::relational::tracing::event_type event_type_;
};

}

namespace std {

template<>
inline void swap(
    dogen::relational::tracing::run_event_key& lhs,
    dogen::relational::tracing::run_event_key& rhs) {
    lhs.swap(rhs);
}

}

#endif
