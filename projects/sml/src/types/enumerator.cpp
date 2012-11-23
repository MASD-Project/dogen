/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/sml/types/enumerator.hpp"

namespace dogen {
namespace sml {

enumerator::enumerator(
    const std::string& name,
    const std::string& value,
    const std::string& documentation)
    : name_(name),
      value_(value),
      documentation_(documentation) { }

void enumerator::swap(enumerator& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(value_, other.value_);
    swap(documentation_, other.documentation_);
}

bool enumerator::operator==(const enumerator& rhs) const {
    return name_ == rhs.name_ &&
        value_ == rhs.value_ &&
        documentation_ == rhs.documentation_;
}

enumerator& enumerator::operator=(enumerator other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} }