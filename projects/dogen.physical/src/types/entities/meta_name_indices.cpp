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
#include "dogen.physical/types/entities/meta_name_indices.hpp"

namespace dogen::physical::entities {

meta_name_indices::meta_name_indices(
    const std::list<dogen::physical::entities::meta_name>& all,
    const std::unordered_map<std::string, std::unordered_set<std::string> >& facet_names_by_backend_name,
    const std::unordered_map<std::string, dogen::physical::entities::archetype_name_set>& by_logical_meta_name,
    const std::unordered_map<std::string, std::unordered_map<std::string, std::list<std::string> > >& by_backend_by_facet)
    : all_(all),
      facet_names_by_backend_name_(facet_names_by_backend_name),
      by_logical_meta_name_(by_logical_meta_name),
      by_backend_by_facet_(by_backend_by_facet) { }

void meta_name_indices::swap(meta_name_indices& other) noexcept {
    using std::swap;
    swap(all_, other.all_);
    swap(facet_names_by_backend_name_, other.facet_names_by_backend_name_);
    swap(by_logical_meta_name_, other.by_logical_meta_name_);
    swap(by_backend_by_facet_, other.by_backend_by_facet_);
}

bool meta_name_indices::operator==(const meta_name_indices& rhs) const {
    return all_ == rhs.all_ &&
        facet_names_by_backend_name_ == rhs.facet_names_by_backend_name_ &&
        by_logical_meta_name_ == rhs.by_logical_meta_name_ &&
        by_backend_by_facet_ == rhs.by_backend_by_facet_;
}

meta_name_indices& meta_name_indices::operator=(meta_name_indices other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::physical::entities::meta_name>& meta_name_indices::all() const {
    return all_;
}

std::list<dogen::physical::entities::meta_name>& meta_name_indices::all() {
    return all_;
}

void meta_name_indices::all(const std::list<dogen::physical::entities::meta_name>& v) {
    all_ = v;
}

void meta_name_indices::all(const std::list<dogen::physical::entities::meta_name>&& v) {
    all_ = std::move(v);
}

const std::unordered_map<std::string, std::unordered_set<std::string> >& meta_name_indices::facet_names_by_backend_name() const {
    return facet_names_by_backend_name_;
}

std::unordered_map<std::string, std::unordered_set<std::string> >& meta_name_indices::facet_names_by_backend_name() {
    return facet_names_by_backend_name_;
}

void meta_name_indices::facet_names_by_backend_name(const std::unordered_map<std::string, std::unordered_set<std::string> >& v) {
    facet_names_by_backend_name_ = v;
}

void meta_name_indices::facet_names_by_backend_name(const std::unordered_map<std::string, std::unordered_set<std::string> >&& v) {
    facet_names_by_backend_name_ = std::move(v);
}

const std::unordered_map<std::string, dogen::physical::entities::archetype_name_set>& meta_name_indices::by_logical_meta_name() const {
    return by_logical_meta_name_;
}

std::unordered_map<std::string, dogen::physical::entities::archetype_name_set>& meta_name_indices::by_logical_meta_name() {
    return by_logical_meta_name_;
}

void meta_name_indices::by_logical_meta_name(const std::unordered_map<std::string, dogen::physical::entities::archetype_name_set>& v) {
    by_logical_meta_name_ = v;
}

void meta_name_indices::by_logical_meta_name(const std::unordered_map<std::string, dogen::physical::entities::archetype_name_set>&& v) {
    by_logical_meta_name_ = std::move(v);
}

const std::unordered_map<std::string, std::unordered_map<std::string, std::list<std::string> > >& meta_name_indices::by_backend_by_facet() const {
    return by_backend_by_facet_;
}

std::unordered_map<std::string, std::unordered_map<std::string, std::list<std::string> > >& meta_name_indices::by_backend_by_facet() {
    return by_backend_by_facet_;
}

void meta_name_indices::by_backend_by_facet(const std::unordered_map<std::string, std::unordered_map<std::string, std::list<std::string> > >& v) {
    by_backend_by_facet_ = v;
}

void meta_name_indices::by_backend_by_facet(const std::unordered_map<std::string, std::unordered_map<std::string, std::list<std::string> > >&& v) {
    by_backend_by_facet_ = std::move(v);
}

}
