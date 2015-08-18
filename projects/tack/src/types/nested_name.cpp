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
#include "dogen/tack/types/nested_name.hpp"

namespace dogen {
namespace tack {

nested_name::nested_name()
    : is_pointer_(static_cast<bool>(0)) { }

nested_name::nested_name(
    const dogen::tack::name& type,
    const std::list<dogen::tack::nested_name>& children,
    const bool is_pointer,
    const std::string& unparsed_name)
    : type_(type),
      children_(children),
      is_pointer_(is_pointer),
      unparsed_name_(unparsed_name) { }

void nested_name::swap(nested_name& other) noexcept {
    using std::swap;
    swap(type_, other.type_);
    swap(children_, other.children_);
    swap(is_pointer_, other.is_pointer_);
    swap(unparsed_name_, other.unparsed_name_);
}

bool nested_name::operator==(const nested_name& rhs) const {
    return type_ == rhs.type_ &&
        children_ == rhs.children_ &&
        is_pointer_ == rhs.is_pointer_ &&
        unparsed_name_ == rhs.unparsed_name_;
}

nested_name& nested_name::operator=(nested_name other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::tack::name& nested_name::type() const {
    return type_;
}

dogen::tack::name& nested_name::type() {
    return type_;
}

void nested_name::type(const dogen::tack::name& v) {
    type_ = v;
}

void nested_name::type(const dogen::tack::name&& v) {
    type_ = std::move(v);
}

const std::list<dogen::tack::nested_name>& nested_name::children() const {
    return children_;
}

std::list<dogen::tack::nested_name>& nested_name::children() {
    return children_;
}

void nested_name::children(const std::list<dogen::tack::nested_name>& v) {
    children_ = v;
}

void nested_name::children(const std::list<dogen::tack::nested_name>&& v) {
    children_ = std::move(v);
}

bool nested_name::is_pointer() const {
    return is_pointer_;
}

void nested_name::is_pointer(const bool v) {
    is_pointer_ = v;
}

const std::string& nested_name::unparsed_name() const {
    return unparsed_name_;
}

std::string& nested_name::unparsed_name() {
    return unparsed_name_;
}

void nested_name::unparsed_name(const std::string& v) {
    unparsed_name_ = v;
}

void nested_name::unparsed_name(const std::string&& v) {
    unparsed_name_ = std::move(v);
}

} }
