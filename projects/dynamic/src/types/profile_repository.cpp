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
#include "dogen/dynamic/types/profile_repository.hpp"

namespace dogen {
namespace dynamic {

profile_repository::profile_repository(
    const dogen::dynamic::profile& default_profile,
    const std::unordered_map<std::string, dogen::dynamic::profile>& profiles_by_name)
    : default_profile_(default_profile),
      profiles_by_name_(profiles_by_name) { }

void profile_repository::swap(profile_repository& other) noexcept {
    using std::swap;
    swap(default_profile_, other.default_profile_);
    swap(profiles_by_name_, other.profiles_by_name_);
}

bool profile_repository::operator==(const profile_repository& rhs) const {
    return default_profile_ == rhs.default_profile_ &&
        profiles_by_name_ == rhs.profiles_by_name_;
}

profile_repository& profile_repository::operator=(profile_repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::dynamic::profile& profile_repository::default_profile() const {
    return default_profile_;
}

dogen::dynamic::profile& profile_repository::default_profile() {
    return default_profile_;
}

void profile_repository::default_profile(const dogen::dynamic::profile& v) {
    default_profile_ = v;
}

void profile_repository::default_profile(const dogen::dynamic::profile&& v) {
    default_profile_ = std::move(v);
}

const std::unordered_map<std::string, dogen::dynamic::profile>& profile_repository::profiles_by_name() const {
    return profiles_by_name_;
}

std::unordered_map<std::string, dogen::dynamic::profile>& profile_repository::profiles_by_name() {
    return profiles_by_name_;
}

void profile_repository::profiles_by_name(const std::unordered_map<std::string, dogen::dynamic::profile>& v) {
    profiles_by_name_ = v;
}

void profile_repository::profiles_by_name(const std::unordered_map<std::string, dogen::dynamic::profile>&& v) {
    profiles_by_name_ = std::move(v);
}

} }
