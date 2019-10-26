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
#include "dogen.relational/types/tracing/transform_components.hpp"

namespace dogen::relational::tracing {

transform_components::transform_components(
    const dogen::relational::tracing::transform_components_key& key,
    const boost::posix_time::ptime& start)
    : key_(key),
      start_(start) { }

void transform_components::swap(transform_components& other) noexcept {
    using std::swap;
    swap(key_, other.key_);
    swap(start_, other.start_);
}

bool transform_components::operator==(const transform_components& rhs) const {
    return key_ == rhs.key_ &&
        start_ == rhs.start_;
}

transform_components& transform_components::operator=(transform_components other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::relational::tracing::transform_components_key& transform_components::key() const {
    return key_;
}

dogen::relational::tracing::transform_components_key& transform_components::key() {
    return key_;
}

void transform_components::key(const dogen::relational::tracing::transform_components_key& v) {
    key_ = v;
}

void transform_components::key(const dogen::relational::tracing::transform_components_key&& v) {
    key_ = std::move(v);
}

const boost::posix_time::ptime& transform_components::start() const {
    return start_;
}

boost::posix_time::ptime& transform_components::start() {
    return start_;
}

void transform_components::start(const boost::posix_time::ptime& v) {
    start_ = v;
}

void transform_components::start(const boost::posix_time::ptime&& v) {
    start_ = std::move(v);
}

}
