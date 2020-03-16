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
#include "dogen.variability/types/entities/potential_binding.hpp"

namespace dogen::variability::entities {

potential_binding::potential_binding()
    : realized_(static_cast<bool>(0)) { }

potential_binding::potential_binding(
    const std::string& name,
    const bool realized)
    : name_(name),
      realized_(realized) { }

void potential_binding::swap(potential_binding& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(realized_, other.realized_);
}

bool potential_binding::operator==(const potential_binding& rhs) const {
    return name_ == rhs.name_ &&
        realized_ == rhs.realized_;
}

potential_binding& potential_binding::operator=(potential_binding other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& potential_binding::name() const {
    return name_;
}

std::string& potential_binding::name() {
    return name_;
}

void potential_binding::name(const std::string& v) {
    name_ = v;
}

void potential_binding::name(const std::string&& v) {
    name_ = std::move(v);
}

bool potential_binding::realized() const {
    return realized_;
}

void potential_binding::realized(const bool v) {
    realized_ = v;
}

}
