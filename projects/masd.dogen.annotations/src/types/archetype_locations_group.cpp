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
#include "masd.dogen.annotations/types/archetype_locations_group.hpp"

namespace masd::dogen::annotations {

archetype_locations_group::archetype_locations_group(
    const std::list<masd::dogen::annotations::archetype_location>& archetype_locations,
    const std::unordered_map<std::string, std::string>& canonical_archetype_locations)
    : archetype_locations_(archetype_locations),
      canonical_archetype_locations_(canonical_archetype_locations) { }

void archetype_locations_group::swap(archetype_locations_group& other) noexcept {
    using std::swap;
    swap(archetype_locations_, other.archetype_locations_);
    swap(canonical_archetype_locations_, other.canonical_archetype_locations_);
}

bool archetype_locations_group::operator==(const archetype_locations_group& rhs) const {
    return archetype_locations_ == rhs.archetype_locations_ &&
        canonical_archetype_locations_ == rhs.canonical_archetype_locations_;
}

archetype_locations_group& archetype_locations_group::operator=(archetype_locations_group other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<masd::dogen::annotations::archetype_location>& archetype_locations_group::archetype_locations() const {
    return archetype_locations_;
}

std::list<masd::dogen::annotations::archetype_location>& archetype_locations_group::archetype_locations() {
    return archetype_locations_;
}

void archetype_locations_group::archetype_locations(const std::list<masd::dogen::annotations::archetype_location>& v) {
    archetype_locations_ = v;
}

void archetype_locations_group::archetype_locations(const std::list<masd::dogen::annotations::archetype_location>&& v) {
    archetype_locations_ = std::move(v);
}

const std::unordered_map<std::string, std::string>& archetype_locations_group::canonical_archetype_locations() const {
    return canonical_archetype_locations_;
}

std::unordered_map<std::string, std::string>& archetype_locations_group::canonical_archetype_locations() {
    return canonical_archetype_locations_;
}

void archetype_locations_group::canonical_archetype_locations(const std::unordered_map<std::string, std::string>& v) {
    canonical_archetype_locations_ = v;
}

void archetype_locations_group::canonical_archetype_locations(const std::unordered_map<std::string, std::string>&& v) {
    canonical_archetype_locations_ = std::move(v);
}

}
