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
#include "dogen/quilt.cpp/types/formattables/global_enablement_properties.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

global_enablement_properties::global_enablement_properties()
    : model_enabled_(static_cast<bool>(0)),
      facet_enabled_(static_cast<bool>(0)),
      formatter_enabled_(static_cast<bool>(0)) { }

global_enablement_properties::global_enablement_properties(
    const bool model_enabled,
    const bool facet_enabled,
    const bool formatter_enabled)
    : model_enabled_(model_enabled),
      facet_enabled_(facet_enabled),
      formatter_enabled_(formatter_enabled) { }

void global_enablement_properties::swap(global_enablement_properties& other) noexcept {
    using std::swap;
    swap(model_enabled_, other.model_enabled_);
    swap(facet_enabled_, other.facet_enabled_);
    swap(formatter_enabled_, other.formatter_enabled_);
}

bool global_enablement_properties::operator==(const global_enablement_properties& rhs) const {
    return model_enabled_ == rhs.model_enabled_ &&
        facet_enabled_ == rhs.facet_enabled_ &&
        formatter_enabled_ == rhs.formatter_enabled_;
}

global_enablement_properties& global_enablement_properties::operator=(global_enablement_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool global_enablement_properties::model_enabled() const {
    return model_enabled_;
}

void global_enablement_properties::model_enabled(const bool v) {
    model_enabled_ = v;
}

bool global_enablement_properties::facet_enabled() const {
    return facet_enabled_;
}

void global_enablement_properties::facet_enabled(const bool v) {
    facet_enabled_ = v;
}

bool global_enablement_properties::formatter_enabled() const {
    return formatter_enabled_;
}

void global_enablement_properties::formatter_enabled(const bool v) {
    formatter_enabled_ = v;
}

} } } }
