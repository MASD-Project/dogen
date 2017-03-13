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
#include "dogen/test_models/northwind/types/territory.hpp"

namespace dogen {
namespace test_models {
namespace northwind {

territory::territory(
    const dogen::test_models::northwind::territory_id& territory_id,
    const std::string& territory_description,
    const dogen::test_models::northwind::region_id& region_id)
    : territory_id_(territory_id),
      territory_description_(territory_description),
      region_id_(region_id) { }

void territory::swap(territory& other) noexcept {
    using std::swap;
    swap(territory_id_, other.territory_id_);
    swap(territory_description_, other.territory_description_);
    swap(region_id_, other.region_id_);
}

bool territory::operator==(const territory& rhs) const {
    return territory_id_ == rhs.territory_id_ &&
        territory_description_ == rhs.territory_description_ &&
        region_id_ == rhs.region_id_;
}

territory& territory::operator=(territory other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::test_models::northwind::territory_id& territory::territory_id() const {
    return territory_id_;
}

dogen::test_models::northwind::territory_id& territory::territory_id() {
    return territory_id_;
}

void territory::territory_id(const dogen::test_models::northwind::territory_id& v) {
    territory_id_ = v;
}

void territory::territory_id(const dogen::test_models::northwind::territory_id&& v) {
    territory_id_ = std::move(v);
}

const std::string& territory::territory_description() const {
    return territory_description_;
}

std::string& territory::territory_description() {
    return territory_description_;
}

void territory::territory_description(const std::string& v) {
    territory_description_ = v;
}

void territory::territory_description(const std::string&& v) {
    territory_description_ = std::move(v);
}

const dogen::test_models::northwind::region_id& territory::region_id() const {
    return region_id_;
}

dogen::test_models::northwind::region_id& territory::region_id() {
    return region_id_;
}

void territory::region_id(const dogen::test_models::northwind::region_id& v) {
    region_id_ = v;
}

void territory::region_id(const dogen::test_models::northwind::region_id&& v) {
    region_id_ = std::move(v);
}

} } }
