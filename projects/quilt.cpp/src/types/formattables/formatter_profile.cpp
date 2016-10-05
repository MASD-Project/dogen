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
#include "dogen/quilt.cpp/types/formattables/formatter_profile.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

formatter_profile::formatter_profile()
    : enabled_(static_cast<bool>(0)),
      overwrite_(static_cast<bool>(0)) { }

formatter_profile::formatter_profile(
    const bool enabled,
    const bool overwrite)
    : enabled_(enabled),
      overwrite_(overwrite) { }

void formatter_profile::swap(formatter_profile& other) noexcept {
    using std::swap;
    swap(enabled_, other.enabled_);
    swap(overwrite_, other.overwrite_);
}

bool formatter_profile::operator==(const formatter_profile& rhs) const {
    return enabled_ == rhs.enabled_ &&
        overwrite_ == rhs.overwrite_;
}

formatter_profile& formatter_profile::operator=(formatter_profile other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool formatter_profile::enabled() const {
    return enabled_;
}

void formatter_profile::enabled(const bool v) {
    enabled_ = v;
}

bool formatter_profile::overwrite() const {
    return overwrite_;
}

void formatter_profile::overwrite(const bool v) {
    overwrite_ = v;
}

} } } }
