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
#include "dogen.physical/types/entities/variable_relation.hpp"

namespace dogen::physical::entities {

variable_relation::variable_relation()
    : type_(static_cast<dogen::physical::entities::variable_relation_type>(0)) { }

variable_relation::variable_relation(
    const std::string& urn,
    const std::string& archetype_urn,
    const dogen::physical::entities::variable_relation_type type)
    : urn_(urn),
      archetype_urn_(archetype_urn),
      type_(type) { }

void variable_relation::swap(variable_relation& other) noexcept {
    using std::swap;
    swap(urn_, other.urn_);
    swap(archetype_urn_, other.archetype_urn_);
    swap(type_, other.type_);
}

bool variable_relation::operator==(const variable_relation& rhs) const {
    return urn_ == rhs.urn_ &&
        archetype_urn_ == rhs.archetype_urn_ &&
        type_ == rhs.type_;
}

variable_relation& variable_relation::operator=(variable_relation other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& variable_relation::urn() const {
    return urn_;
}

std::string& variable_relation::urn() {
    return urn_;
}

void variable_relation::urn(const std::string& v) {
    urn_ = v;
}

void variable_relation::urn(const std::string&& v) {
    urn_ = std::move(v);
}

const std::string& variable_relation::archetype_urn() const {
    return archetype_urn_;
}

std::string& variable_relation::archetype_urn() {
    return archetype_urn_;
}

void variable_relation::archetype_urn(const std::string& v) {
    archetype_urn_ = v;
}

void variable_relation::archetype_urn(const std::string&& v) {
    archetype_urn_ = std::move(v);
}

dogen::physical::entities::variable_relation_type variable_relation::type() const {
    return type_;
}

void variable_relation::type(const dogen::physical::entities::variable_relation_type v) {
    type_ = v;
}

}