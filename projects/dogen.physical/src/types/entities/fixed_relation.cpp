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
#include "dogen.physical/types/entities/fixed_relation.hpp"

namespace dogen::physical::entities {

fixed_relation::fixed_relation(
    const std::string& urn,
    const std::string& archetype_urn,
    const std::string& logical_model_element_id)
    : urn_(urn),
      archetype_urn_(archetype_urn),
      logical_model_element_id_(logical_model_element_id) { }

void fixed_relation::swap(fixed_relation& other) noexcept {
    using std::swap;
    swap(urn_, other.urn_);
    swap(archetype_urn_, other.archetype_urn_);
    swap(logical_model_element_id_, other.logical_model_element_id_);
}

bool fixed_relation::operator==(const fixed_relation& rhs) const {
    return urn_ == rhs.urn_ &&
        archetype_urn_ == rhs.archetype_urn_ &&
        logical_model_element_id_ == rhs.logical_model_element_id_;
}

fixed_relation& fixed_relation::operator=(fixed_relation other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& fixed_relation::urn() const {
    return urn_;
}

std::string& fixed_relation::urn() {
    return urn_;
}

void fixed_relation::urn(const std::string& v) {
    urn_ = v;
}

void fixed_relation::urn(const std::string&& v) {
    urn_ = std::move(v);
}

const std::string& fixed_relation::archetype_urn() const {
    return archetype_urn_;
}

std::string& fixed_relation::archetype_urn() {
    return archetype_urn_;
}

void fixed_relation::archetype_urn(const std::string& v) {
    archetype_urn_ = v;
}

void fixed_relation::archetype_urn(const std::string&& v) {
    archetype_urn_ = std::move(v);
}

const std::string& fixed_relation::logical_model_element_id() const {
    return logical_model_element_id_;
}

std::string& fixed_relation::logical_model_element_id() {
    return logical_model_element_id_;
}

void fixed_relation::logical_model_element_id(const std::string& v) {
    logical_model_element_id_ = v;
}

void fixed_relation::logical_model_element_id(const std::string&& v) {
    logical_model_element_id_ = std::move(v);
}

}
