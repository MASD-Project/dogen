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
#include "dogen/cpp/types/formattables/parent_info.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

parent_info::parent_info(
    const std::string& name,
    const std::list<std::string>& namespaces,
    const std::list<dogen::cpp::formattables::property_info>& properties)
    : name_(name),
      namespaces_(namespaces),
      properties_(properties) { }

void parent_info::swap(parent_info& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(namespaces_, other.namespaces_);
    swap(properties_, other.properties_);
}

bool parent_info::operator==(const parent_info& rhs) const {
    return name_ == rhs.name_ &&
        namespaces_ == rhs.namespaces_ &&
        properties_ == rhs.properties_;
}

parent_info& parent_info::operator=(parent_info other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& parent_info::name() const {
    return name_;
}

std::string& parent_info::name() {
    return name_;
}

void parent_info::name(const std::string& v) {
    name_ = v;
}

void parent_info::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::list<std::string>& parent_info::namespaces() const {
    return namespaces_;
}

std::list<std::string>& parent_info::namespaces() {
    return namespaces_;
}

void parent_info::namespaces(const std::list<std::string>& v) {
    namespaces_ = v;
}

void parent_info::namespaces(const std::list<std::string>&& v) {
    namespaces_ = std::move(v);
}

const std::list<dogen::cpp::formattables::property_info>& parent_info::properties() const {
    return properties_;
}

std::list<dogen::cpp::formattables::property_info>& parent_info::properties() {
    return properties_;
}

void parent_info::properties(const std::list<dogen::cpp::formattables::property_info>& v) {
    properties_ = v;
}

void parent_info::properties(const std::list<dogen::cpp::formattables::property_info>&& v) {
    properties_ = std::move(v);
}

} } }