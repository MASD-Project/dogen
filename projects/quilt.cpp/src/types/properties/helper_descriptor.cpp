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
    const dogen::yarn::name& helped_type,
    const std::string& name_tree_encoded,
    const std::string& name_tree_identifiable)
    : helped_type_(helped_type),
      name_tree_encoded_(name_tree_encoded),
      name_tree_identifiable_(name_tree_identifiable) { }

void helper_descriptor::swap(helper_descriptor& other) noexcept {
    using std::swap;
    swap(helped_type_, other.helped_type_);
    swap(name_tree_encoded_, other.name_tree_encoded_);
    swap(name_tree_identifiable_, other.name_tree_identifiable_);
}

bool helper_descriptor::operator==(const helper_descriptor& rhs) const {
    return helped_type_ == rhs.helped_type_ &&
        name_tree_encoded_ == rhs.name_tree_encoded_ &&
        name_tree_identifiable_ == rhs.name_tree_identifiable_;
}

helper_descriptor& helper_descriptor::operator=(helper_descriptor other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::yarn::name& helper_descriptor::helped_type() const {
    return helped_type_;
}

dogen::yarn::name& helper_descriptor::helped_type() {
    return helped_type_;
}

void helper_descriptor::helped_type(const dogen::yarn::name& v) {
    helped_type_ = v;
}

void helper_descriptor::helped_type(const dogen::yarn::name&& v) {
    helped_type_ = std::move(v);
}

const std::string& helper_descriptor::name_tree_encoded() const {
    return name_tree_encoded_;
}

std::string& helper_descriptor::name_tree_encoded() {
    return name_tree_encoded_;
}

void helper_descriptor::name_tree_encoded(const std::string& v) {
    name_tree_encoded_ = v;
}

void helper_descriptor::name_tree_encoded(const std::string&& v) {
    name_tree_encoded_ = std::move(v);
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

} } } }
