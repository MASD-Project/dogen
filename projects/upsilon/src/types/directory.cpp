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
#include "dogen/upsilon/types/directory.hpp"

namespace dogen {
namespace upsilon {

directory::directory(
    const std::string& public_location,
    const std::string& private_location)
    : public_location_(public_location),
      private_location_(private_location) { }

void directory::swap(directory& other) noexcept {
    using std::swap;
    swap(public_location_, other.public_location_);
    swap(private_location_, other.private_location_);
}

bool directory::operator==(const directory& rhs) const {
    return public_location_ == rhs.public_location_ &&
        private_location_ == rhs.private_location_;
}

directory& directory::operator=(directory other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& directory::public_location() const {
    return public_location_;
}

std::string& directory::public_location() {
    return public_location_;
}

void directory::public_location(const std::string& v) {
    public_location_ = v;
}

void directory::public_location(const std::string&& v) {
    public_location_ = std::move(v);
}

const std::string& directory::private_location() const {
    return private_location_;
}

std::string& directory::private_location() {
    return private_location_;
}

void directory::private_location(const std::string& v) {
    private_location_ = v;
}

void directory::private_location(const std::string&& v) {
    private_location_ = std::move(v);
}

} }
