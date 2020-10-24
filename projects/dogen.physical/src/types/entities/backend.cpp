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
#include "dogen.physical/types/entities/backend.hpp"

namespace dogen::physical::entities {

backend::backend()
    : technical_space_(static_cast<dogen::identification::entities::technical_space>(0)) { }

backend::backend(
    const std::string& directory_name,
    const std::string& description,
    const dogen::identification::entities::physical_meta_name& meta_name,
    const std::list<dogen::identification::entities::label>& labels,
    const dogen::identification::entities::technical_space technical_space,
    const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::part>& parts,
    const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet>& facets,
    const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype>& archetypes,
    const std::unordered_map<std::string, dogen::physical::entities::archetype_kind>& archetype_kinds)
    : directory_name_(directory_name),
      description_(description),
      meta_name_(meta_name),
      labels_(labels),
      technical_space_(technical_space),
      parts_(parts),
      facets_(facets),
      archetypes_(archetypes),
      archetype_kinds_(archetype_kinds) { }

void backend::swap(backend& other) noexcept {
    using std::swap;
    swap(directory_name_, other.directory_name_);
    swap(description_, other.description_);
    swap(meta_name_, other.meta_name_);
    swap(labels_, other.labels_);
    swap(technical_space_, other.technical_space_);
    swap(parts_, other.parts_);
    swap(facets_, other.facets_);
    swap(archetypes_, other.archetypes_);
    swap(archetype_kinds_, other.archetype_kinds_);
}

bool backend::operator==(const backend& rhs) const {
    return directory_name_ == rhs.directory_name_ &&
        description_ == rhs.description_ &&
        meta_name_ == rhs.meta_name_ &&
        labels_ == rhs.labels_ &&
        technical_space_ == rhs.technical_space_ &&
        parts_ == rhs.parts_ &&
        facets_ == rhs.facets_ &&
        archetypes_ == rhs.archetypes_ &&
        archetype_kinds_ == rhs.archetype_kinds_;
}

backend& backend::operator=(backend other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& backend::directory_name() const {
    return directory_name_;
}

std::string& backend::directory_name() {
    return directory_name_;
}

void backend::directory_name(const std::string& v) {
    directory_name_ = v;
}

void backend::directory_name(const std::string&& v) {
    directory_name_ = std::move(v);
}

const std::string& backend::description() const {
    return description_;
}

std::string& backend::description() {
    return description_;
}

void backend::description(const std::string& v) {
    description_ = v;
}

void backend::description(const std::string&& v) {
    description_ = std::move(v);
}

const dogen::identification::entities::physical_meta_name& backend::meta_name() const {
    return meta_name_;
}

dogen::identification::entities::physical_meta_name& backend::meta_name() {
    return meta_name_;
}

void backend::meta_name(const dogen::identification::entities::physical_meta_name& v) {
    meta_name_ = v;
}

void backend::meta_name(const dogen::identification::entities::physical_meta_name&& v) {
    meta_name_ = std::move(v);
}

const std::list<dogen::identification::entities::label>& backend::labels() const {
    return labels_;
}

std::list<dogen::identification::entities::label>& backend::labels() {
    return labels_;
}

void backend::labels(const std::list<dogen::identification::entities::label>& v) {
    labels_ = v;
}

void backend::labels(const std::list<dogen::identification::entities::label>&& v) {
    labels_ = std::move(v);
}

dogen::identification::entities::technical_space backend::technical_space() const {
    return technical_space_;
}

void backend::technical_space(const dogen::identification::entities::technical_space v) {
    technical_space_ = v;
}

const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::part>& backend::parts() const {
    return parts_;
}

std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::part>& backend::parts() {
    return parts_;
}

void backend::parts(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::part>& v) {
    parts_ = v;
}

void backend::parts(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::part>&& v) {
    parts_ = std::move(v);
}

const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet>& backend::facets() const {
    return facets_;
}

std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet>& backend::facets() {
    return facets_;
}

void backend::facets(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet>& v) {
    facets_ = v;
}

void backend::facets(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet>&& v) {
    facets_ = std::move(v);
}

const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype>& backend::archetypes() const {
    return archetypes_;
}

std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype>& backend::archetypes() {
    return archetypes_;
}

void backend::archetypes(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype>& v) {
    archetypes_ = v;
}

void backend::archetypes(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype>&& v) {
    archetypes_ = std::move(v);
}

const std::unordered_map<std::string, dogen::physical::entities::archetype_kind>& backend::archetype_kinds() const {
    return archetype_kinds_;
}

std::unordered_map<std::string, dogen::physical::entities::archetype_kind>& backend::archetype_kinds() {
    return archetype_kinds_;
}

void backend::archetype_kinds(const std::unordered_map<std::string, dogen::physical::entities::archetype_kind>& v) {
    archetype_kinds_ = v;
}

void backend::archetype_kinds(const std::unordered_map<std::string, dogen::physical::entities::archetype_kind>&& v) {
    archetype_kinds_ = std::move(v);
}

}
