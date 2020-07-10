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
#include "dogen.physical/types/entities/artefact_repository.hpp"

namespace dogen::physical::entities {

artefact_repository::artefact_repository(
    const std::unordered_map<std::string, dogen::physical::entities::artefact_set>& artefact_sets_by_logical_id,
    const std::string& identifier,
    const dogen::physical::entities::extraction_properties& extraction_properties,
    const dogen::physical::entities::global_enablement_properties& global_enablement_properties,
    const std::unordered_set<dogen::physical::entities::element_archetype>& enabled_archetype_for_element,
    const std::list<boost::filesystem::path>& managed_directories)
    : artefact_sets_by_logical_id_(artefact_sets_by_logical_id),
      identifier_(identifier),
      extraction_properties_(extraction_properties),
      global_enablement_properties_(global_enablement_properties),
      enabled_archetype_for_element_(enabled_archetype_for_element),
      managed_directories_(managed_directories) { }

void artefact_repository::swap(artefact_repository& other) noexcept {
    using std::swap;
    swap(artefact_sets_by_logical_id_, other.artefact_sets_by_logical_id_);
    swap(identifier_, other.identifier_);
    swap(extraction_properties_, other.extraction_properties_);
    swap(global_enablement_properties_, other.global_enablement_properties_);
    swap(enabled_archetype_for_element_, other.enabled_archetype_for_element_);
    swap(managed_directories_, other.managed_directories_);
}

bool artefact_repository::operator==(const artefact_repository& rhs) const {
    return artefact_sets_by_logical_id_ == rhs.artefact_sets_by_logical_id_ &&
        identifier_ == rhs.identifier_ &&
        extraction_properties_ == rhs.extraction_properties_ &&
        global_enablement_properties_ == rhs.global_enablement_properties_ &&
        enabled_archetype_for_element_ == rhs.enabled_archetype_for_element_ &&
        managed_directories_ == rhs.managed_directories_;
}

artefact_repository& artefact_repository::operator=(artefact_repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, dogen::physical::entities::artefact_set>& artefact_repository::artefact_sets_by_logical_id() const {
    return artefact_sets_by_logical_id_;
}

std::unordered_map<std::string, dogen::physical::entities::artefact_set>& artefact_repository::artefact_sets_by_logical_id() {
    return artefact_sets_by_logical_id_;
}

void artefact_repository::artefact_sets_by_logical_id(const std::unordered_map<std::string, dogen::physical::entities::artefact_set>& v) {
    artefact_sets_by_logical_id_ = v;
}

void artefact_repository::artefact_sets_by_logical_id(const std::unordered_map<std::string, dogen::physical::entities::artefact_set>&& v) {
    artefact_sets_by_logical_id_ = std::move(v);
}

const std::string& artefact_repository::identifier() const {
    return identifier_;
}

std::string& artefact_repository::identifier() {
    return identifier_;
}

void artefact_repository::identifier(const std::string& v) {
    identifier_ = v;
}

void artefact_repository::identifier(const std::string&& v) {
    identifier_ = std::move(v);
}

const dogen::physical::entities::extraction_properties& artefact_repository::extraction_properties() const {
    return extraction_properties_;
}

dogen::physical::entities::extraction_properties& artefact_repository::extraction_properties() {
    return extraction_properties_;
}

void artefact_repository::extraction_properties(const dogen::physical::entities::extraction_properties& v) {
    extraction_properties_ = v;
}

void artefact_repository::extraction_properties(const dogen::physical::entities::extraction_properties&& v) {
    extraction_properties_ = std::move(v);
}

const dogen::physical::entities::global_enablement_properties& artefact_repository::global_enablement_properties() const {
    return global_enablement_properties_;
}

dogen::physical::entities::global_enablement_properties& artefact_repository::global_enablement_properties() {
    return global_enablement_properties_;
}

void artefact_repository::global_enablement_properties(const dogen::physical::entities::global_enablement_properties& v) {
    global_enablement_properties_ = v;
}

void artefact_repository::global_enablement_properties(const dogen::physical::entities::global_enablement_properties&& v) {
    global_enablement_properties_ = std::move(v);
}

const std::unordered_set<dogen::physical::entities::element_archetype>& artefact_repository::enabled_archetype_for_element() const {
    return enabled_archetype_for_element_;
}

std::unordered_set<dogen::physical::entities::element_archetype>& artefact_repository::enabled_archetype_for_element() {
    return enabled_archetype_for_element_;
}

void artefact_repository::enabled_archetype_for_element(const std::unordered_set<dogen::physical::entities::element_archetype>& v) {
    enabled_archetype_for_element_ = v;
}

void artefact_repository::enabled_archetype_for_element(const std::unordered_set<dogen::physical::entities::element_archetype>&& v) {
    enabled_archetype_for_element_ = std::move(v);
}

const std::list<boost::filesystem::path>& artefact_repository::managed_directories() const {
    return managed_directories_;
}

std::list<boost::filesystem::path>& artefact_repository::managed_directories() {
    return managed_directories_;
}

void artefact_repository::managed_directories(const std::list<boost::filesystem::path>& v) {
    managed_directories_ = v;
}

void artefact_repository::managed_directories(const std::list<boost::filesystem::path>&& v) {
    managed_directories_ = std::move(v);
}

}
