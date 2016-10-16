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
#include "dogen/annotations/types/ownership_hierarchy_repository.hpp"

namespace dogen {
namespace annotations {

archetype_location_repository::archetype_location_repository(
    const std::vector<dogen::annotations::archetype_location>& ownership_hierarchies,
    const std::unordered_map<std::string, std::unordered_set<std::string> >& facet_names_by_model_name,
    const std::unordered_map<std::string, std::unordered_set<std::string> >& formatter_names_by_model_name)
    : ownership_hierarchies_(ownership_hierarchies),
      facet_names_by_model_name_(facet_names_by_model_name),
      formatter_names_by_model_name_(formatter_names_by_model_name) { }

void archetype_location_repository::swap(archetype_location_repository& other) noexcept {
    using std::swap;
    swap(ownership_hierarchies_, other.ownership_hierarchies_);
    swap(facet_names_by_model_name_, other.facet_names_by_model_name_);
    swap(formatter_names_by_model_name_, other.formatter_names_by_model_name_);
}

bool archetype_location_repository::operator==(const archetype_location_repository& rhs) const {
    return ownership_hierarchies_ == rhs.ownership_hierarchies_ &&
        facet_names_by_model_name_ == rhs.facet_names_by_model_name_ &&
        formatter_names_by_model_name_ == rhs.formatter_names_by_model_name_;
}

archetype_location_repository& archetype_location_repository::operator=(archetype_location_repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::vector<dogen::annotations::archetype_location>& archetype_location_repository::ownership_hierarchies() const {
    return ownership_hierarchies_;
}

std::vector<dogen::annotations::archetype_location>& archetype_location_repository::ownership_hierarchies() {
    return ownership_hierarchies_;
}

void archetype_location_repository::ownership_hierarchies(const std::vector<dogen::annotations::archetype_location>& v) {
    ownership_hierarchies_ = v;
}

void archetype_location_repository::ownership_hierarchies(const std::vector<dogen::annotations::archetype_location>&& v) {
    ownership_hierarchies_ = std::move(v);
}

const std::unordered_map<std::string, std::unordered_set<std::string> >& archetype_location_repository::facet_names_by_model_name() const {
    return facet_names_by_model_name_;
}

std::unordered_map<std::string, std::unordered_set<std::string> >& archetype_location_repository::facet_names_by_model_name() {
    return facet_names_by_model_name_;
}

void archetype_location_repository::facet_names_by_model_name(const std::unordered_map<std::string, std::unordered_set<std::string> >& v) {
    facet_names_by_model_name_ = v;
}

void archetype_location_repository::facet_names_by_model_name(const std::unordered_map<std::string, std::unordered_set<std::string> >&& v) {
    facet_names_by_model_name_ = std::move(v);
}

const std::unordered_map<std::string, std::unordered_set<std::string> >& archetype_location_repository::formatter_names_by_model_name() const {
    return formatter_names_by_model_name_;
}

std::unordered_map<std::string, std::unordered_set<std::string> >& archetype_location_repository::formatter_names_by_model_name() {
    return formatter_names_by_model_name_;
}

void archetype_location_repository::formatter_names_by_model_name(const std::unordered_map<std::string, std::unordered_set<std::string> >& v) {
    formatter_names_by_model_name_ = v;
}

void archetype_location_repository::formatter_names_by_model_name(const std::unordered_map<std::string, std::unordered_set<std::string> >&& v) {
    formatter_names_by_model_name_ = std::move(v);
}

} }
