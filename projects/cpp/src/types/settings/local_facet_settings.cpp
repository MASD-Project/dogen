/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/cpp/types/settings/local_facet_settings.hpp"

namespace dogen {
namespace cpp {
namespace settings {

local_facet_settings::local_facet_settings()
    : enabled_(static_cast<bool>(0)),
      supported_(static_cast<bool>(0)) { }

local_facet_settings::local_facet_settings(
    const bool enabled,
    const bool supported)
    : enabled_(enabled),
      supported_(supported) { }

void local_facet_settings::swap(local_facet_settings& other) noexcept {
    using std::swap;
    swap(enabled_, other.enabled_);
    swap(supported_, other.supported_);
}

bool local_facet_settings::operator==(const local_facet_settings& rhs) const {
    return enabled_ == rhs.enabled_ &&
        supported_ == rhs.supported_;
}

local_facet_settings& local_facet_settings::operator=(local_facet_settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool local_facet_settings::enabled() const {
    return enabled_;
}

void local_facet_settings::enabled(const bool v) {
    enabled_ = v;
}

bool local_facet_settings::supported() const {
    return supported_;
}

void local_facet_settings::supported(const bool v) {
    supported_ = v;
}

} } }