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
#include "dogen.relational/types/tracing/log_event.hpp"

namespace dogen::relational::tracing {

log_event::log_event(
    const boost::posix_time::ptime& timestamp,
    const dogen::relational::tracing::run_id& run_id,
    const std::string& component,
    const std::string& message)
    : timestamp_(timestamp),
      run_id_(run_id),
      component_(component),
      message_(message) { }

void log_event::swap(log_event& other) noexcept {
    using std::swap;
    swap(timestamp_, other.timestamp_);
    swap(run_id_, other.run_id_);
    swap(component_, other.component_);
    swap(message_, other.message_);
}

bool log_event::operator==(const log_event& rhs) const {
    return timestamp_ == rhs.timestamp_ &&
        run_id_ == rhs.run_id_ &&
        component_ == rhs.component_ &&
        message_ == rhs.message_;
}

log_event& log_event::operator=(log_event other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::posix_time::ptime& log_event::timestamp() const {
    return timestamp_;
}

boost::posix_time::ptime& log_event::timestamp() {
    return timestamp_;
}

void log_event::timestamp(const boost::posix_time::ptime& v) {
    timestamp_ = v;
}

void log_event::timestamp(const boost::posix_time::ptime&& v) {
    timestamp_ = std::move(v);
}

const dogen::relational::tracing::run_id& log_event::run_id() const {
    return run_id_;
}

dogen::relational::tracing::run_id& log_event::run_id() {
    return run_id_;
}

void log_event::run_id(const dogen::relational::tracing::run_id& v) {
    run_id_ = v;
}

void log_event::run_id(const dogen::relational::tracing::run_id&& v) {
    run_id_ = std::move(v);
}

const std::string& log_event::component() const {
    return component_;
}

std::string& log_event::component() {
    return component_;
}

void log_event::component(const std::string& v) {
    component_ = v;
}

void log_event::component(const std::string&& v) {
    component_ = std::move(v);
}

const std::string& log_event::message() const {
    return message_;
}

std::string& log_event::message() {
    return message_;
}

void log_event::message(const std::string& v) {
    message_ = v;
}

void log_event::message(const std::string&& v) {
    message_ = std::move(v);
}

}
