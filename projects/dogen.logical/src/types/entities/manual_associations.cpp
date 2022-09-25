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
#include "dogen.logical/types/entities/manual_associations.hpp"

namespace dogen::logical::entities {

manual_associations::manual_associations(
    const std::list<dogen::identification::entities::logical_name>& aggregation,
    const std::list<dogen::identification::entities::logical_name>& composition,
    const std::list<dogen::identification::entities::logical_name>& association)
    : aggregation_(aggregation),
      composition_(composition),
      association_(association) { }

void manual_associations::swap(manual_associations& other) noexcept {
    using std::swap;
    swap(aggregation_, other.aggregation_);
    swap(composition_, other.composition_);
    swap(association_, other.association_);
}

bool manual_associations::operator==(const manual_associations& rhs) const {
    return aggregation_ == rhs.aggregation_ &&
        composition_ == rhs.composition_ &&
        association_ == rhs.association_;
}

manual_associations& manual_associations::operator=(manual_associations other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::identification::entities::logical_name>& manual_associations::aggregation() const {
    return aggregation_;
}

std::list<dogen::identification::entities::logical_name>& manual_associations::aggregation() {
    return aggregation_;
}

void manual_associations::aggregation(const std::list<dogen::identification::entities::logical_name>& v) {
    aggregation_ = v;
}

void manual_associations::aggregation(const std::list<dogen::identification::entities::logical_name>&& v) {
    aggregation_ = std::move(v);
}

const std::list<dogen::identification::entities::logical_name>& manual_associations::composition() const {
    return composition_;
}

std::list<dogen::identification::entities::logical_name>& manual_associations::composition() {
    return composition_;
}

void manual_associations::composition(const std::list<dogen::identification::entities::logical_name>& v) {
    composition_ = v;
}

void manual_associations::composition(const std::list<dogen::identification::entities::logical_name>&& v) {
    composition_ = std::move(v);
}

const std::list<dogen::identification::entities::logical_name>& manual_associations::association() const {
    return association_;
}

std::list<dogen::identification::entities::logical_name>& manual_associations::association() {
    return association_;
}

void manual_associations::association(const std::list<dogen::identification::entities::logical_name>& v) {
    association_ = v;
}

void manual_associations::association(const std::list<dogen::identification::entities::logical_name>&& v) {
    association_ = std::move(v);
}

}
