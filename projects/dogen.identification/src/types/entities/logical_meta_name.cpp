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
#include "dogen.identification/types/entities/logical_meta_name.hpp"

namespace dogen::identification::entities {

logical_meta_name::logical_meta_name(
    const std::string& simple,
    const dogen::identification::entities::logical_meta_id& qualified)
    : simple_(simple),
      qualified_(qualified) { }

void logical_meta_name::swap(logical_meta_name& other) noexcept {
    using std::swap;
    swap(simple_, other.simple_);
    swap(qualified_, other.qualified_);
}

bool logical_meta_name::operator==(const logical_meta_name& rhs) const {
    return simple_ == rhs.simple_ &&
        qualified_ == rhs.qualified_;
}

logical_meta_name& logical_meta_name::operator=(logical_meta_name other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& logical_meta_name::simple() const {
    return simple_;
}

std::string& logical_meta_name::simple() {
    return simple_;
}

void logical_meta_name::simple(const std::string& v) {
    simple_ = v;
}

void logical_meta_name::simple(const std::string&& v) {
    simple_ = std::move(v);
}

const dogen::identification::entities::logical_meta_id& logical_meta_name::qualified() const {
    return qualified_;
}

dogen::identification::entities::logical_meta_id& logical_meta_name::qualified() {
    return qualified_;
}

void logical_meta_name::qualified(const dogen::identification::entities::logical_meta_id& v) {
    qualified_ = v;
}

void logical_meta_name::qualified(const dogen::identification::entities::logical_meta_id&& v) {
    qualified_ = std::move(v);
}

}
