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
#include "dogen.text/types/helpers/text_to_text_transform_data.hpp"

namespace dogen::text::helpers {

text_to_text_transform_data::text_to_text_transform_data(
    const std::string& name,
    const std::list<dogen::physical::entities::archetype>& archetypes,
    const std::unordered_set<std::string>& logical_meta_model_ids,
    const std::list<dogen::text::entities::element_artefacts>& target_logical_elements)
    : name_(name),
      archetypes_(archetypes),
      logical_meta_model_ids_(logical_meta_model_ids),
      target_logical_elements_(target_logical_elements) { }

void text_to_text_transform_data::swap(text_to_text_transform_data& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(archetypes_, other.archetypes_);
    swap(logical_meta_model_ids_, other.logical_meta_model_ids_);
    swap(target_logical_elements_, other.target_logical_elements_);
}

bool text_to_text_transform_data::operator==(const text_to_text_transform_data& rhs) const {
    return name_ == rhs.name_ &&
        archetypes_ == rhs.archetypes_ &&
        logical_meta_model_ids_ == rhs.logical_meta_model_ids_ &&
        target_logical_elements_ == rhs.target_logical_elements_;
}

text_to_text_transform_data& text_to_text_transform_data::operator=(text_to_text_transform_data other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& text_to_text_transform_data::name() const {
    return name_;
}

std::string& text_to_text_transform_data::name() {
    return name_;
}

void text_to_text_transform_data::name(const std::string& v) {
    name_ = v;
}

void text_to_text_transform_data::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::list<dogen::physical::entities::archetype>& text_to_text_transform_data::archetypes() const {
    return archetypes_;
}

std::list<dogen::physical::entities::archetype>& text_to_text_transform_data::archetypes() {
    return archetypes_;
}

void text_to_text_transform_data::archetypes(const std::list<dogen::physical::entities::archetype>& v) {
    archetypes_ = v;
}

void text_to_text_transform_data::archetypes(const std::list<dogen::physical::entities::archetype>&& v) {
    archetypes_ = std::move(v);
}

const std::unordered_set<std::string>& text_to_text_transform_data::logical_meta_model_ids() const {
    return logical_meta_model_ids_;
}

std::unordered_set<std::string>& text_to_text_transform_data::logical_meta_model_ids() {
    return logical_meta_model_ids_;
}

void text_to_text_transform_data::logical_meta_model_ids(const std::unordered_set<std::string>& v) {
    logical_meta_model_ids_ = v;
}

void text_to_text_transform_data::logical_meta_model_ids(const std::unordered_set<std::string>&& v) {
    logical_meta_model_ids_ = std::move(v);
}

const std::list<dogen::text::entities::element_artefacts>& text_to_text_transform_data::target_logical_elements() const {
    return target_logical_elements_;
}

std::list<dogen::text::entities::element_artefacts>& text_to_text_transform_data::target_logical_elements() {
    return target_logical_elements_;
}

void text_to_text_transform_data::target_logical_elements(const std::list<dogen::text::entities::element_artefacts>& v) {
    target_logical_elements_ = v;
}

void text_to_text_transform_data::target_logical_elements(const std::list<dogen::text::entities::element_artefacts>&& v) {
    target_logical_elements_ = std::move(v);
}

}
