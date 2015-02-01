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
#include "dogen/cpp/types/formattables/inheritance.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

inheritance::inheritance()
    : is_parent_(static_cast<bool>(0)),
      is_final_(static_cast<bool>(0)) { }

inheritance::inheritance(
    const std::list<dogen::cpp::formattables::parent_info>& parents,
    const bool is_parent,
    const std::string& original_parent_name,
    const std::string& original_parent_name_qualified,
    const std::list<std::string>& leaves,
    const bool is_final)
    : parents_(parents),
      is_parent_(is_parent),
      original_parent_name_(original_parent_name),
      original_parent_name_qualified_(original_parent_name_qualified),
      leaves_(leaves),
      is_final_(is_final) { }

void inheritance::swap(inheritance& other) noexcept {
    using std::swap;
    swap(parents_, other.parents_);
    swap(is_parent_, other.is_parent_);
    swap(original_parent_name_, other.original_parent_name_);
    swap(original_parent_name_qualified_, other.original_parent_name_qualified_);
    swap(leaves_, other.leaves_);
    swap(is_final_, other.is_final_);
}

bool inheritance::operator==(const inheritance& rhs) const {
    return parents_ == rhs.parents_ &&
        is_parent_ == rhs.is_parent_ &&
        original_parent_name_ == rhs.original_parent_name_ &&
        original_parent_name_qualified_ == rhs.original_parent_name_qualified_ &&
        leaves_ == rhs.leaves_ &&
        is_final_ == rhs.is_final_;
}

inheritance& inheritance::operator=(inheritance other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::cpp::formattables::parent_info>& inheritance::parents() const {
    return parents_;
}

std::list<dogen::cpp::formattables::parent_info>& inheritance::parents() {
    return parents_;
}

void inheritance::parents(const std::list<dogen::cpp::formattables::parent_info>& v) {
    parents_ = v;
}

void inheritance::parents(const std::list<dogen::cpp::formattables::parent_info>&& v) {
    parents_ = std::move(v);
}

bool inheritance::is_parent() const {
    return is_parent_;
}

void inheritance::is_parent(const bool v) {
    is_parent_ = v;
}

const std::string& inheritance::original_parent_name() const {
    return original_parent_name_;
}

std::string& inheritance::original_parent_name() {
    return original_parent_name_;
}

void inheritance::original_parent_name(const std::string& v) {
    original_parent_name_ = v;
}

void inheritance::original_parent_name(const std::string&& v) {
    original_parent_name_ = std::move(v);
}

const std::string& inheritance::original_parent_name_qualified() const {
    return original_parent_name_qualified_;
}

std::string& inheritance::original_parent_name_qualified() {
    return original_parent_name_qualified_;
}

void inheritance::original_parent_name_qualified(const std::string& v) {
    original_parent_name_qualified_ = v;
}

void inheritance::original_parent_name_qualified(const std::string&& v) {
    original_parent_name_qualified_ = std::move(v);
}

const std::list<std::string>& inheritance::leaves() const {
    return leaves_;
}

std::list<std::string>& inheritance::leaves() {
    return leaves_;
}

void inheritance::leaves(const std::list<std::string>& v) {
    leaves_ = v;
}

void inheritance::leaves(const std::list<std::string>&& v) {
    leaves_ = std::move(v);
}

bool inheritance::is_final() const {
    return is_final_;
}

void inheritance::is_final(const bool v) {
    is_final_ = v;
}

} } }