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
#include "dogen.identification/types/entities/logical_name.hpp"

namespace dogen::identification::entities {

logical_name::logical_name()
    : is_container_(static_cast<bool>(0)) { }

logical_name::logical_name(
    const std::string& simple,
    const dogen::identification::entities::qualified_representations& qualified,
    const dogen::identification::entities::logical_id& id,
    const dogen::identification::entities::logical_location& location,
    const bool is_container)
    : simple_(simple),
      qualified_(qualified),
      id_(id),
      location_(location),
      is_container_(is_container) { }

void logical_name::swap(logical_name& other) noexcept {
    using std::swap;
    swap(simple_, other.simple_);
    swap(qualified_, other.qualified_);
    swap(id_, other.id_);
    swap(location_, other.location_);
    swap(is_container_, other.is_container_);
}

bool logical_name::operator==(const logical_name& rhs) const {
    return simple_ == rhs.simple_ &&
        qualified_ == rhs.qualified_ &&
        id_ == rhs.id_ &&
        location_ == rhs.location_ &&
        is_container_ == rhs.is_container_;
}

logical_name& logical_name::operator=(logical_name other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& logical_name::simple() const {
    return simple_;
}

std::string& logical_name::simple() {
    return simple_;
}

void logical_name::simple(const std::string& v) {
    simple_ = v;
}

void logical_name::simple(const std::string&& v) {
    simple_ = std::move(v);
}

const dogen::identification::entities::qualified_representations& logical_name::qualified() const {
    return qualified_;
}

dogen::identification::entities::qualified_representations& logical_name::qualified() {
    return qualified_;
}

void logical_name::qualified(const dogen::identification::entities::qualified_representations& v) {
    qualified_ = v;
}

void logical_name::qualified(const dogen::identification::entities::qualified_representations&& v) {
    qualified_ = std::move(v);
}

const dogen::identification::entities::logical_id& logical_name::id() const {
    return id_;
}

dogen::identification::entities::logical_id& logical_name::id() {
    return id_;
}

void logical_name::id(const dogen::identification::entities::logical_id& v) {
    id_ = v;
}

void logical_name::id(const dogen::identification::entities::logical_id&& v) {
    id_ = std::move(v);
}

const dogen::identification::entities::logical_location& logical_name::location() const {
    return location_;
}

dogen::identification::entities::logical_location& logical_name::location() {
    return location_;
}

void logical_name::location(const dogen::identification::entities::logical_location& v) {
    location_ = v;
}

void logical_name::location(const dogen::identification::entities::logical_location&& v) {
    location_ = std::move(v);
}

bool logical_name::is_container() const {
    return is_container_;
}

void logical_name::is_container(const bool v) {
    is_container_ = v;
}

}
