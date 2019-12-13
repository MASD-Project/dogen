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
#include "dogen.relational/types/tracing/transform_event_key.hpp"

namespace dogen::relational::tracing {

transform_event_key::transform_event_key()
    : event_type_(static_cast<dogen::relational::tracing::event_type>(0)) { }

transform_event_key::transform_event_key(
    const dogen::relational::tracing::transform_instance_id& transform_instance_id,
    const dogen::relational::tracing::event_type event_type)
    : transform_instance_id_(transform_instance_id),
      event_type_(event_type) { }

void transform_event_key::swap(transform_event_key& other) noexcept {
    using std::swap;
    swap(transform_instance_id_, other.transform_instance_id_);
    swap(event_type_, other.event_type_);
}

bool transform_event_key::operator==(const transform_event_key& rhs) const {
    return transform_instance_id_ == rhs.transform_instance_id_ &&
        event_type_ == rhs.event_type_;
}

transform_event_key& transform_event_key::operator=(transform_event_key other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::relational::tracing::transform_instance_id& transform_event_key::transform_instance_id() const {
    return transform_instance_id_;
}

dogen::relational::tracing::transform_instance_id& transform_event_key::transform_instance_id() {
    return transform_instance_id_;
}

void transform_event_key::transform_instance_id(const dogen::relational::tracing::transform_instance_id& v) {
    transform_instance_id_ = v;
}

void transform_event_key::transform_instance_id(const dogen::relational::tracing::transform_instance_id&& v) {
    transform_instance_id_ = std::move(v);
}

dogen::relational::tracing::event_type transform_event_key::event_type() const {
    return event_type_;
}

void transform_event_key::event_type(const dogen::relational::tracing::event_type v) {
    event_type_ = v;
}

}
