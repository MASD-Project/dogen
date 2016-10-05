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
#include "dogen/quilt.cpp/types/formattables/facet_profile.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

facet_profile::facet_profile()
    : enabled_(static_cast<bool>(0)),
      overwrite_(static_cast<bool>(0)) { }

facet_profile::facet_profile(
    const bool enabled,
    const bool overwrite)
    : enabled_(enabled),
      overwrite_(overwrite) { }

void facet_profile::swap(facet_profile& other) noexcept {
    using std::swap;
    swap(enabled_, other.enabled_);
    swap(overwrite_, other.overwrite_);
}

bool facet_profile::operator==(const facet_profile& rhs) const {
    return enabled_ == rhs.enabled_ &&
        overwrite_ == rhs.overwrite_;
}

facet_profile& facet_profile::operator=(facet_profile other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool facet_profile::enabled() const {
    return enabled_;
}

void facet_profile::enabled(const bool v) {
    enabled_ = v;
}

bool facet_profile::overwrite() const {
    return overwrite_;
}

void facet_profile::overwrite(const bool v) {
    overwrite_ = v;
}

} } } }
