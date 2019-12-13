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
#include "dogen.relational/types/tracing/run_event_key.hpp"

namespace dogen::relational::tracing {

run_event_key::run_event_key()
    : event_type_(static_cast<dogen::relational::tracing::event_type>(0)) { }

run_event_key::run_event_key(
    const dogen::relational::tracing::run_id& run_id,
    const dogen::relational::tracing::event_type event_type)
    : run_id_(run_id),
      event_type_(event_type) { }

void run_event_key::swap(run_event_key& other) noexcept {
    using std::swap;
    swap(run_id_, other.run_id_);
    swap(event_type_, other.event_type_);
}

bool run_event_key::operator==(const run_event_key& rhs) const {
    return run_id_ == rhs.run_id_ &&
        event_type_ == rhs.event_type_;
}

run_event_key& run_event_key::operator=(run_event_key other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::relational::tracing::run_id& run_event_key::run_id() const {
    return run_id_;
}

dogen::relational::tracing::run_id& run_event_key::run_id() {
    return run_id_;
}

void run_event_key::run_id(const dogen::relational::tracing::run_id& v) {
    run_id_ = v;
}

void run_event_key::run_id(const dogen::relational::tracing::run_id&& v) {
    run_id_ = std::move(v);
}

dogen::relational::tracing::event_type run_event_key::event_type() const {
    return event_type_;
}

void run_event_key::event_type(const dogen::relational::tracing::event_type v) {
    event_type_ = v;
}

}
