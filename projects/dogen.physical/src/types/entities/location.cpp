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
#include "dogen.physical/types/entities/location.hpp"

namespace dogen::physical::entities {

location::location(
    const std::string& kernel,
    const std::string& backend,
    const std::string& part,
    const std::string& facet,
    const std::string& archetype)
    : kernel_(kernel),
      backend_(backend),
      part_(part),
      facet_(facet),
      archetype_(archetype) { }

void location::swap(location& other) noexcept {
    using std::swap;
    swap(kernel_, other.kernel_);
    swap(backend_, other.backend_);
    swap(part_, other.part_);
    swap(facet_, other.facet_);
    swap(archetype_, other.archetype_);
}

bool location::operator==(const location& rhs) const {
    return kernel_ == rhs.kernel_ &&
        backend_ == rhs.backend_ &&
        part_ == rhs.part_ &&
        facet_ == rhs.facet_ &&
        archetype_ == rhs.archetype_;
}

location& location::operator=(location other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& location::kernel() const {
    return kernel_;
}

std::string& location::kernel() {
    return kernel_;
}

void location::kernel(const std::string& v) {
    kernel_ = v;
}

void location::kernel(const std::string&& v) {
    kernel_ = std::move(v);
}

const std::string& location::backend() const {
    return backend_;
}

std::string& location::backend() {
    return backend_;
}

void location::backend(const std::string& v) {
    backend_ = v;
}

void location::backend(const std::string&& v) {
    backend_ = std::move(v);
}

const std::string& location::part() const {
    return part_;
}

std::string& location::part() {
    return part_;
}

void location::part(const std::string& v) {
    part_ = v;
}

void location::part(const std::string&& v) {
    part_ = std::move(v);
}

const std::string& location::facet() const {
    return facet_;
}

std::string& location::facet() {
    return facet_;
}

void location::facet(const std::string& v) {
    facet_ = v;
}

void location::facet(const std::string&& v) {
    facet_ = std::move(v);
}

const std::string& location::archetype() const {
    return archetype_;
}

std::string& location::archetype() {
    return archetype_;
}

void location::archetype(const std::string& v) {
    archetype_ = v;
}

void location::archetype(const std::string&& v) {
    archetype_ = std::move(v);
}

}
