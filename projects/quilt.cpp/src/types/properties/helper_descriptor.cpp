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
    : is_primitive_(static_cast<bool>(0)) { }

helper_descriptor::helper_descriptor(helper_descriptor&& rhs)
    : namespaces_(std::move(rhs.namespaces_)),
      name_identifiable_(std::move(rhs.name_identifiable_)),
      name_qualified_(std::move(rhs.name_qualified_)),
      name_tree_qualified_(std::move(rhs.name_tree_qualified_)),
      name_tree_identifiable_(std::move(rhs.name_tree_identifiable_)),
      helper_settings_(std::move(rhs.helper_settings_)),
      streaming_settings_(std::move(rhs.streaming_settings_)),
      is_primitive_(std::move(rhs.is_primitive_)) { }

helper_descriptor::helper_descriptor(
    const std::list<std::string>& namespaces,
    const std::string& name_identifiable,
    const std::string& name_qualified,
    const std::string& name_tree_qualified,
    const std::string& name_tree_identifiable,
    const boost::optional<dogen::quilt::cpp::settings::helper_settings>& helper_settings,
    const boost::optional<dogen::quilt::cpp::settings::streaming_settings>& streaming_settings,
    const bool is_primitive)
    : namespaces_(namespaces),
      name_identifiable_(name_identifiable),
      name_qualified_(name_qualified),
      name_tree_qualified_(name_tree_qualified),
      name_tree_identifiable_(name_tree_identifiable),
      helper_settings_(helper_settings),
      streaming_settings_(streaming_settings),
      is_primitive_(is_primitive) { }

void helper_descriptor::swap(helper_descriptor& other) noexcept {
    using std::swap;
    swap(namespaces_, other.namespaces_);
    swap(name_identifiable_, other.name_identifiable_);
    swap(name_qualified_, other.name_qualified_);
    swap(name_tree_qualified_, other.name_tree_qualified_);
    swap(name_tree_identifiable_, other.name_tree_identifiable_);
    swap(helper_settings_, other.helper_settings_);
    swap(streaming_settings_, other.streaming_settings_);
    swap(is_primitive_, other.is_primitive_);
}

bool helper_descriptor::operator==(const helper_descriptor& rhs) const {
    return namespaces_ == rhs.namespaces_ &&
        name_identifiable_ == rhs.name_identifiable_ &&
        name_qualified_ == rhs.name_qualified_ &&
        name_tree_qualified_ == rhs.name_tree_qualified_ &&
        name_tree_identifiable_ == rhs.name_tree_identifiable_ &&
        helper_settings_ == rhs.helper_settings_ &&
        streaming_settings_ == rhs.streaming_settings_ &&
        is_primitive_ == rhs.is_primitive_;
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

const boost::optional<dogen::quilt::cpp::settings::helper_settings>& helper_descriptor::helper_settings() const {
    return helper_settings_;
}

boost::optional<dogen::quilt::cpp::settings::helper_settings>& helper_descriptor::helper_settings() {
    return helper_settings_;
}

void helper_descriptor::helper_settings(const boost::optional<dogen::quilt::cpp::settings::helper_settings>& v) {
    helper_settings_ = v;
}

void helper_descriptor::helper_settings(const boost::optional<dogen::quilt::cpp::settings::helper_settings>&& v) {
    helper_settings_ = std::move(v);
}

const boost::optional<dogen::quilt::cpp::settings::streaming_settings>& helper_descriptor::streaming_settings() const {
    return streaming_settings_;
}

boost::optional<dogen::quilt::cpp::settings::streaming_settings>& helper_descriptor::streaming_settings() {
    return streaming_settings_;
}

void helper_descriptor::streaming_settings(const boost::optional<dogen::quilt::cpp::settings::streaming_settings>& v) {
    streaming_settings_ = v;
}

void helper_descriptor::streaming_settings(const boost::optional<dogen::quilt::cpp::settings::streaming_settings>&& v) {
    streaming_settings_ = std::move(v);
}

bool helper_descriptor::is_primitive() const {
    return is_primitive_;
}

void helper_descriptor::is_primitive(const bool v) {
    is_primitive_ = v;
}

} } } }
