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
#include "masd.dogen.variability/types/transforms/configuration_processing.hpp"

namespace masd::dogen::variability::transforms {

configuration_processing::configuration_processing()
    : merged_(static_cast<bool>(0)) { }

configuration_processing::configuration_processing(
    const masd::dogen::variability::meta_model::configuration_template& configuration_template,
    const masd::dogen::variability::meta_model::configuration& configuration,
    const bool merged)
    : configuration_template_(configuration_template),
      configuration_(configuration),
      merged_(merged) { }

void configuration_processing::swap(configuration_processing& other) noexcept {
    using std::swap;
    swap(configuration_template_, other.configuration_template_);
    swap(configuration_, other.configuration_);
    swap(merged_, other.merged_);
}

bool configuration_processing::operator==(const configuration_processing& rhs) const {
    return configuration_template_ == rhs.configuration_template_ &&
        configuration_ == rhs.configuration_ &&
        merged_ == rhs.merged_;
}

configuration_processing& configuration_processing::operator=(configuration_processing other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const masd::dogen::variability::meta_model::configuration_template& configuration_processing::configuration_template() const {
    return configuration_template_;
}

masd::dogen::variability::meta_model::configuration_template& configuration_processing::configuration_template() {
    return configuration_template_;
}

void configuration_processing::configuration_template(const masd::dogen::variability::meta_model::configuration_template& v) {
    configuration_template_ = v;
}

void configuration_processing::configuration_template(const masd::dogen::variability::meta_model::configuration_template&& v) {
    configuration_template_ = std::move(v);
}

const masd::dogen::variability::meta_model::configuration& configuration_processing::configuration() const {
    return configuration_;
}

masd::dogen::variability::meta_model::configuration& configuration_processing::configuration() {
    return configuration_;
}

void configuration_processing::configuration(const masd::dogen::variability::meta_model::configuration& v) {
    configuration_ = v;
}

void configuration_processing::configuration(const masd::dogen::variability::meta_model::configuration&& v) {
    configuration_ = std::move(v);
}

bool configuration_processing::merged() const {
    return merged_;
}

void configuration_processing::merged(const bool v) {
    merged_ = v;
}

}
