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
#include "dogen.logical/types/meta_model/name.hpp"

namespace dogen::logical::meta_model {

name::name(
    const dogen::logical::meta_model::fully_qualified_representation& qualified,
    const std::string& simple,
    const dogen::logical::meta_model::location& location)
    : qualified_(qualified),
      simple_(simple),
      location_(location) { }

void name::swap(name& other) noexcept {
    using std::swap;
    swap(qualified_, other.qualified_);
    swap(simple_, other.simple_);
    swap(location_, other.location_);
}

bool name::operator==(const name& rhs) const {
    return qualified_ == rhs.qualified_ &&
        simple_ == rhs.simple_ &&
        location_ == rhs.location_;
}

name& name::operator=(name other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::logical::meta_model::fully_qualified_representation& name::qualified() const {
    return qualified_;
}

dogen::logical::meta_model::fully_qualified_representation& name::qualified() {
    return qualified_;
}

void name::qualified(const dogen::logical::meta_model::fully_qualified_representation& v) {
    qualified_ = v;
}

void name::qualified(const dogen::logical::meta_model::fully_qualified_representation&& v) {
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

const dogen::logical::meta_model::location& name::location() const {
    return location_;
}

dogen::logical::meta_model::location& name::location() {
    return location_;
}

void name::location(const dogen::logical::meta_model::location& v) {
    location_ = v;
}

void name::location(const dogen::logical::meta_model::location&& v) {
    location_ = std::move(v);
}

}
