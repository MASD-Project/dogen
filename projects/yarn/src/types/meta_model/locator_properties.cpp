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
#include "dogen/yarn/types/meta_model/locator_properties.hpp"

namespace dogen {
namespace yarn {
namespace meta_model {

locator_properties::locator_properties()
    : directory_structure_style_(static_cast<dogen::yarn::meta_model::directory_structure_styles>(0)) { }

locator_properties::locator_properties(
    const dogen::yarn::meta_model::directory_structure_styles directory_structure_style,
    const std::string& name_separator,
    const dogen::yarn::meta_model::model_segment_properties& model_segment_properties,
    const std::unordered_map<std::string, dogen::yarn::meta_model::intra_kernel_segment_properties>& intra_kernel_segment_properties,
    const std::unordered_map<std::string, dogen::yarn::meta_model::archetype_group_properties>& archetype_group_properties)
    : directory_structure_style_(directory_structure_style),
      name_separator_(name_separator),
      model_segment_properties_(model_segment_properties),
      intra_kernel_segment_properties_(intra_kernel_segment_properties),
      archetype_group_properties_(archetype_group_properties) { }

void locator_properties::swap(locator_properties& other) noexcept {
    using std::swap;
    swap(directory_structure_style_, other.directory_structure_style_);
    swap(name_separator_, other.name_separator_);
    swap(model_segment_properties_, other.model_segment_properties_);
    swap(intra_kernel_segment_properties_, other.intra_kernel_segment_properties_);
    swap(archetype_group_properties_, other.archetype_group_properties_);
}

bool locator_properties::operator==(const locator_properties& rhs) const {
    return directory_structure_style_ == rhs.directory_structure_style_ &&
        name_separator_ == rhs.name_separator_ &&
        model_segment_properties_ == rhs.model_segment_properties_ &&
        intra_kernel_segment_properties_ == rhs.intra_kernel_segment_properties_ &&
        archetype_group_properties_ == rhs.archetype_group_properties_;
}

locator_properties& locator_properties::operator=(locator_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

dogen::yarn::meta_model::directory_structure_styles locator_properties::directory_structure_style() const {
    return directory_structure_style_;
}

void locator_properties::directory_structure_style(const dogen::yarn::meta_model::directory_structure_styles v) {
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

const dogen::yarn::meta_model::model_segment_properties& locator_properties::model_segment_properties() const {
    return model_segment_properties_;
}

dogen::yarn::meta_model::model_segment_properties& locator_properties::model_segment_properties() {
    return model_segment_properties_;
}

void locator_properties::model_segment_properties(const dogen::yarn::meta_model::model_segment_properties& v) {
    model_segment_properties_ = v;
}

void locator_properties::model_segment_properties(const dogen::yarn::meta_model::model_segment_properties&& v) {
    model_segment_properties_ = std::move(v);
}

const std::unordered_map<std::string, dogen::yarn::meta_model::intra_kernel_segment_properties>& locator_properties::intra_kernel_segment_properties() const {
    return intra_kernel_segment_properties_;
}

std::unordered_map<std::string, dogen::yarn::meta_model::intra_kernel_segment_properties>& locator_properties::intra_kernel_segment_properties() {
    return intra_kernel_segment_properties_;
}

void locator_properties::intra_kernel_segment_properties(const std::unordered_map<std::string, dogen::yarn::meta_model::intra_kernel_segment_properties>& v) {
    intra_kernel_segment_properties_ = v;
}

void locator_properties::intra_kernel_segment_properties(const std::unordered_map<std::string, dogen::yarn::meta_model::intra_kernel_segment_properties>&& v) {
    intra_kernel_segment_properties_ = std::move(v);
}

const std::unordered_map<std::string, dogen::yarn::meta_model::archetype_group_properties>& locator_properties::archetype_group_properties() const {
    return archetype_group_properties_;
}

std::unordered_map<std::string, dogen::yarn::meta_model::archetype_group_properties>& locator_properties::archetype_group_properties() {
    return archetype_group_properties_;
}

void locator_properties::archetype_group_properties(const std::unordered_map<std::string, dogen::yarn::meta_model::archetype_group_properties>& v) {
    archetype_group_properties_ = v;
}

void locator_properties::archetype_group_properties(const std::unordered_map<std::string, dogen::yarn::meta_model::archetype_group_properties>&& v) {
    archetype_group_properties_ = std::move(v);
}

} } }
