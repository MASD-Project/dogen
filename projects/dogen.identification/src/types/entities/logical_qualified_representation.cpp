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
#include "dogen.identification/types/entities/logical_qualified_representation.hpp"

namespace dogen::identification::entities {

logical_qualified_representation::logical_qualified_representation(
    const std::string& dot,
    const std::string& colon,
    const std::string& identifiable,
    const dogen::identification::entities::logical_id& id)
    : dot_(dot),
      colon_(colon),
      identifiable_(identifiable),
      id_(id) { }

void logical_qualified_representation::swap(logical_qualified_representation& other) noexcept {
    using std::swap;
    swap(dot_, other.dot_);
    swap(colon_, other.colon_);
    swap(identifiable_, other.identifiable_);
    swap(id_, other.id_);
}

bool logical_qualified_representation::operator==(const logical_qualified_representation& rhs) const {
    return dot_ == rhs.dot_ &&
        colon_ == rhs.colon_ &&
        identifiable_ == rhs.identifiable_ &&
        id_ == rhs.id_;
}

logical_qualified_representation& logical_qualified_representation::operator=(logical_qualified_representation other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& logical_qualified_representation::dot() const {
    return dot_;
}

std::string& logical_qualified_representation::dot() {
    return dot_;
}

void logical_qualified_representation::dot(const std::string& v) {
    dot_ = v;
}

void logical_qualified_representation::dot(const std::string&& v) {
    dot_ = std::move(v);
}

const std::string& logical_qualified_representation::colon() const {
    return colon_;
}

std::string& logical_qualified_representation::colon() {
    return colon_;
}

void logical_qualified_representation::colon(const std::string& v) {
    colon_ = v;
}

void logical_qualified_representation::colon(const std::string&& v) {
    colon_ = std::move(v);
}

const std::string& logical_qualified_representation::identifiable() const {
    return identifiable_;
}

std::string& logical_qualified_representation::identifiable() {
    return identifiable_;
}

void logical_qualified_representation::identifiable(const std::string& v) {
    identifiable_ = v;
}

void logical_qualified_representation::identifiable(const std::string&& v) {
    identifiable_ = std::move(v);
}

const dogen::identification::entities::logical_id& logical_qualified_representation::id() const {
    return id_;
}

dogen::identification::entities::logical_id& logical_qualified_representation::id() {
    return id_;
}

void logical_qualified_representation::id(const dogen::identification::entities::logical_id& v) {
    id_ = v;
}

void logical_qualified_representation::id(const dogen::identification::entities::logical_id&& v) {
    id_ = std::move(v);
}

}
