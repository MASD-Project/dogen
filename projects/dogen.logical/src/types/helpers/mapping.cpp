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
#include "dogen.logical/types/helpers/mapping.hpp"

namespace dogen::logical::helpers {

mapping::mapping(
    const std::string& agnostic_id,
    const std::unordered_map<dogen::logical::entities::technical_space, dogen::logical::helpers::mapping_value>& by_technical_space)
    : agnostic_id_(agnostic_id),
      by_technical_space_(by_technical_space) { }

void mapping::swap(mapping& other) noexcept {
    using std::swap;
    swap(agnostic_id_, other.agnostic_id_);
    swap(by_technical_space_, other.by_technical_space_);
}

bool mapping::operator==(const mapping& rhs) const {
    return agnostic_id_ == rhs.agnostic_id_ &&
        by_technical_space_ == rhs.by_technical_space_;
}

mapping& mapping::operator=(mapping other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& mapping::agnostic_id() const {
    return agnostic_id_;
}

std::string& mapping::agnostic_id() {
    return agnostic_id_;
}

void mapping::agnostic_id(const std::string& v) {
    agnostic_id_ = v;
}

void mapping::agnostic_id(const std::string&& v) {
    agnostic_id_ = std::move(v);
}

const std::unordered_map<dogen::logical::entities::technical_space, dogen::logical::helpers::mapping_value>& mapping::by_technical_space() const {
    return by_technical_space_;
}

std::unordered_map<dogen::logical::entities::technical_space, dogen::logical::helpers::mapping_value>& mapping::by_technical_space() {
    return by_technical_space_;
}

void mapping::by_technical_space(const std::unordered_map<dogen::logical::entities::technical_space, dogen::logical::helpers::mapping_value>& v) {
    by_technical_space_ = v;
}

void mapping::by_technical_space(const std::unordered_map<dogen::logical::entities::technical_space, dogen::logical::helpers::mapping_value>&& v) {
    by_technical_space_ = std::move(v);
}

}
