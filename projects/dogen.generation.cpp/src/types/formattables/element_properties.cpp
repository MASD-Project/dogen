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
#include "dogen.generation.cpp/types/formattables/element_properties.hpp"

namespace dogen::generation::cpp::formattables {

element_properties::element_properties(
    const dogen::generation::cpp::formattables::aspect_properties& aspect_properties,
    const std::unordered_map<std::string, dogen::generation::cpp::formattables::artefact_properties>& artefact_properties,
    const std::list<dogen::generation::cpp::formattables::helper_properties>& helper_properties,
    const std::unordered_map<std::string, std::string>& canonical_archetype_to_archetype,
    const std::unordered_map<std::string, dogen::generation::cpp::formattables::test_data_properties>& attribute_level_test_data_properties)
    : aspect_properties_(aspect_properties),
      artefact_properties_(artefact_properties),
      helper_properties_(helper_properties),
      canonical_archetype_to_archetype_(canonical_archetype_to_archetype),
      attribute_level_test_data_properties_(attribute_level_test_data_properties) { }

void element_properties::swap(element_properties& other) noexcept {
    using std::swap;
    swap(aspect_properties_, other.aspect_properties_);
    swap(artefact_properties_, other.artefact_properties_);
    swap(helper_properties_, other.helper_properties_);
    swap(canonical_archetype_to_archetype_, other.canonical_archetype_to_archetype_);
    swap(attribute_level_test_data_properties_, other.attribute_level_test_data_properties_);
}

bool element_properties::operator==(const element_properties& rhs) const {
    return aspect_properties_ == rhs.aspect_properties_ &&
        artefact_properties_ == rhs.artefact_properties_ &&
        helper_properties_ == rhs.helper_properties_ &&
        canonical_archetype_to_archetype_ == rhs.canonical_archetype_to_archetype_ &&
        attribute_level_test_data_properties_ == rhs.attribute_level_test_data_properties_;
}

element_properties& element_properties::operator=(element_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::generation::cpp::formattables::aspect_properties& element_properties::aspect_properties() const {
    return aspect_properties_;
}

dogen::generation::cpp::formattables::aspect_properties& element_properties::aspect_properties() {
    return aspect_properties_;
}

void element_properties::aspect_properties(const dogen::generation::cpp::formattables::aspect_properties& v) {
    aspect_properties_ = v;
}

void element_properties::aspect_properties(const dogen::generation::cpp::formattables::aspect_properties&& v) {
    aspect_properties_ = std::move(v);
}

const std::unordered_map<std::string, dogen::generation::cpp::formattables::artefact_properties>& element_properties::artefact_properties() const {
    return artefact_properties_;
}

std::unordered_map<std::string, dogen::generation::cpp::formattables::artefact_properties>& element_properties::artefact_properties() {
    return artefact_properties_;
}

void element_properties::artefact_properties(const std::unordered_map<std::string, dogen::generation::cpp::formattables::artefact_properties>& v) {
    artefact_properties_ = v;
}

void element_properties::artefact_properties(const std::unordered_map<std::string, dogen::generation::cpp::formattables::artefact_properties>&& v) {
    artefact_properties_ = std::move(v);
}

const std::list<dogen::generation::cpp::formattables::helper_properties>& element_properties::helper_properties() const {
    return helper_properties_;
}

std::list<dogen::generation::cpp::formattables::helper_properties>& element_properties::helper_properties() {
    return helper_properties_;
}

void element_properties::helper_properties(const std::list<dogen::generation::cpp::formattables::helper_properties>& v) {
    helper_properties_ = v;
}

void element_properties::helper_properties(const std::list<dogen::generation::cpp::formattables::helper_properties>&& v) {
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

const std::unordered_map<std::string, dogen::generation::cpp::formattables::test_data_properties>& element_properties::attribute_level_test_data_properties() const {
    return attribute_level_test_data_properties_;
}

std::unordered_map<std::string, dogen::generation::cpp::formattables::test_data_properties>& element_properties::attribute_level_test_data_properties() {
    return attribute_level_test_data_properties_;
}

void element_properties::attribute_level_test_data_properties(const std::unordered_map<std::string, dogen::generation::cpp::formattables::test_data_properties>& v) {
    attribute_level_test_data_properties_ = v;
}

void element_properties::attribute_level_test_data_properties(const std::unordered_map<std::string, dogen::generation::cpp::formattables::test_data_properties>&& v) {
    attribute_level_test_data_properties_ = std::move(v);
}

}
