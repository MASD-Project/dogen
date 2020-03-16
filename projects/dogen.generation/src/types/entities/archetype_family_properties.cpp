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
#include "dogen.generation/types/entities/archetype_family_properties.hpp"

namespace dogen::generation::entities {

archetype_family_properties::archetype_family_properties(const std::string& extension)
    : extension_(extension) { }

void archetype_family_properties::swap(archetype_family_properties& other) noexcept {
    using std::swap;
    swap(extension_, other.extension_);
}

bool archetype_family_properties::operator==(const archetype_family_properties& rhs) const {
    return extension_ == rhs.extension_;
}

archetype_family_properties& archetype_family_properties::operator=(archetype_family_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& archetype_family_properties::extension() const {
    return extension_;
}

std::string& archetype_family_properties::extension() {
    return extension_;
}

void archetype_family_properties::extension(const std::string& v) {
    extension_ = v;
}

void archetype_family_properties::extension(const std::string&& v) {
    extension_ = std::move(v);
}

}
