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
#include "dogen.identification/types/entities/codec_provenance.hpp"

namespace dogen::identification::entities {

codec_provenance::codec_provenance()
    : model_type_(static_cast<dogen::identification::entities::model_type>(0)) { }

codec_provenance::codec_provenance(
    const dogen::identification::entities::model_id& model_id,
    const dogen::identification::entities::model_type model_type,
    const dogen::identification::entities::sha1_hash& model_sha1_hash,
    const dogen::identification::entities::codec_id& codec_id,
    const dogen::identification::entities::codec_location& location)
    : model_id_(model_id),
      model_type_(model_type),
      model_sha1_hash_(model_sha1_hash),
      codec_id_(codec_id),
      location_(location) { }

void codec_provenance::swap(codec_provenance& other) noexcept {
    using std::swap;
    swap(model_id_, other.model_id_);
    swap(model_type_, other.model_type_);
    swap(model_sha1_hash_, other.model_sha1_hash_);
    swap(codec_id_, other.codec_id_);
    swap(location_, other.location_);
}

bool codec_provenance::operator==(const codec_provenance& rhs) const {
    return model_id_ == rhs.model_id_ &&
        model_type_ == rhs.model_type_ &&
        model_sha1_hash_ == rhs.model_sha1_hash_ &&
        codec_id_ == rhs.codec_id_ &&
        location_ == rhs.location_;
}

codec_provenance& codec_provenance::operator=(codec_provenance other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::identification::entities::model_id& codec_provenance::model_id() const {
    return model_id_;
}

dogen::identification::entities::model_id& codec_provenance::model_id() {
    return model_id_;
}

void codec_provenance::model_id(const dogen::identification::entities::model_id& v) {
    model_id_ = v;
}

void codec_provenance::model_id(const dogen::identification::entities::model_id&& v) {
    model_id_ = std::move(v);
}

dogen::identification::entities::model_type codec_provenance::model_type() const {
    return model_type_;
}

void codec_provenance::model_type(const dogen::identification::entities::model_type v) {
    model_type_ = v;
}

const dogen::identification::entities::sha1_hash& codec_provenance::model_sha1_hash() const {
    return model_sha1_hash_;
}

dogen::identification::entities::sha1_hash& codec_provenance::model_sha1_hash() {
    return model_sha1_hash_;
}

void codec_provenance::model_sha1_hash(const dogen::identification::entities::sha1_hash& v) {
    model_sha1_hash_ = v;
}

void codec_provenance::model_sha1_hash(const dogen::identification::entities::sha1_hash&& v) {
    model_sha1_hash_ = std::move(v);
}

const dogen::identification::entities::codec_id& codec_provenance::codec_id() const {
    return codec_id_;
}

dogen::identification::entities::codec_id& codec_provenance::codec_id() {
    return codec_id_;
}

void codec_provenance::codec_id(const dogen::identification::entities::codec_id& v) {
    codec_id_ = v;
}

void codec_provenance::codec_id(const dogen::identification::entities::codec_id&& v) {
    codec_id_ = std::move(v);
}

const dogen::identification::entities::codec_location& codec_provenance::location() const {
    return location_;
}

dogen::identification::entities::codec_location& codec_provenance::location() {
    return location_;
}

void codec_provenance::location(const dogen::identification::entities::codec_location& v) {
    location_ = v;
}

void codec_provenance::location(const dogen::identification::entities::codec_location&& v) {
    location_ = std::move(v);
}

}
