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
#include "dogen.identification/types/entities/logical_meta_physical_id.hpp"

namespace dogen::identification::entities {

logical_meta_physical_id::logical_meta_physical_id(
    const dogen::identification::entities::logical_id& logical_id,
    const dogen::identification::entities::physical_meta_id& physical_id)
    : logical_id_(logical_id),
      physical_id_(physical_id) { }

void logical_meta_physical_id::swap(logical_meta_physical_id& other) noexcept {
    using std::swap;
    swap(logical_id_, other.logical_id_);
    swap(physical_id_, other.physical_id_);
}

bool logical_meta_physical_id::operator==(const logical_meta_physical_id& rhs) const {
    return logical_id_ == rhs.logical_id_ &&
        physical_id_ == rhs.physical_id_;
}

logical_meta_physical_id& logical_meta_physical_id::operator=(logical_meta_physical_id other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::identification::entities::logical_id& logical_meta_physical_id::logical_id() const {
    return logical_id_;
}

dogen::identification::entities::logical_id& logical_meta_physical_id::logical_id() {
    return logical_id_;
}

void logical_meta_physical_id::logical_id(const dogen::identification::entities::logical_id& v) {
    logical_id_ = v;
}

void logical_meta_physical_id::logical_id(const dogen::identification::entities::logical_id&& v) {
    logical_id_ = std::move(v);
}

const dogen::identification::entities::physical_meta_id& logical_meta_physical_id::physical_id() const {
    return physical_id_;
}

dogen::identification::entities::physical_meta_id& logical_meta_physical_id::physical_id() {
    return physical_id_;
}

void logical_meta_physical_id::physical_id(const dogen::identification::entities::physical_meta_id& v) {
    physical_id_ = v;
}

void logical_meta_physical_id::physical_id(const dogen::identification::entities::physical_meta_id&& v) {
    physical_id_ = std::move(v);
}

}
