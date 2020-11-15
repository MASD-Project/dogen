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
#include "dogen.text.csharp/types/formattables/aspect_properties.hpp"

namespace dogen::text::csharp::formattables {

aspect_properties::aspect_properties()
    : requires_static_reference_equals_(static_cast<bool>(0)) { }

aspect_properties::aspect_properties(const bool requires_static_reference_equals)
    : requires_static_reference_equals_(requires_static_reference_equals) { }

void aspect_properties::swap(aspect_properties& other) noexcept {
    using std::swap;
    swap(requires_static_reference_equals_, other.requires_static_reference_equals_);
}

bool aspect_properties::operator==(const aspect_properties& rhs) const {
    return requires_static_reference_equals_ == rhs.requires_static_reference_equals_;
}

aspect_properties& aspect_properties::operator=(aspect_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool aspect_properties::requires_static_reference_equals() const {
    return requires_static_reference_equals_;
}

void aspect_properties::requires_static_reference_equals(const bool v) {
    requires_static_reference_equals_ = v;
}

}
