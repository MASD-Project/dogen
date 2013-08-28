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
#include "dogen/om/types/preamble_field.hpp"

namespace dogen {
namespace om {

preamble_field::preamble_field(
    const std::string& name,
    const std::string& value)
    : name_(name),
      value_(value) { }

void preamble_field::swap(preamble_field& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(value_, other.value_);
}

bool preamble_field::operator==(const preamble_field& rhs) const {
    return name_ == rhs.name_ &&
        value_ == rhs.value_;
}

preamble_field& preamble_field::operator=(preamble_field other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& preamble_field::name() const {
    return name_;
}

std::string& preamble_field::name() {
    return name_;
}

void preamble_field::name(const std::string& v) {
    name_ = v;
}

void preamble_field::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::string& preamble_field::value() const {
    return value_;
}

std::string& preamble_field::value() {
    return value_;
}

void preamble_field::value(const std::string& v) {
    value_ = v;
}

void preamble_field::value(const std::string&& v) {
    value_ = std::move(v);
}

} }