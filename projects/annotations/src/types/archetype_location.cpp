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
#include "dogen/annotations/types/archetype_location.hpp"

namespace dogen {
namespace annotations {

archetype_location::archetype_location(
    const std::string& family,
    const std::string& kernel,
    const std::string& facet,
    const std::string& archetype)
    : family_(family),
      kernel_(kernel),
      facet_(facet),
      archetype_(archetype) { }

void archetype_location::swap(archetype_location& other) noexcept {
    using std::swap;
    swap(family_, other.family_);
    swap(kernel_, other.kernel_);
    swap(facet_, other.facet_);
    swap(archetype_, other.archetype_);
}

bool archetype_location::operator==(const archetype_location& rhs) const {
    return family_ == rhs.family_ &&
        kernel_ == rhs.kernel_ &&
        facet_ == rhs.facet_ &&
        archetype_ == rhs.archetype_;
}

archetype_location& archetype_location::operator=(archetype_location other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& archetype_location::family() const {
    return family_;
}

std::string& archetype_location::family() {
    return family_;
}

void archetype_location::family(const std::string& v) {
    family_ = v;
}

void archetype_location::family(const std::string&& v) {
    family_ = std::move(v);
}

const std::string& archetype_location::kernel() const {
    return kernel_;
}

std::string& archetype_location::kernel() {
    return kernel_;
}

void archetype_location::kernel(const std::string& v) {
    kernel_ = v;
}

void archetype_location::kernel(const std::string&& v) {
    kernel_ = std::move(v);
}

const std::string& archetype_location::facet() const {
    return facet_;
}

std::string& archetype_location::facet() {
    return facet_;
}

void archetype_location::facet(const std::string& v) {
    facet_ = v;
}

void archetype_location::facet(const std::string&& v) {
    facet_ = std::move(v);
}

const std::string& archetype_location::archetype() const {
    return archetype_;
}

std::string& archetype_location::archetype() {
    return archetype_;
}

void archetype_location::archetype(const std::string& v) {
    archetype_ = v;
}

void archetype_location::archetype(const std::string&& v) {
    archetype_ = std::move(v);
}

} }
