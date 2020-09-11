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
#include "dogen.physical/types/entities/meta_model_properties.hpp"

namespace dogen::physical::entities {

meta_model_properties::meta_model_properties(
    const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::backend_properties>& backend_properties,
    const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet_properties>& facet_properties,
    const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype_properties>& archetype_properties,
    const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype_kind_properties>& archetype_kind_properties,
    const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::part_properties>& part_properties,
    const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::denormalised_archetype_properties>& denormalised_archetype_enablement_properties)
    : backend_properties_(backend_properties),
      facet_properties_(facet_properties),
      archetype_properties_(archetype_properties),
      archetype_kind_properties_(archetype_kind_properties),
      part_properties_(part_properties),
      denormalised_archetype_enablement_properties_(denormalised_archetype_enablement_properties) { }

void meta_model_properties::swap(meta_model_properties& other) noexcept {
    using std::swap;
    swap(backend_properties_, other.backend_properties_);
    swap(facet_properties_, other.facet_properties_);
    swap(archetype_properties_, other.archetype_properties_);
    swap(archetype_kind_properties_, other.archetype_kind_properties_);
    swap(part_properties_, other.part_properties_);
    swap(denormalised_archetype_enablement_properties_, other.denormalised_archetype_enablement_properties_);
}

bool meta_model_properties::operator==(const meta_model_properties& rhs) const {
    return backend_properties_ == rhs.backend_properties_ &&
        facet_properties_ == rhs.facet_properties_ &&
        archetype_properties_ == rhs.archetype_properties_ &&
        archetype_kind_properties_ == rhs.archetype_kind_properties_ &&
        part_properties_ == rhs.part_properties_ &&
        denormalised_archetype_enablement_properties_ == rhs.denormalised_archetype_enablement_properties_;
}

meta_model_properties& meta_model_properties::operator=(meta_model_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::backend_properties>& meta_model_properties::backend_properties() const {
    return backend_properties_;
}

std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::backend_properties>& meta_model_properties::backend_properties() {
    return backend_properties_;
}

void meta_model_properties::backend_properties(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::backend_properties>& v) {
    backend_properties_ = v;
}

void meta_model_properties::backend_properties(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::backend_properties>&& v) {
    backend_properties_ = std::move(v);
}

const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet_properties>& meta_model_properties::facet_properties() const {
    return facet_properties_;
}

std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet_properties>& meta_model_properties::facet_properties() {
    return facet_properties_;
}

void meta_model_properties::facet_properties(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet_properties>& v) {
    facet_properties_ = v;
}

void meta_model_properties::facet_properties(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet_properties>&& v) {
    facet_properties_ = std::move(v);
}

const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype_properties>& meta_model_properties::archetype_properties() const {
    return archetype_properties_;
}

std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype_properties>& meta_model_properties::archetype_properties() {
    return archetype_properties_;
}

void meta_model_properties::archetype_properties(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype_properties>& v) {
    archetype_properties_ = v;
}

void meta_model_properties::archetype_properties(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype_properties>&& v) {
    archetype_properties_ = std::move(v);
}

const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype_kind_properties>& meta_model_properties::archetype_kind_properties() const {
    return archetype_kind_properties_;
}

std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype_kind_properties>& meta_model_properties::archetype_kind_properties() {
    return archetype_kind_properties_;
}

void meta_model_properties::archetype_kind_properties(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype_kind_properties>& v) {
    archetype_kind_properties_ = v;
}

void meta_model_properties::archetype_kind_properties(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype_kind_properties>&& v) {
    archetype_kind_properties_ = std::move(v);
}

const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::part_properties>& meta_model_properties::part_properties() const {
    return part_properties_;
}

std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::part_properties>& meta_model_properties::part_properties() {
    return part_properties_;
}

void meta_model_properties::part_properties(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::part_properties>& v) {
    part_properties_ = v;
}

void meta_model_properties::part_properties(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::part_properties>&& v) {
    part_properties_ = std::move(v);
}

const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::denormalised_archetype_properties>& meta_model_properties::denormalised_archetype_enablement_properties() const {
    return denormalised_archetype_enablement_properties_;
}

std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::denormalised_archetype_properties>& meta_model_properties::denormalised_archetype_enablement_properties() {
    return denormalised_archetype_enablement_properties_;
}

void meta_model_properties::denormalised_archetype_enablement_properties(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::denormalised_archetype_properties>& v) {
    denormalised_archetype_enablement_properties_ = v;
}

void meta_model_properties::denormalised_archetype_enablement_properties(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::denormalised_archetype_properties>&& v) {
    denormalised_archetype_enablement_properties_ = std::move(v);
}

}
