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
#ifndef DOGEN_RELATIONAL_TYPES_TRACING_RUN_HPP
#define DOGEN_RELATIONAL_TYPES_TRACING_RUN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include "dogen.relational/types/tracing/json.hpp"
#include "dogen.relational/types/tracing/run_id.hpp"
#include "dogen.relational/types/tracing/activity.hpp"

namespace dogen::relational::tracing {

class run final {
public:
    run(const run&) = default;
    run(run&&) = default;
    ~run() = default;

public:
    run();

public:
    run(
        const boost::posix_time::ptime& start,
        const boost::posix_time::ptime& end,
        const dogen::relational::tracing::run_id& id,
        const dogen::relational::tracing::activity activity,
        const std::string& version,
        const dogen::relational::tracing::json& configuration);

public:
    const boost::posix_time::ptime& start() const;
    boost::posix_time::ptime& start();
    void start(const boost::posix_time::ptime& v);
    void start(const boost::posix_time::ptime&& v);

    const boost::posix_time::ptime& end() const;
    boost::posix_time::ptime& end();
    void end(const boost::posix_time::ptime& v);
    void end(const boost::posix_time::ptime&& v);

    const dogen::relational::tracing::run_id& id() const;
    dogen::relational::tracing::run_id& id();
    void id(const dogen::relational::tracing::run_id& v);
    void id(const dogen::relational::tracing::run_id&& v);

    /**
     * @brief What was the dogen activity that was executed, i.e. generate, convert, etc.
     */
    /**@{*/
    dogen::relational::tracing::activity activity() const;
    void activity(const dogen::relational::tracing::activity v);
    /**@}*/

    /**
     * @brief Which version of dogen where we running.
     */
    /**@{*/
    const std::string& version() const;
    std::string& version();
    void version(const std::string& v);
    void version(const std::string&& v);
    /**@}*/

    const dogen::relational::tracing::json& configuration() const;
    dogen::relational::tracing::json& configuration();
    void configuration(const dogen::relational::tracing::json& v);
    void configuration(const dogen::relational::tracing::json&& v);

public:
    bool operator==(const run& rhs) const;
    bool operator!=(const run& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(run& other) noexcept;
    run& operator=(run other);

private:
    boost::posix_time::ptime start_;
    boost::posix_time::ptime end_;
    dogen::relational::tracing::run_id id_;
    dogen::relational::tracing::activity activity_;
    std::string version_;
    dogen::relational::tracing::json configuration_;
};

}

namespace std {

template<>
inline void swap(
    dogen::relational::tracing::run& lhs,
    dogen::relational::tracing::run& rhs) {
    lhs.swap(rhs);
}

}

#endif
