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
#include "dogen.assets/types/meta_model/name.hpp"

namespace dogen::assets::meta_model {

name::name()
    : is_simple_name_internal_(static_cast<bool>(0)) { }

name::name(
    const dogen::assets::meta_model::fully_qualified_representation& qualified,
    const std::string& simple,
    const dogen::assets::meta_model::location& location,
    const bool is_simple_name_internal)
    : qualified_(qualified),
      simple_(simple),
      location_(location),
      is_simple_name_internal_(is_simple_name_internal) { }

void name::swap(name& other) noexcept {
    using std::swap;
    swap(qualified_, other.qualified_);
    swap(simple_, other.simple_);
    swap(location_, other.location_);
    swap(is_simple_name_internal_, other.is_simple_name_internal_);
}

bool name::operator==(const name& rhs) const {
    return qualified_ == rhs.qualified_ &&
        simple_ == rhs.simple_ &&
        location_ == rhs.location_ &&
        is_simple_name_internal_ == rhs.is_simple_name_internal_;
}

name& name::operator=(name other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::assets::meta_model::fully_qualified_representation& name::qualified() const {
    return qualified_;
}

dogen::assets::meta_model::fully_qualified_representation& name::qualified() {
    return qualified_;
}

void name::qualified(const dogen::assets::meta_model::fully_qualified_representation& v) {
    qualified_ = v;
}

void name::qualified(const dogen::assets::meta_model::fully_qualified_representation&& v) {
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

const dogen::assets::meta_model::location& name::location() const {
    return location_;
}

dogen::assets::meta_model::location& name::location() {
    return location_;
}

void name::location(const dogen::assets::meta_model::location& v) {
    location_ = v;
}

void name::location(const dogen::assets::meta_model::location&& v) {
    location_ = std::move(v);
}

bool name::is_simple_name_internal() const {
    return is_simple_name_internal_;
}

void name::is_simple_name_internal(const bool v) {
    is_simple_name_internal_ = v;
}

}
