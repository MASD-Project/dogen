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
#ifndef DOGEN_RELATIONAL_TYPES_TRACING_TRANSFORM_MODEL_HPP
#define DOGEN_RELATIONAL_TYPES_TRACING_TRANSFORM_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen.relational/types/tracing/io_type.hpp"
#include "dogen.relational/types/tracing/model_id.hpp"
#include "dogen.relational/types/tracing/transform_id.hpp"

namespace dogen::relational::tracing {

class transform_model final {
public:
    transform_model(const transform_model&) = default;
    transform_model(transform_model&&) = default;
    ~transform_model() = default;

public:
    transform_model();

public:
    transform_model(
        const dogen::relational::tracing::transform_id& transform_id,
        const dogen::relational::tracing::model_id& model_id,
        const dogen::relational::tracing::io_type type);

public:
    const dogen::relational::tracing::transform_id& transform_id() const;
    dogen::relational::tracing::transform_id& transform_id();
    void transform_id(const dogen::relational::tracing::transform_id& v);
    void transform_id(const dogen::relational::tracing::transform_id&& v);

    const dogen::relational::tracing::model_id& model_id() const;
    dogen::relational::tracing::model_id& model_id();
    void model_id(const dogen::relational::tracing::model_id& v);
    void model_id(const dogen::relational::tracing::model_id&& v);

    dogen::relational::tracing::io_type type() const;
    void type(const dogen::relational::tracing::io_type v);

public:
    bool operator==(const transform_model& rhs) const;
    bool operator!=(const transform_model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(transform_model& other) noexcept;
    transform_model& operator=(transform_model other);

private:
    dogen::relational::tracing::transform_id transform_id_;
    dogen::relational::tracing::model_id model_id_;
    dogen::relational::tracing::io_type type_;
};

}

namespace std {

template<>
inline void swap(
    dogen::relational::tracing::transform_model& lhs,
    dogen::relational::tracing::transform_model& rhs) {
    lhs.swap(rhs);
}

}

#endif
