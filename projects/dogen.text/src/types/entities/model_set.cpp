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
#include "dogen.text/types/entities/model_set.hpp"

namespace dogen::text::entities {

model_set::model_set(
    const dogen::identification::entities::logical_provenance& provenance,
    const std::list<dogen::text::entities::model>& models)
    : provenance_(provenance),
      models_(models) { }

void model_set::swap(model_set& other) noexcept {
    using std::swap;
    swap(provenance_, other.provenance_);
    swap(models_, other.models_);
}

bool model_set::operator==(const model_set& rhs) const {
    return provenance_ == rhs.provenance_ &&
        models_ == rhs.models_;
}

model_set& model_set::operator=(model_set other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::identification::entities::logical_provenance& model_set::provenance() const {
    return provenance_;
}

dogen::identification::entities::logical_provenance& model_set::provenance() {
    return provenance_;
}

void model_set::provenance(const dogen::identification::entities::logical_provenance& v) {
    provenance_ = v;
}

void model_set::provenance(const dogen::identification::entities::logical_provenance&& v) {
    provenance_ = std::move(v);
}

const std::list<dogen::text::entities::model>& model_set::models() const {
    return models_;
}

std::list<dogen::text::entities::model>& model_set::models() {
    return models_;
}

void model_set::models(const std::list<dogen::text::entities::model>& v) {
    models_ = v;
}

void model_set::models(const std::list<dogen::text::entities::model>&& v) {
    models_ = std::move(v);
}

}
