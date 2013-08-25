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
#include "dogen/om/types/cpp_typeref.hpp"

namespace dogen {
namespace om {

cpp_typeref::cpp_typeref()
    : start_at_global_scope_(static_cast<bool>(0)) { }

cpp_typeref::cpp_typeref(
    const std::string& name,
    const bool start_at_global_scope,
    const std::list<dogen::om::cpp_typeref>& type_arguments,
    const std::list<std::string>& namespaces)
    : name_(name),
      start_at_global_scope_(start_at_global_scope),
      type_arguments_(type_arguments),
      namespaces_(namespaces) { }

void cpp_typeref::swap(cpp_typeref& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(start_at_global_scope_, other.start_at_global_scope_);
    swap(type_arguments_, other.type_arguments_);
    swap(namespaces_, other.namespaces_);
}

bool cpp_typeref::operator==(const cpp_typeref& rhs) const {
    return name_ == rhs.name_ &&
        start_at_global_scope_ == rhs.start_at_global_scope_ &&
        type_arguments_ == rhs.type_arguments_ &&
        namespaces_ == rhs.namespaces_;
}

cpp_typeref& cpp_typeref::operator=(cpp_typeref other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& cpp_typeref::name() const {
    return name_;
}

std::string& cpp_typeref::name() {
    return name_;
}

void cpp_typeref::name(const std::string& v) {
    name_ = v;
}

void cpp_typeref::name(const std::string&& v) {
    name_ = std::move(v);
}

bool cpp_typeref::start_at_global_scope() const {
    return start_at_global_scope_;
}

void cpp_typeref::start_at_global_scope(const bool v) {
    start_at_global_scope_ = v;
}

const std::list<dogen::om::cpp_typeref>& cpp_typeref::type_arguments() const {
    return type_arguments_;
}

std::list<dogen::om::cpp_typeref>& cpp_typeref::type_arguments() {
    return type_arguments_;
}

void cpp_typeref::type_arguments(const std::list<dogen::om::cpp_typeref>& v) {
    type_arguments_ = v;
}

void cpp_typeref::type_arguments(const std::list<dogen::om::cpp_typeref>&& v) {
    type_arguments_ = std::move(v);
}

const std::list<std::string>& cpp_typeref::namespaces() const {
    return namespaces_;
}

std::list<std::string>& cpp_typeref::namespaces() {
    return namespaces_;
}

void cpp_typeref::namespaces(const std::list<std::string>& v) {
    namespaces_ = v;
}

void cpp_typeref::namespaces(const std::list<std::string>&& v) {
    namespaces_ = std::move(v);
}

} }