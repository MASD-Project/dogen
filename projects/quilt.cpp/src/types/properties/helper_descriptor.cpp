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
#include "dogen/quilt.cpp/types/properties/helper_descriptor.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

helper_descriptor::helper_descriptor(
    const std::list<std::string>& namespaces,
    const std::string& name_qualified,
    const std::string& name_identifiable,
    const std::string& name_tree_qualified,
    const std::string& name_tree_identifiable,
    const dogen::yarn::name_tree& name_tree)
    : namespaces_(namespaces),
      name_qualified_(name_qualified),
      name_identifiable_(name_identifiable),
      name_tree_qualified_(name_tree_qualified),
      name_tree_identifiable_(name_tree_identifiable),
      name_tree_(name_tree) { }

void helper_descriptor::swap(helper_descriptor& other) noexcept {
    using std::swap;
    swap(namespaces_, other.namespaces_);
    swap(name_qualified_, other.name_qualified_);
    swap(name_identifiable_, other.name_identifiable_);
    swap(name_tree_qualified_, other.name_tree_qualified_);
    swap(name_tree_identifiable_, other.name_tree_identifiable_);
    swap(name_tree_, other.name_tree_);
}

bool helper_descriptor::operator==(const helper_descriptor& rhs) const {
    return namespaces_ == rhs.namespaces_ &&
        name_qualified_ == rhs.name_qualified_ &&
        name_identifiable_ == rhs.name_identifiable_ &&
        name_tree_qualified_ == rhs.name_tree_qualified_ &&
        name_tree_identifiable_ == rhs.name_tree_identifiable_ &&
        name_tree_ == rhs.name_tree_;
}

helper_descriptor& helper_descriptor::operator=(helper_descriptor other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<std::string>& helper_descriptor::namespaces() const {
    return namespaces_;
}

std::list<std::string>& helper_descriptor::namespaces() {
    return namespaces_;
}

void helper_descriptor::namespaces(const std::list<std::string>& v) {
    namespaces_ = v;
}

void helper_descriptor::namespaces(const std::list<std::string>&& v) {
    namespaces_ = std::move(v);
}

const std::string& helper_descriptor::name_qualified() const {
    return name_qualified_;
}

std::string& helper_descriptor::name_qualified() {
    return name_qualified_;
}

void helper_descriptor::name_qualified(const std::string& v) {
    name_qualified_ = v;
}

void helper_descriptor::name_qualified(const std::string&& v) {
    name_qualified_ = std::move(v);
}

const std::string& helper_descriptor::name_identifiable() const {
    return name_identifiable_;
}

std::string& helper_descriptor::name_identifiable() {
    return name_identifiable_;
}

void helper_descriptor::name_identifiable(const std::string& v) {
    name_identifiable_ = v;
}

void helper_descriptor::name_identifiable(const std::string&& v) {
    name_identifiable_ = std::move(v);
}

const std::string& helper_descriptor::name_tree_qualified() const {
    return name_tree_qualified_;
}

std::string& helper_descriptor::name_tree_qualified() {
    return name_tree_qualified_;
}

void helper_descriptor::name_tree_qualified(const std::string& v) {
    name_tree_qualified_ = v;
}

void helper_descriptor::name_tree_qualified(const std::string&& v) {
    name_tree_qualified_ = std::move(v);
}

const std::string& helper_descriptor::name_tree_identifiable() const {
    return name_tree_identifiable_;
}

std::string& helper_descriptor::name_tree_identifiable() {
    return name_tree_identifiable_;
}

void helper_descriptor::name_tree_identifiable(const std::string& v) {
    name_tree_identifiable_ = v;
}

void helper_descriptor::name_tree_identifiable(const std::string&& v) {
    name_tree_identifiable_ = std::move(v);
}

const dogen::yarn::name_tree& helper_descriptor::name_tree() const {
    return name_tree_;
}

dogen::yarn::name_tree& helper_descriptor::name_tree() {
    return name_tree_;
}

void helper_descriptor::name_tree(const dogen::yarn::name_tree& v) {
    name_tree_ = v;
}

void helper_descriptor::name_tree(const dogen::yarn::name_tree&& v) {
    name_tree_ = std::move(v);
}

} } } }
