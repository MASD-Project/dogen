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
#include "dogen/yarn.dia/types/profiled_object.hpp"

namespace dogen {
namespace yarn {
namespace dia {

profiled_object::profiled_object(
    const dogen::yarn::dia::processed_object& object,
    const dogen::yarn::dia::profile& profile)
    : object_(object),
      profile_(profile) { }

void profiled_object::swap(profiled_object& other) noexcept {
    using std::swap;
    swap(object_, other.object_);
    swap(profile_, other.profile_);
}

bool profiled_object::operator==(const profiled_object& rhs) const {
    return object_ == rhs.object_ &&
        profile_ == rhs.profile_;
}

profiled_object& profiled_object::operator=(profiled_object other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::yarn::dia::processed_object& profiled_object::object() const {
    return object_;
}

dogen::yarn::dia::processed_object& profiled_object::object() {
    return object_;
}

void profiled_object::object(const dogen::yarn::dia::processed_object& v) {
    object_ = v;
}

void profiled_object::object(const dogen::yarn::dia::processed_object&& v) {
    object_ = std::move(v);
}

const dogen::yarn::dia::profile& profiled_object::profile() const {
    return profile_;
}

dogen::yarn::dia::profile& profiled_object::profile() {
    return profile_;
}

void profiled_object::profile(const dogen::yarn::dia::profile& v) {
    profile_ = v;
}

void profiled_object::profile(const dogen::yarn::dia::profile&& v) {
    profile_ = std::move(v);
}

} } }
