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
#include "dogen.physical/types/entities/enablement_flags.hpp"

namespace dogen::physical::entities {

enablement_flags::enablement_flags()
    : backend_enabled_(static_cast<bool>(0)),
      facet_enabled_(static_cast<bool>(0)),
      facet_overwrite_(static_cast<bool>(0)),
      archetype_enabled_(static_cast<bool>(0)) { }

enablement_flags::enablement_flags(enablement_flags&& rhs)
    : backend_enabled_(std::move(rhs.backend_enabled_)),
      facet_enabled_(std::move(rhs.facet_enabled_)),
      facet_overwrite_(std::move(rhs.facet_overwrite_)),
      archetype_enabled_(std::move(rhs.archetype_enabled_)),
      archetype_overwrite_(std::move(rhs.archetype_overwrite_)) { }

enablement_flags::enablement_flags(
    const bool backend_enabled,
    const bool facet_enabled,
    const bool facet_overwrite,
    const bool archetype_enabled,
    const boost::optional<bool>& archetype_overwrite)
    : backend_enabled_(backend_enabled),
      facet_enabled_(facet_enabled),
      facet_overwrite_(facet_overwrite),
      archetype_enabled_(archetype_enabled),
      archetype_overwrite_(archetype_overwrite) { }

void enablement_flags::swap(enablement_flags& other) noexcept {
    using std::swap;
    swap(backend_enabled_, other.backend_enabled_);
    swap(facet_enabled_, other.facet_enabled_);
    swap(facet_overwrite_, other.facet_overwrite_);
    swap(archetype_enabled_, other.archetype_enabled_);
    swap(archetype_overwrite_, other.archetype_overwrite_);
}

bool enablement_flags::operator==(const enablement_flags& rhs) const {
    return backend_enabled_ == rhs.backend_enabled_ &&
        facet_enabled_ == rhs.facet_enabled_ &&
        facet_overwrite_ == rhs.facet_overwrite_ &&
        archetype_enabled_ == rhs.archetype_enabled_ &&
        archetype_overwrite_ == rhs.archetype_overwrite_;
}

enablement_flags& enablement_flags::operator=(enablement_flags other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool enablement_flags::backend_enabled() const {
    return backend_enabled_;
}

void enablement_flags::backend_enabled(const bool v) {
    backend_enabled_ = v;
}

bool enablement_flags::facet_enabled() const {
    return facet_enabled_;
}

void enablement_flags::facet_enabled(const bool v) {
    facet_enabled_ = v;
}

bool enablement_flags::facet_overwrite() const {
    return facet_overwrite_;
}

void enablement_flags::facet_overwrite(const bool v) {
    facet_overwrite_ = v;
}

bool enablement_flags::archetype_enabled() const {
    return archetype_enabled_;
}

void enablement_flags::archetype_enabled(const bool v) {
    archetype_enabled_ = v;
}

const boost::optional<bool>& enablement_flags::archetype_overwrite() const {
    return archetype_overwrite_;
}

boost::optional<bool>& enablement_flags::archetype_overwrite() {
    return archetype_overwrite_;
}

void enablement_flags::archetype_overwrite(const boost::optional<bool>& v) {
    archetype_overwrite_ = v;
}

void enablement_flags::archetype_overwrite(const boost::optional<bool>&& v) {
    archetype_overwrite_ = std::move(v);
}

}
