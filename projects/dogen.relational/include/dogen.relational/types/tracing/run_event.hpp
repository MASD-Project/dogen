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
#ifndef DOGEN_RELATIONAL_TYPES_TRACING_RUN_EVENT_HPP
#define DOGEN_RELATIONAL_TYPES_TRACING_RUN_EVENT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include "dogen.relational/types/tracing/json.hpp"
#include "dogen.relational/types/tracing/activity.hpp"
#include "dogen.relational/types/tracing/run_event_key.hpp"

namespace dogen::relational::tracing {

class run_event final {
public:
    run_event(const run_event&) = default;
    run_event(run_event&&) = default;
    ~run_event() = default;

public:
    run_event();

public:
    run_event(
        const boost::posix_time::ptime& timestamp,
        const dogen::relational::tracing::run_event_key& run_event_key,
        const std::string& version,
        const dogen::relational::tracing::json& payload,
        const dogen::relational::tracing::activity activity);

public:
    const boost::posix_time::ptime& timestamp() const;
    boost::posix_time::ptime& timestamp();
    void timestamp(const boost::posix_time::ptime& v);
    void timestamp(const boost::posix_time::ptime&& v);

    const dogen::relational::tracing::run_event_key& run_event_key() const;
    dogen::relational::tracing::run_event_key& run_event_key();
    void run_event_key(const dogen::relational::tracing::run_event_key& v);
    void run_event_key(const dogen::relational::tracing::run_event_key&& v);

    /**
     * @brief Which version of dogen where we running.
     */
    /**@{*/
    const std::string& version() const;
    std::string& version();
    void version(const std::string& v);
    void version(const std::string&& v);
    /**@}*/

    const dogen::relational::tracing::json& payload() const;
    dogen::relational::tracing::json& payload();
    void payload(const dogen::relational::tracing::json& v);
    void payload(const dogen::relational::tracing::json&& v);

    dogen::relational::tracing::activity activity() const;
    void activity(const dogen::relational::tracing::activity v);

public:
    bool operator==(const run_event& rhs) const;
    bool operator!=(const run_event& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(run_event& other) noexcept;
    run_event& operator=(run_event other);

private:
    boost::posix_time::ptime timestamp_;
    dogen::relational::tracing::run_event_key run_event_key_;
    std::string version_;
    dogen::relational::tracing::json payload_;
    dogen::relational::tracing::activity activity_;
};

}

namespace std {

template<>
inline void swap(
    dogen::relational::tracing::run_event& lhs,
    dogen::relational::tracing::run_event& rhs) {
    lhs.swap(rhs);
}

}

#endif
