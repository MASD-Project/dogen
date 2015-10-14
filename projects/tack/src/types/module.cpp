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
#include "dogen/tack/types/module.hpp"

namespace dogen {
namespace tack {

module::module()
    : generation_type_(static_cast<dogen::tack::generation_types>(0)),
      origin_type_(static_cast<dogen::tack::origin_types>(0)) { }

module::module(module&& rhs)
    : documentation_(std::move(rhs.documentation_)),
      extensions_(std::move(rhs.extensions_)),
      name_(std::move(rhs.name_)),
      generation_type_(std::move(rhs.generation_type_)),
      origin_type_(std::move(rhs.origin_type_)),
      containing_module_(std::move(rhs.containing_module_)),
      members_(std::move(rhs.members_)) { }

module::module(
    const std::string& documentation,
    const dogen::dynamic::object& extensions,
    const dogen::tack::name& name,
    const dogen::tack::generation_types generation_type,
    const dogen::tack::origin_types origin_type,
    const boost::optional<dogen::tack::name>& containing_module,
    const std::list<dogen::tack::name>& members)
    : documentation_(documentation),
      extensions_(extensions),
      name_(name),
      generation_type_(generation_type),
      origin_type_(origin_type),
      containing_module_(containing_module),
      members_(members) { }

void module::swap(module& other) noexcept {
    using std::swap;
    swap(documentation_, other.documentation_);
    swap(extensions_, other.extensions_);
    swap(name_, other.name_);
    swap(generation_type_, other.generation_type_);
    swap(origin_type_, other.origin_type_);
    swap(containing_module_, other.containing_module_);
    swap(members_, other.members_);
}

bool module::operator==(const module& rhs) const {
    return documentation_ == rhs.documentation_ &&
        extensions_ == rhs.extensions_ &&
        name_ == rhs.name_ &&
        generation_type_ == rhs.generation_type_ &&
        origin_type_ == rhs.origin_type_ &&
        containing_module_ == rhs.containing_module_ &&
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

const dogen::dynamic::object& module::extensions() const {
    return extensions_;
}

dogen::dynamic::object& module::extensions() {
    return extensions_;
}

void module::extensions(const dogen::dynamic::object& v) {
    extensions_ = v;
}

void module::extensions(const dogen::dynamic::object&& v) {
    extensions_ = std::move(v);
}

const dogen::tack::name& module::name() const {
    return name_;
}

dogen::tack::name& module::name() {
    return name_;
}

void module::name(const dogen::tack::name& v) {
    name_ = v;
}

void module::name(const dogen::tack::name&& v) {
    name_ = std::move(v);
}

dogen::tack::generation_types module::generation_type() const {
    return generation_type_;
}

void module::generation_type(const dogen::tack::generation_types v) {
    generation_type_ = v;
}

dogen::tack::origin_types module::origin_type() const {
    return origin_type_;
}

void module::origin_type(const dogen::tack::origin_types v) {
    origin_type_ = v;
}

const boost::optional<dogen::tack::name>& module::containing_module() const {
    return containing_module_;
}

boost::optional<dogen::tack::name>& module::containing_module() {
    return containing_module_;
}

void module::containing_module(const boost::optional<dogen::tack::name>& v) {
    containing_module_ = v;
}

void module::containing_module(const boost::optional<dogen::tack::name>&& v) {
    containing_module_ = std::move(v);
}

const std::list<dogen::tack::name>& module::members() const {
    return members_;
}

std::list<dogen::tack::name>& module::members() {
    return members_;
}

void module::members(const std::list<dogen::tack::name>& v) {
    members_ = v;
}

void module::members(const std::list<dogen::tack::name>&& v) {
    members_ = std::move(v);
}

} }
