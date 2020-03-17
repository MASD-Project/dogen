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
#include "dogen.physical/types/entities/kernel.hpp"

namespace dogen::physical::entities {

kernel::kernel(
    const dogen::physical::entities::location& location,
    const std::string& description,
    const std::list<dogen::physical::entities::backend>& backends,
    const dogen::physical::entities::location_repository& locations)
    : location_(location),
      description_(description),
      backends_(backends),
      locations_(locations) { }

void kernel::swap(kernel& other) noexcept {
    using std::swap;
    swap(location_, other.location_);
    swap(description_, other.description_);
    swap(backends_, other.backends_);
    swap(locations_, other.locations_);
}

bool kernel::operator==(const kernel& rhs) const {
    return location_ == rhs.location_ &&
        description_ == rhs.description_ &&
        backends_ == rhs.backends_ &&
        locations_ == rhs.locations_;
}

kernel& kernel::operator=(kernel other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::physical::entities::location& kernel::location() const {
    return location_;
}

dogen::physical::entities::location& kernel::location() {
    return location_;
}

void kernel::location(const dogen::physical::entities::location& v) {
    location_ = v;
}

void kernel::location(const dogen::physical::entities::location&& v) {
    location_ = std::move(v);
}

const std::string& kernel::description() const {
    return description_;
}

std::string& kernel::description() {
    return description_;
}

void kernel::description(const std::string& v) {
    description_ = v;
}

void kernel::description(const std::string&& v) {
    description_ = std::move(v);
}

const std::list<dogen::physical::entities::backend>& kernel::backends() const {
    return backends_;
}

std::list<dogen::physical::entities::backend>& kernel::backends() {
    return backends_;
}

void kernel::backends(const std::list<dogen::physical::entities::backend>& v) {
    backends_ = v;
}

void kernel::backends(const std::list<dogen::physical::entities::backend>&& v) {
    backends_ = std::move(v);
}

const dogen::physical::entities::location_repository& kernel::locations() const {
    return locations_;
}

dogen::physical::entities::location_repository& kernel::locations() {
    return locations_;
}

void kernel::locations(const dogen::physical::entities::location_repository& v) {
    locations_ = v;
}

void kernel::locations(const dogen::physical::entities::location_repository&& v) {
    locations_ = std::move(v);
}

}
