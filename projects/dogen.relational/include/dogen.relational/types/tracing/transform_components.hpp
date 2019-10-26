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
#ifndef DOGEN_RELATIONAL_TYPES_TRACING_TRANSFORM_COMPONENTS_HPP
#define DOGEN_RELATIONAL_TYPES_TRACING_TRANSFORM_COMPONENTS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include "dogen.relational/types/tracing/transform_components_key.hpp"

namespace dogen::relational::tracing {

class transform_components final {
public:
    transform_components() = default;
    transform_components(const transform_components&) = default;
    transform_components(transform_components&&) = default;
    ~transform_components() = default;

public:
    transform_components(
        const dogen::relational::tracing::transform_components_key& key,
        const boost::posix_time::ptime& start);

public:
    const dogen::relational::tracing::transform_components_key& key() const;
    dogen::relational::tracing::transform_components_key& key();
    void key(const dogen::relational::tracing::transform_components_key& v);
    void key(const dogen::relational::tracing::transform_components_key&& v);

    const boost::posix_time::ptime& start() const;
    boost::posix_time::ptime& start();
    void start(const boost::posix_time::ptime& v);
    void start(const boost::posix_time::ptime&& v);

public:
    bool operator==(const transform_components& rhs) const;
    bool operator!=(const transform_components& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(transform_components& other) noexcept;
    transform_components& operator=(transform_components other);

private:
    dogen::relational::tracing::transform_components_key key_;
    boost::posix_time::ptime start_;
};

}

namespace std {

template<>
inline void swap(
    dogen::relational::tracing::transform_components& lhs,
    dogen::relational::tracing::transform_components& rhs) {
    lhs.swap(rhs);
}

}

#endif
