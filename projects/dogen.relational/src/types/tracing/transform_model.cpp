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
#include "dogen.relational/types/tracing/transform_model.hpp"

namespace dogen::relational::tracing {

transform_model::transform_model()
    : type_(static_cast<dogen::relational::tracing::io_type>(0)) { }

transform_model::transform_model(
    const dogen::relational::tracing::transform_id& transform_id,
    const dogen::relational::tracing::model_id& model_id,
    const dogen::relational::tracing::io_type type)
    : transform_id_(transform_id),
      model_id_(model_id),
      type_(type) { }

void transform_model::swap(transform_model& other) noexcept {
    using std::swap;
    swap(transform_id_, other.transform_id_);
    swap(model_id_, other.model_id_);
    swap(type_, other.type_);
}

bool transform_model::operator==(const transform_model& rhs) const {
    return transform_id_ == rhs.transform_id_ &&
        model_id_ == rhs.model_id_ &&
        type_ == rhs.type_;
}

transform_model& transform_model::operator=(transform_model other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::relational::tracing::transform_id& transform_model::transform_id() const {
    return transform_id_;
}

dogen::relational::tracing::transform_id& transform_model::transform_id() {
    return transform_id_;
}

void transform_model::transform_id(const dogen::relational::tracing::transform_id& v) {
    transform_id_ = v;
}

void transform_model::transform_id(const dogen::relational::tracing::transform_id&& v) {
    transform_id_ = std::move(v);
}

const dogen::relational::tracing::model_id& transform_model::model_id() const {
    return model_id_;
}

dogen::relational::tracing::model_id& transform_model::model_id() {
    return model_id_;
}

void transform_model::model_id(const dogen::relational::tracing::model_id& v) {
    model_id_ = v;
}

void transform_model::model_id(const dogen::relational::tracing::model_id&& v) {
    model_id_ = std::move(v);
}

dogen::relational::tracing::io_type transform_model::type() const {
    return type_;
}

void transform_model::type(const dogen::relational::tracing::io_type v) {
    type_ = v;
}

}
