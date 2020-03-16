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
#include "dogen.generation/types/entities/intra_backend_segment_properties.hpp"

namespace dogen::generation::entities {

intra_backend_segment_properties::intra_backend_segment_properties()
    : external_modules_(static_cast<dogen::generation::entities::path_contribution_types>(0)),
      model_modules_(static_cast<dogen::generation::entities::path_contribution_types>(0)),
      internal_modules_(static_cast<dogen::generation::entities::path_contribution_types>(0)),
      facet_(static_cast<dogen::generation::entities::path_contribution_types>(0)) { }

intra_backend_segment_properties::intra_backend_segment_properties(intra_backend_segment_properties&& rhs)
    : override_parent_path_(std::move(rhs.override_parent_path_)),
      path_segment_(std::move(rhs.path_segment_)),
      external_modules_(std::move(rhs.external_modules_)),
      model_modules_(std::move(rhs.model_modules_)),
      internal_modules_(std::move(rhs.internal_modules_)),
      facet_(std::move(rhs.facet_)) { }

intra_backend_segment_properties::intra_backend_segment_properties(
    const boost::filesystem::path& override_parent_path,
    const boost::filesystem::path& path_segment,
    const dogen::generation::entities::path_contribution_types external_modules,
    const dogen::generation::entities::path_contribution_types model_modules,
    const dogen::generation::entities::path_contribution_types internal_modules,
    const dogen::generation::entities::path_contribution_types facet)
    : override_parent_path_(override_parent_path),
      path_segment_(path_segment),
      external_modules_(external_modules),
      model_modules_(model_modules),
      internal_modules_(internal_modules),
      facet_(facet) { }

void intra_backend_segment_properties::swap(intra_backend_segment_properties& other) noexcept {
    using std::swap;
    swap(override_parent_path_, other.override_parent_path_);
    swap(path_segment_, other.path_segment_);
    swap(external_modules_, other.external_modules_);
    swap(model_modules_, other.model_modules_);
    swap(internal_modules_, other.internal_modules_);
    swap(facet_, other.facet_);
}

bool intra_backend_segment_properties::operator==(const intra_backend_segment_properties& rhs) const {
    return override_parent_path_ == rhs.override_parent_path_ &&
        path_segment_ == rhs.path_segment_ &&
        external_modules_ == rhs.external_modules_ &&
        model_modules_ == rhs.model_modules_ &&
        internal_modules_ == rhs.internal_modules_ &&
        facet_ == rhs.facet_;
}

intra_backend_segment_properties& intra_backend_segment_properties::operator=(intra_backend_segment_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::filesystem::path& intra_backend_segment_properties::override_parent_path() const {
    return override_parent_path_;
}

boost::filesystem::path& intra_backend_segment_properties::override_parent_path() {
    return override_parent_path_;
}

void intra_backend_segment_properties::override_parent_path(const boost::filesystem::path& v) {
    override_parent_path_ = v;
}

void intra_backend_segment_properties::override_parent_path(const boost::filesystem::path&& v) {
    override_parent_path_ = std::move(v);
}

const boost::filesystem::path& intra_backend_segment_properties::path_segment() const {
    return path_segment_;
}

boost::filesystem::path& intra_backend_segment_properties::path_segment() {
    return path_segment_;
}

void intra_backend_segment_properties::path_segment(const boost::filesystem::path& v) {
    path_segment_ = v;
}

void intra_backend_segment_properties::path_segment(const boost::filesystem::path&& v) {
    path_segment_ = std::move(v);
}

dogen::generation::entities::path_contribution_types intra_backend_segment_properties::external_modules() const {
    return external_modules_;
}

void intra_backend_segment_properties::external_modules(const dogen::generation::entities::path_contribution_types v) {
    external_modules_ = v;
}

dogen::generation::entities::path_contribution_types intra_backend_segment_properties::model_modules() const {
    return model_modules_;
}

void intra_backend_segment_properties::model_modules(const dogen::generation::entities::path_contribution_types v) {
    model_modules_ = v;
}

dogen::generation::entities::path_contribution_types intra_backend_segment_properties::internal_modules() const {
    return internal_modules_;
}

void intra_backend_segment_properties::internal_modules(const dogen::generation::entities::path_contribution_types v) {
    internal_modules_ = v;
}

dogen::generation::entities::path_contribution_types intra_backend_segment_properties::facet() const {
    return facet_;
}

void intra_backend_segment_properties::facet(const dogen::generation::entities::path_contribution_types v) {
    facet_ = v;
}

}
