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
#include "dogen/cpp/types/exception_info.hpp"

namespace dogen {
namespace cpp {

exception_info::exception_info(
    const std::string& documentation,
    const std::string& name,
    const std::list<std::string>& namespaces)
    : documentation_(documentation),
      name_(name),
      namespaces_(namespaces) { }

void exception_info::swap(exception_info& other) noexcept {
    using std::swap;
    swap(documentation_, other.documentation_);
    swap(name_, other.name_);
    swap(namespaces_, other.namespaces_);
}

bool exception_info::operator==(const exception_info& rhs) const {
    return documentation_ == rhs.documentation_ &&
        name_ == rhs.name_ &&
        namespaces_ == rhs.namespaces_;
}

exception_info& exception_info::operator=(exception_info other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& exception_info::documentation() const {
    return documentation_;
}

std::string& exception_info::documentation() {
    return documentation_;
}

void exception_info::documentation(const std::string& v) {
    documentation_ = v;
}

void exception_info::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

const std::string& exception_info::name() const {
    return name_;
}

std::string& exception_info::name() {
    return name_;
}

void exception_info::name(const std::string& v) {
    name_ = v;
}

void exception_info::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::list<std::string>& exception_info::namespaces() const {
    return namespaces_;
}

std::list<std::string>& exception_info::namespaces() {
    return namespaces_;
}

void exception_info::namespaces(const std::list<std::string>& v) {
    namespaces_ = v;
}

void exception_info::namespaces(const std::list<std::string>&& v) {
    namespaces_ = std::move(v);
}

} }