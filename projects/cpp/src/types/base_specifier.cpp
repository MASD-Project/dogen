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
#include "dogen/cpp/types/base_specifier.hpp"

namespace dogen {
namespace cpp {

base_specifier::base_specifier()
    : is_virtual_(static_cast<bool>(0)),
      access_(static_cast<dogen::cpp::access_specifier_types>(0)) { }

base_specifier::base_specifier(
    const bool is_virtual,
    const dogen::cpp::access_specifier_types& access,
    const dogen::cpp::qualified_id& name)
    : is_virtual_(is_virtual),
      access_(access),
      name_(name) { }

void base_specifier::swap(base_specifier& other) noexcept {
    using std::swap;
    swap(is_virtual_, other.is_virtual_);
    swap(access_, other.access_);
    swap(name_, other.name_);
}

bool base_specifier::operator==(const base_specifier& rhs) const {
    return is_virtual_ == rhs.is_virtual_ &&
        access_ == rhs.access_ &&
        name_ == rhs.name_;
}

base_specifier& base_specifier::operator=(base_specifier other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool base_specifier::is_virtual() const {
    return is_virtual_;
}

void base_specifier::is_virtual(const bool v) {
    is_virtual_ = v;
}

dogen::cpp::access_specifier_types base_specifier::access() const {
    return access_;
}

void base_specifier::access(const dogen::cpp::access_specifier_types& v) {
    access_ = v;
}

const dogen::cpp::qualified_id& base_specifier::name() const {
    return name_;
}

dogen::cpp::qualified_id& base_specifier::name() {
    return name_;
}

void base_specifier::name(const dogen::cpp::qualified_id& v) {
    name_ = v;
}

void base_specifier::name(const dogen::cpp::qualified_id&& v) {
    name_ = std::move(v);
}

} }