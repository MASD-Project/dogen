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
#include "dogen/cpp/types/visitor_info.hpp"

namespace dogen {
namespace cpp {

visitor_info::visitor_info(
    const std::string& name,
    const std::list<std::string>& types,
    const std::string& documentation,
    const std::list<std::string>& namespaces)
    : name_(name),
      types_(types),
      documentation_(documentation),
      namespaces_(namespaces) { }

void visitor_info::swap(visitor_info& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(types_, other.types_);
    swap(documentation_, other.documentation_);
    swap(namespaces_, other.namespaces_);
}

bool visitor_info::operator==(const visitor_info& rhs) const {
    return name_ == rhs.name_ &&
        types_ == rhs.types_ &&
        documentation_ == rhs.documentation_ &&
        namespaces_ == rhs.namespaces_;
}

visitor_info& visitor_info::operator=(visitor_info other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& visitor_info::name() const {
    return name_;
}

std::string& visitor_info::name() {
    return name_;
}

void visitor_info::name(const std::string& v) {
    name_ = v;
}

void visitor_info::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::list<std::string>& visitor_info::types() const {
    return types_;
}

std::list<std::string>& visitor_info::types() {
    return types_;
}

void visitor_info::types(const std::list<std::string>& v) {
    types_ = v;
}

void visitor_info::types(const std::list<std::string>&& v) {
    types_ = std::move(v);
}

const std::string& visitor_info::documentation() const {
    return documentation_;
}

std::string& visitor_info::documentation() {
    return documentation_;
}

void visitor_info::documentation(const std::string& v) {
    documentation_ = v;
}

void visitor_info::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

const std::list<std::string>& visitor_info::namespaces() const {
    return namespaces_;
}

std::list<std::string>& visitor_info::namespaces() {
    return namespaces_;
}

void visitor_info::namespaces(const std::list<std::string>& v) {
    namespaces_ = v;
}

void visitor_info::namespaces(const std::list<std::string>&& v) {
    namespaces_ = std::move(v);
}

} }