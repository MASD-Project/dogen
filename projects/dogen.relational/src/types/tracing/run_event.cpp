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
#include "dogen.relational/types/tracing/run_event.hpp"

namespace dogen::relational::tracing {

run_event::run_event()
    : activity_(static_cast<dogen::relational::tracing::activity>(0)),
      event_type_(static_cast<dogen::relational::tracing::event_type>(0)) { }

run_event::run_event(
    const boost::posix_time::ptime& timestamp,
    const dogen::relational::tracing::run_id& id,
    const dogen::relational::tracing::activity activity,
    const std::string& version,
    const dogen::relational::tracing::json& payload,
    const dogen::relational::tracing::event_type event_type)
    : timestamp_(timestamp),
      id_(id),
      activity_(activity),
      version_(version),
      payload_(payload),
      event_type_(event_type) { }

void run_event::swap(run_event& other) noexcept {
    using std::swap;
    swap(timestamp_, other.timestamp_);
    swap(id_, other.id_);
    swap(activity_, other.activity_);
    swap(version_, other.version_);
    swap(payload_, other.payload_);
    swap(event_type_, other.event_type_);
}

bool run_event::operator==(const run_event& rhs) const {
    return timestamp_ == rhs.timestamp_ &&
        id_ == rhs.id_ &&
        activity_ == rhs.activity_ &&
        version_ == rhs.version_ &&
        payload_ == rhs.payload_ &&
        event_type_ == rhs.event_type_;
}

run_event& run_event::operator=(run_event other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::posix_time::ptime& run_event::timestamp() const {
    return timestamp_;
}

boost::posix_time::ptime& run_event::timestamp() {
    return timestamp_;
}

void run_event::timestamp(const boost::posix_time::ptime& v) {
    timestamp_ = v;
}

void run_event::timestamp(const boost::posix_time::ptime&& v) {
    timestamp_ = std::move(v);
}

const dogen::relational::tracing::run_id& run_event::id() const {
    return id_;
}

dogen::relational::tracing::run_id& run_event::id() {
    return id_;
}

void run_event::id(const dogen::relational::tracing::run_id& v) {
    id_ = v;
}

void run_event::id(const dogen::relational::tracing::run_id&& v) {
    id_ = std::move(v);
}

dogen::relational::tracing::activity run_event::activity() const {
    return activity_;
}

void run_event::activity(const dogen::relational::tracing::activity v) {
    activity_ = v;
}

const std::string& run_event::version() const {
    return version_;
}

std::string& run_event::version() {
    return version_;
}

void run_event::version(const std::string& v) {
    version_ = v;
}

void run_event::version(const std::string&& v) {
    version_ = std::move(v);
}

const dogen::relational::tracing::json& run_event::payload() const {
    return payload_;
}

dogen::relational::tracing::json& run_event::payload() {
    return payload_;
}

void run_event::payload(const dogen::relational::tracing::json& v) {
    payload_ = v;
}

void run_event::payload(const dogen::relational::tracing::json&& v) {
    payload_ = std::move(v);
}

dogen::relational::tracing::event_type run_event::event_type() const {
    return event_type_;
}

void run_event::event_type(const dogen::relational::tracing::event_type v) {
    event_type_ = v;
}

}
