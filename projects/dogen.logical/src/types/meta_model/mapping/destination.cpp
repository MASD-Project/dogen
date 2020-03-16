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
#include "dogen.logical/types/meta_model/mapping/destination.hpp"

namespace dogen::logical::meta_model::mapping {

destination::destination()
    : technical_space_(static_cast<dogen::logical::meta_model::technical_space>(0)) { }

destination::destination(
    const dogen::logical::meta_model::name& name,
    const dogen::logical::meta_model::technical_space technical_space)
    : name_(name),
      technical_space_(technical_space) { }

void destination::swap(destination& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(technical_space_, other.technical_space_);
}

bool destination::operator==(const destination& rhs) const {
    return name_ == rhs.name_ &&
        technical_space_ == rhs.technical_space_;
}

destination& destination::operator=(destination other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::logical::meta_model::name& destination::name() const {
    return name_;
}

dogen::logical::meta_model::name& destination::name() {
    return name_;
}

void destination::name(const dogen::logical::meta_model::name& v) {
    name_ = v;
}

void destination::name(const dogen::logical::meta_model::name&& v) {
    name_ = std::move(v);
}

dogen::logical::meta_model::technical_space destination::technical_space() const {
    return technical_space_;
}

void destination::technical_space(const dogen::logical::meta_model::technical_space v) {
    technical_space_ = v;
}

}
