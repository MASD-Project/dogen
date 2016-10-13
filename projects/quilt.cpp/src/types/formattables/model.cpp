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
#include "dogen/quilt.cpp/types/formattables/model.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

model::model(
    const std::unordered_map<std::string, dogen::quilt::cpp::formattables::streaming_properties>& streaming_properties,
    const std::unordered_map<std::string, dogen::quilt::cpp::formattables::formattable>& formattables,
    const std::unordered_map<std::string, dogen::quilt::cpp::formattables::facet_properties>& facet_properties)
    : streaming_properties_(streaming_properties),
      formattables_(formattables),
      facet_properties_(facet_properties) { }

void model::swap(model& other) noexcept {
    using std::swap;
    swap(streaming_properties_, other.streaming_properties_);
    swap(formattables_, other.formattables_);
    swap(facet_properties_, other.facet_properties_);
}

bool model::operator==(const model& rhs) const {
    return streaming_properties_ == rhs.streaming_properties_ &&
        formattables_ == rhs.formattables_ &&
        facet_properties_ == rhs.facet_properties_;
}

model& model::operator=(model other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, dogen::quilt::cpp::formattables::streaming_properties>& model::streaming_properties() const {
    return streaming_properties_;
}

std::unordered_map<std::string, dogen::quilt::cpp::formattables::streaming_properties>& model::streaming_properties() {
    return streaming_properties_;
}

void model::streaming_properties(const std::unordered_map<std::string, dogen::quilt::cpp::formattables::streaming_properties>& v) {
    streaming_properties_ = v;
}

void model::streaming_properties(const std::unordered_map<std::string, dogen::quilt::cpp::formattables::streaming_properties>&& v) {
    streaming_properties_ = std::move(v);
}

const std::unordered_map<std::string, dogen::quilt::cpp::formattables::formattable>& model::formattables() const {
    return formattables_;
}

std::unordered_map<std::string, dogen::quilt::cpp::formattables::formattable>& model::formattables() {
    return formattables_;
}

void model::formattables(const std::unordered_map<std::string, dogen::quilt::cpp::formattables::formattable>& v) {
    formattables_ = v;
}

void model::formattables(const std::unordered_map<std::string, dogen::quilt::cpp::formattables::formattable>&& v) {
    formattables_ = std::move(v);
}

const std::unordered_map<std::string, dogen::quilt::cpp::formattables::facet_properties>& model::facet_properties() const {
    return facet_properties_;
}

std::unordered_map<std::string, dogen::quilt::cpp::formattables::facet_properties>& model::facet_properties() {
    return facet_properties_;
}

void model::facet_properties(const std::unordered_map<std::string, dogen::quilt::cpp::formattables::facet_properties>& v) {
    facet_properties_ = v;
}

void model::facet_properties(const std::unordered_map<std::string, dogen::quilt::cpp::formattables::facet_properties>&& v) {
    facet_properties_ = std::move(v);
}

} } } }
