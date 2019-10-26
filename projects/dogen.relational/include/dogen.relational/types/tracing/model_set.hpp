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
#ifndef DOGEN_RELATIONAL_TYPES_TRACING_MODEL_SET_HPP
#define DOGEN_RELATIONAL_TYPES_TRACING_MODEL_SET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen.relational/types/tracing/model_set_id.hpp"

namespace dogen::relational::tracing {

class model_set final {
public:
    model_set() = default;
    model_set(const model_set&) = default;
    model_set(model_set&&) = default;
    ~model_set() = default;

public:
    model_set(
        const dogen::relational::tracing::model_set_id& id,
        const std::string& qualified_name);

public:
    const dogen::relational::tracing::model_set_id& id() const;
    dogen::relational::tracing::model_set_id& id();
    void id(const dogen::relational::tracing::model_set_id& v);
    void id(const dogen::relational::tracing::model_set_id&& v);

    const std::string& qualified_name() const;
    std::string& qualified_name();
    void qualified_name(const std::string& v);
    void qualified_name(const std::string&& v);

public:
    bool operator==(const model_set& rhs) const;
    bool operator!=(const model_set& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(model_set& other) noexcept;
    model_set& operator=(model_set other);

private:
    dogen::relational::tracing::model_set_id id_;
    std::string qualified_name_;
};

}

namespace std {

template<>
inline void swap(
    dogen::relational::tracing::model_set& lhs,
    dogen::relational::tracing::model_set& rhs) {
    lhs.swap(rhs);
}

}

#endif
