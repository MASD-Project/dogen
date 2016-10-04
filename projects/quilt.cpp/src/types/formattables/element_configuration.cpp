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
#include "dogen/quilt.cpp/types/formattables/element_configuration.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

element_configuration::element_configuration(element_configuration&& rhs)
    : decoration_configuration_(std::move(rhs.decoration_configuration_)),
      aspect_configuration_(std::move(rhs.aspect_configuration_)),
      formatter_configurations_(std::move(rhs.formatter_configurations_)),
      helper_configurations_(std::move(rhs.helper_configurations_)),
      canonical_formatter_to_formatter_(std::move(rhs.canonical_formatter_to_formatter_)) { }

element_configuration::element_configuration(
    const boost::optional<dogen::formatters::decoration_configuration>& decoration_configuration,
    const dogen::quilt::cpp::formattables::aspect_configuration& aspect_configuration,
    const std::unordered_map<std::string, dogen::quilt::cpp::formattables::formatter_configuration>& formatter_configurations,
    const std::list<dogen::quilt::cpp::formattables::helper_configuration>& helper_configurations,
    const std::unordered_map<std::string, std::string>& canonical_formatter_to_formatter)
    : decoration_configuration_(decoration_configuration),
      aspect_configuration_(aspect_configuration),
      formatter_configurations_(formatter_configurations),
      helper_configurations_(helper_configurations),
      canonical_formatter_to_formatter_(canonical_formatter_to_formatter) { }

void element_configuration::swap(element_configuration& other) noexcept {
    using std::swap;
    swap(decoration_configuration_, other.decoration_configuration_);
    swap(aspect_configuration_, other.aspect_configuration_);
    swap(formatter_configurations_, other.formatter_configurations_);
    swap(helper_configurations_, other.helper_configurations_);
    swap(canonical_formatter_to_formatter_, other.canonical_formatter_to_formatter_);
}

bool element_configuration::operator==(const element_configuration& rhs) const {
    return decoration_configuration_ == rhs.decoration_configuration_ &&
        aspect_configuration_ == rhs.aspect_configuration_ &&
        formatter_configurations_ == rhs.formatter_configurations_ &&
        helper_configurations_ == rhs.helper_configurations_ &&
        canonical_formatter_to_formatter_ == rhs.canonical_formatter_to_formatter_;
}

element_configuration& element_configuration::operator=(element_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::optional<dogen::formatters::decoration_configuration>& element_configuration::decoration_configuration() const {
    return decoration_configuration_;
}

boost::optional<dogen::formatters::decoration_configuration>& element_configuration::decoration_configuration() {
    return decoration_configuration_;
}

void element_configuration::decoration_configuration(const boost::optional<dogen::formatters::decoration_configuration>& v) {
    decoration_configuration_ = v;
}

void element_configuration::decoration_configuration(const boost::optional<dogen::formatters::decoration_configuration>&& v) {
    decoration_configuration_ = std::move(v);
}

const dogen::quilt::cpp::formattables::aspect_configuration& element_configuration::aspect_configuration() const {
    return aspect_configuration_;
}

dogen::quilt::cpp::formattables::aspect_configuration& element_configuration::aspect_configuration() {
    return aspect_configuration_;
}

void element_configuration::aspect_configuration(const dogen::quilt::cpp::formattables::aspect_configuration& v) {
    aspect_configuration_ = v;
}

void element_configuration::aspect_configuration(const dogen::quilt::cpp::formattables::aspect_configuration&& v) {
    aspect_configuration_ = std::move(v);
}

const std::unordered_map<std::string, dogen::quilt::cpp::formattables::formatter_configuration>& element_configuration::formatter_configurations() const {
    return formatter_configurations_;
}

std::unordered_map<std::string, dogen::quilt::cpp::formattables::formatter_configuration>& element_configuration::formatter_configurations() {
    return formatter_configurations_;
}

void element_configuration::formatter_configurations(const std::unordered_map<std::string, dogen::quilt::cpp::formattables::formatter_configuration>& v) {
    formatter_configurations_ = v;
}

void element_configuration::formatter_configurations(const std::unordered_map<std::string, dogen::quilt::cpp::formattables::formatter_configuration>&& v) {
    formatter_configurations_ = std::move(v);
}

const std::list<dogen::quilt::cpp::formattables::helper_configuration>& element_configuration::helper_configurations() const {
    return helper_configurations_;
}

std::list<dogen::quilt::cpp::formattables::helper_configuration>& element_configuration::helper_configurations() {
    return helper_configurations_;
}

void element_configuration::helper_configurations(const std::list<dogen::quilt::cpp::formattables::helper_configuration>& v) {
    helper_configurations_ = v;
}

void element_configuration::helper_configurations(const std::list<dogen::quilt::cpp::formattables::helper_configuration>&& v) {
    helper_configurations_ = std::move(v);
}

const std::unordered_map<std::string, std::string>& element_configuration::canonical_formatter_to_formatter() const {
    return canonical_formatter_to_formatter_;
}

std::unordered_map<std::string, std::string>& element_configuration::canonical_formatter_to_formatter() {
    return canonical_formatter_to_formatter_;
}

void element_configuration::canonical_formatter_to_formatter(const std::unordered_map<std::string, std::string>& v) {
    canonical_formatter_to_formatter_ = v;
}

void element_configuration::canonical_formatter_to_formatter(const std::unordered_map<std::string, std::string>&& v) {
    canonical_formatter_to_formatter_ = std::move(v);
}

} } } }
