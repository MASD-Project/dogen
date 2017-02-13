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
#include "dogen/test_models/database/types/northwind/region.hpp"

namespace dogen {
namespace test_models {
namespace database {
namespace northwind {

region::region(
    const dogen::test_models::database::northwind::region_id& region_id,
    const std::string& region_description)
    : region_id_(region_id),
      region_description_(region_description) { }

void region::swap(region& other) noexcept {
    using std::swap;
    swap(region_id_, other.region_id_);
    swap(region_description_, other.region_description_);
}

bool region::operator==(const region& rhs) const {
    return region_id_ == rhs.region_id_ &&
        region_description_ == rhs.region_description_;
}

region& region::operator=(region other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::test_models::database::northwind::region_id& region::region_id() const {
    return region_id_;
}

dogen::test_models::database::northwind::region_id& region::region_id() {
    return region_id_;
}

void region::region_id(const dogen::test_models::database::northwind::region_id& v) {
    region_id_ = v;
}

void region::region_id(const dogen::test_models::database::northwind::region_id&& v) {
    region_id_ = std::move(v);
}

const std::string& region::region_description() const {
    return region_description_;
}

std::string& region::region_description() {
    return region_description_;
}

void region::region_description(const std::string& v) {
    region_description_ = v;
}

void region::region_description(const std::string&& v) {
    region_description_ = std::move(v);
}

} } } }
