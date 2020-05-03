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
#include "dogen.text.csharp/types/formattables/attribute_properties.hpp"

namespace dogen::text::csharp::formattables {

attribute_properties::attribute_properties(const std::unordered_map<std::string, dogen::text::csharp::formattables::auxiliary_function_properties>& auxiliary_function_properties)
    : auxiliary_function_properties_(auxiliary_function_properties) { }

void attribute_properties::swap(attribute_properties& other) noexcept {
    using std::swap;
    swap(auxiliary_function_properties_, other.auxiliary_function_properties_);
}

bool attribute_properties::operator==(const attribute_properties& rhs) const {
    return auxiliary_function_properties_ == rhs.auxiliary_function_properties_;
}

attribute_properties& attribute_properties::operator=(attribute_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, dogen::text::csharp::formattables::auxiliary_function_properties>& attribute_properties::auxiliary_function_properties() const {
    return auxiliary_function_properties_;
}

std::unordered_map<std::string, dogen::text::csharp::formattables::auxiliary_function_properties>& attribute_properties::auxiliary_function_properties() {
    return auxiliary_function_properties_;
}

void attribute_properties::auxiliary_function_properties(const std::unordered_map<std::string, dogen::text::csharp::formattables::auxiliary_function_properties>& v) {
    auxiliary_function_properties_ = v;
}

void attribute_properties::auxiliary_function_properties(const std::unordered_map<std::string, dogen::text::csharp::formattables::auxiliary_function_properties>&& v) {
    auxiliary_function_properties_ = std::move(v);
}

}
