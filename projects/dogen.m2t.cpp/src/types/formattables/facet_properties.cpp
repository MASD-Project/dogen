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
#include "dogen.m2t.cpp/types/formattables/facet_properties.hpp"

namespace dogen::m2t::cpp::formattables {

facet_properties::facet_properties()
    : enabled_(static_cast<bool>(0)) { }

facet_properties::facet_properties(
    const std::string& directory,
    const bool enabled)
    : directory_(directory),
      enabled_(enabled) { }

void facet_properties::swap(facet_properties& other) noexcept {
    using std::swap;
    swap(directory_, other.directory_);
    swap(enabled_, other.enabled_);
}

bool facet_properties::operator==(const facet_properties& rhs) const {
    return directory_ == rhs.directory_ &&
        enabled_ == rhs.enabled_;
}

facet_properties& facet_properties::operator=(facet_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& facet_properties::directory() const {
    return directory_;
}

std::string& facet_properties::directory() {
    return directory_;
}

void facet_properties::directory(const std::string& v) {
    directory_ = v;
}

void facet_properties::directory(const std::string&& v) {
    directory_ = std::move(v);
}

bool facet_properties::enabled() const {
    return enabled_;
}

void facet_properties::enabled(const bool v) {
    enabled_ = v;
}

}
