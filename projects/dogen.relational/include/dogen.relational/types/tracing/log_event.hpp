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
#ifndef DOGEN_RELATIONAL_TYPES_TRACING_LOG_EVENT_HPP
#define DOGEN_RELATIONAL_TYPES_TRACING_LOG_EVENT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include "dogen.relational/types/tracing/run_id.hpp"

namespace dogen::relational::tracing {

class log_event final {
public:
    log_event() = default;
    log_event(const log_event&) = default;
    log_event(log_event&&) = default;
    ~log_event() = default;

public:
    log_event(
        const boost::posix_time::ptime& timestamp,
        const dogen::relational::tracing::run_id& run_id,
        const std::string& component,
        const std::string& message);

public:
    const boost::posix_time::ptime& timestamp() const;
    boost::posix_time::ptime& timestamp();
    void timestamp(const boost::posix_time::ptime& v);
    void timestamp(const boost::posix_time::ptime&& v);

    const dogen::relational::tracing::run_id& run_id() const;
    dogen::relational::tracing::run_id& run_id();
    void run_id(const dogen::relational::tracing::run_id& v);
    void run_id(const dogen::relational::tracing::run_id&& v);

    const std::string& component() const;
    std::string& component();
    void component(const std::string& v);
    void component(const std::string&& v);

    const std::string& message() const;
    std::string& message();
    void message(const std::string& v);
    void message(const std::string&& v);

public:
    bool operator==(const log_event& rhs) const;
    bool operator!=(const log_event& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(log_event& other) noexcept;
    log_event& operator=(log_event other);

private:
    boost::posix_time::ptime timestamp_;
    dogen::relational::tracing::run_id run_id_;
    std::string component_;
    std::string message_;
};

}

namespace std {

template<>
inline void swap(
    dogen::relational::tracing::log_event& lhs,
    dogen::relational::tracing::log_event& rhs) {
    lhs.swap(rhs);
}

}

#endif
