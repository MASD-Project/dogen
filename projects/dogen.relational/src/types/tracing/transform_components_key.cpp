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
#include "dogen.relational/types/tracing/transform_components_key.hpp"

namespace dogen::relational::tracing {

transform_components_key::transform_components_key(
    const dogen::relational::tracing::transform_id& parent_id,
    const dogen::relational::tracing::transform_id& component_id)
    : parent_id_(parent_id),
      component_id_(component_id) { }

void transform_components_key::swap(transform_components_key& other) noexcept {
    using std::swap;
    swap(parent_id_, other.parent_id_);
    swap(component_id_, other.component_id_);
}

bool transform_components_key::operator==(const transform_components_key& rhs) const {
    return parent_id_ == rhs.parent_id_ &&
        component_id_ == rhs.component_id_;
}

transform_components_key& transform_components_key::operator=(transform_components_key other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::relational::tracing::transform_id& transform_components_key::parent_id() const {
    return parent_id_;
}

dogen::relational::tracing::transform_id& transform_components_key::parent_id() {
    return parent_id_;
}

void transform_components_key::parent_id(const dogen::relational::tracing::transform_id& v) {
    parent_id_ = v;
}

void transform_components_key::parent_id(const dogen::relational::tracing::transform_id&& v) {
    parent_id_ = std::move(v);
}

const dogen::relational::tracing::transform_id& transform_components_key::component_id() const {
    return component_id_;
}

dogen::relational::tracing::transform_id& transform_components_key::component_id() {
    return component_id_;
}

void transform_components_key::component_id(const dogen::relational::tracing::transform_id& v) {
    component_id_ = v;
}

void transform_components_key::component_id(const dogen::relational::tracing::transform_id&& v) {
    component_id_ = std::move(v);
}

}
