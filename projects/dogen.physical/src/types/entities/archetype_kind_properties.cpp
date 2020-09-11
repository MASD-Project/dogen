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
#include "dogen.physical/types/entities/archetype_kind_properties.hpp"

namespace dogen::physical::entities {

archetype_kind_properties::archetype_kind_properties(
    const dogen::identification::entities::physical_meta_name& meta_name,
    const std::string& file_extension)
    : meta_name_(meta_name),
      file_extension_(file_extension) { }

void archetype_kind_properties::swap(archetype_kind_properties& other) noexcept {
    using std::swap;
    swap(meta_name_, other.meta_name_);
    swap(file_extension_, other.file_extension_);
}

bool archetype_kind_properties::operator==(const archetype_kind_properties& rhs) const {
    return meta_name_ == rhs.meta_name_ &&
        file_extension_ == rhs.file_extension_;
}

archetype_kind_properties& archetype_kind_properties::operator=(archetype_kind_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::identification::entities::physical_meta_name& archetype_kind_properties::meta_name() const {
    return meta_name_;
}

dogen::identification::entities::physical_meta_name& archetype_kind_properties::meta_name() {
    return meta_name_;
}

void archetype_kind_properties::meta_name(const dogen::identification::entities::physical_meta_name& v) {
    meta_name_ = v;
}

void archetype_kind_properties::meta_name(const dogen::identification::entities::physical_meta_name&& v) {
    meta_name_ = std::move(v);
}

const std::string& archetype_kind_properties::file_extension() const {
    return file_extension_;
}

std::string& archetype_kind_properties::file_extension() {
    return file_extension_;
}

void archetype_kind_properties::file_extension(const std::string& v) {
    file_extension_ = v;
}

void archetype_kind_properties::file_extension(const std::string&& v) {
    file_extension_ = std::move(v);
}

}
