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
#include "dogen.physical/types/entities/path_configuration.hpp"

namespace dogen::physical::entities {

path_configuration::path_configuration()
    : external_modules_(static_cast<dogen::physical::entities::path_contribution_type>(0)),
      model_modules_(static_cast<dogen::physical::entities::path_contribution_type>(0)),
      facet_(static_cast<dogen::physical::entities::path_contribution_type>(0)),
      internal_modules_(static_cast<dogen::physical::entities::path_contribution_type>(0)) { }

path_configuration::path_configuration(
    const dogen::physical::entities::path_contribution_type external_modules,
    const dogen::physical::entities::path_contribution_type model_modules,
    const dogen::physical::entities::path_contribution_type facet,
    const dogen::physical::entities::path_contribution_type internal_modules)
    : external_modules_(external_modules),
      model_modules_(model_modules),
      facet_(facet),
      internal_modules_(internal_modules) { }

void path_configuration::swap(path_configuration& other) noexcept {
    using std::swap;
    swap(external_modules_, other.external_modules_);
    swap(model_modules_, other.model_modules_);
    swap(facet_, other.facet_);
    swap(internal_modules_, other.internal_modules_);
}

bool path_configuration::operator==(const path_configuration& rhs) const {
    return external_modules_ == rhs.external_modules_ &&
        model_modules_ == rhs.model_modules_ &&
        facet_ == rhs.facet_ &&
        internal_modules_ == rhs.internal_modules_;
}

path_configuration& path_configuration::operator=(path_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

dogen::physical::entities::path_contribution_type path_configuration::external_modules() const {
    return external_modules_;
}

void path_configuration::external_modules(const dogen::physical::entities::path_contribution_type v) {
    external_modules_ = v;
}

dogen::physical::entities::path_contribution_type path_configuration::model_modules() const {
    return model_modules_;
}

void path_configuration::model_modules(const dogen::physical::entities::path_contribution_type v) {
    model_modules_ = v;
}

dogen::physical::entities::path_contribution_type path_configuration::facet() const {
    return facet_;
}

void path_configuration::facet(const dogen::physical::entities::path_contribution_type v) {
    facet_ = v;
}

dogen::physical::entities::path_contribution_type path_configuration::internal_modules() const {
    return internal_modules_;
}

void path_configuration::internal_modules(const dogen::physical::entities::path_contribution_type v) {
    internal_modules_ = v;
}

}
