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
#include "dogen/sml/types/nested_qualified_name.hpp"

namespace dogen {
namespace sml {

nested_qualified_name::nested_qualified_name()
    : is_pointer_(static_cast<bool>(0)) { }

nested_qualified_name::nested_qualified_name(
    const dogen::sml::qualified_name& type,
    const std::list<dogen::sml::nested_qualified_name>& children,
    const bool is_pointer)
    : type_(type),
      children_(children),
      is_pointer_(is_pointer) { }

void nested_qualified_name::swap(nested_qualified_name& other) noexcept {
    using std::swap;
    swap(type_, other.type_);
    swap(children_, other.children_);
    swap(is_pointer_, other.is_pointer_);
}

bool nested_qualified_name::operator==(const nested_qualified_name& rhs) const {
    return type_ == rhs.type_ &&
        children_ == rhs.children_ &&
        is_pointer_ == rhs.is_pointer_;
}

nested_qualified_name& nested_qualified_name::operator=(nested_qualified_name other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} }