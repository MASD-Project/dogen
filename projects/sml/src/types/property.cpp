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
#include "dogen/sml/types/property.hpp"

namespace dogen {
namespace sml {

property::property(
    const std::string& name,
    const dogen::sml::nested_qname& type_name,
    const std::string& default_value,
    const std::string& documentation)
    : name_(name),
      type_name_(type_name),
      default_value_(default_value),
      documentation_(documentation) { }

void property::swap(property& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(type_name_, other.type_name_);
    swap(default_value_, other.default_value_);
    swap(documentation_, other.documentation_);
}

bool property::operator==(const property& rhs) const {
    return name_ == rhs.name_ &&
        type_name_ == rhs.type_name_ &&
        default_value_ == rhs.default_value_ &&
        documentation_ == rhs.documentation_;
}

property& property::operator=(property other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& property::name() const {
    return name_;
}

std::string& property::name() {
    return name_;
}

void property::name(const std::string& v) {
    name_ = v;
}

void property::name(const std::string&& v) {
    name_ = std::move(v);
}

const dogen::sml::nested_qname& property::type_name() const {
    return type_name_;
}

dogen::sml::nested_qname& property::type_name() {
    return type_name_;
}

void property::type_name(const dogen::sml::nested_qname& v) {
    type_name_ = v;
}

void property::type_name(const dogen::sml::nested_qname&& v) {
    type_name_ = std::move(v);
}

const std::string& property::default_value() const {
    return default_value_;
}

std::string& property::default_value() {
    return default_value_;
}

void property::default_value(const std::string& v) {
    default_value_ = v;
}

void property::default_value(const std::string&& v) {
    default_value_ = std::move(v);
}

const std::string& property::documentation() const {
    return documentation_;
}

std::string& property::documentation() {
    return documentation_;
}

void property::documentation(const std::string& v) {
    documentation_ = v;
}

void property::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

} }