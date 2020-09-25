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
#include "dogen.physical/types/entities/part.hpp"

namespace dogen::physical::entities {

part::part()
    : requires_relative_path_(static_cast<bool>(0)) { }

part::part(
    const std::string& default_directory_name,
    const std::string& override_directory_name,
    const std::string& description,
    const dogen::identification::entities::physical_meta_name& meta_name,
    const std::list<dogen::identification::entities::label>& labels,
    const std::string& directory_name,
    const dogen::physical::entities::path_configuration& path_configuration,
    const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet>& facets,
    const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype>& archetypes,
    const bool requires_relative_path)
    : default_directory_name_(default_directory_name),
      override_directory_name_(override_directory_name),
      description_(description),
      meta_name_(meta_name),
      labels_(labels),
      directory_name_(directory_name),
      path_configuration_(path_configuration),
      facets_(facets),
      archetypes_(archetypes),
      requires_relative_path_(requires_relative_path) { }

void part::swap(part& other) noexcept {
    using std::swap;
    swap(default_directory_name_, other.default_directory_name_);
    swap(override_directory_name_, other.override_directory_name_);
    swap(description_, other.description_);
    swap(meta_name_, other.meta_name_);
    swap(labels_, other.labels_);
    swap(directory_name_, other.directory_name_);
    swap(path_configuration_, other.path_configuration_);
    swap(facets_, other.facets_);
    swap(archetypes_, other.archetypes_);
    swap(requires_relative_path_, other.requires_relative_path_);
}

bool part::operator==(const part& rhs) const {
    return default_directory_name_ == rhs.default_directory_name_ &&
        override_directory_name_ == rhs.override_directory_name_ &&
        description_ == rhs.description_ &&
        meta_name_ == rhs.meta_name_ &&
        labels_ == rhs.labels_ &&
        directory_name_ == rhs.directory_name_ &&
        path_configuration_ == rhs.path_configuration_ &&
        facets_ == rhs.facets_ &&
        archetypes_ == rhs.archetypes_ &&
        requires_relative_path_ == rhs.requires_relative_path_;
}

part& part::operator=(part other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& part::default_directory_name() const {
    return default_directory_name_;
}

std::string& part::default_directory_name() {
    return default_directory_name_;
}

void part::default_directory_name(const std::string& v) {
    default_directory_name_ = v;
}

void part::default_directory_name(const std::string&& v) {
    default_directory_name_ = std::move(v);
}

const std::string& part::override_directory_name() const {
    return override_directory_name_;
}

std::string& part::override_directory_name() {
    return override_directory_name_;
}

void part::override_directory_name(const std::string& v) {
    override_directory_name_ = v;
}

void part::override_directory_name(const std::string&& v) {
    override_directory_name_ = std::move(v);
}

const std::string& part::description() const {
    return description_;
}

std::string& part::description() {
    return description_;
}

void part::description(const std::string& v) {
    description_ = v;
}

void part::description(const std::string&& v) {
    description_ = std::move(v);
}

const dogen::identification::entities::physical_meta_name& part::meta_name() const {
    return meta_name_;
}

dogen::identification::entities::physical_meta_name& part::meta_name() {
    return meta_name_;
}

void part::meta_name(const dogen::identification::entities::physical_meta_name& v) {
    meta_name_ = v;
}

void part::meta_name(const dogen::identification::entities::physical_meta_name&& v) {
    meta_name_ = std::move(v);
}

const std::list<dogen::identification::entities::label>& part::labels() const {
    return labels_;
}

std::list<dogen::identification::entities::label>& part::labels() {
    return labels_;
}

void part::labels(const std::list<dogen::identification::entities::label>& v) {
    labels_ = v;
}

void part::labels(const std::list<dogen::identification::entities::label>&& v) {
    labels_ = std::move(v);
}

const std::string& part::directory_name() const {
    return directory_name_;
}

std::string& part::directory_name() {
    return directory_name_;
}

void part::directory_name(const std::string& v) {
    directory_name_ = v;
}

void part::directory_name(const std::string&& v) {
    directory_name_ = std::move(v);
}

const dogen::physical::entities::path_configuration& part::path_configuration() const {
    return path_configuration_;
}

dogen::physical::entities::path_configuration& part::path_configuration() {
    return path_configuration_;
}

void part::path_configuration(const dogen::physical::entities::path_configuration& v) {
    path_configuration_ = v;
}

void part::path_configuration(const dogen::physical::entities::path_configuration&& v) {
    path_configuration_ = std::move(v);
}

const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet>& part::facets() const {
    return facets_;
}

std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet>& part::facets() {
    return facets_;
}

void part::facets(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet>& v) {
    facets_ = v;
}

void part::facets(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet>&& v) {
    facets_ = std::move(v);
}

const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype>& part::archetypes() const {
    return archetypes_;
}

std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype>& part::archetypes() {
    return archetypes_;
}

void part::archetypes(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype>& v) {
    archetypes_ = v;
}

void part::archetypes(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype>&& v) {
    archetypes_ = std::move(v);
}

bool part::requires_relative_path() const {
    return requires_relative_path_;
}

void part::requires_relative_path(const bool v) {
    requires_relative_path_ = v;
}

}
