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
#include "dogen.relational/types/tracing/transform.hpp"

namespace dogen::relational::tracing {

transform::transform()
    : type_(static_cast<dogen::relational::tracing::transform_type>(0)) { }

transform::transform(
    const boost::posix_time::ptime& start,
    const boost::posix_time::ptime& end,
    const dogen::relational::tracing::transform_id& id,
    const dogen::relational::tracing::transform_instance_id& instance_id,
    const dogen::relational::tracing::run_id& run_id,
    const dogen::relational::tracing::transform_type type,
    const dogen::relational::tracing::json& input,
    const dogen::relational::tracing::json& output)
    : start_(start),
      end_(end),
      id_(id),
      instance_id_(instance_id),
      run_id_(run_id),
      type_(type),
      input_(input),
      output_(output) { }

void transform::swap(transform& other) noexcept {
    using std::swap;
    swap(start_, other.start_);
    swap(end_, other.end_);
    swap(id_, other.id_);
    swap(instance_id_, other.instance_id_);
    swap(run_id_, other.run_id_);
    swap(type_, other.type_);
    swap(input_, other.input_);
    swap(output_, other.output_);
}

bool transform::operator==(const transform& rhs) const {
    return start_ == rhs.start_ &&
        end_ == rhs.end_ &&
        id_ == rhs.id_ &&
        instance_id_ == rhs.instance_id_ &&
        run_id_ == rhs.run_id_ &&
        type_ == rhs.type_ &&
        input_ == rhs.input_ &&
        output_ == rhs.output_;
}

transform& transform::operator=(transform other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::posix_time::ptime& transform::start() const {
    return start_;
}

boost::posix_time::ptime& transform::start() {
    return start_;
}

void transform::start(const boost::posix_time::ptime& v) {
    start_ = v;
}

void transform::start(const boost::posix_time::ptime&& v) {
    start_ = std::move(v);
}

const boost::posix_time::ptime& transform::end() const {
    return end_;
}

boost::posix_time::ptime& transform::end() {
    return end_;
}

void transform::end(const boost::posix_time::ptime& v) {
    end_ = v;
}

void transform::end(const boost::posix_time::ptime&& v) {
    end_ = std::move(v);
}

const dogen::relational::tracing::transform_id& transform::id() const {
    return id_;
}

dogen::relational::tracing::transform_id& transform::id() {
    return id_;
}

void transform::id(const dogen::relational::tracing::transform_id& v) {
    id_ = v;
}

void transform::id(const dogen::relational::tracing::transform_id&& v) {
    id_ = std::move(v);
}

const dogen::relational::tracing::transform_instance_id& transform::instance_id() const {
    return instance_id_;
}

dogen::relational::tracing::transform_instance_id& transform::instance_id() {
    return instance_id_;
}

void transform::instance_id(const dogen::relational::tracing::transform_instance_id& v) {
    instance_id_ = v;
}

void transform::instance_id(const dogen::relational::tracing::transform_instance_id&& v) {
    instance_id_ = std::move(v);
}

const dogen::relational::tracing::run_id& transform::run_id() const {
    return run_id_;
}

dogen::relational::tracing::run_id& transform::run_id() {
    return run_id_;
}

void transform::run_id(const dogen::relational::tracing::run_id& v) {
    run_id_ = v;
}

void transform::run_id(const dogen::relational::tracing::run_id&& v) {
    run_id_ = std::move(v);
}

dogen::relational::tracing::transform_type transform::type() const {
    return type_;
}

void transform::type(const dogen::relational::tracing::transform_type v) {
    type_ = v;
}

const dogen::relational::tracing::json& transform::input() const {
    return input_;
}

dogen::relational::tracing::json& transform::input() {
    return input_;
}

void transform::input(const dogen::relational::tracing::json& v) {
    input_ = v;
}

void transform::input(const dogen::relational::tracing::json&& v) {
    input_ = std::move(v);
}

const dogen::relational::tracing::json& transform::output() const {
    return output_;
}

dogen::relational::tracing::json& transform::output() {
    return output_;
}

void transform::output(const dogen::relational::tracing::json& v) {
    output_ = v;
}

void transform::output(const dogen::relational::tracing::json&& v) {
    output_ = std::move(v);
}

}
