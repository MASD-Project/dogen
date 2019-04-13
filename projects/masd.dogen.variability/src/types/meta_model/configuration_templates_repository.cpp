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
#include "masd.dogen.variability/types/meta_model/configuration_templates_repository.hpp"

namespace masd::dogen::variability::meta_model {

configuration_templates_repository::configuration_templates_repository(const std::unordered_map<std::string, masd::dogen::variability::meta_model::configuration_template>& by_name)
    : by_name_(by_name) { }

void configuration_templates_repository::swap(configuration_templates_repository& other) noexcept {
    using std::swap;
    swap(by_name_, other.by_name_);
}

bool configuration_templates_repository::operator==(const configuration_templates_repository& rhs) const {
    return by_name_ == rhs.by_name_;
}

configuration_templates_repository& configuration_templates_repository::operator=(configuration_templates_repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, masd::dogen::variability::meta_model::configuration_template>& configuration_templates_repository::by_name() const {
    return by_name_;
}

std::unordered_map<std::string, masd::dogen::variability::meta_model::configuration_template>& configuration_templates_repository::by_name() {
    return by_name_;
}

void configuration_templates_repository::by_name(const std::unordered_map<std::string, masd::dogen::variability::meta_model::configuration_template>& v) {
    by_name_ = v;
}

void configuration_templates_repository::by_name(const std::unordered_map<std::string, masd::dogen::variability::meta_model::configuration_template>&& v) {
    by_name_ = std::move(v);
}

}
