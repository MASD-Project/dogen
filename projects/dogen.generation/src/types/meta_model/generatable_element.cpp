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
#include "dogen.modeling/types/meta_model/element.hpp"
#include "dogen.generation/types/meta_model/generatable_element.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::modeling::meta_model::element>& lhs,
const boost::shared_ptr<dogen::modeling::meta_model::element>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen {
namespace generation {
namespace meta_model {

generatable_element::generatable_element(
    const boost::shared_ptr<dogen::modeling::meta_model::element>& modeling_element,
    const dogen::formatting::decoration_properties& decoration_properties,
    const std::unordered_map<std::string, dogen::generation::meta_model::artefact_properties>& artefact_properties,
    const std::unordered_map<std::string, dogen::generation::meta_model::local_archetype_location_properties>& archetype_location_properties)
    : modeling_element_(modeling_element),
      decoration_properties_(decoration_properties),
      artefact_properties_(artefact_properties),
      archetype_location_properties_(archetype_location_properties) { }

void generatable_element::swap(generatable_element& other) noexcept {
    using std::swap;
    swap(modeling_element_, other.modeling_element_);
    swap(decoration_properties_, other.decoration_properties_);
    swap(artefact_properties_, other.artefact_properties_);
    swap(archetype_location_properties_, other.archetype_location_properties_);
}

bool generatable_element::operator==(const generatable_element& rhs) const {
    return modeling_element_ == rhs.modeling_element_ &&
        decoration_properties_ == rhs.decoration_properties_ &&
        artefact_properties_ == rhs.artefact_properties_ &&
        archetype_location_properties_ == rhs.archetype_location_properties_;
}

generatable_element& generatable_element::operator=(generatable_element other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::shared_ptr<dogen::modeling::meta_model::element>& generatable_element::modeling_element() const {
    return modeling_element_;
}

boost::shared_ptr<dogen::modeling::meta_model::element>& generatable_element::modeling_element() {
    return modeling_element_;
}

void generatable_element::modeling_element(const boost::shared_ptr<dogen::modeling::meta_model::element>& v) {
    modeling_element_ = v;
}

void generatable_element::modeling_element(const boost::shared_ptr<dogen::modeling::meta_model::element>&& v) {
    modeling_element_ = std::move(v);
}

const dogen::formatting::decoration_properties& generatable_element::decoration_properties() const {
    return decoration_properties_;
}

dogen::formatting::decoration_properties& generatable_element::decoration_properties() {
    return decoration_properties_;
}

void generatable_element::decoration_properties(const dogen::formatting::decoration_properties& v) {
    decoration_properties_ = v;
}

void generatable_element::decoration_properties(const dogen::formatting::decoration_properties&& v) {
    decoration_properties_ = std::move(v);
}

const std::unordered_map<std::string, dogen::generation::meta_model::artefact_properties>& generatable_element::artefact_properties() const {
    return artefact_properties_;
}

std::unordered_map<std::string, dogen::generation::meta_model::artefact_properties>& generatable_element::artefact_properties() {
    return artefact_properties_;
}

void generatable_element::artefact_properties(const std::unordered_map<std::string, dogen::generation::meta_model::artefact_properties>& v) {
    artefact_properties_ = v;
}

void generatable_element::artefact_properties(const std::unordered_map<std::string, dogen::generation::meta_model::artefact_properties>&& v) {
    artefact_properties_ = std::move(v);
}

const std::unordered_map<std::string, dogen::generation::meta_model::local_archetype_location_properties>& generatable_element::archetype_location_properties() const {
    return archetype_location_properties_;
}

std::unordered_map<std::string, dogen::generation::meta_model::local_archetype_location_properties>& generatable_element::archetype_location_properties() {
    return archetype_location_properties_;
}

void generatable_element::archetype_location_properties(const std::unordered_map<std::string, dogen::generation::meta_model::local_archetype_location_properties>& v) {
    archetype_location_properties_ = v;
}

void generatable_element::archetype_location_properties(const std::unordered_map<std::string, dogen::generation::meta_model::local_archetype_location_properties>&& v) {
    archetype_location_properties_ = std::move(v);
}

} } }
