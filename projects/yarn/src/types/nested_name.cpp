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
#include "dogen/yarn/types/nested_name.hpp"

namespace dogen {
namespace yarn {

nested_name::nested_name()
    : is_pointer_(static_cast<bool>(0)) { }

nested_name::nested_name(
    const dogen::yarn::name& parent,
    const std::list<dogen::yarn::nested_name>& children,
    const bool is_pointer)
    : parent_(parent),
      children_(children),
      is_pointer_(is_pointer) { }

void nested_name::swap(nested_name& other) noexcept {
    using std::swap;
    swap(parent_, other.parent_);
    swap(children_, other.children_);
    swap(is_pointer_, other.is_pointer_);
}

bool nested_name::operator==(const nested_name& rhs) const {
    return parent_ == rhs.parent_ &&
        children_ == rhs.children_ &&
        is_pointer_ == rhs.is_pointer_;
}

nested_name& nested_name::operator=(nested_name other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::yarn::name& nested_name::parent() const {
    return parent_;
}

dogen::yarn::name& nested_name::parent() {
    return parent_;
}

void nested_name::parent(const dogen::yarn::name& v) {
    parent_ = v;
}

void nested_name::parent(const dogen::yarn::name&& v) {
    parent_ = std::move(v);
}

const std::list<dogen::yarn::nested_name>& nested_name::children() const {
    return children_;
}

std::list<dogen::yarn::nested_name>& nested_name::children() {
    return children_;
}

void nested_name::children(const std::list<dogen::yarn::nested_name>& v) {
    children_ = v;
}

void nested_name::children(const std::list<dogen::yarn::nested_name>&& v) {
    children_ = std::move(v);
}

bool nested_name::is_pointer() const {
    return is_pointer_;
}

void nested_name::is_pointer(const bool v) {
    is_pointer_ = v;
}

} }
