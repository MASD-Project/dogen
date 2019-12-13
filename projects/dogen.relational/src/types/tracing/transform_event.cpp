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
#include "dogen.relational/types/tracing/transform_event.hpp"

namespace dogen::relational::tracing {

transform_event::transform_event()
    : transform_type_(static_cast<dogen::relational::tracing::transform_type>(0)) { }

transform_event::transform_event(
    const boost::posix_time::ptime& timestamp,
    const dogen::relational::tracing::transform_event_key& transform_event_key,
    const dogen::relational::tracing::run_id& run_id,
    const dogen::relational::tracing::transform_type transform_type,
    const dogen::relational::tracing::transform_id& transform_id,
    const dogen::relational::tracing::json& payload)
    : timestamp_(timestamp),
      transform_event_key_(transform_event_key),
      run_id_(run_id),
      transform_type_(transform_type),
      transform_id_(transform_id),
      payload_(payload) { }

void transform_event::swap(transform_event& other) noexcept {
    using std::swap;
    swap(timestamp_, other.timestamp_);
    swap(transform_event_key_, other.transform_event_key_);
    swap(run_id_, other.run_id_);
    swap(transform_type_, other.transform_type_);
    swap(transform_id_, other.transform_id_);
    swap(payload_, other.payload_);
}

bool transform_event::operator==(const transform_event& rhs) const {
    return timestamp_ == rhs.timestamp_ &&
        transform_event_key_ == rhs.transform_event_key_ &&
        run_id_ == rhs.run_id_ &&
        transform_type_ == rhs.transform_type_ &&
        transform_id_ == rhs.transform_id_ &&
        payload_ == rhs.payload_;
}

transform_event& transform_event::operator=(transform_event other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::posix_time::ptime& transform_event::timestamp() const {
    return timestamp_;
}

boost::posix_time::ptime& transform_event::timestamp() {
    return timestamp_;
}

void transform_event::timestamp(const boost::posix_time::ptime& v) {
    timestamp_ = v;
}

void transform_event::timestamp(const boost::posix_time::ptime&& v) {
    timestamp_ = std::move(v);
}

const dogen::relational::tracing::transform_event_key& transform_event::transform_event_key() const {
    return transform_event_key_;
}

dogen::relational::tracing::transform_event_key& transform_event::transform_event_key() {
    return transform_event_key_;
}

void transform_event::transform_event_key(const dogen::relational::tracing::transform_event_key& v) {
    transform_event_key_ = v;
}

void transform_event::transform_event_key(const dogen::relational::tracing::transform_event_key&& v) {
    transform_event_key_ = std::move(v);
}

const dogen::relational::tracing::run_id& transform_event::run_id() const {
    return run_id_;
}

dogen::relational::tracing::run_id& transform_event::run_id() {
    return run_id_;
}

void transform_event::run_id(const dogen::relational::tracing::run_id& v) {
    run_id_ = v;
}

void transform_event::run_id(const dogen::relational::tracing::run_id&& v) {
    run_id_ = std::move(v);
}

dogen::relational::tracing::transform_type transform_event::transform_type() const {
    return transform_type_;
}

void transform_event::transform_type(const dogen::relational::tracing::transform_type v) {
    transform_type_ = v;
}

const dogen::relational::tracing::transform_id& transform_event::transform_id() const {
    return transform_id_;
}

dogen::relational::tracing::transform_id& transform_event::transform_id() {
    return transform_id_;
}

void transform_event::transform_id(const dogen::relational::tracing::transform_id& v) {
    transform_id_ = v;
}

void transform_event::transform_id(const dogen::relational::tracing::transform_id&& v) {
    transform_id_ = std::move(v);
}

const dogen::relational::tracing::json& transform_event::payload() const {
    return payload_;
}

dogen::relational::tracing::json& transform_event::payload() {
    return payload_;
}

void transform_event::payload(const dogen::relational::tracing::json& v) {
    payload_ = v;
}

void transform_event::payload(const dogen::relational::tracing::json&& v) {
    payload_ = std::move(v);
}

}
