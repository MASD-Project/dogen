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
#include "masd.dogen.variability/types/profiler_configuration.hpp"

namespace masd::dogen::variability {

profiler_configuration::profiler_configuration()
    : merged_(static_cast<bool>(0)) { }

profiler_configuration::profiler_configuration(
    const masd::dogen::variability::profile& profile,
    const masd::dogen::variability::annotation& annotation,
    const bool merged)
    : profile_(profile),
      annotation_(annotation),
      merged_(merged) { }

void profiler_configuration::swap(profiler_configuration& other) noexcept {
    using std::swap;
    swap(profile_, other.profile_);
    swap(annotation_, other.annotation_);
    swap(merged_, other.merged_);
}

bool profiler_configuration::operator==(const profiler_configuration& rhs) const {
    return profile_ == rhs.profile_ &&
        annotation_ == rhs.annotation_ &&
        merged_ == rhs.merged_;
}

profiler_configuration& profiler_configuration::operator=(profiler_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const masd::dogen::variability::profile& profiler_configuration::profile() const {
    return profile_;
}

masd::dogen::variability::profile& profiler_configuration::profile() {
    return profile_;
}

void profiler_configuration::profile(const masd::dogen::variability::profile& v) {
    profile_ = v;
}

void profiler_configuration::profile(const masd::dogen::variability::profile&& v) {
    profile_ = std::move(v);
}

const masd::dogen::variability::annotation& profiler_configuration::annotation() const {
    return annotation_;
}

masd::dogen::variability::annotation& profiler_configuration::annotation() {
    return annotation_;
}

void profiler_configuration::annotation(const masd::dogen::variability::annotation& v) {
    annotation_ = v;
}

void profiler_configuration::annotation(const masd::dogen::variability::annotation&& v) {
    annotation_ = std::move(v);
}

bool profiler_configuration::merged() const {
    return merged_;
}

void profiler_configuration::merged(const bool v) {
    merged_ = v;
}

}
