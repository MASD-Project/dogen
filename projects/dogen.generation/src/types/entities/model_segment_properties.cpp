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
#include "dogen.generation/types/entities/model_segment_properties.hpp"

namespace dogen::generation::entities {

model_segment_properties::model_segment_properties()
    : external_modules_(static_cast<dogen::generation::entities::path_contribution_types>(0)),
      model_modules_(static_cast<dogen::generation::entities::path_contribution_types>(0)) { }

model_segment_properties::model_segment_properties(
    const std::string& directory,
    const dogen::generation::entities::path_contribution_types external_modules,
    const dogen::generation::entities::path_contribution_types model_modules)
    : directory_(directory),
      external_modules_(external_modules),
      model_modules_(model_modules) { }

void model_segment_properties::swap(model_segment_properties& other) noexcept {
    using std::swap;
    swap(directory_, other.directory_);
    swap(external_modules_, other.external_modules_);
    swap(model_modules_, other.model_modules_);
}

bool model_segment_properties::operator==(const model_segment_properties& rhs) const {
    return directory_ == rhs.directory_ &&
        external_modules_ == rhs.external_modules_ &&
        model_modules_ == rhs.model_modules_;
}

model_segment_properties& model_segment_properties::operator=(model_segment_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& model_segment_properties::directory() const {
    return directory_;
}

std::string& model_segment_properties::directory() {
    return directory_;
}

void model_segment_properties::directory(const std::string& v) {
    directory_ = v;
}

void model_segment_properties::directory(const std::string&& v) {
    directory_ = std::move(v);
}

dogen::generation::entities::path_contribution_types model_segment_properties::external_modules() const {
    return external_modules_;
}

void model_segment_properties::external_modules(const dogen::generation::entities::path_contribution_types v) {
    external_modules_ = v;
}

dogen::generation::entities::path_contribution_types model_segment_properties::model_modules() const {
    return model_modules_;
}

void model_segment_properties::model_modules(const dogen::generation::entities::path_contribution_types v) {
    model_modules_ = v;
}

}
