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
#include "dogen/om/types/cpp_base.hpp"

namespace dogen {
namespace om {

cpp_base::cpp_base()
    : is_virtual_(static_cast<bool>(0)),
      access_(static_cast<dogen::om::cpp_access_specifier_types>(0)) { }

cpp_base::cpp_base(
    const bool is_virtual,
    const dogen::om::cpp_access_specifier_types& access,
    const dogen::om::cpp_typeref& type)
    : is_virtual_(is_virtual),
      access_(access),
      type_(type) { }

void cpp_base::swap(cpp_base& other) noexcept {
    using std::swap;
    swap(is_virtual_, other.is_virtual_);
    swap(access_, other.access_);
    swap(type_, other.type_);
}

bool cpp_base::operator==(const cpp_base& rhs) const {
    return is_virtual_ == rhs.is_virtual_ &&
        access_ == rhs.access_ &&
        type_ == rhs.type_;
}

cpp_base& cpp_base::operator=(cpp_base other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool cpp_base::is_virtual() const {
    return is_virtual_;
}

void cpp_base::is_virtual(const bool v) {
    is_virtual_ = v;
}

dogen::om::cpp_access_specifier_types cpp_base::access() const {
    return access_;
}

void cpp_base::access(const dogen::om::cpp_access_specifier_types& v) {
    access_ = v;
}

const dogen::om::cpp_typeref& cpp_base::type() const {
    return type_;
}

dogen::om::cpp_typeref& cpp_base::type() {
    return type_;
}

void cpp_base::type(const dogen::om::cpp_typeref& v) {
    type_ = v;
}

void cpp_base::type(const dogen::om::cpp_typeref&& v) {
    type_ = std::move(v);
}

} }