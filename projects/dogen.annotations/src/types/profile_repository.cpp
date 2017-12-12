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
#include "dogen/annotations/types/profile_repository.hpp"

namespace dogen {
namespace annotations {

profile_repository::profile_repository(const std::unordered_map<std::string, dogen::annotations::profile>& profiles_by_name)
    : profiles_by_name_(profiles_by_name) { }

void profile_repository::swap(profile_repository& other) noexcept {
    using std::swap;
    swap(profiles_by_name_, other.profiles_by_name_);
}

bool profile_repository::operator==(const profile_repository& rhs) const {
    return profiles_by_name_ == rhs.profiles_by_name_;
}

profile_repository& profile_repository::operator=(profile_repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, dogen::annotations::profile>& profile_repository::profiles_by_name() const {
    return profiles_by_name_;
}

std::unordered_map<std::string, dogen::annotations::profile>& profile_repository::profiles_by_name() {
    return profiles_by_name_;
}

void profile_repository::profiles_by_name(const std::unordered_map<std::string, dogen::annotations::profile>& v) {
    profiles_by_name_ = v;
}

void profile_repository::profiles_by_name(const std::unordered_map<std::string, dogen::annotations::profile>&& v) {
    profiles_by_name_ = std::move(v);
}

} }
