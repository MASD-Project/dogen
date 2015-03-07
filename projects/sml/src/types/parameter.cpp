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
#include "dogen/sml/types/parameter.hpp"

namespace dogen {
namespace sml {

parameter::parameter(
    const std::string& documentation,
    const dogen::dynamic::schema::object& extensions,
    const std::string& name,
    const dogen::sml::nested_qname& type)
    : documentation_(documentation),
      extensions_(extensions),
      name_(name),
      type_(type) { }

void parameter::swap(parameter& other) noexcept {
    using std::swap;
    swap(documentation_, other.documentation_);
    swap(extensions_, other.extensions_);
    swap(name_, other.name_);
    swap(type_, other.type_);
}

bool parameter::operator==(const parameter& rhs) const {
    return documentation_ == rhs.documentation_ &&
        extensions_ == rhs.extensions_ &&
        name_ == rhs.name_ &&
        type_ == rhs.type_;
}

parameter& parameter::operator=(parameter other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& parameter::documentation() const {
    return documentation_;
}

std::string& parameter::documentation() {
    return documentation_;
}

void parameter::documentation(const std::string& v) {
    documentation_ = v;
}

void parameter::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

const dogen::dynamic::schema::object& parameter::extensions() const {
    return extensions_;
}

dogen::dynamic::schema::object& parameter::extensions() {
    return extensions_;
}

void parameter::extensions(const dogen::dynamic::schema::object& v) {
    extensions_ = v;
}

void parameter::extensions(const dogen::dynamic::schema::object&& v) {
    extensions_ = std::move(v);
}

const std::string& parameter::name() const {
    return name_;
}

std::string& parameter::name() {
    return name_;
}

void parameter::name(const std::string& v) {
    name_ = v;
}

void parameter::name(const std::string&& v) {
    name_ = std::move(v);
}

const dogen::sml::nested_qname& parameter::type() const {
    return type_;
}

dogen::sml::nested_qname& parameter::type() {
    return type_;
}

void parameter::type(const dogen::sml::nested_qname& v) {
    type_ = v;
}

void parameter::type(const dogen::sml::nested_qname&& v) {
    type_ = std::move(v);
}

} }