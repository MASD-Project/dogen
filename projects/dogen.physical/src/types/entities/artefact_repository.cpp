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

artefact_repository::artefact_repository()
    : has_generatable_artefacts_(static_cast<bool>(0)) { }

artefact_repository::artefact_repository(
    const dogen::identification::entities::logical_provenance& provenance,
    const std::unordered_map<dogen::identification::entities::logical_id, dogen::physical::entities::artefact_set>& artefact_sets_by_logical_id,
    const dogen::physical::entities::extraction_properties& extraction_properties,
    const std::unordered_set<dogen::identification::entities::logical_meta_physical_id>& enabled_archetype_for_element,
    const std::list<boost::filesystem::path>& managed_directories,
    const bool has_generatable_artefacts,
    const dogen::physical::entities::meta_model_properties& meta_model_properties)
    : provenance_(provenance),
      artefact_sets_by_logical_id_(artefact_sets_by_logical_id),
      extraction_properties_(extraction_properties),
      enabled_archetype_for_element_(enabled_archetype_for_element),
      managed_directories_(managed_directories),
      has_generatable_artefacts_(has_generatable_artefacts),
      meta_model_properties_(meta_model_properties) { }

void artefact_repository::swap(artefact_repository& other) noexcept {
    using std::swap;
    swap(provenance_, other.provenance_);
    swap(artefact_sets_by_logical_id_, other.artefact_sets_by_logical_id_);
    swap(extraction_properties_, other.extraction_properties_);
    swap(enabled_archetype_for_element_, other.enabled_archetype_for_element_);
    swap(managed_directories_, other.managed_directories_);
    swap(has_generatable_artefacts_, other.has_generatable_artefacts_);
    swap(meta_model_properties_, other.meta_model_properties_);
}

bool artefact_repository::operator==(const artefact_repository& rhs) const {
    return provenance_ == rhs.provenance_ &&
        artefact_sets_by_logical_id_ == rhs.artefact_sets_by_logical_id_ &&
        extraction_properties_ == rhs.extraction_properties_ &&
        enabled_archetype_for_element_ == rhs.enabled_archetype_for_element_ &&
        managed_directories_ == rhs.managed_directories_ &&
        has_generatable_artefacts_ == rhs.has_generatable_artefacts_ &&
        meta_model_properties_ == rhs.meta_model_properties_;
}

artefact_repository& artefact_repository::operator=(artefact_repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::identification::entities::logical_provenance& artefact_repository::provenance() const {
    return provenance_;
}

dogen::identification::entities::logical_provenance& artefact_repository::provenance() {
    return provenance_;
}

void artefact_repository::provenance(const dogen::identification::entities::logical_provenance& v) {
    provenance_ = v;
}

void artefact_repository::provenance(const dogen::identification::entities::logical_provenance&& v) {
    provenance_ = std::move(v);
}

const std::unordered_map<dogen::identification::entities::logical_id, dogen::physical::entities::artefact_set>& artefact_repository::artefact_sets_by_logical_id() const {
    return artefact_sets_by_logical_id_;
}

std::unordered_map<dogen::identification::entities::logical_id, dogen::physical::entities::artefact_set>& artefact_repository::artefact_sets_by_logical_id() {
    return artefact_sets_by_logical_id_;
}

void artefact_repository::artefact_sets_by_logical_id(const std::unordered_map<dogen::identification::entities::logical_id, dogen::physical::entities::artefact_set>& v) {
    artefact_sets_by_logical_id_ = v;
}

void artefact_repository::artefact_sets_by_logical_id(const std::unordered_map<dogen::identification::entities::logical_id, dogen::physical::entities::artefact_set>&& v) {
    artefact_sets_by_logical_id_ = std::move(v);
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

const std::unordered_set<dogen::identification::entities::logical_meta_physical_id>& artefact_repository::enabled_archetype_for_element() const {
    return enabled_archetype_for_element_;
}

std::unordered_set<dogen::identification::entities::logical_meta_physical_id>& artefact_repository::enabled_archetype_for_element() {
    return enabled_archetype_for_element_;
}

void artefact_repository::enabled_archetype_for_element(const std::unordered_set<dogen::identification::entities::logical_meta_physical_id>& v) {
    enabled_archetype_for_element_ = v;
}

void artefact_repository::enabled_archetype_for_element(const std::unordered_set<dogen::identification::entities::logical_meta_physical_id>&& v) {
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

bool artefact_repository::has_generatable_artefacts() const {
    return has_generatable_artefacts_;
}

void artefact_repository::has_generatable_artefacts(const bool v) {
    has_generatable_artefacts_ = v;
}

const dogen::physical::entities::meta_model_properties& artefact_repository::meta_model_properties() const {
    return meta_model_properties_;
}

dogen::physical::entities::meta_model_properties& artefact_repository::meta_model_properties() {
    return meta_model_properties_;
}

void artefact_repository::meta_model_properties(const dogen::physical::entities::meta_model_properties& v) {
    meta_model_properties_ = v;
}

void artefact_repository::meta_model_properties(const dogen::physical::entities::meta_model_properties&& v) {
    meta_model_properties_ = std::move(v);
}

}
