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
#include "dogen.variability/types/transforms/profile_repository_inputs.hpp"

namespace dogen::variability::transforms {

profile_repository_inputs::profile_repository_inputs(
    const std::list<dogen::variability::meta_model::profile>& profiles,
    const std::list<dogen::variability::meta_model::profile_template>& templates)
    : profiles_(profiles),
      templates_(templates) { }

void profile_repository_inputs::swap(profile_repository_inputs& other) noexcept {
    using std::swap;
    swap(profiles_, other.profiles_);
    swap(templates_, other.templates_);
}

bool profile_repository_inputs::operator==(const profile_repository_inputs& rhs) const {
    return profiles_ == rhs.profiles_ &&
        templates_ == rhs.templates_;
}

profile_repository_inputs& profile_repository_inputs::operator=(profile_repository_inputs other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::variability::meta_model::profile>& profile_repository_inputs::profiles() const {
    return profiles_;
}

std::list<dogen::variability::meta_model::profile>& profile_repository_inputs::profiles() {
    return profiles_;
}

void profile_repository_inputs::profiles(const std::list<dogen::variability::meta_model::profile>& v) {
    profiles_ = v;
}

void profile_repository_inputs::profiles(const std::list<dogen::variability::meta_model::profile>&& v) {
    profiles_ = std::move(v);
}

const std::list<dogen::variability::meta_model::profile_template>& profile_repository_inputs::templates() const {
    return templates_;
}

std::list<dogen::variability::meta_model::profile_template>& profile_repository_inputs::templates() {
    return templates_;
}

void profile_repository_inputs::templates(const std::list<dogen::variability::meta_model::profile_template>& v) {
    templates_ = v;
}

void profile_repository_inputs::templates(const std::list<dogen::variability::meta_model::profile_template>&& v) {
    templates_ = std::move(v);
}

}
