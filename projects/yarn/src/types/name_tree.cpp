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
#include "dogen/yarn/types/name_tree.hpp"

namespace dogen {
namespace yarn {

name_tree::name_tree()
    : are_children_opaque_(static_cast<bool>(0)),
      is_circular_dependency_(static_cast<bool>(0)) { }

name_tree::name_tree(
    const dogen::yarn::name& parent,
    const std::list<dogen::yarn::name_tree>& children,
    const bool are_children_opaque,
    const bool is_circular_dependency,
    const std::string& unparsed_type,
    const std::map<dogen::yarn::language, std::string>& qualified_for,
    const std::string& identifiable)
    : parent_(parent),
      children_(children),
      are_children_opaque_(are_children_opaque),
      is_circular_dependency_(is_circular_dependency),
      unparsed_type_(unparsed_type),
      qualified_for_(qualified_for),
      identifiable_(identifiable) { }

void name_tree::swap(name_tree& other) noexcept {
    using std::swap;
    swap(parent_, other.parent_);
    swap(children_, other.children_);
    swap(are_children_opaque_, other.are_children_opaque_);
    swap(is_circular_dependency_, other.is_circular_dependency_);
    swap(unparsed_type_, other.unparsed_type_);
    swap(qualified_for_, other.qualified_for_);
    swap(identifiable_, other.identifiable_);
}

bool name_tree::operator==(const name_tree& rhs) const {
    return parent_ == rhs.parent_ &&
        children_ == rhs.children_ &&
        are_children_opaque_ == rhs.are_children_opaque_ &&
        is_circular_dependency_ == rhs.is_circular_dependency_ &&
        unparsed_type_ == rhs.unparsed_type_ &&
        qualified_for_ == rhs.qualified_for_ &&
        identifiable_ == rhs.identifiable_;
}

name_tree& name_tree::operator=(name_tree other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::yarn::name& name_tree::parent() const {
    return parent_;
}

dogen::yarn::name& name_tree::parent() {
    return parent_;
}

void name_tree::parent(const dogen::yarn::name& v) {
    parent_ = v;
}

void name_tree::parent(const dogen::yarn::name&& v) {
    parent_ = std::move(v);
}

const std::list<dogen::yarn::name_tree>& name_tree::children() const {
    return children_;
}

std::list<dogen::yarn::name_tree>& name_tree::children() {
    return children_;
}

void name_tree::children(const std::list<dogen::yarn::name_tree>& v) {
    children_ = v;
}

void name_tree::children(const std::list<dogen::yarn::name_tree>&& v) {
    children_ = std::move(v);
}

bool name_tree::are_children_opaque() const {
    return are_children_opaque_;
}

void name_tree::are_children_opaque(const bool v) {
    are_children_opaque_ = v;
}

bool name_tree::is_circular_dependency() const {
    return is_circular_dependency_;
}

void name_tree::is_circular_dependency(const bool v) {
    is_circular_dependency_ = v;
}

const std::string& name_tree::unparsed_type() const {
    return unparsed_type_;
}

std::string& name_tree::unparsed_type() {
    return unparsed_type_;
}

void name_tree::unparsed_type(const std::string& v) {
    unparsed_type_ = v;
}

void name_tree::unparsed_type(const std::string&& v) {
    unparsed_type_ = std::move(v);
}

const std::map<dogen::yarn::language, std::string>& name_tree::qualified_for() const {
    return qualified_for_;
}

std::map<dogen::yarn::language, std::string>& name_tree::qualified_for() {
    return qualified_for_;
}

void name_tree::qualified_for(const std::map<dogen::yarn::language, std::string>& v) {
    qualified_for_ = v;
}

void name_tree::qualified_for(const std::map<dogen::yarn::language, std::string>&& v) {
    qualified_for_ = std::move(v);
}

const std::string& name_tree::identifiable() const {
    return identifiable_;
}

std::string& name_tree::identifiable() {
    return identifiable_;
}

void name_tree::identifiable(const std::string& v) {
    identifiable_ = v;
}

void name_tree::identifiable(const std::string&& v) {
    identifiable_ = std::move(v);
}

} }
