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
#include "dogen/annotations/types/ownership_hierarchy.hpp"

namespace dogen {
namespace annotations {

ownership_hierarchy::ownership_hierarchy(
    const std::string& kernel,
    const std::string& facet,
    const std::string& archetype)
    : kernel_(kernel),
      facet_(facet),
      archetype_(archetype) { }

void ownership_hierarchy::swap(ownership_hierarchy& other) noexcept {
    using std::swap;
    swap(kernel_, other.kernel_);
    swap(facet_, other.facet_);
    swap(archetype_, other.archetype_);
}

bool ownership_hierarchy::operator==(const ownership_hierarchy& rhs) const {
    return kernel_ == rhs.kernel_ &&
        facet_ == rhs.facet_ &&
        archetype_ == rhs.archetype_;
}

ownership_hierarchy& ownership_hierarchy::operator=(ownership_hierarchy other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& ownership_hierarchy::kernel() const {
    return kernel_;
}

std::string& ownership_hierarchy::kernel() {
    return kernel_;
}

void ownership_hierarchy::kernel(const std::string& v) {
    kernel_ = v;
}

void ownership_hierarchy::kernel(const std::string&& v) {
    kernel_ = std::move(v);
}

const std::string& ownership_hierarchy::facet() const {
    return facet_;
}

std::string& ownership_hierarchy::facet() {
    return facet_;
}

void ownership_hierarchy::facet(const std::string& v) {
    facet_ = v;
}

void ownership_hierarchy::facet(const std::string&& v) {
    facet_ = std::move(v);
}

const std::string& ownership_hierarchy::archetype() const {
    return archetype_;
}

std::string& ownership_hierarchy::archetype() {
    return archetype_;
}

void ownership_hierarchy::archetype(const std::string& v) {
    archetype_ = v;
}

void ownership_hierarchy::archetype(const std::string&& v) {
    archetype_ = std::move(v);
}

} }
