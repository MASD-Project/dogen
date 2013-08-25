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
#include "dogen/om/types/cpp_enumerator.hpp"

namespace dogen {
namespace om {

cpp_enumerator::cpp_enumerator(
    const std::list<dogen::om::doxygen_command>& commands,
    const std::string& name,
    const std::string& value)
    : commands_(commands),
      name_(name),
      value_(value) { }

void cpp_enumerator::swap(cpp_enumerator& other) noexcept {
    using std::swap;
    swap(commands_, other.commands_);
    swap(name_, other.name_);
    swap(value_, other.value_);
}

bool cpp_enumerator::operator==(const cpp_enumerator& rhs) const {
    return commands_ == rhs.commands_ &&
        name_ == rhs.name_ &&
        value_ == rhs.value_;
}

cpp_enumerator& cpp_enumerator::operator=(cpp_enumerator other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::om::doxygen_command>& cpp_enumerator::commands() const {
    return commands_;
}

std::list<dogen::om::doxygen_command>& cpp_enumerator::commands() {
    return commands_;
}

void cpp_enumerator::commands(const std::list<dogen::om::doxygen_command>& v) {
    commands_ = v;
}

void cpp_enumerator::commands(const std::list<dogen::om::doxygen_command>&& v) {
    commands_ = std::move(v);
}

const std::string& cpp_enumerator::name() const {
    return name_;
}

std::string& cpp_enumerator::name() {
    return name_;
}

void cpp_enumerator::name(const std::string& v) {
    name_ = v;
}

void cpp_enumerator::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::string& cpp_enumerator::value() const {
    return value_;
}

std::string& cpp_enumerator::value() {
    return value_;
}

void cpp_enumerator::value(const std::string& v) {
    value_ = v;
}

void cpp_enumerator::value(const std::string&& v) {
    value_ = std::move(v);
}

} }