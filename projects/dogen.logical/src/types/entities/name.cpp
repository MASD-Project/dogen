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
#include "dogen.logical/types/entities/name.hpp"

namespace dogen::logical::entities {

name::name()
    : is_container_(static_cast<bool>(0)) { }

name::name(
    const dogen::logical::entities::fully_qualified_representation& qualified,
    const std::string& simple,
    const dogen::logical::entities::location& location,
    const bool is_container)
    : qualified_(qualified),
      simple_(simple),
      location_(location),
      is_container_(is_container) { }

void name::swap(name& other) noexcept {
    using std::swap;
    swap(qualified_, other.qualified_);
    swap(simple_, other.simple_);
    swap(location_, other.location_);
    swap(is_container_, other.is_container_);
}

bool name::operator==(const name& rhs) const {
    return qualified_ == rhs.qualified_ &&
        simple_ == rhs.simple_ &&
        location_ == rhs.location_ &&
        is_container_ == rhs.is_container_;
}

name& name::operator=(name other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::logical::entities::fully_qualified_representation& name::qualified() const {
    return qualified_;
}

dogen::logical::entities::fully_qualified_representation& name::qualified() {
    return qualified_;
}

void name::qualified(const dogen::logical::entities::fully_qualified_representation& v) {
    qualified_ = v;
}

void name::qualified(const dogen::logical::entities::fully_qualified_representation&& v) {
    qualified_ = std::move(v);
}

const std::string& name::simple() const {
    return simple_;
}

std::string& name::simple() {
    return simple_;
}

void name::simple(const std::string& v) {
    simple_ = v;
}

void name::simple(const std::string&& v) {
    simple_ = std::move(v);
}

const dogen::logical::entities::location& name::location() const {
    return location_;
}

dogen::logical::entities::location& name::location() {
    return location_;
}

void name::location(const dogen::logical::entities::location& v) {
    location_ = v;
}

void name::location(const dogen::logical::entities::location&& v) {
    location_ = std::move(v);
}

bool name::is_container() const {
    return is_container_;
}

void name::is_container(const bool v) {
    is_container_ = v;
}

}
