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
#include "dogen/yarn/types/property.hpp"

namespace dogen {
namespace yarn {

property::property()
    : is_immutable_(static_cast<bool>(0)),
      is_fluent_(static_cast<bool>(0)) { }

property::property(
    const std::string& documentation,
    const dogen::dynamic::object& extensions,
    const std::string& name,
    const dogen::yarn::nested_name& type,
    const bool is_immutable,
    const bool is_fluent,
    const std::string& unparsed_type)
    : documentation_(documentation),
      extensions_(extensions),
      name_(name),
      type_(type),
      is_immutable_(is_immutable),
      is_fluent_(is_fluent),
      unparsed_type_(unparsed_type) { }

void property::swap(property& other) noexcept {
    using std::swap;
    swap(documentation_, other.documentation_);
    swap(extensions_, other.extensions_);
    swap(name_, other.name_);
    swap(type_, other.type_);
    swap(is_immutable_, other.is_immutable_);
    swap(is_fluent_, other.is_fluent_);
    swap(unparsed_type_, other.unparsed_type_);
}

bool property::operator==(const property& rhs) const {
    return documentation_ == rhs.documentation_ &&
        extensions_ == rhs.extensions_ &&
        name_ == rhs.name_ &&
        type_ == rhs.type_ &&
        is_immutable_ == rhs.is_immutable_ &&
        is_fluent_ == rhs.is_fluent_ &&
        unparsed_type_ == rhs.unparsed_type_;
}

property& property::operator=(property other) {
    using std::swap;
    swap(*this, other);
    return *this;
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

const dogen::dynamic::object& property::extensions() const {
    return extensions_;
}

dogen::dynamic::object& property::extensions() {
    return extensions_;
}

void property::extensions(const dogen::dynamic::object& v) {
    extensions_ = v;
}

void property::extensions(const dogen::dynamic::object&& v) {
    extensions_ = std::move(v);
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

const dogen::yarn::nested_name& property::type() const {
    return type_;
}

dogen::yarn::nested_name& property::type() {
    return type_;
}

void property::type(const dogen::yarn::nested_name& v) {
    type_ = v;
}

void property::type(const dogen::yarn::nested_name&& v) {
    type_ = std::move(v);
}

bool property::is_immutable() const {
    return is_immutable_;
}

void property::is_immutable(const bool v) {
    is_immutable_ = v;
}

bool property::is_fluent() const {
    return is_fluent_;
}

void property::is_fluent(const bool v) {
    is_fluent_ = v;
}

const std::string& property::unparsed_type() const {
    return unparsed_type_;
}

std::string& property::unparsed_type() {
    return unparsed_type_;
}

void property::unparsed_type(const std::string& v) {
    unparsed_type_ = v;
}

void property::unparsed_type(const std::string&& v) {
    unparsed_type_ = std::move(v);
}

} }
