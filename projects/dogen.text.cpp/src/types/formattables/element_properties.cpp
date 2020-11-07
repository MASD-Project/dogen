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
#include "dogen.text.cpp/types/formattables/element_properties.hpp"

namespace dogen::text::cpp::formattables {

element_properties::element_properties(const std::list<dogen::logical::entities::helper_properties>& helper_properties)
    : helper_properties_(helper_properties) { }

void element_properties::swap(element_properties& other) noexcept {
    using std::swap;
    swap(helper_properties_, other.helper_properties_);
}

bool element_properties::operator==(const element_properties& rhs) const {
    return helper_properties_ == rhs.helper_properties_;
}

element_properties& element_properties::operator=(element_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::logical::entities::helper_properties>& element_properties::helper_properties() const {
    return helper_properties_;
}

std::list<dogen::logical::entities::helper_properties>& element_properties::helper_properties() {
    return helper_properties_;
}

void element_properties::helper_properties(const std::list<dogen::logical::entities::helper_properties>& v) {
    helper_properties_ = v;
}

void element_properties::helper_properties(const std::list<dogen::logical::entities::helper_properties>&& v) {
    helper_properties_ = std::move(v);
}

}
