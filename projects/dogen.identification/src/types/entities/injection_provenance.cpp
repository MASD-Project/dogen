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
#include "dogen.identification/types/entities/injection_provenance.hpp"

namespace dogen::identification::entities {

injection_provenance::injection_provenance()
    : model_type_(static_cast<dogen::identification::entities::model_type>(0)) { }

injection_provenance::injection_provenance(
    const dogen::identification::entities::model_id& model_id,
    const dogen::identification::entities::model_type model_type,
    const dogen::identification::entities::sha1_hash& model_sha1_hash,
    const dogen::identification::entities::injection_id& injection_id,
    const dogen::identification::entities::injection_location& location)
    : model_id_(model_id),
      model_type_(model_type),
      model_sha1_hash_(model_sha1_hash),
      injection_id_(injection_id),
      location_(location) { }

void injection_provenance::swap(injection_provenance& other) noexcept {
    using std::swap;
    swap(model_id_, other.model_id_);
    swap(model_type_, other.model_type_);
    swap(model_sha1_hash_, other.model_sha1_hash_);
    swap(injection_id_, other.injection_id_);
    swap(location_, other.location_);
}

bool injection_provenance::operator==(const injection_provenance& rhs) const {
    return model_id_ == rhs.model_id_ &&
        model_type_ == rhs.model_type_ &&
        model_sha1_hash_ == rhs.model_sha1_hash_ &&
        injection_id_ == rhs.injection_id_ &&
        location_ == rhs.location_;
}

injection_provenance& injection_provenance::operator=(injection_provenance other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::identification::entities::model_id& injection_provenance::model_id() const {
    return model_id_;
}

dogen::identification::entities::model_id& injection_provenance::model_id() {
    return model_id_;
}

void injection_provenance::model_id(const dogen::identification::entities::model_id& v) {
    model_id_ = v;
}

void injection_provenance::model_id(const dogen::identification::entities::model_id&& v) {
    model_id_ = std::move(v);
}

dogen::identification::entities::model_type injection_provenance::model_type() const {
    return model_type_;
}

void injection_provenance::model_type(const dogen::identification::entities::model_type v) {
    model_type_ = v;
}

const dogen::identification::entities::sha1_hash& injection_provenance::model_sha1_hash() const {
    return model_sha1_hash_;
}

dogen::identification::entities::sha1_hash& injection_provenance::model_sha1_hash() {
    return model_sha1_hash_;
}

void injection_provenance::model_sha1_hash(const dogen::identification::entities::sha1_hash& v) {
    model_sha1_hash_ = v;
}

void injection_provenance::model_sha1_hash(const dogen::identification::entities::sha1_hash&& v) {
    model_sha1_hash_ = std::move(v);
}

const dogen::identification::entities::injection_id& injection_provenance::injection_id() const {
    return injection_id_;
}

dogen::identification::entities::injection_id& injection_provenance::injection_id() {
    return injection_id_;
}

void injection_provenance::injection_id(const dogen::identification::entities::injection_id& v) {
    injection_id_ = v;
}

void injection_provenance::injection_id(const dogen::identification::entities::injection_id&& v) {
    injection_id_ = std::move(v);
}

const dogen::identification::entities::injection_location& injection_provenance::location() const {
    return location_;
}

dogen::identification::entities::injection_location& injection_provenance::location() {
    return location_;
}

void injection_provenance::location(const dogen::identification::entities::injection_location& v) {
    location_ = v;
}

void injection_provenance::location(const dogen::identification::entities::injection_location&& v) {
    location_ = std::move(v);
}

}
