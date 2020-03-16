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
#include "dogen.generation/types/entities/locator_properties.hpp"

namespace dogen::generation::entities {

locator_properties::locator_properties()
    : directory_structure_style_(static_cast<dogen::generation::entities::directory_structure_styles>(0)),
      force_backend_directory_(static_cast<bool>(0)),
      disable_facet_directories_(static_cast<bool>(0)) { }

locator_properties::locator_properties(
    const dogen::generation::entities::directory_structure_styles directory_structure_style,
    const std::string& name_separator,
    const dogen::generation::entities::model_segment_properties& model_segment_properties,
    const std::unordered_map<std::string, dogen::generation::entities::intra_backend_segment_properties>& intra_backend_segment_properties,
    const std::unordered_map<std::string, dogen::generation::entities::archetype_family_properties>& archetype_family_properties,
    const bool force_backend_directory,
    const bool disable_facet_directories)
    : directory_structure_style_(directory_structure_style),
      name_separator_(name_separator),
      model_segment_properties_(model_segment_properties),
      intra_backend_segment_properties_(intra_backend_segment_properties),
      archetype_family_properties_(archetype_family_properties),
      force_backend_directory_(force_backend_directory),
      disable_facet_directories_(disable_facet_directories) { }

void locator_properties::swap(locator_properties& other) noexcept {
    using std::swap;
    swap(directory_structure_style_, other.directory_structure_style_);
    swap(name_separator_, other.name_separator_);
    swap(model_segment_properties_, other.model_segment_properties_);
    swap(intra_backend_segment_properties_, other.intra_backend_segment_properties_);
    swap(archetype_family_properties_, other.archetype_family_properties_);
    swap(force_backend_directory_, other.force_backend_directory_);
    swap(disable_facet_directories_, other.disable_facet_directories_);
}

bool locator_properties::operator==(const locator_properties& rhs) const {
    return directory_structure_style_ == rhs.directory_structure_style_ &&
        name_separator_ == rhs.name_separator_ &&
        model_segment_properties_ == rhs.model_segment_properties_ &&
        intra_backend_segment_properties_ == rhs.intra_backend_segment_properties_ &&
        archetype_family_properties_ == rhs.archetype_family_properties_ &&
        force_backend_directory_ == rhs.force_backend_directory_ &&
        disable_facet_directories_ == rhs.disable_facet_directories_;
}

locator_properties& locator_properties::operator=(locator_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

dogen::generation::entities::directory_structure_styles locator_properties::directory_structure_style() const {
    return directory_structure_style_;
}

void locator_properties::directory_structure_style(const dogen::generation::entities::directory_structure_styles v) {
    directory_structure_style_ = v;
}

const std::string& locator_properties::name_separator() const {
    return name_separator_;
}

std::string& locator_properties::name_separator() {
    return name_separator_;
}

void locator_properties::name_separator(const std::string& v) {
    name_separator_ = v;
}

void locator_properties::name_separator(const std::string&& v) {
    name_separator_ = std::move(v);
}

const dogen::generation::entities::model_segment_properties& locator_properties::model_segment_properties() const {
    return model_segment_properties_;
}

dogen::generation::entities::model_segment_properties& locator_properties::model_segment_properties() {
    return model_segment_properties_;
}

void locator_properties::model_segment_properties(const dogen::generation::entities::model_segment_properties& v) {
    model_segment_properties_ = v;
}

void locator_properties::model_segment_properties(const dogen::generation::entities::model_segment_properties&& v) {
    model_segment_properties_ = std::move(v);
}

const std::unordered_map<std::string, dogen::generation::entities::intra_backend_segment_properties>& locator_properties::intra_backend_segment_properties() const {
    return intra_backend_segment_properties_;
}

std::unordered_map<std::string, dogen::generation::entities::intra_backend_segment_properties>& locator_properties::intra_backend_segment_properties() {
    return intra_backend_segment_properties_;
}

void locator_properties::intra_backend_segment_properties(const std::unordered_map<std::string, dogen::generation::entities::intra_backend_segment_properties>& v) {
    intra_backend_segment_properties_ = v;
}

void locator_properties::intra_backend_segment_properties(const std::unordered_map<std::string, dogen::generation::entities::intra_backend_segment_properties>&& v) {
    intra_backend_segment_properties_ = std::move(v);
}

const std::unordered_map<std::string, dogen::generation::entities::archetype_family_properties>& locator_properties::archetype_family_properties() const {
    return archetype_family_properties_;
}

std::unordered_map<std::string, dogen::generation::entities::archetype_family_properties>& locator_properties::archetype_family_properties() {
    return archetype_family_properties_;
}

void locator_properties::archetype_family_properties(const std::unordered_map<std::string, dogen::generation::entities::archetype_family_properties>& v) {
    archetype_family_properties_ = v;
}

void locator_properties::archetype_family_properties(const std::unordered_map<std::string, dogen::generation::entities::archetype_family_properties>&& v) {
    archetype_family_properties_ = std::move(v);
}

bool locator_properties::force_backend_directory() const {
    return force_backend_directory_;
}

void locator_properties::force_backend_directory(const bool v) {
    force_backend_directory_ = v;
}

bool locator_properties::disable_facet_directories() const {
    return disable_facet_directories_;
}

void locator_properties::disable_facet_directories(const bool v) {
    disable_facet_directories_ = v;
}

}
