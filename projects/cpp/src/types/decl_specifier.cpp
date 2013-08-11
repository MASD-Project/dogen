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
#include "dogen/cpp/types/decl_specifier.hpp"

namespace dogen {
namespace cpp {

decl_specifier::decl_specifier()
    : storage_class_type_(static_cast<dogen::cpp::storage_class_types>(0)),
      function_specifier_(static_cast<dogen::cpp::function_specifier_types>(0)),
      is_friend_(static_cast<bool>(0)),
      is_typedef_(static_cast<bool>(0)) { }

decl_specifier::decl_specifier(
    const dogen::cpp::storage_class_types& storage_class_type,
    const dogen::cpp::type_specifier& type_specifier,
    const dogen::cpp::function_specifier_types& function_specifier,
    const bool is_friend,
    const bool is_typedef)
    : storage_class_type_(storage_class_type),
      type_specifier_(type_specifier),
      function_specifier_(function_specifier),
      is_friend_(is_friend),
      is_typedef_(is_typedef) { }

void decl_specifier::swap(decl_specifier& other) noexcept {
    using std::swap;
    swap(storage_class_type_, other.storage_class_type_);
    swap(type_specifier_, other.type_specifier_);
    swap(function_specifier_, other.function_specifier_);
    swap(is_friend_, other.is_friend_);
    swap(is_typedef_, other.is_typedef_);
}

bool decl_specifier::operator==(const decl_specifier& rhs) const {
    return storage_class_type_ == rhs.storage_class_type_ &&
        type_specifier_ == rhs.type_specifier_ &&
        function_specifier_ == rhs.function_specifier_ &&
        is_friend_ == rhs.is_friend_ &&
        is_typedef_ == rhs.is_typedef_;
}

decl_specifier& decl_specifier::operator=(decl_specifier other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

dogen::cpp::storage_class_types decl_specifier::storage_class_type() const {
    return storage_class_type_;
}

void decl_specifier::storage_class_type(const dogen::cpp::storage_class_types& v) {
    storage_class_type_ = v;
}

const dogen::cpp::type_specifier& decl_specifier::type_specifier() const {
    return type_specifier_;
}

dogen::cpp::type_specifier& decl_specifier::type_specifier() {
    return type_specifier_;
}

void decl_specifier::type_specifier(const dogen::cpp::type_specifier& v) {
    type_specifier_ = v;
}

void decl_specifier::type_specifier(const dogen::cpp::type_specifier&& v) {
    type_specifier_ = std::move(v);
}

dogen::cpp::function_specifier_types decl_specifier::function_specifier() const {
    return function_specifier_;
}

void decl_specifier::function_specifier(const dogen::cpp::function_specifier_types& v) {
    function_specifier_ = v;
}

bool decl_specifier::is_friend() const {
    return is_friend_;
}

void decl_specifier::is_friend(const bool v) {
    is_friend_ = v;
}

bool decl_specifier::is_typedef() const {
    return is_typedef_;
}

void decl_specifier::is_typedef(const bool v) {
    is_typedef_ = v;
}

} }