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
#include "dogen.physical/types/entities/constant_relation.hpp"

namespace dogen::physical::entities {

constant_relation::constant_relation(
    const std::string& urn,
    const std::string& archetype_urn,
    const std::list<dogen::physical::entities::label>& labels,
    const std::string& logical_model_element_id)
    : urn_(urn),
      archetype_urn_(archetype_urn),
      labels_(labels),
      logical_model_element_id_(logical_model_element_id) { }

void constant_relation::swap(constant_relation& other) noexcept {
    using std::swap;
    swap(urn_, other.urn_);
    swap(archetype_urn_, other.archetype_urn_);
    swap(labels_, other.labels_);
    swap(logical_model_element_id_, other.logical_model_element_id_);
}

bool constant_relation::operator==(const constant_relation& rhs) const {
    return urn_ == rhs.urn_ &&
        archetype_urn_ == rhs.archetype_urn_ &&
        labels_ == rhs.labels_ &&
        logical_model_element_id_ == rhs.logical_model_element_id_;
}

constant_relation& constant_relation::operator=(constant_relation other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& constant_relation::urn() const {
    return urn_;
}

std::string& constant_relation::urn() {
    return urn_;
}

void constant_relation::urn(const std::string& v) {
    urn_ = v;
}

void constant_relation::urn(const std::string&& v) {
    urn_ = std::move(v);
}

const std::string& constant_relation::archetype_urn() const {
    return archetype_urn_;
}

std::string& constant_relation::archetype_urn() {
    return archetype_urn_;
}

void constant_relation::archetype_urn(const std::string& v) {
    archetype_urn_ = v;
}

void constant_relation::archetype_urn(const std::string&& v) {
    archetype_urn_ = std::move(v);
}

const std::list<dogen::physical::entities::label>& constant_relation::labels() const {
    return labels_;
}

std::list<dogen::physical::entities::label>& constant_relation::labels() {
    return labels_;
}

void constant_relation::labels(const std::list<dogen::physical::entities::label>& v) {
    labels_ = v;
}

void constant_relation::labels(const std::list<dogen::physical::entities::label>&& v) {
    labels_ = std::move(v);
}

const std::string& constant_relation::logical_model_element_id() const {
    return logical_model_element_id_;
}

std::string& constant_relation::logical_model_element_id() {
    return logical_model_element_id_;
}

void constant_relation::logical_model_element_id(const std::string& v) {
    logical_model_element_id_ = v;
}

void constant_relation::logical_model_element_id(const std::string&& v) {
    logical_model_element_id_ = std::move(v);
}

}
