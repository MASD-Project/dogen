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
#include "dogen/sml/types/nested_qname.hpp"

namespace dogen {
namespace sml {

nested_qname::nested_qname()
    : is_pointer_(static_cast<bool>(0)) { }

nested_qname::nested_qname(
    const dogen::sml::qname& type,
    const std::list<dogen::sml::nested_qname>& children,
    const bool is_pointer)
    : type_(type),
      children_(children),
      is_pointer_(is_pointer) { }

void nested_qname::swap(nested_qname& other) noexcept {
    using std::swap;
    swap(type_, other.type_);
    swap(children_, other.children_);
    swap(is_pointer_, other.is_pointer_);
}

bool nested_qname::operator==(const nested_qname& rhs) const {
    return type_ == rhs.type_ &&
        children_ == rhs.children_ &&
        is_pointer_ == rhs.is_pointer_;
}

nested_qname& nested_qname::operator=(nested_qname other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::sml::qname& nested_qname::type() const {
    return type_;
}

dogen::sml::qname& nested_qname::type() {
    return type_;
}

void nested_qname::type(const dogen::sml::qname& v) {
    type_ = v;
}

void nested_qname::type(const dogen::sml::qname&& v) {
    type_ = std::move(v);
}

const std::list<dogen::sml::nested_qname>& nested_qname::children() const {
    return children_;
}

std::list<dogen::sml::nested_qname>& nested_qname::children() {
    return children_;
}

void nested_qname::children(const std::list<dogen::sml::nested_qname>& v) {
    children_ = v;
}

void nested_qname::children(const std::list<dogen::sml::nested_qname>&& v) {
    children_ = std::move(v);
}

bool nested_qname::is_pointer() const {
    return is_pointer_;
}

void nested_qname::is_pointer(const bool v) {
    is_pointer_ = v;
}

} }
