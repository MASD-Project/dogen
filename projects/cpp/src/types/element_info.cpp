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
#include "dogen/cpp/types/element_info.hpp"

namespace dogen {
namespace cpp {

element_info::element_info(
    const std::string& name,
    const std::string& documentation)
    : name_(name),
      documentation_(documentation) { }

void element_info::swap(element_info& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(documentation_, other.documentation_);
}

bool element_info::operator==(const element_info& rhs) const {
    return name_ == rhs.name_ &&
        documentation_ == rhs.documentation_;
}

element_info& element_info::operator=(element_info other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& element_info::name() const {
    return name_;
}

std::string& element_info::name() {
    return name_;
}

void element_info::name(const std::string& v) {
    name_ = v;
}

void element_info::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::string& element_info::documentation() const {
    return documentation_;
}

std::string& element_info::documentation() {
    return documentation_;
}

void element_info::documentation(const std::string& v) {
    documentation_ = v;
}

void element_info::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

} }