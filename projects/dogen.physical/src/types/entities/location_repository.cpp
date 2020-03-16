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
#include "dogen.physical/types/entities/location_repository.hpp"

namespace dogen::physical::entities {

location_repository::location_repository(
    const std::list<dogen::physical::entities::location>& all,
    const std::unordered_map<std::string, std::unordered_set<std::string> >& facet_names_by_backend_name,
    const std::unordered_map<std::string, std::unordered_set<std::string> >& formatter_names_by_backend_name,
    const std::unordered_map<std::string, dogen::physical::entities::locations_group>& by_meta_name,
    const std::unordered_map<std::string, std::list<dogen::physical::entities::location> >& by_family,
    const std::unordered_map<std::string, std::unordered_map<std::string, std::list<std::string> > >& by_backend_by_facet)
    : all_(all),
      facet_names_by_backend_name_(facet_names_by_backend_name),
      formatter_names_by_backend_name_(formatter_names_by_backend_name),
      by_meta_name_(by_meta_name),
      by_family_(by_family),
      by_backend_by_facet_(by_backend_by_facet) { }

void location_repository::swap(location_repository& other) noexcept {
    using std::swap;
    swap(all_, other.all_);
    swap(facet_names_by_backend_name_, other.facet_names_by_backend_name_);
    swap(formatter_names_by_backend_name_, other.formatter_names_by_backend_name_);
    swap(by_meta_name_, other.by_meta_name_);
    swap(by_family_, other.by_family_);
    swap(by_backend_by_facet_, other.by_backend_by_facet_);
}

bool location_repository::operator==(const location_repository& rhs) const {
    return all_ == rhs.all_ &&
        facet_names_by_backend_name_ == rhs.facet_names_by_backend_name_ &&
        formatter_names_by_backend_name_ == rhs.formatter_names_by_backend_name_ &&
        by_meta_name_ == rhs.by_meta_name_ &&
        by_family_ == rhs.by_family_ &&
        by_backend_by_facet_ == rhs.by_backend_by_facet_;
}

location_repository& location_repository::operator=(location_repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::physical::entities::location>& location_repository::all() const {
    return all_;
}

std::list<dogen::physical::entities::location>& location_repository::all() {
    return all_;
}

void location_repository::all(const std::list<dogen::physical::entities::location>& v) {
    all_ = v;
}

void location_repository::all(const std::list<dogen::physical::entities::location>&& v) {
    all_ = std::move(v);
}

const std::unordered_map<std::string, std::unordered_set<std::string> >& location_repository::facet_names_by_backend_name() const {
    return facet_names_by_backend_name_;
}

std::unordered_map<std::string, std::unordered_set<std::string> >& location_repository::facet_names_by_backend_name() {
    return facet_names_by_backend_name_;
}

void location_repository::facet_names_by_backend_name(const std::unordered_map<std::string, std::unordered_set<std::string> >& v) {
    facet_names_by_backend_name_ = v;
}

void location_repository::facet_names_by_backend_name(const std::unordered_map<std::string, std::unordered_set<std::string> >&& v) {
    facet_names_by_backend_name_ = std::move(v);
}

const std::unordered_map<std::string, std::unordered_set<std::string> >& location_repository::formatter_names_by_backend_name() const {
    return formatter_names_by_backend_name_;
}

std::unordered_map<std::string, std::unordered_set<std::string> >& location_repository::formatter_names_by_backend_name() {
    return formatter_names_by_backend_name_;
}

void location_repository::formatter_names_by_backend_name(const std::unordered_map<std::string, std::unordered_set<std::string> >& v) {
    formatter_names_by_backend_name_ = v;
}

void location_repository::formatter_names_by_backend_name(const std::unordered_map<std::string, std::unordered_set<std::string> >&& v) {
    formatter_names_by_backend_name_ = std::move(v);
}

const std::unordered_map<std::string, dogen::physical::entities::locations_group>& location_repository::by_meta_name() const {
    return by_meta_name_;
}

std::unordered_map<std::string, dogen::physical::entities::locations_group>& location_repository::by_meta_name() {
    return by_meta_name_;
}

void location_repository::by_meta_name(const std::unordered_map<std::string, dogen::physical::entities::locations_group>& v) {
    by_meta_name_ = v;
}

void location_repository::by_meta_name(const std::unordered_map<std::string, dogen::physical::entities::locations_group>&& v) {
    by_meta_name_ = std::move(v);
}

const std::unordered_map<std::string, std::list<dogen::physical::entities::location> >& location_repository::by_family() const {
    return by_family_;
}

std::unordered_map<std::string, std::list<dogen::physical::entities::location> >& location_repository::by_family() {
    return by_family_;
}

void location_repository::by_family(const std::unordered_map<std::string, std::list<dogen::physical::entities::location> >& v) {
    by_family_ = v;
}

void location_repository::by_family(const std::unordered_map<std::string, std::list<dogen::physical::entities::location> >&& v) {
    by_family_ = std::move(v);
}

const std::unordered_map<std::string, std::unordered_map<std::string, std::list<std::string> > >& location_repository::by_backend_by_facet() const {
    return by_backend_by_facet_;
}

std::unordered_map<std::string, std::unordered_map<std::string, std::list<std::string> > >& location_repository::by_backend_by_facet() {
    return by_backend_by_facet_;
}

void location_repository::by_backend_by_facet(const std::unordered_map<std::string, std::unordered_map<std::string, std::list<std::string> > >& v) {
    by_backend_by_facet_ = v;
}

void location_repository::by_backend_by_facet(const std::unordered_map<std::string, std::unordered_map<std::string, std::list<std::string> > >&& v) {
    by_backend_by_facet_ = std::move(v);
}

}
