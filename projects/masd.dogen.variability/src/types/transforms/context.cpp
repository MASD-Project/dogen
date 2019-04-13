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
#include "masd.dogen.variability/types/transforms/context.hpp"

namespace masd::dogen::variability::transforms {

context::context(
    const masd::dogen::archetypes::location_repository& archetype_location_repository,
    const std::vector<boost::filesystem::path>& data_directories)
    : archetype_location_repository_(archetype_location_repository),
      data_directories_(data_directories) { }

void context::swap(context& other) noexcept {
    using std::swap;
    swap(archetype_location_repository_, other.archetype_location_repository_);
    swap(data_directories_, other.data_directories_);
}

bool context::operator==(const context& rhs) const {
    return archetype_location_repository_ == rhs.archetype_location_repository_ &&
        data_directories_ == rhs.data_directories_;
}

context& context::operator=(context other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const masd::dogen::archetypes::location_repository& context::archetype_location_repository() const {
    return archetype_location_repository_;
}

masd::dogen::archetypes::location_repository& context::archetype_location_repository() {
    return archetype_location_repository_;
}

void context::archetype_location_repository(const masd::dogen::archetypes::location_repository& v) {
    archetype_location_repository_ = v;
}

void context::archetype_location_repository(const masd::dogen::archetypes::location_repository&& v) {
    archetype_location_repository_ = std::move(v);
}

const std::vector<boost::filesystem::path>& context::data_directories() const {
    return data_directories_;
}

std::vector<boost::filesystem::path>& context::data_directories() {
    return data_directories_;
}

void context::data_directories(const std::vector<boost::filesystem::path>& v) {
    data_directories_ = v;
}

void context::data_directories(const std::vector<boost::filesystem::path>&& v) {
    data_directories_ = std::move(v);
}

}
