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
#include "dogen.text/types/entities/model.hpp"

namespace dogen::text::entities {

model::model()
    : has_generatable_types_(static_cast<bool>(0)) { }

model::model(
    const dogen::identification::entities::logical_provenance& provenance,
    const std::list<dogen::text::entities::element_artefacts>& elements,
    const bool has_generatable_types,
    const std::unordered_set<dogen::identification::entities::logical_meta_physical_id>& enabled_archetype_for_element,
    const dogen::physical::entities::extraction_properties& extraction_properties,
    const std::list<boost::filesystem::path>& managed_directories,
    const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet_properties>& facet_properties,
    const dogen::logical::entities::model& logical)
    : provenance_(provenance),
      elements_(elements),
      has_generatable_types_(has_generatable_types),
      enabled_archetype_for_element_(enabled_archetype_for_element),
      extraction_properties_(extraction_properties),
      managed_directories_(managed_directories),
      facet_properties_(facet_properties),
      logical_(logical) { }

void model::swap(model& other) noexcept {
    using std::swap;
    swap(provenance_, other.provenance_);
    swap(elements_, other.elements_);
    swap(has_generatable_types_, other.has_generatable_types_);
    swap(enabled_archetype_for_element_, other.enabled_archetype_for_element_);
    swap(extraction_properties_, other.extraction_properties_);
    swap(managed_directories_, other.managed_directories_);
    swap(facet_properties_, other.facet_properties_);
    swap(logical_, other.logical_);
}

bool model::operator==(const model& rhs) const {
    return provenance_ == rhs.provenance_ &&
        elements_ == rhs.elements_ &&
        has_generatable_types_ == rhs.has_generatable_types_ &&
        enabled_archetype_for_element_ == rhs.enabled_archetype_for_element_ &&
        extraction_properties_ == rhs.extraction_properties_ &&
        managed_directories_ == rhs.managed_directories_ &&
        facet_properties_ == rhs.facet_properties_ &&
        logical_ == rhs.logical_;
}

model& model::operator=(model other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::identification::entities::logical_provenance& model::provenance() const {
    return provenance_;
}

dogen::identification::entities::logical_provenance& model::provenance() {
    return provenance_;
}

void model::provenance(const dogen::identification::entities::logical_provenance& v) {
    provenance_ = v;
}

void model::provenance(const dogen::identification::entities::logical_provenance&& v) {
    provenance_ = std::move(v);
}

const std::list<dogen::text::entities::element_artefacts>& model::elements() const {
    return elements_;
}

std::list<dogen::text::entities::element_artefacts>& model::elements() {
    return elements_;
}

void model::elements(const std::list<dogen::text::entities::element_artefacts>& v) {
    elements_ = v;
}

void model::elements(const std::list<dogen::text::entities::element_artefacts>&& v) {
    elements_ = std::move(v);
}

bool model::has_generatable_types() const {
    return has_generatable_types_;
}

void model::has_generatable_types(const bool v) {
    has_generatable_types_ = v;
}

const std::unordered_set<dogen::identification::entities::logical_meta_physical_id>& model::enabled_archetype_for_element() const {
    return enabled_archetype_for_element_;
}

std::unordered_set<dogen::identification::entities::logical_meta_physical_id>& model::enabled_archetype_for_element() {
    return enabled_archetype_for_element_;
}

void model::enabled_archetype_for_element(const std::unordered_set<dogen::identification::entities::logical_meta_physical_id>& v) {
    enabled_archetype_for_element_ = v;
}

void model::enabled_archetype_for_element(const std::unordered_set<dogen::identification::entities::logical_meta_physical_id>&& v) {
    enabled_archetype_for_element_ = std::move(v);
}

const dogen::physical::entities::extraction_properties& model::extraction_properties() const {
    return extraction_properties_;
}

dogen::physical::entities::extraction_properties& model::extraction_properties() {
    return extraction_properties_;
}

void model::extraction_properties(const dogen::physical::entities::extraction_properties& v) {
    extraction_properties_ = v;
}

void model::extraction_properties(const dogen::physical::entities::extraction_properties&& v) {
    extraction_properties_ = std::move(v);
}

const std::list<boost::filesystem::path>& model::managed_directories() const {
    return managed_directories_;
}

std::list<boost::filesystem::path>& model::managed_directories() {
    return managed_directories_;
}

void model::managed_directories(const std::list<boost::filesystem::path>& v) {
    managed_directories_ = v;
}

void model::managed_directories(const std::list<boost::filesystem::path>&& v) {
    managed_directories_ = std::move(v);
}

const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet_properties>& model::facet_properties() const {
    return facet_properties_;
}

std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet_properties>& model::facet_properties() {
    return facet_properties_;
}

void model::facet_properties(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet_properties>& v) {
    facet_properties_ = v;
}

void model::facet_properties(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet_properties>&& v) {
    facet_properties_ = std::move(v);
}

const dogen::logical::entities::model& model::logical() const {
    return logical_;
}

dogen::logical::entities::model& model::logical() {
    return logical_;
}

void model::logical(const dogen::logical::entities::model& v) {
    logical_ = v;
}

void model::logical(const dogen::logical::entities::model&& v) {
    logical_ = std::move(v);
}

}
