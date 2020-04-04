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
#include "dogen.physical/types/entities/meta_name.hpp"

namespace dogen::physical::entities {

meta_name::meta_name(
    const std::string& simple,
    const std::string& qualified,
    const dogen::physical::entities::location& location)
    : simple_(simple),
      qualified_(qualified),
      location_(location) { }

void meta_name::swap(meta_name& other) noexcept {
    using std::swap;
    swap(simple_, other.simple_);
    swap(qualified_, other.qualified_);
    swap(location_, other.location_);
}

bool meta_name::operator==(const meta_name& rhs) const {
    return simple_ == rhs.simple_ &&
        qualified_ == rhs.qualified_ &&
        location_ == rhs.location_;
}

meta_name& meta_name::operator=(meta_name other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& meta_name::simple() const {
    return simple_;
}

std::string& meta_name::simple() {
    return simple_;
}

void meta_name::simple(const std::string& v) {
    simple_ = v;
}

void meta_name::simple(const std::string&& v) {
    simple_ = std::move(v);
}

const std::string& meta_name::qualified() const {
    return qualified_;
}

std::string& meta_name::qualified() {
    return qualified_;
}

void meta_name::qualified(const std::string& v) {
    qualified_ = v;
}

void meta_name::qualified(const std::string&& v) {
    qualified_ = std::move(v);
}

const dogen::physical::entities::location& meta_name::location() const {
    return location_;
}

dogen::physical::entities::location& meta_name::location() {
    return location_;
}

void meta_name::location(const dogen::physical::entities::location& v) {
    location_ = v;
}

void meta_name::location(const dogen::physical::entities::location&& v) {
    location_ = std::move(v);
}

}
