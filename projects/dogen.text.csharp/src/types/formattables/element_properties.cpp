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
#include "dogen.text.csharp/types/formattables/element_properties.hpp"

namespace dogen::text::csharp::formattables {

element_properties::element_properties(
    const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::text::csharp::formattables::artefact_properties>& artefact_properties,
    const std::list<dogen::text::csharp::formattables::helper_properties>& helper_properties,
    const std::unordered_map<std::string, dogen::text::csharp::formattables::attribute_properties>& attribute_properties)
    : artefact_properties_(artefact_properties),
      helper_properties_(helper_properties),
      attribute_properties_(attribute_properties) { }

void element_properties::swap(element_properties& other) noexcept {
    using std::swap;
    swap(artefact_properties_, other.artefact_properties_);
    swap(helper_properties_, other.helper_properties_);
    swap(attribute_properties_, other.attribute_properties_);
}

bool element_properties::operator==(const element_properties& rhs) const {
    return artefact_properties_ == rhs.artefact_properties_ &&
        helper_properties_ == rhs.helper_properties_ &&
        attribute_properties_ == rhs.attribute_properties_;
}

element_properties& element_properties::operator=(element_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::text::csharp::formattables::artefact_properties>& element_properties::artefact_properties() const {
    return artefact_properties_;
}

std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::text::csharp::formattables::artefact_properties>& element_properties::artefact_properties() {
    return artefact_properties_;
}

void element_properties::artefact_properties(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::text::csharp::formattables::artefact_properties>& v) {
    artefact_properties_ = v;
}

void element_properties::artefact_properties(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::text::csharp::formattables::artefact_properties>&& v) {
    artefact_properties_ = std::move(v);
}

const std::list<dogen::text::csharp::formattables::helper_properties>& element_properties::helper_properties() const {
    return helper_properties_;
}

std::list<dogen::text::csharp::formattables::helper_properties>& element_properties::helper_properties() {
    return helper_properties_;
}

void element_properties::helper_properties(const std::list<dogen::text::csharp::formattables::helper_properties>& v) {
    helper_properties_ = v;
}

void element_properties::helper_properties(const std::list<dogen::text::csharp::formattables::helper_properties>&& v) {
    helper_properties_ = std::move(v);
}

const std::unordered_map<std::string, dogen::text::csharp::formattables::attribute_properties>& element_properties::attribute_properties() const {
    return attribute_properties_;
}

std::unordered_map<std::string, dogen::text::csharp::formattables::attribute_properties>& element_properties::attribute_properties() {
    return attribute_properties_;
}

void element_properties::attribute_properties(const std::unordered_map<std::string, dogen::text::csharp::formattables::attribute_properties>& v) {
    attribute_properties_ = v;
}

void element_properties::attribute_properties(const std::unordered_map<std::string, dogen::text::csharp::formattables::attribute_properties>&& v) {
    attribute_properties_ = std::move(v);
}

}
