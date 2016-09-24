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
#include "dogen/quilt.cpp/types/formattables/local_enablement_configuration.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

local_enablement_configuration::local_enablement_configuration()
    : supported_(static_cast<bool>(0)) { }

local_enablement_configuration::local_enablement_configuration(local_enablement_configuration&& rhs)
    : enabled_(std::move(rhs.enabled_)),
      supported_(std::move(rhs.supported_)) { }

local_enablement_configuration::local_enablement_configuration(
    const boost::optional<bool>& enabled,
    const bool supported)
    : enabled_(enabled),
      supported_(supported) { }

void local_enablement_configuration::swap(local_enablement_configuration& other) noexcept {
    using std::swap;
    swap(enabled_, other.enabled_);
    swap(supported_, other.supported_);
}

bool local_enablement_configuration::operator==(const local_enablement_configuration& rhs) const {
    return enabled_ == rhs.enabled_ &&
        supported_ == rhs.supported_;
}

local_enablement_configuration& local_enablement_configuration::operator=(local_enablement_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::optional<bool>& local_enablement_configuration::enabled() const {
    return enabled_;
}

boost::optional<bool>& local_enablement_configuration::enabled() {
    return enabled_;
}

void local_enablement_configuration::enabled(const boost::optional<bool>& v) {
    enabled_ = v;
}

void local_enablement_configuration::enabled(const boost::optional<bool>&& v) {
    enabled_ = std::move(v);
}

bool local_enablement_configuration::supported() const {
    return supported_;
}

void local_enablement_configuration::supported(const bool v) {
    supported_ = v;
}

} } } }
