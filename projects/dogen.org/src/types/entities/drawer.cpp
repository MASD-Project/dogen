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
#include "dogen.org/types/entities/drawer.hpp"

namespace dogen::org::entities {

drawer::drawer()
    : type_(static_cast<dogen::org::entities::drawer_type>(0)) { }

drawer::drawer(
    const dogen::org::entities::drawer_type type,
    const std::list<dogen::org::entities::drawer_content>& contents)
    : type_(type),
      contents_(contents) { }

void drawer::swap(drawer& other) noexcept {
    using std::swap;
    swap(type_, other.type_);
    swap(contents_, other.contents_);
}

bool drawer::operator==(const drawer& rhs) const {
    return type_ == rhs.type_ &&
        contents_ == rhs.contents_;
}

drawer& drawer::operator=(drawer other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

dogen::org::entities::drawer_type drawer::type() const {
    return type_;
}

void drawer::type(const dogen::org::entities::drawer_type v) {
    type_ = v;
}

const std::list<dogen::org::entities::drawer_content>& drawer::contents() const {
    return contents_;
}

std::list<dogen::org::entities::drawer_content>& drawer::contents() {
    return contents_;
}

void drawer::contents(const std::list<dogen::org::entities::drawer_content>& v) {
    contents_ = v;
}

void drawer::contents(const std::list<dogen::org::entities::drawer_content>&& v) {
    contents_ = std::move(v);
}

}
