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
#include "dogen.relational/types/tracing/run.hpp"

namespace dogen::relational::tracing {

run::run()
    : activity_(static_cast<dogen::relational::tracing::activity>(0)) { }

run::run(
    const boost::posix_time::ptime& start,
    const boost::posix_time::ptime& end,
    const dogen::relational::tracing::run_id& id,
    const dogen::relational::tracing::activity activity,
    const std::string& version,
    const dogen::relational::tracing::json& configuration)
    : start_(start),
      end_(end),
      id_(id),
      activity_(activity),
      version_(version),
      configuration_(configuration) { }

void run::swap(run& other) noexcept {
    using std::swap;
    swap(start_, other.start_);
    swap(end_, other.end_);
    swap(id_, other.id_);
    swap(activity_, other.activity_);
    swap(version_, other.version_);
    swap(configuration_, other.configuration_);
}

bool run::operator==(const run& rhs) const {
    return start_ == rhs.start_ &&
        end_ == rhs.end_ &&
        id_ == rhs.id_ &&
        activity_ == rhs.activity_ &&
        version_ == rhs.version_ &&
        configuration_ == rhs.configuration_;
}

run& run::operator=(run other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::posix_time::ptime& run::start() const {
    return start_;
}

boost::posix_time::ptime& run::start() {
    return start_;
}

void run::start(const boost::posix_time::ptime& v) {
    start_ = v;
}

void run::start(const boost::posix_time::ptime&& v) {
    start_ = std::move(v);
}

const boost::posix_time::ptime& run::end() const {
    return end_;
}

boost::posix_time::ptime& run::end() {
    return end_;
}

void run::end(const boost::posix_time::ptime& v) {
    end_ = v;
}

void run::end(const boost::posix_time::ptime&& v) {
    end_ = std::move(v);
}

const dogen::relational::tracing::run_id& run::id() const {
    return id_;
}

dogen::relational::tracing::run_id& run::id() {
    return id_;
}

void run::id(const dogen::relational::tracing::run_id& v) {
    id_ = v;
}

void run::id(const dogen::relational::tracing::run_id&& v) {
    id_ = std::move(v);
}

dogen::relational::tracing::activity run::activity() const {
    return activity_;
}

void run::activity(const dogen::relational::tracing::activity v) {
    activity_ = v;
}

const std::string& run::version() const {
    return version_;
}

std::string& run::version() {
    return version_;
}

void run::version(const std::string& v) {
    version_ = v;
}

void run::version(const std::string&& v) {
    version_ = std::move(v);
}

const dogen::relational::tracing::json& run::configuration() const {
    return configuration_;
}

dogen::relational::tracing::json& run::configuration() {
    return configuration_;
}

void run::configuration(const dogen::relational::tracing::json& v) {
    configuration_ = v;
}

void run::configuration(const dogen::relational::tracing::json&& v) {
    configuration_ = std::move(v);
}

}
