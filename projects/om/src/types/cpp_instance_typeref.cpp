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
#include "dogen/om/types/cpp_instance_typeref.hpp"

namespace dogen {
namespace om {

cpp_instance_typeref::cpp_instance_typeref()
    : is_const_(static_cast<bool>(0)),
      start_at_global_scope_(static_cast<bool>(0)),
      memory_type_(static_cast<dogen::om::cpp_memory_types>(0)) { }

cpp_instance_typeref::cpp_instance_typeref(
    const bool is_const,
    const bool start_at_global_scope,
    const std::list<std::string>& namespaces,
    const std::string& name,
    const std::list<dogen::om::cpp_typeref>& type_arguments,
    const dogen::om::cpp_memory_types& memory_type)
    : is_const_(is_const),
      start_at_global_scope_(start_at_global_scope),
      namespaces_(namespaces),
      name_(name),
      type_arguments_(type_arguments),
      memory_type_(memory_type) { }

void cpp_instance_typeref::swap(cpp_instance_typeref& other) noexcept {
    using std::swap;
    swap(is_const_, other.is_const_);
    swap(start_at_global_scope_, other.start_at_global_scope_);
    swap(namespaces_, other.namespaces_);
    swap(name_, other.name_);
    swap(type_arguments_, other.type_arguments_);
    swap(memory_type_, other.memory_type_);
}

bool cpp_instance_typeref::operator==(const cpp_instance_typeref& rhs) const {
    return is_const_ == rhs.is_const_ &&
        start_at_global_scope_ == rhs.start_at_global_scope_ &&
        namespaces_ == rhs.namespaces_ &&
        name_ == rhs.name_ &&
        type_arguments_ == rhs.type_arguments_ &&
        memory_type_ == rhs.memory_type_;
}

cpp_instance_typeref& cpp_instance_typeref::operator=(cpp_instance_typeref other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool cpp_instance_typeref::is_const() const {
    return is_const_;
}

void cpp_instance_typeref::is_const(const bool v) {
    is_const_ = v;
}

bool cpp_instance_typeref::start_at_global_scope() const {
    return start_at_global_scope_;
}

void cpp_instance_typeref::start_at_global_scope(const bool v) {
    start_at_global_scope_ = v;
}

const std::list<std::string>& cpp_instance_typeref::namespaces() const {
    return namespaces_;
}

std::list<std::string>& cpp_instance_typeref::namespaces() {
    return namespaces_;
}

void cpp_instance_typeref::namespaces(const std::list<std::string>& v) {
    namespaces_ = v;
}

void cpp_instance_typeref::namespaces(const std::list<std::string>&& v) {
    namespaces_ = std::move(v);
}

const std::string& cpp_instance_typeref::name() const {
    return name_;
}

std::string& cpp_instance_typeref::name() {
    return name_;
}

void cpp_instance_typeref::name(const std::string& v) {
    name_ = v;
}

void cpp_instance_typeref::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::list<dogen::om::cpp_typeref>& cpp_instance_typeref::type_arguments() const {
    return type_arguments_;
}

std::list<dogen::om::cpp_typeref>& cpp_instance_typeref::type_arguments() {
    return type_arguments_;
}

void cpp_instance_typeref::type_arguments(const std::list<dogen::om::cpp_typeref>& v) {
    type_arguments_ = v;
}

void cpp_instance_typeref::type_arguments(const std::list<dogen::om::cpp_typeref>&& v) {
    type_arguments_ = std::move(v);
}

dogen::om::cpp_memory_types cpp_instance_typeref::memory_type() const {
    return memory_type_;
}

void cpp_instance_typeref::memory_type(const dogen::om::cpp_memory_types& v) {
    memory_type_ = v;
}

} }