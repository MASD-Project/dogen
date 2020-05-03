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
#include "dogen.text.csharp/types/formattables/helper_properties.hpp"

namespace dogen::text::csharp::formattables {

helper_properties::helper_properties()
    : in_inheritance_relationship_(static_cast<bool>(0)) { }

helper_properties::helper_properties(
    const dogen::text::csharp::formattables::helper_descriptor& current,
    const std::list<dogen::text::csharp::formattables::helper_descriptor>& direct_descendants,
    const bool in_inheritance_relationship)
    : current_(current),
      direct_descendants_(direct_descendants),
      in_inheritance_relationship_(in_inheritance_relationship) { }

void helper_properties::swap(helper_properties& other) noexcept {
    using std::swap;
    swap(current_, other.current_);
    swap(direct_descendants_, other.direct_descendants_);
    swap(in_inheritance_relationship_, other.in_inheritance_relationship_);
}

bool helper_properties::operator==(const helper_properties& rhs) const {
    return current_ == rhs.current_ &&
        direct_descendants_ == rhs.direct_descendants_ &&
        in_inheritance_relationship_ == rhs.in_inheritance_relationship_;
}

helper_properties& helper_properties::operator=(helper_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::text::csharp::formattables::helper_descriptor& helper_properties::current() const {
    return current_;
}

dogen::text::csharp::formattables::helper_descriptor& helper_properties::current() {
    return current_;
}

void helper_properties::current(const dogen::text::csharp::formattables::helper_descriptor& v) {
    current_ = v;
}

void helper_properties::current(const dogen::text::csharp::formattables::helper_descriptor&& v) {
    current_ = std::move(v);
}

const std::list<dogen::text::csharp::formattables::helper_descriptor>& helper_properties::direct_descendants() const {
    return direct_descendants_;
}

std::list<dogen::text::csharp::formattables::helper_descriptor>& helper_properties::direct_descendants() {
    return direct_descendants_;
}

void helper_properties::direct_descendants(const std::list<dogen::text::csharp::formattables::helper_descriptor>& v) {
    direct_descendants_ = v;
}

void helper_properties::direct_descendants(const std::list<dogen::text::csharp::formattables::helper_descriptor>&& v) {
    direct_descendants_ = std::move(v);
}

bool helper_properties::in_inheritance_relationship() const {
    return in_inheritance_relationship_;
}

void helper_properties::in_inheritance_relationship(const bool v) {
    in_inheritance_relationship_ = v;
}

}
