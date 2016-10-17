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
    : decoration_properties_(std::move(rhs.decoration_properties_)),
      aspect_properties_(std::move(rhs.aspect_properties_)),
      artefact_properties_(std::move(rhs.artefact_properties_)),
      helper_properties_(std::move(rhs.helper_properties_)),
      canonical_archetype_to_archetype_(std::move(rhs.canonical_archetype_to_archetype_)),
      odb_properties_(std::move(rhs.odb_properties_)) { }

element_properties::element_properties(
    const boost::optional<dogen::formatters::decoration_properties>& decoration_properties,
    const dogen::quilt::cpp::formattables::aspect_properties& aspect_properties,
    const std::unordered_map<std::string, dogen::quilt::cpp::formattables::artefact_properties>& artefact_properties,
    const std::list<dogen::quilt::cpp::formattables::helper_properties>& helper_properties,
    const std::unordered_map<std::string, std::string>& canonical_archetype_to_archetype,
    const boost::optional<dogen::quilt::cpp::formattables::odb_properties>& odb_properties)
    : decoration_properties_(decoration_properties),
      aspect_properties_(aspect_properties),
      artefact_properties_(artefact_properties),
      helper_properties_(helper_properties),
      canonical_archetype_to_archetype_(canonical_archetype_to_archetype),
      odb_properties_(odb_properties) { }

void element_properties::swap(element_properties& other) noexcept {
    using std::swap;
    swap(decoration_properties_, other.decoration_properties_);
    swap(aspect_properties_, other.aspect_properties_);
    swap(artefact_properties_, other.artefact_properties_);
    swap(helper_properties_, other.helper_properties_);
    swap(canonical_archetype_to_archetype_, other.canonical_archetype_to_archetype_);
    swap(odb_properties_, other.odb_properties_);
}

bool element_properties::operator==(const element_properties& rhs) const {
    return decoration_properties_ == rhs.decoration_properties_ &&
        aspect_properties_ == rhs.aspect_properties_ &&
        artefact_properties_ == rhs.artefact_properties_ &&
        helper_properties_ == rhs.helper_properties_ &&
        canonical_archetype_to_archetype_ == rhs.canonical_archetype_to_archetype_ &&
        odb_properties_ == rhs.odb_properties_;
}

element_properties& element_properties::operator=(element_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::optional<dogen::formatters::decoration_properties>& element_properties::decoration_properties() const {
    return decoration_properties_;
}

boost::optional<dogen::formatters::decoration_properties>& element_properties::decoration_properties() {
    return decoration_properties_;
}

void element_properties::decoration_properties(const boost::optional<dogen::formatters::decoration_properties>& v) {
    decoration_properties_ = v;
}

void element_properties::decoration_properties(const boost::optional<dogen::formatters::decoration_properties>&& v) {
    decoration_properties_ = std::move(v);
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

const std::unordered_map<std::string, dogen::quilt::cpp::formattables::artefact_properties>& element_properties::artefact_properties() const {
    return artefact_properties_;
}

std::unordered_map<std::string, dogen::quilt::cpp::formattables::artefact_properties>& element_properties::artefact_properties() {
    return artefact_properties_;
}

void element_properties::artefact_properties(const std::unordered_map<std::string, dogen::quilt::cpp::formattables::artefact_properties>& v) {
    artefact_properties_ = v;
}

void element_properties::artefact_properties(const std::unordered_map<std::string, dogen::quilt::cpp::formattables::artefact_properties>&& v) {
    artefact_properties_ = std::move(v);
}

const std::list<dogen::quilt::cpp::formattables::helper_properties>& element_properties::helper_properties() const {
    return helper_properties_;
}

std::list<dogen::quilt::cpp::formattables::helper_properties>& element_properties::helper_properties() {
    return helper_properties_;
}

void element_properties::helper_properties(const std::list<dogen::quilt::cpp::formattables::helper_properties>& v) {
    helper_properties_ = v;
}

void element_properties::helper_properties(const std::list<dogen::quilt::cpp::formattables::helper_properties>&& v) {
    helper_properties_ = std::move(v);
}

const std::unordered_map<std::string, std::string>& element_properties::canonical_archetype_to_archetype() const {
    return canonical_archetype_to_archetype_;
}

std::unordered_map<std::string, std::string>& element_properties::canonical_archetype_to_archetype() {
    return canonical_archetype_to_archetype_;
}

void element_properties::canonical_archetype_to_archetype(const std::unordered_map<std::string, std::string>& v) {
    canonical_archetype_to_archetype_ = v;
}

void element_properties::canonical_archetype_to_archetype(const std::unordered_map<std::string, std::string>&& v) {
    canonical_archetype_to_archetype_ = std::move(v);
}

const boost::optional<dogen::quilt::cpp::formattables::odb_properties>& element_properties::odb_properties() const {
    return odb_properties_;
}

boost::optional<dogen::quilt::cpp::formattables::odb_properties>& element_properties::odb_properties() {
    return odb_properties_;
}

void element_properties::odb_properties(const boost::optional<dogen::quilt::cpp::formattables::odb_properties>& v) {
    odb_properties_ = v;
}

void element_properties::odb_properties(const boost::optional<dogen::quilt::cpp::formattables::odb_properties>&& v) {
    odb_properties_ = std::move(v);
}

} } } }
