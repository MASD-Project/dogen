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
#ifndef DOGEN_RELATIONAL_TYPES_TRACING_TRANSFORM_EVENT_HPP
#define DOGEN_RELATIONAL_TYPES_TRACING_TRANSFORM_EVENT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include "dogen.relational/types/tracing/json.hpp"
#include "dogen.relational/types/tracing/run_id.hpp"
#include "dogen.relational/types/tracing/transform_id.hpp"
#include "dogen.relational/types/tracing/transform_type.hpp"
#include "dogen.relational/types/tracing/transform_event_key.hpp"

namespace dogen::relational::tracing {

class transform_event final {
public:
    transform_event(const transform_event&) = default;
    transform_event(transform_event&&) = default;
    ~transform_event() = default;

public:
    transform_event();

public:
    transform_event(
        const boost::posix_time::ptime& timestamp,
        const dogen::relational::tracing::transform_event_key& transform_event_key,
        const dogen::relational::tracing::run_id& run_id,
        const dogen::relational::tracing::transform_type transform_type,
        const dogen::relational::tracing::transform_id& transform_id,
        const dogen::relational::tracing::json& payload);

public:
    const boost::posix_time::ptime& timestamp() const;
    boost::posix_time::ptime& timestamp();
    void timestamp(const boost::posix_time::ptime& v);
    void timestamp(const boost::posix_time::ptime&& v);

    const dogen::relational::tracing::transform_event_key& transform_event_key() const;
    dogen::relational::tracing::transform_event_key& transform_event_key();
    void transform_event_key(const dogen::relational::tracing::transform_event_key& v);
    void transform_event_key(const dogen::relational::tracing::transform_event_key&& v);

    const dogen::relational::tracing::run_id& run_id() const;
    dogen::relational::tracing::run_id& run_id();
    void run_id(const dogen::relational::tracing::run_id& v);
    void run_id(const dogen::relational::tracing::run_id&& v);

    dogen::relational::tracing::transform_type transform_type() const;
    void transform_type(const dogen::relational::tracing::transform_type v);

    const dogen::relational::tracing::transform_id& transform_id() const;
    dogen::relational::tracing::transform_id& transform_id();
    void transform_id(const dogen::relational::tracing::transform_id& v);
    void transform_id(const dogen::relational::tracing::transform_id&& v);

    const dogen::relational::tracing::json& payload() const;
    dogen::relational::tracing::json& payload();
    void payload(const dogen::relational::tracing::json& v);
    void payload(const dogen::relational::tracing::json&& v);

public:
    bool operator==(const transform_event& rhs) const;
    bool operator!=(const transform_event& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(transform_event& other) noexcept;
    transform_event& operator=(transform_event other);

private:
    boost::posix_time::ptime timestamp_;
    dogen::relational::tracing::transform_event_key transform_event_key_;
    dogen::relational::tracing::run_id run_id_;
    dogen::relational::tracing::transform_type transform_type_;
    dogen::relational::tracing::transform_id transform_id_;
    dogen::relational::tracing::json payload_;
};

}

namespace std {

template<>
inline void swap(
    dogen::relational::tracing::transform_event& lhs,
    dogen::relational::tracing::transform_event& rhs) {
    lhs.swap(rhs);
}

}

#endif
