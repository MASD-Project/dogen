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
#include "dogen/sml_to_cpp/types/relationships.hpp"

namespace dogen {
namespace sml_to_cpp {

relationships::relationships()
    : has_std_string_(static_cast<bool>(0)),
      has_variant_(static_cast<bool>(0)),
      is_parent_(static_cast<bool>(0)),
      is_child_(static_cast<bool>(0)),
      requires_stream_manipulators_(static_cast<bool>(0)),
      has_std_pair_(static_cast<bool>(0)) { }

relationships::relationships(relationships&& rhs)
    : names_(std::move(rhs.names_)),
      forward_decls_(std::move(rhs.forward_decls_)),
      keys_(std::move(rhs.keys_)),
      leaves_(std::move(rhs.leaves_)),
      has_std_string_(std::move(rhs.has_std_string_)),
      has_variant_(std::move(rhs.has_variant_)),
      is_parent_(std::move(rhs.is_parent_)),
      is_child_(std::move(rhs.is_child_)),
      requires_stream_manipulators_(std::move(rhs.requires_stream_manipulators_)),
      has_std_pair_(std::move(rhs.has_std_pair_)),
      visitor_(std::move(rhs.visitor_)) { }

relationships::relationships(
    const std::unordered_set<dogen::sml::qname>& names,
    const std::unordered_set<dogen::sml::qname>& forward_decls,
    const std::unordered_set<dogen::sml::qname>& keys,
    const std::unordered_set<dogen::sml::qname>& leaves,
    const bool has_std_string,
    const bool has_variant,
    const bool is_parent,
    const bool is_child,
    const bool requires_stream_manipulators,
    const bool has_std_pair,
    const boost::optional<dogen::sml::qname>& visitor)
    : names_(names),
      forward_decls_(forward_decls),
      keys_(keys),
      leaves_(leaves),
      has_std_string_(has_std_string),
      has_variant_(has_variant),
      is_parent_(is_parent),
      is_child_(is_child),
      requires_stream_manipulators_(requires_stream_manipulators),
      has_std_pair_(has_std_pair),
      visitor_(visitor) { }

void relationships::swap(relationships& other) noexcept {
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
    swap(visitor_, other.visitor_);
}

bool relationships::operator==(const relationships& rhs) const {
    return names_ == rhs.names_ &&
        forward_decls_ == rhs.forward_decls_ &&
        keys_ == rhs.keys_ &&
        leaves_ == rhs.leaves_ &&
        has_std_string_ == rhs.has_std_string_ &&
        has_variant_ == rhs.has_variant_ &&
        is_parent_ == rhs.is_parent_ &&
        is_child_ == rhs.is_child_ &&
        requires_stream_manipulators_ == rhs.requires_stream_manipulators_ &&
        has_std_pair_ == rhs.has_std_pair_ &&
        visitor_ == rhs.visitor_;
}

relationships& relationships::operator=(relationships other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_set<dogen::sml::qname>& relationships::names() const {
    return names_;
}

std::unordered_set<dogen::sml::qname>& relationships::names() {
    return names_;
}

void relationships::names(const std::unordered_set<dogen::sml::qname>& v) {
    names_ = v;
}

void relationships::names(const std::unordered_set<dogen::sml::qname>&& v) {
    names_ = std::move(v);
}

const std::unordered_set<dogen::sml::qname>& relationships::forward_decls() const {
    return forward_decls_;
}

std::unordered_set<dogen::sml::qname>& relationships::forward_decls() {
    return forward_decls_;
}

void relationships::forward_decls(const std::unordered_set<dogen::sml::qname>& v) {
    forward_decls_ = v;
}

void relationships::forward_decls(const std::unordered_set<dogen::sml::qname>&& v) {
    forward_decls_ = std::move(v);
}

const std::unordered_set<dogen::sml::qname>& relationships::keys() const {
    return keys_;
}

std::unordered_set<dogen::sml::qname>& relationships::keys() {
    return keys_;
}

void relationships::keys(const std::unordered_set<dogen::sml::qname>& v) {
    keys_ = v;
}

void relationships::keys(const std::unordered_set<dogen::sml::qname>&& v) {
    keys_ = std::move(v);
}

const std::unordered_set<dogen::sml::qname>& relationships::leaves() const {
    return leaves_;
}

std::unordered_set<dogen::sml::qname>& relationships::leaves() {
    return leaves_;
}

void relationships::leaves(const std::unordered_set<dogen::sml::qname>& v) {
    leaves_ = v;
}

void relationships::leaves(const std::unordered_set<dogen::sml::qname>&& v) {
    leaves_ = std::move(v);
}

bool relationships::has_std_string() const {
    return has_std_string_;
}

void relationships::has_std_string(const bool v) {
    has_std_string_ = v;
}

bool relationships::has_variant() const {
    return has_variant_;
}

void relationships::has_variant(const bool v) {
    has_variant_ = v;
}

bool relationships::is_parent() const {
    return is_parent_;
}

void relationships::is_parent(const bool v) {
    is_parent_ = v;
}

bool relationships::is_child() const {
    return is_child_;
}

void relationships::is_child(const bool v) {
    is_child_ = v;
}

bool relationships::requires_stream_manipulators() const {
    return requires_stream_manipulators_;
}

void relationships::requires_stream_manipulators(const bool v) {
    requires_stream_manipulators_ = v;
}

bool relationships::has_std_pair() const {
    return has_std_pair_;
}

void relationships::has_std_pair(const bool v) {
    has_std_pair_ = v;
}

const boost::optional<dogen::sml::qname>& relationships::visitor() const {
    return visitor_;
}

boost::optional<dogen::sml::qname>& relationships::visitor() {
    return visitor_;
}

void relationships::visitor(const boost::optional<dogen::sml::qname>& v) {
    visitor_ = v;
}

void relationships::visitor(const boost::optional<dogen::sml::qname>&& v) {
    visitor_ = std::move(v);
}

} }