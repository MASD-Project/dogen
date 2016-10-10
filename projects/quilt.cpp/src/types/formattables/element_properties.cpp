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
#include "dogen/quilt.cpp/types/formattables/element_properties.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

element_properties::element_properties(element_properties&& rhs)
    : decoration_configuration_(std::move(rhs.decoration_configuration_)),
      aspect_properties_(std::move(rhs.aspect_properties_)),
      formatter_configurations_(std::move(rhs.formatter_configurations_)),
      helper_configurations_(std::move(rhs.helper_configurations_)),
      canonical_formatter_to_formatter_(std::move(rhs.canonical_formatter_to_formatter_)),
      local_profile_group_(std::move(rhs.local_profile_group_)),
      odb_configuration_(std::move(rhs.odb_configuration_)) { }

element_properties::element_properties(
    const boost::optional<dogen::formatters::decoration_configuration>& decoration_configuration,
    const dogen::quilt::cpp::formattables::aspect_properties& aspect_properties,
    const std::unordered_map<std::string, dogen::quilt::cpp::formattables::formatter_configuration>& formatter_configurations,
    const std::list<dogen::quilt::cpp::formattables::helper_configuration>& helper_configurations,
    const std::unordered_map<std::string, std::string>& canonical_formatter_to_formatter,
    const boost::optional<dogen::quilt::cpp::formattables::profile_group>& local_profile_group,
    const boost::optional<dogen::quilt::cpp::formattables::odb_configuration>& odb_configuration)
    : decoration_configuration_(decoration_configuration),
      aspect_properties_(aspect_properties),
      formatter_configurations_(formatter_configurations),
      helper_configurations_(helper_configurations),
      canonical_formatter_to_formatter_(canonical_formatter_to_formatter),
      local_profile_group_(local_profile_group),
      odb_configuration_(odb_configuration) { }

void element_properties::swap(element_properties& other) noexcept {
    using std::swap;
    swap(decoration_configuration_, other.decoration_configuration_);
    swap(aspect_properties_, other.aspect_properties_);
    swap(formatter_configurations_, other.formatter_configurations_);
    swap(helper_configurations_, other.helper_configurations_);
    swap(canonical_formatter_to_formatter_, other.canonical_formatter_to_formatter_);
    swap(local_profile_group_, other.local_profile_group_);
    swap(odb_configuration_, other.odb_configuration_);
}

bool element_properties::operator==(const element_properties& rhs) const {
    return decoration_configuration_ == rhs.decoration_configuration_ &&
        aspect_properties_ == rhs.aspect_properties_ &&
        formatter_configurations_ == rhs.formatter_configurations_ &&
        helper_configurations_ == rhs.helper_configurations_ &&
        canonical_formatter_to_formatter_ == rhs.canonical_formatter_to_formatter_ &&
        local_profile_group_ == rhs.local_profile_group_ &&
        odb_configuration_ == rhs.odb_configuration_;
}

element_properties& element_properties::operator=(element_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::optional<dogen::formatters::decoration_configuration>& element_properties::decoration_configuration() const {
    return decoration_configuration_;
}

boost::optional<dogen::formatters::decoration_configuration>& element_properties::decoration_configuration() {
    return decoration_configuration_;
}

void element_properties::decoration_configuration(const boost::optional<dogen::formatters::decoration_configuration>& v) {
    decoration_configuration_ = v;
}

void element_properties::decoration_configuration(const boost::optional<dogen::formatters::decoration_configuration>&& v) {
    decoration_configuration_ = std::move(v);
}

const dogen::quilt::cpp::formattables::aspect_properties& element_properties::aspect_properties() const {
    return aspect_properties_;
}

dogen::quilt::cpp::formattables::aspect_properties& element_properties::aspect_properties() {
    return aspect_properties_;
}

void element_properties::aspect_properties(const dogen::quilt::cpp::formattables::aspect_properties& v) {
    aspect_properties_ = v;
}

void element_properties::aspect_properties(const dogen::quilt::cpp::formattables::aspect_properties&& v) {
    aspect_properties_ = std::move(v);
}

const std::unordered_map<std::string, dogen::quilt::cpp::formattables::formatter_configuration>& element_properties::formatter_configurations() const {
    return formatter_configurations_;
}

std::unordered_map<std::string, dogen::quilt::cpp::formattables::formatter_configuration>& element_properties::formatter_configurations() {
    return formatter_configurations_;
}

void element_properties::formatter_configurations(const std::unordered_map<std::string, dogen::quilt::cpp::formattables::formatter_configuration>& v) {
    formatter_configurations_ = v;
}

void element_properties::formatter_configurations(const std::unordered_map<std::string, dogen::quilt::cpp::formattables::formatter_configuration>&& v) {
    formatter_configurations_ = std::move(v);
}

const std::list<dogen::quilt::cpp::formattables::helper_configuration>& element_properties::helper_configurations() const {
    return helper_configurations_;
}

std::list<dogen::quilt::cpp::formattables::helper_configuration>& element_properties::helper_configurations() {
    return helper_configurations_;
}

void element_properties::helper_configurations(const std::list<dogen::quilt::cpp::formattables::helper_configuration>& v) {
    helper_configurations_ = v;
}

void element_properties::helper_configurations(const std::list<dogen::quilt::cpp::formattables::helper_configuration>&& v) {
    helper_configurations_ = std::move(v);
}

const std::unordered_map<std::string, std::string>& element_properties::canonical_formatter_to_formatter() const {
    return canonical_formatter_to_formatter_;
}

std::unordered_map<std::string, std::string>& element_properties::canonical_formatter_to_formatter() {
    return canonical_formatter_to_formatter_;
}

void element_properties::canonical_formatter_to_formatter(const std::unordered_map<std::string, std::string>& v) {
    canonical_formatter_to_formatter_ = v;
}

void element_properties::canonical_formatter_to_formatter(const std::unordered_map<std::string, std::string>&& v) {
    canonical_formatter_to_formatter_ = std::move(v);
}

const boost::optional<dogen::quilt::cpp::formattables::profile_group>& element_properties::local_profile_group() const {
    return local_profile_group_;
}

boost::optional<dogen::quilt::cpp::formattables::profile_group>& element_properties::local_profile_group() {
    return local_profile_group_;
}

void element_properties::local_profile_group(const boost::optional<dogen::quilt::cpp::formattables::profile_group>& v) {
    local_profile_group_ = v;
}

void element_properties::local_profile_group(const boost::optional<dogen::quilt::cpp::formattables::profile_group>&& v) {
    local_profile_group_ = std::move(v);
}

const boost::optional<dogen::quilt::cpp::formattables::odb_configuration>& element_properties::odb_configuration() const {
    return odb_configuration_;
}

boost::optional<dogen::quilt::cpp::formattables::odb_configuration>& element_properties::odb_configuration() {
    return odb_configuration_;
}

void element_properties::odb_configuration(const boost::optional<dogen::quilt::cpp::formattables::odb_configuration>& v) {
    odb_configuration_ = v;
}

void element_properties::odb_configuration(const boost::optional<dogen::quilt::cpp::formattables::odb_configuration>&& v) {
    odb_configuration_ = std::move(v);
}

} } } }
