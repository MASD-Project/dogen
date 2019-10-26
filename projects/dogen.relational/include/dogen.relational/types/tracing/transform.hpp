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
#ifndef DOGEN_RELATIONAL_TYPES_TRACING_TRANSFORM_HPP
#define DOGEN_RELATIONAL_TYPES_TRACING_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include "dogen.relational/types/tracing/run_id.hpp"
#include "dogen.relational/types/tracing/transform_id.hpp"
#include "dogen.relational/types/tracing/transform_type.hpp"

namespace dogen::relational::tracing {

class transform final {
public:
    transform(const transform&) = default;
    transform(transform&&) = default;
    ~transform() = default;

public:
    transform();

public:
    transform(
        const boost::posix_time::ptime& start,
        const boost::posix_time::ptime& end,
        const dogen::relational::tracing::transform_id& id,
        const std::string& name,
        const std::string& description,
        const dogen::relational::tracing::run_id& run_id,
        const dogen::relational::tracing::transform_type type);

public:
    const boost::posix_time::ptime& start() const;
    boost::posix_time::ptime& start();
    void start(const boost::posix_time::ptime& v);
    void start(const boost::posix_time::ptime&& v);

    const boost::posix_time::ptime& end() const;
    boost::posix_time::ptime& end();
    void end(const boost::posix_time::ptime& v);
    void end(const boost::posix_time::ptime&& v);

    const dogen::relational::tracing::transform_id& id() const;
    dogen::relational::tracing::transform_id& id();
    void id(const dogen::relational::tracing::transform_id& v);
    void id(const dogen::relational::tracing::transform_id&& v);

    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);

    const std::string& description() const;
    std::string& description();
    void description(const std::string& v);
    void description(const std::string&& v);

    const dogen::relational::tracing::run_id& run_id() const;
    dogen::relational::tracing::run_id& run_id();
    void run_id(const dogen::relational::tracing::run_id& v);
    void run_id(const dogen::relational::tracing::run_id&& v);

    dogen::relational::tracing::transform_type type() const;
    void type(const dogen::relational::tracing::transform_type v);

public:
    bool operator==(const transform& rhs) const;
    bool operator!=(const transform& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(transform& other) noexcept;
    transform& operator=(transform other);

private:
    boost::posix_time::ptime start_;
    boost::posix_time::ptime end_;
    dogen::relational::tracing::transform_id id_;
    std::string name_;
    std::string description_;
    dogen::relational::tracing::run_id run_id_;
    dogen::relational::tracing::transform_type type_;
};

}

namespace std {

template<>
inline void swap(
    dogen::relational::tracing::transform& lhs,
    dogen::relational::tracing::transform& rhs) {
    lhs.swap(rhs);
}

}

#endif
