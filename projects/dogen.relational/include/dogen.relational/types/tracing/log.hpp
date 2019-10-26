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
#ifndef DOGEN_RELATIONAL_TYPES_TRACING_LOG_HPP
#define DOGEN_RELATIONAL_TYPES_TRACING_LOG_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen.relational/types/tracing/transform_id.hpp"

namespace dogen::relational::tracing {

class log final {
public:
    log() = default;
    log(const log&) = default;
    log(log&&) = default;
    ~log() = default;

public:
    log(
        const dogen::relational::tracing::transform_id& transform_id,
        const std::string& component,
        const std::string& message);

public:
    const dogen::relational::tracing::transform_id& transform_id() const;
    dogen::relational::tracing::transform_id& transform_id();
    void transform_id(const dogen::relational::tracing::transform_id& v);
    void transform_id(const dogen::relational::tracing::transform_id&& v);

    const std::string& component() const;
    std::string& component();
    void component(const std::string& v);
    void component(const std::string&& v);

    const std::string& message() const;
    std::string& message();
    void message(const std::string& v);
    void message(const std::string&& v);

public:
    bool operator==(const log& rhs) const;
    bool operator!=(const log& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(log& other) noexcept;
    log& operator=(log other);

private:
    dogen::relational::tracing::transform_id transform_id_;
    std::string component_;
    std::string message_;
};

}

namespace std {

template<>
inline void swap(
    dogen::relational::tracing::log& lhs,
    dogen::relational::tracing::log& rhs) {
    lhs.swap(rhs);
}

}

#endif
