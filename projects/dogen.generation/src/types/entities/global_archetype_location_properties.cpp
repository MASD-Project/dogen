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
#include "dogen.generation/types/entities/global_archetype_location_properties.hpp"

namespace dogen::generation::entities {

global_archetype_location_properties::global_archetype_location_properties(
    const std::unordered_map<std::string, dogen::generation::entities::backend_properties>& backend_properties,
    const std::unordered_map<std::string, dogen::generation::entities::facet_properties>& facet_properties,
    const std::unordered_map<std::string, dogen::generation::entities::archetype_properties>& archetype_properties,
    const std::unordered_map<std::string, dogen::generation::entities::denormalised_archetype_properties>& denormalised_archetype_properties)
    : backend_properties_(backend_properties),
      facet_properties_(facet_properties),
      archetype_properties_(archetype_properties),
      denormalised_archetype_properties_(denormalised_archetype_properties) { }

void global_archetype_location_properties::swap(global_archetype_location_properties& other) noexcept {
    using std::swap;
    swap(backend_properties_, other.backend_properties_);
    swap(facet_properties_, other.facet_properties_);
    swap(archetype_properties_, other.archetype_properties_);
    swap(denormalised_archetype_properties_, other.denormalised_archetype_properties_);
}

bool global_archetype_location_properties::operator==(const global_archetype_location_properties& rhs) const {
    return backend_properties_ == rhs.backend_properties_ &&
        facet_properties_ == rhs.facet_properties_ &&
        archetype_properties_ == rhs.archetype_properties_ &&
        denormalised_archetype_properties_ == rhs.denormalised_archetype_properties_;
}

global_archetype_location_properties& global_archetype_location_properties::operator=(global_archetype_location_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, dogen::generation::entities::backend_properties>& global_archetype_location_properties::backend_properties() const {
    return backend_properties_;
}

std::unordered_map<std::string, dogen::generation::entities::backend_properties>& global_archetype_location_properties::backend_properties() {
    return backend_properties_;
}

void global_archetype_location_properties::backend_properties(const std::unordered_map<std::string, dogen::generation::entities::backend_properties>& v) {
    backend_properties_ = v;
}

void global_archetype_location_properties::backend_properties(const std::unordered_map<std::string, dogen::generation::entities::backend_properties>&& v) {
    backend_properties_ = std::move(v);
}

const std::unordered_map<std::string, dogen::generation::entities::facet_properties>& global_archetype_location_properties::facet_properties() const {
    return facet_properties_;
}

std::unordered_map<std::string, dogen::generation::entities::facet_properties>& global_archetype_location_properties::facet_properties() {
    return facet_properties_;
}

void global_archetype_location_properties::facet_properties(const std::unordered_map<std::string, dogen::generation::entities::facet_properties>& v) {
    facet_properties_ = v;
}

void global_archetype_location_properties::facet_properties(const std::unordered_map<std::string, dogen::generation::entities::facet_properties>&& v) {
    facet_properties_ = std::move(v);
}

const std::unordered_map<std::string, dogen::generation::entities::archetype_properties>& global_archetype_location_properties::archetype_properties() const {
    return archetype_properties_;
}

std::unordered_map<std::string, dogen::generation::entities::archetype_properties>& global_archetype_location_properties::archetype_properties() {
    return archetype_properties_;
}

void global_archetype_location_properties::archetype_properties(const std::unordered_map<std::string, dogen::generation::entities::archetype_properties>& v) {
    archetype_properties_ = v;
}

void global_archetype_location_properties::archetype_properties(const std::unordered_map<std::string, dogen::generation::entities::archetype_properties>&& v) {
    archetype_properties_ = std::move(v);
}

const std::unordered_map<std::string, dogen::generation::entities::denormalised_archetype_properties>& global_archetype_location_properties::denormalised_archetype_properties() const {
    return denormalised_archetype_properties_;
}

std::unordered_map<std::string, dogen::generation::entities::denormalised_archetype_properties>& global_archetype_location_properties::denormalised_archetype_properties() {
    return denormalised_archetype_properties_;
}

void global_archetype_location_properties::denormalised_archetype_properties(const std::unordered_map<std::string, dogen::generation::entities::denormalised_archetype_properties>& v) {
    denormalised_archetype_properties_ = v;
}

void global_archetype_location_properties::denormalised_archetype_properties(const std::unordered_map<std::string, dogen::generation::entities::denormalised_archetype_properties>&& v) {
    denormalised_archetype_properties_ = std::move(v);
}

}
