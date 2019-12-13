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
    : transform_type_(static_cast<dogen::relational::tracing::transform_type>(0)),
      event_type_(static_cast<dogen::relational::tracing::event_type>(0)) { }

transform_event::transform_event(
    const boost::posix_time::ptime& timestamp,
    const dogen::relational::tracing::transform_id& id,
    const dogen::relational::tracing::transform_instance_id& instance_id,
    const dogen::relational::tracing::run_id& run_id,
    const dogen::relational::tracing::transform_type transform_type,
    const dogen::relational::tracing::event_type event_type,
    const dogen::relational::tracing::json& payload)
    : timestamp_(timestamp),
      id_(id),
      instance_id_(instance_id),
      run_id_(run_id),
      transform_type_(transform_type),
      event_type_(event_type),
      payload_(payload) { }

void transform_event::swap(transform_event& other) noexcept {
    using std::swap;
    swap(timestamp_, other.timestamp_);
    swap(id_, other.id_);
    swap(instance_id_, other.instance_id_);
    swap(run_id_, other.run_id_);
    swap(transform_type_, other.transform_type_);
    swap(event_type_, other.event_type_);
    swap(payload_, other.payload_);
}

bool transform_event::operator==(const transform_event& rhs) const {
    return timestamp_ == rhs.timestamp_ &&
        id_ == rhs.id_ &&
        instance_id_ == rhs.instance_id_ &&
        run_id_ == rhs.run_id_ &&
        transform_type_ == rhs.transform_type_ &&
        event_type_ == rhs.event_type_ &&
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

const dogen::relational::tracing::transform_id& transform_event::id() const {
    return id_;
}

dogen::relational::tracing::transform_id& transform_event::id() {
    return id_;
}

void transform_event::id(const dogen::relational::tracing::transform_id& v) {
    id_ = v;
}

void transform_event::id(const dogen::relational::tracing::transform_id&& v) {
    id_ = std::move(v);
}

const dogen::relational::tracing::transform_instance_id& transform_event::instance_id() const {
    return instance_id_;
}

dogen::relational::tracing::transform_instance_id& transform_event::instance_id() {
    return instance_id_;
}

void transform_event::instance_id(const dogen::relational::tracing::transform_instance_id& v) {
    instance_id_ = v;
}

void transform_event::instance_id(const dogen::relational::tracing::transform_instance_id&& v) {
    instance_id_ = std::move(v);
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

dogen::relational::tracing::event_type transform_event::event_type() const {
    return event_type_;
}

void transform_event::event_type(const dogen::relational::tracing::event_type v) {
    event_type_ = v;
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
