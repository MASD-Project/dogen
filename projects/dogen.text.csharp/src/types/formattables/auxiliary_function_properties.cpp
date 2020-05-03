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
#include "dogen.text.csharp/types/formattables/auxiliary_function_properties.hpp"

namespace dogen::text::csharp::formattables {

auxiliary_function_properties::auxiliary_function_properties()
    : type_(static_cast<dogen::text::csharp::formattables::auxiliary_function_types>(0)) { }

auxiliary_function_properties::auxiliary_function_properties(
    const dogen::text::csharp::formattables::auxiliary_function_types type,
    const std::string& name)
    : type_(type),
      name_(name) { }

void auxiliary_function_properties::swap(auxiliary_function_properties& other) noexcept {
    using std::swap;
    swap(type_, other.type_);
    swap(name_, other.name_);
}

bool auxiliary_function_properties::operator==(const auxiliary_function_properties& rhs) const {
    return type_ == rhs.type_ &&
        name_ == rhs.name_;
}

auxiliary_function_properties& auxiliary_function_properties::operator=(auxiliary_function_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

dogen::text::csharp::formattables::auxiliary_function_types auxiliary_function_properties::type() const {
    return type_;
}

void auxiliary_function_properties::type(const dogen::text::csharp::formattables::auxiliary_function_types v) {
    type_ = v;
}

const std::string& auxiliary_function_properties::name() const {
    return name_;
}

std::string& auxiliary_function_properties::name() {
    return name_;
}

void auxiliary_function_properties::name(const std::string& v) {
    name_ = v;
}

void auxiliary_function_properties::name(const std::string&& v) {
    name_ = std::move(v);
}

}
