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
#include "dogen.identification/types/entities/physical_meta_name_indices.hpp"

namespace dogen::identification::entities {

physical_meta_name_indices::physical_meta_name_indices(
    const std::list<dogen::identification::entities::physical_meta_name>& all,
    const std::unordered_map<dogen::identification::entities::physical_meta_id, std::unordered_set<dogen::identification::entities::physical_meta_id> >& facet_names_by_backend_name,
    const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::identification::entities::archetype_name_set>& archetype_names_by_logical_meta_name,
    const std::unordered_map<dogen::identification::entities::physical_meta_id, std::unordered_map<dogen::identification::entities::physical_meta_id, std::list<dogen::identification::entities::physical_meta_id> > >& archetype_names_by_backend_by_facet)
    : all_(all),
      facet_names_by_backend_name_(facet_names_by_backend_name),
      archetype_names_by_logical_meta_name_(archetype_names_by_logical_meta_name),
      archetype_names_by_backend_by_facet_(archetype_names_by_backend_by_facet) { }

void physical_meta_name_indices::swap(physical_meta_name_indices& other) noexcept {
    using std::swap;
    swap(all_, other.all_);
    swap(facet_names_by_backend_name_, other.facet_names_by_backend_name_);
    swap(archetype_names_by_logical_meta_name_, other.archetype_names_by_logical_meta_name_);
    swap(archetype_names_by_backend_by_facet_, other.archetype_names_by_backend_by_facet_);
}

bool physical_meta_name_indices::operator==(const physical_meta_name_indices& rhs) const {
    return all_ == rhs.all_ &&
        facet_names_by_backend_name_ == rhs.facet_names_by_backend_name_ &&
        archetype_names_by_logical_meta_name_ == rhs.archetype_names_by_logical_meta_name_ &&
        archetype_names_by_backend_by_facet_ == rhs.archetype_names_by_backend_by_facet_;
}

physical_meta_name_indices& physical_meta_name_indices::operator=(physical_meta_name_indices other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::identification::entities::physical_meta_name>& physical_meta_name_indices::all() const {
    return all_;
}

std::list<dogen::identification::entities::physical_meta_name>& physical_meta_name_indices::all() {
    return all_;
}

void physical_meta_name_indices::all(const std::list<dogen::identification::entities::physical_meta_name>& v) {
    all_ = v;
}

void physical_meta_name_indices::all(const std::list<dogen::identification::entities::physical_meta_name>&& v) {
    all_ = std::move(v);
}

const std::unordered_map<dogen::identification::entities::physical_meta_id, std::unordered_set<dogen::identification::entities::physical_meta_id> >& physical_meta_name_indices::facet_names_by_backend_name() const {
    return facet_names_by_backend_name_;
}

std::unordered_map<dogen::identification::entities::physical_meta_id, std::unordered_set<dogen::identification::entities::physical_meta_id> >& physical_meta_name_indices::facet_names_by_backend_name() {
    return facet_names_by_backend_name_;
}

void physical_meta_name_indices::facet_names_by_backend_name(const std::unordered_map<dogen::identification::entities::physical_meta_id, std::unordered_set<dogen::identification::entities::physical_meta_id> >& v) {
    facet_names_by_backend_name_ = v;
}

void physical_meta_name_indices::facet_names_by_backend_name(const std::unordered_map<dogen::identification::entities::physical_meta_id, std::unordered_set<dogen::identification::entities::physical_meta_id> >&& v) {
    facet_names_by_backend_name_ = std::move(v);
}

const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::identification::entities::archetype_name_set>& physical_meta_name_indices::archetype_names_by_logical_meta_name() const {
    return archetype_names_by_logical_meta_name_;
}

std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::identification::entities::archetype_name_set>& physical_meta_name_indices::archetype_names_by_logical_meta_name() {
    return archetype_names_by_logical_meta_name_;
}

void physical_meta_name_indices::archetype_names_by_logical_meta_name(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::identification::entities::archetype_name_set>& v) {
    archetype_names_by_logical_meta_name_ = v;
}

void physical_meta_name_indices::archetype_names_by_logical_meta_name(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::identification::entities::archetype_name_set>&& v) {
    archetype_names_by_logical_meta_name_ = std::move(v);
}

const std::unordered_map<dogen::identification::entities::physical_meta_id, std::unordered_map<dogen::identification::entities::physical_meta_id, std::list<dogen::identification::entities::physical_meta_id> > >& physical_meta_name_indices::archetype_names_by_backend_by_facet() const {
    return archetype_names_by_backend_by_facet_;
}

std::unordered_map<dogen::identification::entities::physical_meta_id, std::unordered_map<dogen::identification::entities::physical_meta_id, std::list<dogen::identification::entities::physical_meta_id> > >& physical_meta_name_indices::archetype_names_by_backend_by_facet() {
    return archetype_names_by_backend_by_facet_;
}

void physical_meta_name_indices::archetype_names_by_backend_by_facet(const std::unordered_map<dogen::identification::entities::physical_meta_id, std::unordered_map<dogen::identification::entities::physical_meta_id, std::list<dogen::identification::entities::physical_meta_id> > >& v) {
    archetype_names_by_backend_by_facet_ = v;
}

void physical_meta_name_indices::archetype_names_by_backend_by_facet(const std::unordered_map<dogen::identification::entities::physical_meta_id, std::unordered_map<dogen::identification::entities::physical_meta_id, std::list<dogen::identification::entities::physical_meta_id> > >&& v) {
    archetype_names_by_backend_by_facet_ = std::move(v);
}

}
