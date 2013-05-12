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
#include "dogen/cpp/types/enumeration_info.hpp"

namespace dogen {
namespace cpp {

enumeration_info::enumeration_info(
    const std::string& name,
    const std::list<std::string>& namespaces,
    const std::list<dogen::cpp::enumerator_info>& enumerators,
    const std::string& documentation)
    : name_(name),
      namespaces_(namespaces),
      enumerators_(enumerators),
      documentation_(documentation) { }

void enumeration_info::swap(enumeration_info& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(namespaces_, other.namespaces_);
    swap(enumerators_, other.enumerators_);
    swap(documentation_, other.documentation_);
}

bool enumeration_info::operator==(const enumeration_info& rhs) const {
    return name_ == rhs.name_ &&
        namespaces_ == rhs.namespaces_ &&
        enumerators_ == rhs.enumerators_ &&
        documentation_ == rhs.documentation_;
}

enumeration_info& enumeration_info::operator=(enumeration_info other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& enumeration_info::name() const {
    return name_;
}

std::string& enumeration_info::name() {
    return name_;
}

void enumeration_info::name(const std::string& v) {
    name_ = v;
}

void enumeration_info::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::list<std::string>& enumeration_info::namespaces() const {
    return namespaces_;
}

std::list<std::string>& enumeration_info::namespaces() {
    return namespaces_;
}

void enumeration_info::namespaces(const std::list<std::string>& v) {
    namespaces_ = v;
}

void enumeration_info::namespaces(const std::list<std::string>&& v) {
    namespaces_ = std::move(v);
}

const std::list<dogen::cpp::enumerator_info>& enumeration_info::enumerators() const {
    return enumerators_;
}

std::list<dogen::cpp::enumerator_info>& enumeration_info::enumerators() {
    return enumerators_;
}

void enumeration_info::enumerators(const std::list<dogen::cpp::enumerator_info>& v) {
    enumerators_ = v;
}

void enumeration_info::enumerators(const std::list<dogen::cpp::enumerator_info>&& v) {
    enumerators_ = std::move(v);
}

const std::string& enumeration_info::documentation() const {
    return documentation_;
}

std::string& enumeration_info::documentation() {
    return documentation_;
}

void enumeration_info::documentation(const std::string& v) {
    documentation_ = v;
}

void enumeration_info::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

} }