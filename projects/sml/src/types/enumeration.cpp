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
#include "dogen/sml/types/enumeration.hpp"

namespace dogen {
namespace sml {

enumeration::enumeration()
    : generation_type_(static_cast<dogen::sml::generation_types>(0)) { }

enumeration::enumeration(
    const dogen::sml::qualified_name& name,
    const dogen::sml::generation_types& generation_type,
    const std::string& documentation,
    const std::vector<dogen::sml::enumerator>& enumerators)
    : name_(name),
      generation_type_(generation_type),
      documentation_(documentation),
      enumerators_(enumerators) { }

void enumeration::swap(enumeration& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(generation_type_, other.generation_type_);
    swap(documentation_, other.documentation_);
    swap(enumerators_, other.enumerators_);
}

bool enumeration::operator==(const enumeration& rhs) const {
    return name_ == rhs.name_ &&
        generation_type_ == rhs.generation_type_ &&
        documentation_ == rhs.documentation_ &&
        enumerators_ == rhs.enumerators_;
}

enumeration& enumeration::operator=(enumeration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} }