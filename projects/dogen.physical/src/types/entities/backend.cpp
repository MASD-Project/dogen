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

backend::backend(
    const std::string& default_directory_name,
    const std::string& override_directory_name,
    const dogen::physical::entities::location& location,
    const std::string& description,
    const dogen::physical::entities::meta_name& meta_name,
    const std::unordered_map<std::string, dogen::physical::entities::part>& parts,
    const std::unordered_map<std::string, dogen::physical::entities::facet>& facets,
    const std::unordered_map<std::string, dogen::physical::entities::archetype>& archetypes,
    const std::unordered_map<std::string, dogen::physical::entities::archetype_kind>& archetype_kinds)
    : default_directory_name_(default_directory_name),
      override_directory_name_(override_directory_name),
      location_(location),
      description_(description),
      meta_name_(meta_name),
      parts_(parts),
      facets_(facets),
      archetypes_(archetypes),
      archetype_kinds_(archetype_kinds) { }

void backend::swap(backend& other) noexcept {
    using std::swap;
    swap(default_directory_name_, other.default_directory_name_);
    swap(override_directory_name_, other.override_directory_name_);
    swap(location_, other.location_);
    swap(description_, other.description_);
    swap(meta_name_, other.meta_name_);
    swap(parts_, other.parts_);
    swap(facets_, other.facets_);
    swap(archetypes_, other.archetypes_);
    swap(archetype_kinds_, other.archetype_kinds_);
}

bool backend::operator==(const backend& rhs) const {
    return default_directory_name_ == rhs.default_directory_name_ &&
        override_directory_name_ == rhs.override_directory_name_ &&
        location_ == rhs.location_ &&
        description_ == rhs.description_ &&
        meta_name_ == rhs.meta_name_ &&
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

const std::string& backend::default_directory_name() const {
    return default_directory_name_;
}

std::string& backend::default_directory_name() {
    return default_directory_name_;
}

void backend::default_directory_name(const std::string& v) {
    default_directory_name_ = v;
}

void backend::default_directory_name(const std::string&& v) {
    default_directory_name_ = std::move(v);
}

const std::string& backend::override_directory_name() const {
    return override_directory_name_;
}

std::string& backend::override_directory_name() {
    return override_directory_name_;
}

void backend::override_directory_name(const std::string& v) {
    override_directory_name_ = v;
}

void backend::override_directory_name(const std::string&& v) {
    override_directory_name_ = std::move(v);
}

const dogen::physical::entities::location& backend::location() const {
    return location_;
}

dogen::physical::entities::location& backend::location() {
    return location_;
}

void backend::location(const dogen::physical::entities::location& v) {
    location_ = v;
}

void backend::location(const dogen::physical::entities::location&& v) {
    location_ = std::move(v);
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

const dogen::physical::entities::meta_name& backend::meta_name() const {
    return meta_name_;
}

dogen::physical::entities::meta_name& backend::meta_name() {
    return meta_name_;
}

void backend::meta_name(const dogen::physical::entities::meta_name& v) {
    meta_name_ = v;
}

void backend::meta_name(const dogen::physical::entities::meta_name&& v) {
    meta_name_ = std::move(v);
}

const std::unordered_map<std::string, dogen::physical::entities::part>& backend::parts() const {
    return parts_;
}

std::unordered_map<std::string, dogen::physical::entities::part>& backend::parts() {
    return parts_;
}

void backend::parts(const std::unordered_map<std::string, dogen::physical::entities::part>& v) {
    parts_ = v;
}

void backend::parts(const std::unordered_map<std::string, dogen::physical::entities::part>&& v) {
    parts_ = std::move(v);
}

const std::unordered_map<std::string, dogen::physical::entities::facet>& backend::facets() const {
    return facets_;
}

std::unordered_map<std::string, dogen::physical::entities::facet>& backend::facets() {
    return facets_;
}

void backend::facets(const std::unordered_map<std::string, dogen::physical::entities::facet>& v) {
    facets_ = v;
}

void backend::facets(const std::unordered_map<std::string, dogen::physical::entities::facet>&& v) {
    facets_ = std::move(v);
}

const std::unordered_map<std::string, dogen::physical::entities::archetype>& backend::archetypes() const {
    return archetypes_;
}

std::unordered_map<std::string, dogen::physical::entities::archetype>& backend::archetypes() {
    return archetypes_;
}

void backend::archetypes(const std::unordered_map<std::string, dogen::physical::entities::archetype>& v) {
    archetypes_ = v;
}

void backend::archetypes(const std::unordered_map<std::string, dogen::physical::entities::archetype>&& v) {
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
