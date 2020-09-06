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
#include "dogen.text.cpp/types/formattables/helper_configuration.hpp"

namespace dogen::text::cpp::formattables {

helper_configuration::helper_configuration(
    const std::unordered_map<dogen::identification::entities::logical_id, std::string>& helper_families,
    const std::unordered_map<dogen::identification::entities::logical_id, dogen::text::cpp::formattables::streaming_properties>& streaming_properties)
    : helper_families_(helper_families),
      streaming_properties_(streaming_properties) { }

void helper_configuration::swap(helper_configuration& other) noexcept {
    using std::swap;
    swap(helper_families_, other.helper_families_);
    swap(streaming_properties_, other.streaming_properties_);
}

bool helper_configuration::operator==(const helper_configuration& rhs) const {
    return helper_families_ == rhs.helper_families_ &&
        streaming_properties_ == rhs.streaming_properties_;
}

helper_configuration& helper_configuration::operator=(helper_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<dogen::identification::entities::logical_id, std::string>& helper_configuration::helper_families() const {
    return helper_families_;
}

std::unordered_map<dogen::identification::entities::logical_id, std::string>& helper_configuration::helper_families() {
    return helper_families_;
}

void helper_configuration::helper_families(const std::unordered_map<dogen::identification::entities::logical_id, std::string>& v) {
    helper_families_ = v;
}

void helper_configuration::helper_families(const std::unordered_map<dogen::identification::entities::logical_id, std::string>&& v) {
    helper_families_ = std::move(v);
}

const std::unordered_map<dogen::identification::entities::logical_id, dogen::text::cpp::formattables::streaming_properties>& helper_configuration::streaming_properties() const {
    return streaming_properties_;
}

std::unordered_map<dogen::identification::entities::logical_id, dogen::text::cpp::formattables::streaming_properties>& helper_configuration::streaming_properties() {
    return streaming_properties_;
}

void helper_configuration::streaming_properties(const std::unordered_map<dogen::identification::entities::logical_id, dogen::text::cpp::formattables::streaming_properties>& v) {
    streaming_properties_ = v;
}

void helper_configuration::streaming_properties(const std::unordered_map<dogen::identification::entities::logical_id, dogen::text::cpp::formattables::streaming_properties>&& v) {
    streaming_properties_ = std::move(v);
}

}
