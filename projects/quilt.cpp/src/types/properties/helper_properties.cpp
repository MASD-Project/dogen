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
#include "dogen/quilt.cpp/types/properties/helper_properties.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

helper_properties::helper_properties(
    const dogen::quilt::cpp::properties::helper_descriptor& descriptors,
    const std::list<dogen::quilt::cpp::properties::helper_descriptor>& associated_helpers,
    const dogen::quilt::cpp::settings::helper_settings& settings)
    : descriptors_(descriptors),
      associated_helpers_(associated_helpers),
      settings_(settings) { }

void helper_properties::swap(helper_properties& other) noexcept {
    using std::swap;
    swap(descriptors_, other.descriptors_);
    swap(associated_helpers_, other.associated_helpers_);
    swap(settings_, other.settings_);
}

bool helper_properties::operator==(const helper_properties& rhs) const {
    return descriptors_ == rhs.descriptors_ &&
        associated_helpers_ == rhs.associated_helpers_ &&
        settings_ == rhs.settings_;
}

helper_properties& helper_properties::operator=(helper_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::quilt::cpp::properties::helper_descriptor& helper_properties::descriptors() const {
    return descriptors_;
}

dogen::quilt::cpp::properties::helper_descriptor& helper_properties::descriptors() {
    return descriptors_;
}

void helper_properties::descriptors(const dogen::quilt::cpp::properties::helper_descriptor& v) {
    descriptors_ = v;
}

void helper_properties::descriptors(const dogen::quilt::cpp::properties::helper_descriptor&& v) {
    descriptors_ = std::move(v);
}

const std::list<dogen::quilt::cpp::properties::helper_descriptor>& helper_properties::associated_helpers() const {
    return associated_helpers_;
}

std::list<dogen::quilt::cpp::properties::helper_descriptor>& helper_properties::associated_helpers() {
    return associated_helpers_;
}

void helper_properties::associated_helpers(const std::list<dogen::quilt::cpp::properties::helper_descriptor>& v) {
    associated_helpers_ = v;
}

void helper_properties::associated_helpers(const std::list<dogen::quilt::cpp::properties::helper_descriptor>&& v) {
    associated_helpers_ = std::move(v);
}

const dogen::quilt::cpp::settings::helper_settings& helper_properties::settings() const {
    return settings_;
}

dogen::quilt::cpp::settings::helper_settings& helper_properties::settings() {
    return settings_;
}

void helper_properties::settings(const dogen::quilt::cpp::settings::helper_settings& v) {
    settings_ = v;
}

void helper_properties::settings(const dogen::quilt::cpp::settings::helper_settings&& v) {
    settings_ = std::move(v);
}

} } } }
