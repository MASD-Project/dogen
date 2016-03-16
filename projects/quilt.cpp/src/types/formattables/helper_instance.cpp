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
#include "dogen/quilt.cpp/types/formattables/helper_instance.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

helper_instance::helper_instance(
    const std::string& family,
    const dogen::quilt::cpp::formattables::helper_instance_properties& properties,
    const std::list<dogen::quilt::cpp::formattables::helper_instance_properties>& associated_helpers,
    const dogen::quilt::cpp::settings::helper_settings& settings)
    : family_(family),
      properties_(properties),
      associated_helpers_(associated_helpers),
      settings_(settings) { }

void helper_instance::swap(helper_instance& other) noexcept {
    using std::swap;
    swap(family_, other.family_);
    swap(properties_, other.properties_);
    swap(associated_helpers_, other.associated_helpers_);
    swap(settings_, other.settings_);
}

bool helper_instance::operator==(const helper_instance& rhs) const {
    return family_ == rhs.family_ &&
        properties_ == rhs.properties_ &&
        associated_helpers_ == rhs.associated_helpers_ &&
        settings_ == rhs.settings_;
}

helper_instance& helper_instance::operator=(helper_instance other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& helper_instance::family() const {
    return family_;
}

std::string& helper_instance::family() {
    return family_;
}

void helper_instance::family(const std::string& v) {
    family_ = v;
}

void helper_instance::family(const std::string&& v) {
    family_ = std::move(v);
}

const dogen::quilt::cpp::formattables::helper_instance_properties& helper_instance::properties() const {
    return properties_;
}

dogen::quilt::cpp::formattables::helper_instance_properties& helper_instance::properties() {
    return properties_;
}

void helper_instance::properties(const dogen::quilt::cpp::formattables::helper_instance_properties& v) {
    properties_ = v;
}

void helper_instance::properties(const dogen::quilt::cpp::formattables::helper_instance_properties&& v) {
    properties_ = std::move(v);
}

const std::list<dogen::quilt::cpp::formattables::helper_instance_properties>& helper_instance::associated_helpers() const {
    return associated_helpers_;
}

std::list<dogen::quilt::cpp::formattables::helper_instance_properties>& helper_instance::associated_helpers() {
    return associated_helpers_;
}

void helper_instance::associated_helpers(const std::list<dogen::quilt::cpp::formattables::helper_instance_properties>& v) {
    associated_helpers_ = v;
}

void helper_instance::associated_helpers(const std::list<dogen::quilt::cpp::formattables::helper_instance_properties>&& v) {
    associated_helpers_ = std::move(v);
}

const dogen::quilt::cpp::settings::helper_settings& helper_instance::settings() const {
    return settings_;
}

dogen::quilt::cpp::settings::helper_settings& helper_instance::settings() {
    return settings_;
}

void helper_instance::settings(const dogen::quilt::cpp::settings::helper_settings& v) {
    settings_ = v;
}

void helper_instance::settings(const dogen::quilt::cpp::settings::helper_settings&& v) {
    settings_ = std::move(v);
}

} } } }
