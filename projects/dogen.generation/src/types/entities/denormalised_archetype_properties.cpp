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
#include "dogen.generation/types/entities/denormalised_archetype_properties.hpp"

namespace dogen::generation::entities {

denormalised_archetype_properties::denormalised_archetype_properties()
    : backend_enabled_(static_cast<bool>(0)),
      facet_enabled_(static_cast<bool>(0)),
      facet_overwrite_(static_cast<bool>(0)),
      archetype_enabled_(static_cast<bool>(0)) { }

denormalised_archetype_properties::denormalised_archetype_properties(denormalised_archetype_properties&& rhs)
    : backend_enabled_(std::move(rhs.backend_enabled_)),
      backend_directory_(std::move(rhs.backend_directory_)),
      facet_enabled_(std::move(rhs.facet_enabled_)),
      facet_overwrite_(std::move(rhs.facet_overwrite_)),
      facet_directory_(std::move(rhs.facet_directory_)),
      facet_postfix_(std::move(rhs.facet_postfix_)),
      archetype_enabled_(std::move(rhs.archetype_enabled_)),
      archetype_overwrite_(std::move(rhs.archetype_overwrite_)),
      archetype_postfix_(std::move(rhs.archetype_postfix_)) { }

denormalised_archetype_properties::denormalised_archetype_properties(
    const bool backend_enabled,
    const std::string& backend_directory,
    const bool facet_enabled,
    const bool facet_overwrite,
    const std::string& facet_directory,
    const std::string& facet_postfix,
    const bool archetype_enabled,
    const boost::optional<bool>& archetype_overwrite,
    const std::string& archetype_postfix)
    : backend_enabled_(backend_enabled),
      backend_directory_(backend_directory),
      facet_enabled_(facet_enabled),
      facet_overwrite_(facet_overwrite),
      facet_directory_(facet_directory),
      facet_postfix_(facet_postfix),
      archetype_enabled_(archetype_enabled),
      archetype_overwrite_(archetype_overwrite),
      archetype_postfix_(archetype_postfix) { }

void denormalised_archetype_properties::swap(denormalised_archetype_properties& other) noexcept {
    using std::swap;
    swap(backend_enabled_, other.backend_enabled_);
    swap(backend_directory_, other.backend_directory_);
    swap(facet_enabled_, other.facet_enabled_);
    swap(facet_overwrite_, other.facet_overwrite_);
    swap(facet_directory_, other.facet_directory_);
    swap(facet_postfix_, other.facet_postfix_);
    swap(archetype_enabled_, other.archetype_enabled_);
    swap(archetype_overwrite_, other.archetype_overwrite_);
    swap(archetype_postfix_, other.archetype_postfix_);
}

bool denormalised_archetype_properties::operator==(const denormalised_archetype_properties& rhs) const {
    return backend_enabled_ == rhs.backend_enabled_ &&
        backend_directory_ == rhs.backend_directory_ &&
        facet_enabled_ == rhs.facet_enabled_ &&
        facet_overwrite_ == rhs.facet_overwrite_ &&
        facet_directory_ == rhs.facet_directory_ &&
        facet_postfix_ == rhs.facet_postfix_ &&
        archetype_enabled_ == rhs.archetype_enabled_ &&
        archetype_overwrite_ == rhs.archetype_overwrite_ &&
        archetype_postfix_ == rhs.archetype_postfix_;
}

denormalised_archetype_properties& denormalised_archetype_properties::operator=(denormalised_archetype_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool denormalised_archetype_properties::backend_enabled() const {
    return backend_enabled_;
}

void denormalised_archetype_properties::backend_enabled(const bool v) {
    backend_enabled_ = v;
}

const std::string& denormalised_archetype_properties::backend_directory() const {
    return backend_directory_;
}

std::string& denormalised_archetype_properties::backend_directory() {
    return backend_directory_;
}

void denormalised_archetype_properties::backend_directory(const std::string& v) {
    backend_directory_ = v;
}

void denormalised_archetype_properties::backend_directory(const std::string&& v) {
    backend_directory_ = std::move(v);
}

bool denormalised_archetype_properties::facet_enabled() const {
    return facet_enabled_;
}

void denormalised_archetype_properties::facet_enabled(const bool v) {
    facet_enabled_ = v;
}

bool denormalised_archetype_properties::facet_overwrite() const {
    return facet_overwrite_;
}

void denormalised_archetype_properties::facet_overwrite(const bool v) {
    facet_overwrite_ = v;
}

const std::string& denormalised_archetype_properties::facet_directory() const {
    return facet_directory_;
}

std::string& denormalised_archetype_properties::facet_directory() {
    return facet_directory_;
}

void denormalised_archetype_properties::facet_directory(const std::string& v) {
    facet_directory_ = v;
}

void denormalised_archetype_properties::facet_directory(const std::string&& v) {
    facet_directory_ = std::move(v);
}

const std::string& denormalised_archetype_properties::facet_postfix() const {
    return facet_postfix_;
}

std::string& denormalised_archetype_properties::facet_postfix() {
    return facet_postfix_;
}

void denormalised_archetype_properties::facet_postfix(const std::string& v) {
    facet_postfix_ = v;
}

void denormalised_archetype_properties::facet_postfix(const std::string&& v) {
    facet_postfix_ = std::move(v);
}

bool denormalised_archetype_properties::archetype_enabled() const {
    return archetype_enabled_;
}

void denormalised_archetype_properties::archetype_enabled(const bool v) {
    archetype_enabled_ = v;
}

const boost::optional<bool>& denormalised_archetype_properties::archetype_overwrite() const {
    return archetype_overwrite_;
}

boost::optional<bool>& denormalised_archetype_properties::archetype_overwrite() {
    return archetype_overwrite_;
}

void denormalised_archetype_properties::archetype_overwrite(const boost::optional<bool>& v) {
    archetype_overwrite_ = v;
}

void denormalised_archetype_properties::archetype_overwrite(const boost::optional<bool>&& v) {
    archetype_overwrite_ = std::move(v);
}

const std::string& denormalised_archetype_properties::archetype_postfix() const {
    return archetype_postfix_;
}

std::string& denormalised_archetype_properties::archetype_postfix() {
    return archetype_postfix_;
}

void denormalised_archetype_properties::archetype_postfix(const std::string& v) {
    archetype_postfix_ = v;
}

void denormalised_archetype_properties::archetype_postfix(const std::string&& v) {
    archetype_postfix_ = std::move(v);
}

}
