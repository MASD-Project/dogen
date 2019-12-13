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
#include "dogen.relational/types/tracing/log.hpp"

namespace dogen::relational::tracing {

log::log(
    const dogen::relational::tracing::run_id& run_id,
    const boost::posix_time::ptime& timestamp,
    const std::string& component,
    const std::string& message)
    : run_id_(run_id),
      timestamp_(timestamp),
      component_(component),
      message_(message) { }

void log::swap(log& other) noexcept {
    using std::swap;
    swap(run_id_, other.run_id_);
    swap(timestamp_, other.timestamp_);
    swap(component_, other.component_);
    swap(message_, other.message_);
}

bool log::operator==(const log& rhs) const {
    return run_id_ == rhs.run_id_ &&
        timestamp_ == rhs.timestamp_ &&
        component_ == rhs.component_ &&
        message_ == rhs.message_;
}

log& log::operator=(log other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::relational::tracing::run_id& log::run_id() const {
    return run_id_;
}

dogen::relational::tracing::run_id& log::run_id() {
    return run_id_;
}

void log::run_id(const dogen::relational::tracing::run_id& v) {
    run_id_ = v;
}

void log::run_id(const dogen::relational::tracing::run_id&& v) {
    run_id_ = std::move(v);
}

const boost::posix_time::ptime& log::timestamp() const {
    return timestamp_;
}

boost::posix_time::ptime& log::timestamp() {
    return timestamp_;
}

void log::timestamp(const boost::posix_time::ptime& v) {
    timestamp_ = v;
}

void log::timestamp(const boost::posix_time::ptime&& v) {
    timestamp_ = std::move(v);
}

const std::string& log::component() const {
    return component_;
}

std::string& log::component() {
    return component_;
}

void log::component(const std::string& v) {
    component_ = v;
}

void log::component(const std::string&& v) {
    component_ = std::move(v);
}

const std::string& log::message() const {
    return message_;
}

std::string& log::message() {
    return message_;
}

void log::message(const std::string& v) {
    message_ = v;
}

void log::message(const std::string&& v) {
    message_ = std::move(v);
}

}
