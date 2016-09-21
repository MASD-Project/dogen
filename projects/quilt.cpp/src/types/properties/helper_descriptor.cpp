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

helper_descriptor::helper_descriptor()
    : is_simple_type_(static_cast<bool>(0)),
      requires_hashing_helper_(static_cast<bool>(0)),
      is_circular_dependency_(static_cast<bool>(0)),
      is_pointer_(static_cast<bool>(0)) { }

helper_descriptor::helper_descriptor(helper_descriptor&& rhs)
    : namespaces_(std::move(rhs.namespaces_)),
      name_identifiable_(std::move(rhs.name_identifiable_)),
      name_qualified_(std::move(rhs.name_qualified_)),
      name_tree_qualified_(std::move(rhs.name_tree_qualified_)),
      name_tree_identifiable_(std::move(rhs.name_tree_identifiable_)),
      helper_annotations_(std::move(rhs.helper_annotations_)),
      streaming_annotations_(std::move(rhs.streaming_annotations_)),
      is_simple_type_(std::move(rhs.is_simple_type_)),
      requires_hashing_helper_(std::move(rhs.requires_hashing_helper_)),
      is_circular_dependency_(std::move(rhs.is_circular_dependency_)),
      is_pointer_(std::move(rhs.is_pointer_)) { }

helper_descriptor::helper_descriptor(
    const std::list<std::string>& namespaces,
    const std::string& name_identifiable,
    const std::string& name_qualified,
    const std::string& name_tree_qualified,
    const std::string& name_tree_identifiable,
    const dogen::quilt::cpp::annotations::helper_annotations& helper_annotations,
    const boost::optional<dogen::quilt::cpp::annotations::streaming_annotations>& streaming_annotations,
    const bool is_simple_type,
    const bool requires_hashing_helper,
    const bool is_circular_dependency,
    const bool is_pointer)
    : namespaces_(namespaces),
      name_identifiable_(name_identifiable),
      name_qualified_(name_qualified),
      name_tree_qualified_(name_tree_qualified),
      name_tree_identifiable_(name_tree_identifiable),
      helper_annotations_(helper_annotations),
      streaming_annotations_(streaming_annotations),
      is_simple_type_(is_simple_type),
      requires_hashing_helper_(requires_hashing_helper),
      is_circular_dependency_(is_circular_dependency),
      is_pointer_(is_pointer) { }

void helper_descriptor::swap(helper_descriptor& other) noexcept {
    using std::swap;
    swap(namespaces_, other.namespaces_);
    swap(name_identifiable_, other.name_identifiable_);
    swap(name_qualified_, other.name_qualified_);
    swap(name_tree_qualified_, other.name_tree_qualified_);
    swap(name_tree_identifiable_, other.name_tree_identifiable_);
    swap(helper_annotations_, other.helper_annotations_);
    swap(streaming_annotations_, other.streaming_annotations_);
    swap(is_simple_type_, other.is_simple_type_);
    swap(requires_hashing_helper_, other.requires_hashing_helper_);
    swap(is_circular_dependency_, other.is_circular_dependency_);
    swap(is_pointer_, other.is_pointer_);
}

bool helper_descriptor::operator==(const helper_descriptor& rhs) const {
    return namespaces_ == rhs.namespaces_ &&
        name_identifiable_ == rhs.name_identifiable_ &&
        name_qualified_ == rhs.name_qualified_ &&
        name_tree_qualified_ == rhs.name_tree_qualified_ &&
        name_tree_identifiable_ == rhs.name_tree_identifiable_ &&
        helper_annotations_ == rhs.helper_annotations_ &&
        streaming_annotations_ == rhs.streaming_annotations_ &&
        is_simple_type_ == rhs.is_simple_type_ &&
        requires_hashing_helper_ == rhs.requires_hashing_helper_ &&
        is_circular_dependency_ == rhs.is_circular_dependency_ &&
        is_pointer_ == rhs.is_pointer_;
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

const dogen::quilt::cpp::annotations::helper_annotations& helper_descriptor::helper_annotations() const {
    return helper_annotations_;
}

dogen::quilt::cpp::annotations::helper_annotations& helper_descriptor::helper_annotations() {
    return helper_annotations_;
}

void helper_descriptor::helper_annotations(const dogen::quilt::cpp::annotations::helper_annotations& v) {
    helper_annotations_ = v;
}

void helper_descriptor::helper_annotations(const dogen::quilt::cpp::annotations::helper_annotations&& v) {
    helper_annotations_ = std::move(v);
}

const boost::optional<dogen::quilt::cpp::annotations::streaming_annotations>& helper_descriptor::streaming_annotations() const {
    return streaming_annotations_;
}

boost::optional<dogen::quilt::cpp::annotations::streaming_annotations>& helper_descriptor::streaming_annotations() {
    return streaming_annotations_;
}

void helper_descriptor::streaming_annotations(const boost::optional<dogen::quilt::cpp::annotations::streaming_annotations>& v) {
    streaming_annotations_ = v;
}

void helper_descriptor::streaming_annotations(const boost::optional<dogen::quilt::cpp::annotations::streaming_annotations>&& v) {
    streaming_annotations_ = std::move(v);
}

bool helper_descriptor::is_simple_type() const {
    return is_simple_type_;
}

void helper_descriptor::is_simple_type(const bool v) {
    is_simple_type_ = v;
}

bool helper_descriptor::requires_hashing_helper() const {
    return requires_hashing_helper_;
}

void helper_descriptor::requires_hashing_helper(const bool v) {
    requires_hashing_helper_ = v;
}

bool helper_descriptor::is_circular_dependency() const {
    return is_circular_dependency_;
}

void helper_descriptor::is_circular_dependency(const bool v) {
    is_circular_dependency_ = v;
}

bool helper_descriptor::is_pointer() const {
    return is_pointer_;
}

void helper_descriptor::is_pointer(const bool v) {
    is_pointer_ = v;
}

} } } }
