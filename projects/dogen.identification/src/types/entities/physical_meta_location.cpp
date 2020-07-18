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
#include "dogen.identification/types/entities/physical_meta_location.hpp"

namespace dogen::identification::entities {

physical_meta_location::physical_meta_location(
    const std::string& meta_model,
    const std::string& backend,
    const std::string& facet,
    const std::string& archetype)
    : meta_model_(meta_model),
      backend_(backend),
      facet_(facet),
      archetype_(archetype) { }

void physical_meta_location::swap(physical_meta_location& other) noexcept {
    using std::swap;
    swap(meta_model_, other.meta_model_);
    swap(backend_, other.backend_);
    swap(facet_, other.facet_);
    swap(archetype_, other.archetype_);
}

bool physical_meta_location::operator==(const physical_meta_location& rhs) const {
    return meta_model_ == rhs.meta_model_ &&
        backend_ == rhs.backend_ &&
        facet_ == rhs.facet_ &&
        archetype_ == rhs.archetype_;
}

physical_meta_location& physical_meta_location::operator=(physical_meta_location other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& physical_meta_location::meta_model() const {
    return meta_model_;
}

std::string& physical_meta_location::meta_model() {
    return meta_model_;
}

void physical_meta_location::meta_model(const std::string& v) {
    meta_model_ = v;
}

void physical_meta_location::meta_model(const std::string&& v) {
    meta_model_ = std::move(v);
}

const std::string& physical_meta_location::backend() const {
    return backend_;
}

std::string& physical_meta_location::backend() {
    return backend_;
}

void physical_meta_location::backend(const std::string& v) {
    backend_ = v;
}

void physical_meta_location::backend(const std::string&& v) {
    backend_ = std::move(v);
}

const std::string& physical_meta_location::facet() const {
    return facet_;
}

std::string& physical_meta_location::facet() {
    return facet_;
}

void physical_meta_location::facet(const std::string& v) {
    facet_ = v;
}

void physical_meta_location::facet(const std::string&& v) {
    facet_ = std::move(v);
}

const std::string& physical_meta_location::archetype() const {
    return archetype_;
}

std::string& physical_meta_location::archetype() {
    return archetype_;
}

void physical_meta_location::archetype(const std::string& v) {
    archetype_ = v;
}

void physical_meta_location::archetype(const std::string&& v) {
    archetype_ = std::move(v);
}

}
