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
#include "dogen/cpp/types/dependency_details.hpp"

namespace dogen {
namespace cpp {

dependency_details::dependency_details()
    : has_std_string_(static_cast<bool>(0)),
      has_variant_(static_cast<bool>(0)),
      is_parent_(static_cast<bool>(0)),
      is_child_(static_cast<bool>(0)),
      requires_stream_manipulators_(static_cast<bool>(0)),
      has_std_pair_(static_cast<bool>(0)) { }

dependency_details::dependency_details(
    const std::unordered_set<dogen::sml::qname>& names,
    const std::unordered_set<dogen::sml::qname>& forward_decls,
    const std::unordered_set<dogen::sml::qname>& keys,
    const std::unordered_set<dogen::sml::qname>& leaves,
    const bool has_std_string,
    const bool has_variant,
    const bool is_parent,
    const bool is_child,
    const bool requires_stream_manipulators,
    const bool has_std_pair)
    : names_(names),
      forward_decls_(forward_decls),
      keys_(keys),
      leaves_(leaves),
      has_std_string_(has_std_string),
      has_variant_(has_variant),
      is_parent_(is_parent),
      is_child_(is_child),
      requires_stream_manipulators_(requires_stream_manipulators),
      has_std_pair_(has_std_pair) { }

void dependency_details::swap(dependency_details& other) noexcept {
    using std::swap;
    swap(names_, other.names_);
    swap(forward_decls_, other.forward_decls_);
    swap(keys_, other.keys_);
    swap(leaves_, other.leaves_);
    swap(has_std_string_, other.has_std_string_);
    swap(has_variant_, other.has_variant_);
    swap(is_parent_, other.is_parent_);
    swap(is_child_, other.is_child_);
    swap(requires_stream_manipulators_, other.requires_stream_manipulators_);
    swap(has_std_pair_, other.has_std_pair_);
}

bool dependency_details::operator==(const dependency_details& rhs) const {
    return names_ == rhs.names_ &&
        forward_decls_ == rhs.forward_decls_ &&
        keys_ == rhs.keys_ &&
        leaves_ == rhs.leaves_ &&
        has_std_string_ == rhs.has_std_string_ &&
        has_variant_ == rhs.has_variant_ &&
        is_parent_ == rhs.is_parent_ &&
        is_child_ == rhs.is_child_ &&
        requires_stream_manipulators_ == rhs.requires_stream_manipulators_ &&
        has_std_pair_ == rhs.has_std_pair_;
}

dependency_details& dependency_details::operator=(dependency_details other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_set<dogen::sml::qname>& dependency_details::names() const {
    return names_;
}

std::unordered_set<dogen::sml::qname>& dependency_details::names() {
    return names_;
}

void dependency_details::names(const std::unordered_set<dogen::sml::qname>& v) {
    names_ = v;
}

void dependency_details::names(const std::unordered_set<dogen::sml::qname>&& v) {
    names_ = std::move(v);
}

const std::unordered_set<dogen::sml::qname>& dependency_details::forward_decls() const {
    return forward_decls_;
}

std::unordered_set<dogen::sml::qname>& dependency_details::forward_decls() {
    return forward_decls_;
}

void dependency_details::forward_decls(const std::unordered_set<dogen::sml::qname>& v) {
    forward_decls_ = v;
}

void dependency_details::forward_decls(const std::unordered_set<dogen::sml::qname>&& v) {
    forward_decls_ = std::move(v);
}

const std::unordered_set<dogen::sml::qname>& dependency_details::keys() const {
    return keys_;
}

std::unordered_set<dogen::sml::qname>& dependency_details::keys() {
    return keys_;
}

void dependency_details::keys(const std::unordered_set<dogen::sml::qname>& v) {
    keys_ = v;
}

void dependency_details::keys(const std::unordered_set<dogen::sml::qname>&& v) {
    keys_ = std::move(v);
}

const std::unordered_set<dogen::sml::qname>& dependency_details::leaves() const {
    return leaves_;
}

std::unordered_set<dogen::sml::qname>& dependency_details::leaves() {
    return leaves_;
}

void dependency_details::leaves(const std::unordered_set<dogen::sml::qname>& v) {
    leaves_ = v;
}

void dependency_details::leaves(const std::unordered_set<dogen::sml::qname>&& v) {
    leaves_ = std::move(v);
}

bool dependency_details::has_std_string() const {
    return has_std_string_;
}

void dependency_details::has_std_string(const bool v) {
    has_std_string_ = v;
}

bool dependency_details::has_variant() const {
    return has_variant_;
}

void dependency_details::has_variant(const bool v) {
    has_variant_ = v;
}

bool dependency_details::is_parent() const {
    return is_parent_;
}

void dependency_details::is_parent(const bool v) {
    is_parent_ = v;
}

bool dependency_details::is_child() const {
    return is_child_;
}

void dependency_details::is_child(const bool v) {
    is_child_ = v;
}

bool dependency_details::requires_stream_manipulators() const {
    return requires_stream_manipulators_;
}

void dependency_details::requires_stream_manipulators(const bool v) {
    requires_stream_manipulators_ = v;
}

bool dependency_details::has_std_pair() const {
    return has_std_pair_;
}

void dependency_details::has_std_pair(const bool v) {
    has_std_pair_ = v;
}

} }