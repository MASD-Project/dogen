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
#include "dogen.coding/types/meta_model/mapping/destination.hpp"

namespace dogen::coding::meta_model::mapping {

destination::destination()
    : action_(static_cast<dogen::coding::meta_model::mapping::action>(0)) { }

destination::destination(
    const std::string& element_id,
    const dogen::coding::meta_model::mapping::action action)
    : element_id_(element_id),
      action_(action) { }

void destination::swap(destination& other) noexcept {
    using std::swap;
    swap(element_id_, other.element_id_);
    swap(action_, other.action_);
}

bool destination::operator==(const destination& rhs) const {
    return element_id_ == rhs.element_id_ &&
        action_ == rhs.action_;
}

destination& destination::operator=(destination other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& destination::element_id() const {
    return element_id_;
}

std::string& destination::element_id() {
    return element_id_;
}

void destination::element_id(const std::string& v) {
    element_id_ = v;
}

void destination::element_id(const std::string&& v) {
    element_id_ = std::move(v);
}

dogen::coding::meta_model::mapping::action destination::action() const {
    return action_;
}

void destination::action(const dogen::coding::meta_model::mapping::action v) {
    action_ = v;
}

}
