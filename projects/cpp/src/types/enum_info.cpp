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
#include "dogen/cpp/types/enum_info.hpp"

namespace dogen {
namespace cpp {

enum_info::enum_info(
    const std::string& name,
    const std::list<std::string>& namespaces,
    const std::list<dogen::cpp::enumerator_info>& enumerators,
    const std::string& documentation)
    : name_(name),
      namespaces_(namespaces),
      enumerators_(enumerators),
      documentation_(documentation) { }

void enum_info::swap(enum_info& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(namespaces_, other.namespaces_);
    swap(enumerators_, other.enumerators_);
    swap(documentation_, other.documentation_);
}

bool enum_info::operator==(const enum_info& rhs) const {
    return name_ == rhs.name_ &&
        namespaces_ == rhs.namespaces_ &&
        enumerators_ == rhs.enumerators_ &&
        documentation_ == rhs.documentation_;
}

enum_info& enum_info::operator=(enum_info other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& enum_info::name() const {
    return name_;
}

std::string& enum_info::name() {
    return name_;
}

void enum_info::name(const std::string& v) {
    name_ = v;
}

void enum_info::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::list<std::string>& enum_info::namespaces() const {
    return namespaces_;
}

std::list<std::string>& enum_info::namespaces() {
    return namespaces_;
}

void enum_info::namespaces(const std::list<std::string>& v) {
    namespaces_ = v;
}

void enum_info::namespaces(const std::list<std::string>&& v) {
    namespaces_ = std::move(v);
}

const std::list<dogen::cpp::enumerator_info>& enum_info::enumerators() const {
    return enumerators_;
}

std::list<dogen::cpp::enumerator_info>& enum_info::enumerators() {
    return enumerators_;
}

void enum_info::enumerators(const std::list<dogen::cpp::enumerator_info>& v) {
    enumerators_ = v;
}

void enum_info::enumerators(const std::list<dogen::cpp::enumerator_info>&& v) {
    enumerators_ = std::move(v);
}

const std::string& enum_info::documentation() const {
    return documentation_;
}

std::string& enum_info::documentation() {
    return documentation_;
}

void enum_info::documentation(const std::string& v) {
    documentation_ = v;
}

void enum_info::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

} }