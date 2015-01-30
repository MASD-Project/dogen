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
#include "dogen/cpp/types/abilities.hpp"

namespace dogen {
namespace cpp {

abilities::abilities()
    : is_comparable_(static_cast<bool>(0)),
      is_visitable_(static_cast<bool>(0)),
      is_immutable_(static_cast<bool>(0)),
      is_original_parent_visitable_(static_cast<bool>(0)),
      is_assignable_(static_cast<bool>(0)),
      is_swappable_(static_cast<bool>(0)) { }

abilities::abilities(
    const bool is_comparable,
    const bool is_visitable,
    const bool is_immutable,
    const bool is_original_parent_visitable,
    const bool is_assignable,
    const bool is_swappable)
    : is_comparable_(is_comparable),
      is_visitable_(is_visitable),
      is_immutable_(is_immutable),
      is_original_parent_visitable_(is_original_parent_visitable),
      is_assignable_(is_assignable),
      is_swappable_(is_swappable) { }

void abilities::swap(abilities& other) noexcept {
    using std::swap;
    swap(is_comparable_, other.is_comparable_);
    swap(is_visitable_, other.is_visitable_);
    swap(is_immutable_, other.is_immutable_);
    swap(is_original_parent_visitable_, other.is_original_parent_visitable_);
    swap(is_assignable_, other.is_assignable_);
    swap(is_swappable_, other.is_swappable_);
}

bool abilities::operator==(const abilities& rhs) const {
    return is_comparable_ == rhs.is_comparable_ &&
        is_visitable_ == rhs.is_visitable_ &&
        is_immutable_ == rhs.is_immutable_ &&
        is_original_parent_visitable_ == rhs.is_original_parent_visitable_ &&
        is_assignable_ == rhs.is_assignable_ &&
        is_swappable_ == rhs.is_swappable_;
}

abilities& abilities::operator=(abilities other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool abilities::is_comparable() const {
    return is_comparable_;
}

void abilities::is_comparable(const bool v) {
    is_comparable_ = v;
}

bool abilities::is_visitable() const {
    return is_visitable_;
}

void abilities::is_visitable(const bool v) {
    is_visitable_ = v;
}

bool abilities::is_immutable() const {
    return is_immutable_;
}

void abilities::is_immutable(const bool v) {
    is_immutable_ = v;
}

bool abilities::is_original_parent_visitable() const {
    return is_original_parent_visitable_;
}

void abilities::is_original_parent_visitable(const bool v) {
    is_original_parent_visitable_ = v;
}

bool abilities::is_assignable() const {
    return is_assignable_;
}

void abilities::is_assignable(const bool v) {
    is_assignable_ = v;
}

bool abilities::is_swappable() const {
    return is_swappable_;
}

void abilities::is_swappable(const bool v) {
    is_swappable_ = v;
}

} }