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
#include "dogen/sml/types/module.hpp"

namespace dogen {
namespace sml {

module::module()
    : generation_type_(static_cast<dogen::sml::generation_types>(0)),
      origin_type_(static_cast<dogen::sml::origin_types>(0)) { }

module::module(
    const std::string& documentation,
    const std::unordered_map<std::string, std::string>& simple_tags,
    const std::unordered_map<std::string, std::list<std::string> >& complex_tags,
    const dogen::sml::qname& name,
    const dogen::sml::generation_types& generation_type,
    const dogen::sml::origin_types& origin_type,
    const std::list<dogen::sml::qname>& members)
    : documentation_(documentation),
      simple_tags_(simple_tags),
      complex_tags_(complex_tags),
      name_(name),
      generation_type_(generation_type),
      origin_type_(origin_type),
      members_(members) { }

void module::swap(module& other) noexcept {
    using std::swap;
    swap(documentation_, other.documentation_);
    swap(simple_tags_, other.simple_tags_);
    swap(complex_tags_, other.complex_tags_);
    swap(name_, other.name_);
    swap(generation_type_, other.generation_type_);
    swap(origin_type_, other.origin_type_);
    swap(members_, other.members_);
}

bool module::operator==(const module& rhs) const {
    return documentation_ == rhs.documentation_ &&
        simple_tags_ == rhs.simple_tags_ &&
        complex_tags_ == rhs.complex_tags_ &&
        name_ == rhs.name_ &&
        generation_type_ == rhs.generation_type_ &&
        origin_type_ == rhs.origin_type_ &&
        members_ == rhs.members_;
}

module& module::operator=(module other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& module::documentation() const {
    return documentation_;
}

std::string& module::documentation() {
    return documentation_;
}

void module::documentation(const std::string& v) {
    documentation_ = v;
}

void module::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

const std::unordered_map<std::string, std::string>& module::simple_tags() const {
    return simple_tags_;
}

std::unordered_map<std::string, std::string>& module::simple_tags() {
    return simple_tags_;
}

void module::simple_tags(const std::unordered_map<std::string, std::string>& v) {
    simple_tags_ = v;
}

void module::simple_tags(const std::unordered_map<std::string, std::string>&& v) {
    simple_tags_ = std::move(v);
}

const std::unordered_map<std::string, std::list<std::string> >& module::complex_tags() const {
    return complex_tags_;
}

std::unordered_map<std::string, std::list<std::string> >& module::complex_tags() {
    return complex_tags_;
}

void module::complex_tags(const std::unordered_map<std::string, std::list<std::string> >& v) {
    complex_tags_ = v;
}

void module::complex_tags(const std::unordered_map<std::string, std::list<std::string> >&& v) {
    complex_tags_ = std::move(v);
}

const dogen::sml::qname& module::name() const {
    return name_;
}

dogen::sml::qname& module::name() {
    return name_;
}

void module::name(const dogen::sml::qname& v) {
    name_ = v;
}

void module::name(const dogen::sml::qname&& v) {
    name_ = std::move(v);
}

dogen::sml::generation_types module::generation_type() const {
    return generation_type_;
}

void module::generation_type(const dogen::sml::generation_types& v) {
    generation_type_ = v;
}

dogen::sml::origin_types module::origin_type() const {
    return origin_type_;
}

void module::origin_type(const dogen::sml::origin_types& v) {
    origin_type_ = v;
}

const std::list<dogen::sml::qname>& module::members() const {
    return members_;
}

std::list<dogen::sml::qname>& module::members() {
    return members_;
}

void module::members(const std::list<dogen::sml::qname>& v) {
    members_ = v;
}

void module::members(const std::list<dogen::sml::qname>&& v) {
    members_ = std::move(v);
}

} }