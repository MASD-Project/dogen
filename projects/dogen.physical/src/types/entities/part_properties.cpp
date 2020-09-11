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
#include "dogen.physical/types/entities/part_properties.hpp"

namespace dogen::physical::entities {

part_properties::part_properties(
    const dogen::identification::entities::physical_meta_name& meta_name,
    const std::string& directory)
    : meta_name_(meta_name),
      directory_(directory) { }

void part_properties::swap(part_properties& other) noexcept {
    using std::swap;
    swap(meta_name_, other.meta_name_);
    swap(directory_, other.directory_);
}

bool part_properties::operator==(const part_properties& rhs) const {
    return meta_name_ == rhs.meta_name_ &&
        directory_ == rhs.directory_;
}

part_properties& part_properties::operator=(part_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::identification::entities::physical_meta_name& part_properties::meta_name() const {
    return meta_name_;
}

dogen::identification::entities::physical_meta_name& part_properties::meta_name() {
    return meta_name_;
}

void part_properties::meta_name(const dogen::identification::entities::physical_meta_name& v) {
    meta_name_ = v;
}

void part_properties::meta_name(const dogen::identification::entities::physical_meta_name&& v) {
    meta_name_ = std::move(v);
}

const std::string& part_properties::directory() const {
    return directory_;
}

std::string& part_properties::directory() {
    return directory_;
}

void part_properties::directory(const std::string& v) {
    directory_ = v;
}

void part_properties::directory(const std::string&& v) {
    directory_ = std::move(v);
}

}
