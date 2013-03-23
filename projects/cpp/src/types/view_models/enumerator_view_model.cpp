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
#include "dogen/cpp/types/view_models/enumerator_view_model.hpp"

namespace dogen {
namespace cpp {
namespace view_models {

enumerator_view_model::enumerator_view_model(
    const std::string& name,
    const std::string& value,
    const std::string& documentation)
    : name_(name),
      value_(value),
      documentation_(documentation) { }

void enumerator_view_model::swap(enumerator_view_model& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(value_, other.value_);
    swap(documentation_, other.documentation_);
}

bool enumerator_view_model::operator==(const enumerator_view_model& rhs) const {
    return name_ == rhs.name_ &&
        value_ == rhs.value_ &&
        documentation_ == rhs.documentation_;
}

enumerator_view_model& enumerator_view_model::operator=(enumerator_view_model other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& enumerator_view_model::name() const {
    return name_;
}

std::string& enumerator_view_model::name() {
    return name_;
}

void enumerator_view_model::name(const std::string& v) {
    name_ = v;
}

void enumerator_view_model::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::string& enumerator_view_model::value() const {
    return value_;
}

std::string& enumerator_view_model::value() {
    return value_;
}

void enumerator_view_model::value(const std::string& v) {
    value_ = v;
}

void enumerator_view_model::value(const std::string&& v) {
    value_ = std::move(v);
}

const std::string& enumerator_view_model::documentation() const {
    return documentation_;
}

std::string& enumerator_view_model::documentation() {
    return documentation_;
}

void enumerator_view_model::documentation(const std::string& v) {
    documentation_ = v;
}

void enumerator_view_model::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

} } }