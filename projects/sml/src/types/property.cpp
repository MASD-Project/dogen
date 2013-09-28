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

property::property()
    : is_immutable_(static_cast<bool>(0)),
      is_fluent_(static_cast<bool>(0)) { }

property::property(
    const std::string& documentation,
    const std::unordered_map<std::string, std::string>& simple_tags,
    const std::unordered_map<std::string, std::list<std::string> >& complex_tags,
    const std::string& name,
    const dogen::sml::nested_qname& type,
    const std::string& default_value,
    const bool is_immutable,
    const bool is_fluent)
    : documentation_(documentation),
      simple_tags_(simple_tags),
      complex_tags_(complex_tags),
      name_(name),
      type_(type),
      default_value_(default_value),
      is_immutable_(is_immutable),
      is_fluent_(is_fluent) { }

void property::swap(property& other) noexcept {
    using std::swap;
    swap(documentation_, other.documentation_);
    swap(simple_tags_, other.simple_tags_);
    swap(complex_tags_, other.complex_tags_);
    swap(name_, other.name_);
    swap(type_, other.type_);
    swap(default_value_, other.default_value_);
    swap(is_immutable_, other.is_immutable_);
    swap(is_fluent_, other.is_fluent_);
}

bool property::operator==(const property& rhs) const {
    return documentation_ == rhs.documentation_ &&
        simple_tags_ == rhs.simple_tags_ &&
        complex_tags_ == rhs.complex_tags_ &&
        name_ == rhs.name_ &&
        type_ == rhs.type_ &&
        default_value_ == rhs.default_value_ &&
        is_immutable_ == rhs.is_immutable_ &&
        is_fluent_ == rhs.is_fluent_;
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

const std::unordered_map<std::string, std::string>& property::simple_tags() const {
    return simple_tags_;
}

std::unordered_map<std::string, std::string>& property::simple_tags() {
    return simple_tags_;
}

void property::simple_tags(const std::unordered_map<std::string, std::string>& v) {
    simple_tags_ = v;
}

void property::simple_tags(const std::unordered_map<std::string, std::string>&& v) {
    simple_tags_ = std::move(v);
}

const std::unordered_map<std::string, std::list<std::string> >& property::complex_tags() const {
    return complex_tags_;
}

std::unordered_map<std::string, std::list<std::string> >& property::complex_tags() {
    return complex_tags_;
}

void property::complex_tags(const std::unordered_map<std::string, std::list<std::string> >& v) {
    complex_tags_ = v;
}

void property::complex_tags(const std::unordered_map<std::string, std::list<std::string> >&& v) {
    complex_tags_ = std::move(v);
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

const dogen::sml::nested_qname& property::type() const {
    return type_;
}

dogen::sml::nested_qname& property::type() {
    return type_;
}

void property::type(const dogen::sml::nested_qname& v) {
    type_ = v;
}

void property::type(const dogen::sml::nested_qname&& v) {
    type_ = std::move(v);
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

} }