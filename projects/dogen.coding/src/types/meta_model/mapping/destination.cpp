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
    : action_(static_cast<dogen::coding::meta_model::mapping::action>(0)),
      technical_space_(static_cast<dogen::coding::meta_model::technical_space>(0)) { }

destination::destination(
    const dogen::coding::meta_model::name& name,
    const dogen::coding::meta_model::mapping::action action,
    const dogen::coding::meta_model::technical_space technical_space)
    : name_(name),
      action_(action),
      technical_space_(technical_space) { }

void destination::swap(destination& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(action_, other.action_);
    swap(technical_space_, other.technical_space_);
}

bool destination::operator==(const destination& rhs) const {
    return name_ == rhs.name_ &&
        action_ == rhs.action_ &&
        technical_space_ == rhs.technical_space_;
}

destination& destination::operator=(destination other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::coding::meta_model::name& destination::name() const {
    return name_;
}

dogen::coding::meta_model::name& destination::name() {
    return name_;
}

void destination::name(const dogen::coding::meta_model::name& v) {
    name_ = v;
}

void destination::name(const dogen::coding::meta_model::name&& v) {
    name_ = std::move(v);
}

dogen::coding::meta_model::mapping::action destination::action() const {
    return action_;
}

void destination::action(const dogen::coding::meta_model::mapping::action v) {
    action_ = v;
}

dogen::coding::meta_model::technical_space destination::technical_space() const {
    return technical_space_;
}

void destination::technical_space(const dogen::coding::meta_model::technical_space v) {
    technical_space_ = v;
}

}
