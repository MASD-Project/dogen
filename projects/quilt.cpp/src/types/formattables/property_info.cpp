/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#include "dogen/quilt.cpp/types/formattables/property_info.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

property_info::property_info()
    : is_immutable_(static_cast<bool>(0)),
      is_fluent_(static_cast<bool>(0)) { }

property_info::property_info(
    const std::string& name,
    const std::string& qualified_name,
    const std::string& documentation,
    const dogen::quilt::cpp::formattables::nested_type_info& type,
    const bool is_immutable,
    const bool is_fluent,
    const std::string& id)
    : name_(name),
      qualified_name_(qualified_name),
      documentation_(documentation),
      type_(type),
      is_immutable_(is_immutable),
      is_fluent_(is_fluent),
      id_(id) { }

void property_info::swap(property_info& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(qualified_name_, other.qualified_name_);
    swap(documentation_, other.documentation_);
    swap(type_, other.type_);
    swap(is_immutable_, other.is_immutable_);
    swap(is_fluent_, other.is_fluent_);
    swap(id_, other.id_);
}

bool property_info::operator==(const property_info& rhs) const {
    return name_ == rhs.name_ &&
        qualified_name_ == rhs.qualified_name_ &&
        documentation_ == rhs.documentation_ &&
        type_ == rhs.type_ &&
        is_immutable_ == rhs.is_immutable_ &&
        is_fluent_ == rhs.is_fluent_ &&
        id_ == rhs.id_;
}

property_info& property_info::operator=(property_info other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& property_info::name() const {
    return name_;
}

std::string& property_info::name() {
    return name_;
}

void property_info::name(const std::string& v) {
    name_ = v;
}

void property_info::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::string& property_info::qualified_name() const {
    return qualified_name_;
}

std::string& property_info::qualified_name() {
    return qualified_name_;
}

void property_info::qualified_name(const std::string& v) {
    qualified_name_ = v;
}

void property_info::qualified_name(const std::string&& v) {
    qualified_name_ = std::move(v);
}

const std::string& property_info::documentation() const {
    return documentation_;
}

std::string& property_info::documentation() {
    return documentation_;
}

void property_info::documentation(const std::string& v) {
    documentation_ = v;
}

void property_info::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

const dogen::quilt::cpp::formattables::nested_type_info& property_info::type() const {
    return type_;
}

dogen::quilt::cpp::formattables::nested_type_info& property_info::type() {
    return type_;
}

void property_info::type(const dogen::quilt::cpp::formattables::nested_type_info& v) {
    type_ = v;
}

void property_info::type(const dogen::quilt::cpp::formattables::nested_type_info&& v) {
    type_ = std::move(v);
}

bool property_info::is_immutable() const {
    return is_immutable_;
}

void property_info::is_immutable(const bool v) {
    is_immutable_ = v;
}

bool property_info::is_fluent() const {
    return is_fluent_;
}

void property_info::is_fluent(const bool v) {
    is_fluent_ = v;
}

const std::string& property_info::id() const {
    return id_;
}

std::string& property_info::id() {
    return id_;
}

void property_info::id(const std::string& v) {
    id_ = v;
}

void property_info::id(const std::string&& v) {
    id_ = std::move(v);
}

} } } }
