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
#include "dogen/yarn/types/transforms/global_enablement_configuration.hpp"

namespace dogen {
namespace yarn {
namespace transforms {

global_enablement_configuration::global_enablement_configuration()
    : kernel_enabled_(static_cast<bool>(0)),
      facet_enabled_(static_cast<bool>(0)),
      archetype_enabled_(static_cast<bool>(0)),
      facet_overwrite_(static_cast<bool>(0)) { }

global_enablement_configuration::global_enablement_configuration(global_enablement_configuration&& rhs)
    : kernel_enabled_(std::move(rhs.kernel_enabled_)),
      facet_enabled_(std::move(rhs.facet_enabled_)),
      archetype_enabled_(std::move(rhs.archetype_enabled_)),
      facet_overwrite_(std::move(rhs.facet_overwrite_)),
      archetype_overwrite_(std::move(rhs.archetype_overwrite_)) { }

global_enablement_configuration::global_enablement_configuration(
    const bool kernel_enabled,
    const bool facet_enabled,
    const bool archetype_enabled,
    const bool facet_overwrite,
    const boost::optional<bool>& archetype_overwrite)
    : kernel_enabled_(kernel_enabled),
      facet_enabled_(facet_enabled),
      archetype_enabled_(archetype_enabled),
      facet_overwrite_(facet_overwrite),
      archetype_overwrite_(archetype_overwrite) { }

void global_enablement_configuration::swap(global_enablement_configuration& other) noexcept {
    using std::swap;
    swap(kernel_enabled_, other.kernel_enabled_);
    swap(facet_enabled_, other.facet_enabled_);
    swap(archetype_enabled_, other.archetype_enabled_);
    swap(facet_overwrite_, other.facet_overwrite_);
    swap(archetype_overwrite_, other.archetype_overwrite_);
}

bool global_enablement_configuration::operator==(const global_enablement_configuration& rhs) const {
    return kernel_enabled_ == rhs.kernel_enabled_ &&
        facet_enabled_ == rhs.facet_enabled_ &&
        archetype_enabled_ == rhs.archetype_enabled_ &&
        facet_overwrite_ == rhs.facet_overwrite_ &&
        archetype_overwrite_ == rhs.archetype_overwrite_;
}

global_enablement_configuration& global_enablement_configuration::operator=(global_enablement_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool global_enablement_configuration::kernel_enabled() const {
    return kernel_enabled_;
}

void global_enablement_configuration::kernel_enabled(const bool v) {
    kernel_enabled_ = v;
}

bool global_enablement_configuration::facet_enabled() const {
    return facet_enabled_;
}

void global_enablement_configuration::facet_enabled(const bool v) {
    facet_enabled_ = v;
}

bool global_enablement_configuration::archetype_enabled() const {
    return archetype_enabled_;
}

void global_enablement_configuration::archetype_enabled(const bool v) {
    archetype_enabled_ = v;
}

bool global_enablement_configuration::facet_overwrite() const {
    return facet_overwrite_;
}

void global_enablement_configuration::facet_overwrite(const bool v) {
    facet_overwrite_ = v;
}

const boost::optional<bool>& global_enablement_configuration::archetype_overwrite() const {
    return archetype_overwrite_;
}

boost::optional<bool>& global_enablement_configuration::archetype_overwrite() {
    return archetype_overwrite_;
}

void global_enablement_configuration::archetype_overwrite(const boost::optional<bool>& v) {
    archetype_overwrite_ = v;
}

void global_enablement_configuration::archetype_overwrite(const boost::optional<bool>&& v) {
    archetype_overwrite_ = std::move(v);
}

} } }
