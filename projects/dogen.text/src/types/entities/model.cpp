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
#include "dogen.text/types/entities/model.hpp"

namespace dogen::text::entities {

model::model(
    const dogen::identification::entities::logical_provenance& provenance,
    const dogen::logical::entities::model& logical,
    const dogen::physical::entities::model& physical,
    const std::list<dogen::text::entities::logical_physical_region>& logical_physical_regions)
    : provenance_(provenance),
      logical_(logical),
      physical_(physical),
      logical_physical_regions_(logical_physical_regions) { }

void model::swap(model& other) noexcept {
    using std::swap;
    swap(provenance_, other.provenance_);
    swap(logical_, other.logical_);
    swap(physical_, other.physical_);
    swap(logical_physical_regions_, other.logical_physical_regions_);
}

bool model::operator==(const model& rhs) const {
    return provenance_ == rhs.provenance_ &&
        logical_ == rhs.logical_ &&
        physical_ == rhs.physical_ &&
        logical_physical_regions_ == rhs.logical_physical_regions_;
}

model& model::operator=(model other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::identification::entities::logical_provenance& model::provenance() const {
    return provenance_;
}

dogen::identification::entities::logical_provenance& model::provenance() {
    return provenance_;
}

void model::provenance(const dogen::identification::entities::logical_provenance& v) {
    provenance_ = v;
}

void model::provenance(const dogen::identification::entities::logical_provenance&& v) {
    provenance_ = std::move(v);
}

const dogen::logical::entities::model& model::logical() const {
    return logical_;
}

dogen::logical::entities::model& model::logical() {
    return logical_;
}

void model::logical(const dogen::logical::entities::model& v) {
    logical_ = v;
}

void model::logical(const dogen::logical::entities::model&& v) {
    logical_ = std::move(v);
}

const dogen::physical::entities::model& model::physical() const {
    return physical_;
}

dogen::physical::entities::model& model::physical() {
    return physical_;
}

void model::physical(const dogen::physical::entities::model& v) {
    physical_ = v;
}

void model::physical(const dogen::physical::entities::model&& v) {
    physical_ = std::move(v);
}

const std::list<dogen::text::entities::logical_physical_region>& model::logical_physical_regions() const {
    return logical_physical_regions_;
}

std::list<dogen::text::entities::logical_physical_region>& model::logical_physical_regions() {
    return logical_physical_regions_;
}

void model::logical_physical_regions(const std::list<dogen::text::entities::logical_physical_region>& v) {
    logical_physical_regions_ = v;
}

void model::logical_physical_regions(const std::list<dogen::text::entities::logical_physical_region>&& v) {
    logical_physical_regions_ = std::move(v);
}

}
